/* -----------------------------------------------------------------------------
 *
 *     Copyright (c)  2014  -  GEMALTO DEVELOPEMENT - R&D
 *
 * -----------------------------------------------------------------------------
 * GEMALTO MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. GEMALTO SHALL NOT BE
 * LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 *
 * THIS SOFTWARE IS NOT DESIGNED OR INTENDED FOR USE OR RESALE AS ON-LINE
 * CONTROL EQUIPMENT IN HAZARDOUS ENVIRONMENTS REQUIRING FAIL-SAFE
 * PERFORMANCE, SUCH AS IN THE OPERATION OF NUCLEAR FACILITIES, AIRCRAFT
 * NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL, DIRECT LIFE
 * SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH THE FAILURE OF THE
 * SOFTWARE COULD LEAD DIRECTLY TO DEATH, PERSONAL INJURY, OR SEVERE
 * PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH RISK ACTIVITIES"). GEMALTO
 * SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR
 * HIGH RISK ACTIVITIES.
 *
 * -----------------------------------------------------------------------------
 */

#import "FirstViewController.h"

#import "FakeAppData.h"

/**
 * User action state
 */
typedef NS_ENUM(NSInteger, EMUserActionState) {
    /**
     * Initial state
     */
    EMUserActionStateNotDefined = 0,
    /**
     * User select upgrade to multi auth mode
     */
    EMUserActionStateUpgradeToMultiAuthMode,
    /**
     * User select to get OTP with PIN
     */
    EMUserActionStateGetOtp,
};

static const int UIAlertView_TAG_PIN = 0;

@interface FirstViewController () <UIAlertViewDelegate>

@end

@implementation FirstViewController
{
    EMUserActionState _userState;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Initialize user state
    _userState = EMUserActionStateNotDefined;

    self.example = [[Example alloc] init];
    self.example.progressDelegate = self;
    
    // NOTE: For simplicity of the example, we're clearing off all the tokens at the beginning of the application running.
    [self.example resetAllTokens];
    
    // Setting empty text to allow the UIWebView to re-scale accordingly
    self.html = [NSMutableString string];
    [self reportProgressWithTitle:@"" message:@""];
}

#pragma mark - Example Delegate

-(void)reportProgressWithTitle:(NSString *)title message:(NSString *)message {
    
    [self.html appendString:[NSString stringWithFormat:@"<b><font color=\"#0000FF\" size=\"2\" face=\"arial\">%@</font></b></br>", title]];
    [self.html appendString:[NSString stringWithFormat:@"<font size=\"1\" face=\"arial\">%@</font></br></br>", message]];
    [self.webView loadHTMLString:self.html baseURL:nil];
}

- (void) provisioningCompleteWithError:(NSString*)error {
    
    if (error == nil) {
        // Provisioning was successful.
        [self updateUIControlsAfterProvisioning];
    }
}

- (void)upgradeToMultiAuthModeCompleted
{
    [self updateUIControlsAfterUpgradeToMultiAuthModeCompleted];
}


#pragma mark Private

- (void)updateUIControlsAfterProvisioning
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.btnActivateBioFP.enabled = YES;
        self.btnGetOTPWithPin.enabled = YES;
        self.btnProvisioning.enabled = NO;
        self.txfCode.enabled = NO;
    });
}

- (void)updateUIControlsAfterUpgradeToMultiAuthModeCompleted
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.btnActivateBioFP.enabled = NO;
        self.btnGetOTPWithPin.enabled = YES;
    });
}

- (void)showPinpad
{
    @try {
        EMUIModule *uiModule = [EMUIModule uiModule];
        EMSecureInputService *secureInputService = [EMSecureInputService serviceWithModule:uiModule];
        
        id<EMSecureInputBuilder> pinpadBuilder = [secureInputService secureInputBuilder];
        [pinpadBuilder setTextLabel:@"Enter your PIN"];
        
        UIViewController *pinpad = [pinpadBuilder buildWithScrambling:YES doublePin:NO onFinishBlock:^(id<EMPinAuthInput> firstPin, id<EMPinAuthInput> secondPin) {
            // First call the delegate to dismiss the pinpad view
            [self dismissViewControllerAnimated:YES completion:nil];

            if (_userState == EMUserActionStateUpgradeToMultiAuthMode) {
                // Token migration
                [self.example upgradeAndActivateAllModesWithPinAuthInput:firstPin];
            } else if (_userState == EMUserActionStateGetOtp) {
                // Get OTP using PIN
                [self.example generateOtpWithAuthInput:firstPin];
            }
            
            // Wipe the pinpadBuilder for security reason
            [pinpadBuilder wipe];
        }];
        [self presentViewController:pinpad animated:YES completion:nil];
    }
    @catch (EMException *exception) {
        if ([EMActivationException isEqualToString:[exception name]]) {
            UIAlertView *pinInput = [[UIAlertView alloc] initWithTitle:@"Cap Example" message:@"Please enter PIN:" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Ok", nil];
            pinInput.tag = UIAlertView_TAG_PIN;
            pinInput.alertViewStyle = UIAlertViewStyleSecureTextInput;
            pinInput.delegate = self;
            [pinInput show];
        } else {
            @throw exception;
        }
    }
}

#pragma mark IBAction

- (IBAction)btnProvisioningTouchedUpInside:(id)sender {
    
    id<EMSecureContainerFactory> sdf = [self.example.core secureContainerFactory];
    id<EMSecureString> regCode = [sdf secureStringFromString:self.txfCode.text];
    
    // Call the callback
    [_example provisionWithRegCode:regCode];
    
    // Wipe registration code
    [regCode wipe];

    // Hide keyboard
    [self.txfCode resignFirstResponder];
}

- (IBAction)btnGetOtpWithPinTouchedUpInside:(id)sender
{
    // Set user action state
    _userState = EMUserActionStateGetOtp;
    
    // Show pinpad
    [self showPinpad];
}

- (IBAction)btnUpgradeToMultiAuthModeTouchedUpInside:(id)sender
{
    // Set user action state
    _userState = EMUserActionStateUpgradeToMultiAuthMode;
    
    // Show pinpad
    [self showPinpad];
}

#pragma mark UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == alertView.cancelButtonIndex) {
        return;
    }
    
    if (alertView.tag == UIAlertView_TAG_PIN) {
        // Get the clear text pin (we have only 1 text field, so it should be located at text field index 0)
        NSString *pinStr = [alertView textFieldAtIndex:0].text;
        
        EMAuthModule *authModule = [EMAuthModule authModule];
        EMPinAuthService *pinAuthService = [EMPinAuthService serviceWithModule:authModule];

        id<EMPinAuthInput> pinCode = [pinAuthService createAuthInputWithString:pinStr error:nil];

        if (_userState == EMUserActionStateUpgradeToMultiAuthMode) {
            [self.example upgradeAndActivateAllModesWithPinAuthInput:pinCode];
        } else if (_userState == EMUserActionStateGetOtp) {
            [self.example generateOtpWithAuthInput:pinCode];
        }

        // Security Guideline: GEN08. PIN sanitization
        // The PIN must be wiped ASAP.
        [pinCode wipe];
    }
}

@end

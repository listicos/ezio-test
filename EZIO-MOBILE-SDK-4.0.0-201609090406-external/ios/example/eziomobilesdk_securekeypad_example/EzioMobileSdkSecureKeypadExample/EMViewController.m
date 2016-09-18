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


#import "EMViewController.h"
#import <EzioMobile/EzioMobile.h>

@interface EMViewController ()

@end

@implementation EMViewController {
    
    
    id<EMTokenBuilder> _offlineTokenBuilder;
    id<EMToken> _token;
    BOOL _tokenRetrievalComplete;
    
    
    NSString *_error;
}

// Set the Secure Pin Pad here.
BOOL isScramblingEnabled = true;
BOOL isDoublePassword = false;



- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Display on the screen
    NSString *lblScrambleStr = [self.lblScrambleMode.text stringByAppendingString:(isScramblingEnabled)?@"YES":@"NO"];
    self.lblScrambleMode.text = lblScrambleStr;
    NSString *lblDblPasswordStr =  [self.lblDblPasswordMode.text stringByAppendingString:(isDoublePassword)?@"YES":@"NO"];
    self.lblDblPasswordMode.text = lblDblPasswordStr;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark Actions

- (IBAction)btnShowKeypadTouchedUpInside:(id)sender {
    // *** WARNING *** This requires an activation code in order to
    // use the secure pin pad example.  Please contact your Gemalto
    // representative if you do not have one.
    NSData* dummyActivationCode = nil;
    
    if (dummyActivationCode == nil) {
        [self _requiresActivationCode];
        return;
    }
    
    if(![EMCore isConfigured]){
        [EMCore configureWithActivationCode:dummyActivationCode configurations:[NSSet set]];
    }

    EMUIModule *uiModule = [EMUIModule uiModule];
    EMSecureInputService *secureInputService = [EMSecureInputService serviceWithModule:uiModule];
    id<EMSecureInputBuilder> securePinpad = [secureInputService secureInputBuilder];
    if (securePinpad == nil) {
        [self _requiresActivationCode];
        return;
    }
    
    [securePinpad setScreenBackgroundColor:EMUIColorFromRGBA(0xFFFFFFFF)];
    
    [securePinpad setButtonCharacterColorNormal:EMUIColorFromRGBA(0x000000FF)];
    [securePinpad setButtonCharacterColorDisabled:EMUIColorFromRGBA(0x000000FF)];
    [securePinpad setButtonSpacing:2];
    [securePinpad setButtonGradientNormalStart:EMUIColorFromRGBA(0xDDDDDDFF)];
    [securePinpad setButtonGradientNormalEnd:EMUIColorFromRGBA(0xCCCCCCFF)];
    [securePinpad setButtonGradientDisabledStart:EMUIColorFromRGBA(0xDDDDAAFF)];
    [securePinpad setButtonGradientDisabledEnd:EMUIColorFromRGBA(0xCCCCA0FF)];
    
    [securePinpad setLabelTextColor:EMUIColorFromRGBA(0x000000FF)];
    
    [securePinpad setMinimumInputLength:4];
    [securePinpad setMaximumInputLength:8];
    
    UIViewController *controller = [securePinpad buildWithScrambling:isScramblingEnabled
                                                           doublePin:isDoublePassword onFinishBlock:^(id<EMPinAuthInput> firstPin,                                                                                                                       id<EMPinAuthInput> secondPin) {
                                                               // The pins cannot be extracted from these two EMSecureData objects.
                                                               
                                                               NSLog(@"Pin has just been entered");
                                                               // Dismiss the keypad
                                                               [self.navigationController popViewControllerAnimated:YES];
                                                               
                                                               // Generate OTP and display
                                                               [self _generateOTPAndDisplay:firstPin];
                                                               
                                                               // Wipe pinpad builder for security purpose.
                                                               [securePinpad wipe];
                                                           }];
    
    //Push in the Secure Pin Pad to the current view.
    [self.navigationController pushViewController:controller animated:YES];
}

#pragma mark Private
- (void) _generateOTPAndDisplay:(id<EMPinAuthInput>)pin {
    // Implement the function generating OTP here
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"New PIN Object Created"
                                                        message:@"Press OK to resume."
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
    }
}

-(void) _requiresActivationCode {
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Requires activation code to use this feature"
                                                    message:@"Press OK to resume."
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [alert show];
}

@end

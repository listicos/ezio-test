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

#import "Example.h"
#import "FakeUI.h"
#import "FakeAppData.h"

@implementation Example
{
    NSString *currentOperation;
    NSString *currentTokenName;
}

#pragma mark Constructor

- (instancetype)init
{
    self = [super init];
    if (self) {
        // Initialize/ Configure EMCore
        NSData *activationCode = [FakeAppData activationAllEnabled];
        EMOtpConfiguration *otpConfig=[EMOtpConfiguration defaultConfiguration];
        NSSet *configs = [NSSet setWithObject:otpConfig];
        _core = [EMCore configureWithActivationCode:activationCode configurations:configs];
    }

    return self;
}

#pragma mark Public Methods

/**
 * This method will provision the device with a new user (if successful). It
 * provides a real world example (minus the fake UI) of how this should be
 * performed and it includes all security guidelines that must be followed.
 */
- (void)provisionWithRegCode:(id<EMSecureString>)regCode
{
    // Security Guideline: IOS11. Implement jailbreak detection inline
    //
    //Before starting the provisioning, check if the device is jailbroken.
    //The jailbreak check should NOT be done in a separate Objective-c method since such a
    //method could easily be hooked.
    currentOperation = @"Jailbreak detection";
    if (EMJailbreakDetectorGetJailbreakStatus() == EMJailbreakStatusJailbroken) {
        //Abort
        [self publishProgress:@"The device is jailbroken. For your security reason the application is not allowed to run."];
        return;
    } else {
        [self publishProgress:@"The device is not jailbroken"];
    }

    currentOperation = @"Provision";
    // Security Guideline: GEN20. Atomicity of personalization
    // EMSecureData wipes it's internal data automatically when deallocated.
    
    // FAKE UI: The application needs to ask the user for this
    // information before creating the token. You can freely alter the
    // FakeUi class to alter the registration code, etc.
    currentTokenName = [FakeUI promptForAccountName];
    
    // CONFIGURE THE TOKENBUILDER: See each setup step for further details.
    EMProvisioningConfiguration *epsConf = [self setupEpsConfigurationWithRegCode:regCode];
    EMDeviceFingerprintTokenPolicy *deviceFingerprintTokenPolicy = [self setupDeviceFingerprintTokenPolicy];
    
    // CREATE THE TOKEN: This will establish a data connection with the
    // URL provided to the EpsConfiguration (see setupEpsConfiguration)
    // in order to retrieve the token credentials.
    // By passing TokenCapability in create function, it will create a VicToken into database.
    [self publishProgress:[NSString stringWithFormat:@"Creating Token: %@ \nURL=%@", currentTokenName, [FakeAppData epsUrl]]];

    EMOtpModule *otpModule = [EMOtpModule otpModule];
    EMCapService *capService = [EMCapService serviceWithModule:otpModule];
    id<EMCapTokenManager> tokenManager = [capService tokenManager:nil];
    [tokenManager createTokenWithName:currentTokenName provisioningConfiguration:epsConf deviceFingerprintTokenPolicy:deviceFingerprintTokenPolicy completionHandler:^(id<EMCapToken> token, NSError *error) {
        if (error) {
            [self publishProgress:[NSString stringWithFormat:@"Error: %@ </br>%@ </br>%@ </br>%@ </br>%@", error.localizedDescription,
                                   @"---",
                                   @"* Verify the URL is correct",
                                   @"* Try generating a new PIN and registration code in the EPS",
                                   @"* Is the URL insecure?  Then configure the TlsConfiguration to permit insecure connections"]];
            [self.progressDelegate provisioningCompleteWithError:error.localizedDescription];
        } else {
            [self publishProgress:[NSString stringWithFormat:@"Token created: %@", token.name]];
            [self.progressDelegate provisioningCompleteWithError:nil];
        }
    }];
}

/**
 * Is multi auth mode enabled.
 */
- (BOOL)isMultiAuthModeEnabled
{
    BOOL enabled = NO;
    
    // IS MULTI AUTH MODE ENABLED
    currentOperation = @"Is multi auth mode enabled";
    
    // Get CAP token
    id<EMCapToken> token = [self getCapToken];
    enabled = [token isMultiAuthModeEnabled];
    if (enabled) {
        [self publishProgress:@"Multi auth mode enabled"];
    } else {
        [self publishProgress:@"Multi auth mode disabled?"];
    }
    
    return enabled;
}

/**
 * This method will do the following tasks:
 * 1. Upgrade to multi auth mode if it's not enabled.
 * 2. Activate all the testing modes
 */
- (void)upgradeAndActivateAllModesWithPinAuthInput:(id<EMPinAuthInput>)authInput
{
    // UPGRADE TO MULTI AUTH MODE
    currentOperation = @"Upgrade to multi auth mode";
    
    // Get CAP token
    id<EMCapToken> token = [self getCapToken];
    
    // Upgrade to multi auth mode if it's not enabled
    if (![token isMultiAuthModeEnabled]) {
        [self publishProgress:@"Multi auth mode is not enabled, token will be upgraded to multi auth mode"];
        [token upgradeToMultiAuthMode:authInput error:nil];
    }
    
    [self.progressDelegate upgradeToMultiAuthModeCompleted];
}

///**
// * This method will generate a CAP mode 2 OTP for all the tokens provisioned
// * in the device. It provides a real world example (minus the bad UI) of
// * how this should be performed and it includes all security guidelines that
// * must be followed.
// */
- (void)generateOtpWithAuthInput:(id<EMAuthInput>)authInput
{
    // GENERATE CAP MODE 2 OTPs
    currentOperation = @"Generate OTP";

    // Get CAP token
    id<EMCapToken> token=[self getCapToken];

    // A device is the object that generates OTP. Notice this will
    // create CAP OTP.
    EMCapFactory *capFactory = [[EMCapFactory alloc] init];
    id<EMCapDevice> device = [capFactory createCapDeviceWithToken:token error:nil];
    id<EMSecureString> otp = [device otpMode2WithAuthInput:authInput error:nil];
    
    // Security Guideline: IOS01. Sensitive data leaks
    // The OTP will remain displayed in the UI even after this local
    // variable is wiped. The application should clear this
    // information as soon as it is consumed by the user (in
    // this example's case, until the app is paused).
    [self publishProgress:[NSString stringWithFormat:@"Name= %@ \nOTP=%@", currentTokenName, [otp stringValue]]];

    // Security Guideline: GEN12. Wiping assets
    // The OTP must be wiped after use.
    [otp wipe];
}

- (void)resetAllTokens
{
    NSError* error = NULL;
    
    EMOtpModule *otpModule = [EMOtpModule otpModule];
    EMCapService *capService = [EMCapService serviceWithModule:otpModule];
    id<EMTokenManager> tokenManager = [capService tokenManager:nil];
    for (NSString *tokenName in [tokenManager tokenNames:&error]) {
        [tokenManager removeTokenWithName:tokenName error:&error];
    }
}

#pragma mark Private Methods

/**
 * Get CAP token
 */
-(id<EMCapToken>)getCapToken
{
    id<EMCapToken> token = nil;
    
    EMOtpModule *otpModule = [EMOtpModule otpModule];
    EMCapService *capService = [EMCapService serviceWithModule:otpModule];
    id<EMCapTokenManager> tokenManager = [capService tokenManager:nil];

    // For the sake of example, we only consider the first token.
    currentTokenName = [[tokenManager tokenNames:nil].allObjects firstObject];

    // Notice that the fingerprint is included when creating the
    // token.  Also a real app should handle the error.
    token = (id<EMCapToken>)[tokenManager tokenWithName:currentTokenName fingerprintCustomData:[FakeAppData customFingerprintData] error:NULL];
    
    return token;
}

/**
 * Setup the EPS configuration values. The inputs come from the FakeAppData
 * class.
 */
-(EMProvisioningConfiguration *)setupEpsConfigurationWithRegCode:(id<EMSecureString>)regCode
{
    NSURL *epsUrl = [NSURL URLWithString:[FakeAppData epsUrl]];
    
    EMProvisioningConfiguration *eps = [EMProvisioningConfiguration epsConfigurationWithURL:epsUrl  rsaKeyId:[FakeAppData rsaKeyId] rsaExponent:[FakeAppData rsaKeyExponent]
        rsaModulus:[FakeAppData rsaKeyModulus] registrationCode:regCode provisioningProtocol:EMMobileProvisioningProtocolVersion1 optionalParameters:^(EMEpsConfigurationBuilder *builder) {
        // Security Guideline: GEN02. Communication over HTTP forbidden
        // Security Guideline: GEN04. Reject invalid SSL certificates
        //
        // Use this to lower the security of the TLS connection. It is preferred
        // to not alter the TLS settings in order to ensure the highest level of
        // security.
        EMTlsConfiguration *tls = [[EMTlsConfiguration alloc] init];
        
        // This is unnecessary if one uses the default TlsConfiguration.
        // However, this example leaves this call in order to demonstrate how
        // to use the TLS options.
        
        builder.tlsConfiguration = tls;
    }];
    
    return eps;
}

/**
 * Setup the device fingerprint token policy. 
 * This data will seal the user credentials to
 * this device and/or a UUID so an attacker cannot simply copy the
 * device's raw data.
 */
- (EMDeviceFingerprintTokenPolicy *)setupDeviceFingerprintTokenPolicy
{
    BOOL checkFingerprintWhenTokenIsLoaded = YES;
    
    // Security Guideline: GEN10. Anti-cloning data
    // Use all available fingerprinting features
    NSSet *types = [NSSet setWithObjects:@(EMDeviceFingerprintTypeSoft), nil];
    
    EMDeviceFingerprintSource *source = [[EMDeviceFingerprintSource alloc] initWithCustomData:[FakeAppData customFingerprintData]
                                                                        deviceFingerprintType:types];
    
    EMDeviceFingerprintTokenPolicy *deviceFingerprintTokenPolicy = [[EMDeviceFingerprintTokenPolicy alloc] initWithDeviceFingerprintSource:source
                                                                                                                             failIfInvalid:checkFingerprintWhenTokenIsLoaded];
    
    return deviceFingerprintTokenPolicy;
}

- (void)publishProgress:(NSString *)message {
    
    if (self.progressDelegate && [self.progressDelegate respondsToSelector:@selector(reportProgressWithTitle:message:)])
    {
        [self.progressDelegate reportProgressWithTitle:currentOperation message:message];
    }
}

@end
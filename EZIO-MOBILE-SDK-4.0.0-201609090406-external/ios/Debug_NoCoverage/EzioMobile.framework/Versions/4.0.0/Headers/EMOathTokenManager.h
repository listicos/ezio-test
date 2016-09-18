/* -----------------------------------------------------------------------------
 *
 *     Copyright (c) 2016  -  GEMALTO DEVELOPMENT - R&D
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


#import <Foundation/Foundation.h>
#import "EMOathToken.h"
#import "EMSecureByteArray.h"
#import "EMTokenManager.h"
#import "EMTokenCapability.h"
#import "EMProvisioningConfiguration.h"
#import "EMDeviceFingerprintTokenPolicy.h"
#import "EMEnumSet.h"

/**
 * OATH Token Manager
 */
@protocol EMOathTokenManager <NSObject,EMTokenManager>
/**
 Returns an existing token with the given name.
 
 @param name The name of the token.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @return The token, `nil` if not found or if an error occurred.
 */
- (id<EMOathToken>)tokenWithName:(NSString *)name error:(NSError **)error;

/**
 Returns an existing token with the given name and fingerprint.
 
 @param name The name of the token.
 @param fingerprintCustomData The fingerprint custom data, `nil` if none.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @return The token, `nil` if not found or if an error occurred.
 */
- (id<EMOathToken>)tokenWithName:(NSString *)name fingerprintCustomData:(NSData *)fingerprintCustomData error:(NSError **)error;

/**
 Starts the creation of a new token with the specified token name and the provisioning configuration.
 
 @param name The token name.
 @param configuration The provisioning configuration.
 @param completionHandler mandatory block to be invoked when error occurs or when token creation is completed.
 */
- (void)createTokenWithName:(NSString *)name provisioningConfiguration:(EMProvisioningConfiguration *)configuration completionHandler:(void (^)(id<EMOathToken>, NSError*))completionHandler;


/**
 Starts the creation of a new token with the specified token name, provisioning configuration, and device fingerprint policy.
 
 @param name The token name.
 @param configuration The provisioning configuration.
 @param deviceFingerprintTokenPolicy device fingerprint token policy
 @param completionHandler mandatory block to be invoked when error occurs or when token creation is completed.
 */
- (void)createTokenWithName:(NSString *)name provisioningConfiguration:(EMProvisioningConfiguration *)configuration deviceFingerprintTokenPolicy:(EMDeviceFingerprintTokenPolicy *)deviceFingerprintTokenPolicy completionHandler:(void (^)(id<EMOathToken>, NSError*))completionHandler;

/**
 Starts the creation of a new token with the specified token name, provisioning configuration, device fingerprint policy, and token capability.
 
 @param name The token name.
 @param configuration The provisioning configuration.
 @param deviceFingerprintTokenPolicy device fingerprint token policy
 @param capability The token capability (OTP computation, dual seed...). See EMTokenCapability.
 @param completionHandler mandatory block to be invoked when error occurs or when token creation is completed.
 @return The token manager.
 
 @exception EMActivationException When the activation code does not have the capability's feature turned on.
 */
- (void)createTokenWithName:(NSString *)name provisioningConfiguration:(EMProvisioningConfiguration *)configuration deviceFingerprintTokenPolicy:(EMDeviceFingerprintTokenPolicy *)deviceFingerprintTokenPolicy capability:(EMTokenCapability)capability completionHandler:(void (^)(id<EMOathToken>, NSError*))completionHandler;

/**
 Starts the creation of a new token with the specified token name, provisioning configuration and the token capability.
 
 @param name The token name.
 @param configuration The provisioning configuration.
 @param capability The token capability (OTP computation, dual seed...). See EMTokenCapability.
 @param completionHandler mandatory block to be invoked when error occurs or when token creation is completed.
 @return The token manager.
 
 @exception EMActivationException When the activation code does not have the capability's feature turned on.
 */
- (void)createTokenWithName:(NSString *)name provisioningConfiguration:(EMProvisioningConfiguration *)configuration capability:(EMTokenCapability)capability completionHandler:(void (^)(id<EMOathToken>, NSError*))completionHandler;

/**
 Get capabilities of token with given name.
 @param name The name of the token. Returns the capabilities of an existing token.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @return The collection of token capabilities. See EMTokenCapability
 
 @exception EMCredentialDoesNotExistException When the token does not exist
 @exception NSInternalInconsistencyException When an unexpected error occurs
 while reading the token from the DB
 
 @since 4.0
 */
-(EMEnumSet *)tokenCapabilitiesWithName:(NSString *)name error:(NSError **)error;
@end

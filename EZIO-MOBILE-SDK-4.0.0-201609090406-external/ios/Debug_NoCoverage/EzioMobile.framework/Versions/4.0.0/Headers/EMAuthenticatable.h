/* -----------------------------------------------------------------------------
 *
 *     Copyright (c) 2015  -  GEMALTO DEVELOPMENT - R&D
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
#import "EMAuthMode.h"
#import "EMAuthInput.h"

/**
 The protocol a token type conforms to, if it supports multiple authentication modes.

 @since 3.2
 */
@protocol EMAuthenticatable <NSObject>

/**
 Check if a particular authentication mode is activated or not.
 
 @param authMode The authentication mode to be checked.
 
 @return 'YES' if mode is active, 'NO' otherwise.
 
 @since 3.2
 */
- (BOOL)isAuthModeActive:(id<EMAuthMode>) authMode;

/**
 Get list of activated modes.

 @return list of activated modes.

 @since 3.2
 */
- (NSSet *)activatedModes;

/**
 Activate an authentication mode.  An active authentication input is required to access protected data.
 Currently, only supports using EMPinAuthMode to activate EMBioFingerprintAuthMode. 
 <p>
 Prior to activate the mode, this method will check if it is well-configured on the platform.
 
 @param authMode The authentication mode to activate.
 @param activatedAuthInput The authentication input for an activated authentication mode that gives access to protected data.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @return 'YES' if mode has been activated, 'NO' otherwise.
 
 @since 3.2
 */
- (BOOL)activateAuthMode:(id<EMAuthMode>)authMode usingActivatedInput:(id<EMAuthInput>)activatedAuthInput error:(NSError **)error;

/**
 Deactivate an authentication mode without user authentication.
 <p>
 Prior to deactivate the mode, this method will check if it is well-configured on the platform.
 
 @param authMode The authentication mode to be deactivated.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @return 'YES' if mode has been deactivated, 'NO' otherwise.

 @since 3.2
 */
- (BOOL)deactivateAuthMode:(id<EMAuthMode>)authMode error:(NSError **)error;


/**
 Indicate if the token has already been migrated to the multi authentication mode.
 
 @return 'YES' if token has been migrated,'NO' otherwise.
 
 @since 3.2
 */
- (BOOL)isMultiAuthModeEnabled;

/**
 Get the UUID.

 @return UUID.

 @since 4.0
 */
- (NSString *)uuid;

@end

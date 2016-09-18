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
#import "EMBioFingerprintAuthService.h"
#import "EMBioFingerprintAuthInput.h"
#import "EMAuthenticatable.h"

/**
 The biometric fingerprint authentication container.
 
 @warning Do not subclass this interface.
 @since 4.0
 */
@interface EMBioFingerprintContainer : NSObject


/**
 * Designated constructor.
 * Returns the EMBioFingerprintContainer object created using the EMBioFingerprintAuthService
 * <p>
 * @param service the instance of EMBioFingerprintAuthService
 * @return instance of this class
 * @since 4.0
 */
+ (EMBioFingerprintContainer *)containerWithBioFingerprintAuthService:(EMBioFingerprintAuthService *)service;


/**
 Authenticate user by Touch ID, returns an EMBioFingerprintAuthInput object upon success, that can be used to generate OTPs.
 <p>
 
 @param authenticatable the target authenticatable item (e.g. CapToken)
 @param localizedMessage the message that will be displayed on Touch ID
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @return instance of this class
 @since 4.0
 */
- (id<EMBioFingerprintAuthInput>)authenticateUser:(id<EMAuthenticatable>)authenticatable withMessage:(NSString *)localizedMessage error:(NSError **)error;

@end

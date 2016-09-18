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

#import "EMOobManager.h"

/**
 * The Out-Of-Band Module
 *
 * @since 4.0
 */
@interface EMOobModule : NSObject

/**
 * The OOB Module Object.
 *
 * @return The OOB Module object.
 *
 * @since 4.0
 */
+ (EMOobModule *)oobModule;


/**
 * Creates an instance of OOB Manager with configuration
 *
 * @param url The URL. Should not be nil.
 * @param domain The domain. Should not be nil.
 * @param applicationId The applicationId. Should not be nil.
 * @param rsaExponent The rsaModulus. Should not be nil.
 * @param rsaModulus The rsaModulus. Should not be nil.
 * @param anError If an error occurs, upon returns contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in NULL.
 *
 * @return OOB Manager object.
 * @since 4.0
 */
- (id<EMOobManager>)createOobManagerWithURL:(NSURL *)url
                                     domain:(NSString *)domain
                              applicationId:(NSString *)applicationId
                                rsaExponent:(NSData *)rsaExponent
                                 rsaModulus:(NSData *)rsaModulus
                                      error:(NSError **)anError;


@end

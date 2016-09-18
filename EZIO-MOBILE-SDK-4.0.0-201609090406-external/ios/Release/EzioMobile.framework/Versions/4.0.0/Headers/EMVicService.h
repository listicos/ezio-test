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
#import "EMOtpModule.h"
#import "EMVicTokenManager.h"
#import "EMVicFactory.h"

/**
 * VIC Service
 *
 * @since 4.0
 */
@interface EMVicService : NSObject

/**
 * Designated constructor.
 * Returns the EMVicService object created using the EMOtpModule
 *
 * @param module an instance of EMOtpModule
 * @return EMVicService module instance.
 *
 * @since 4.0
 */
+ (EMVicService *)serviceWithModule:(EMOtpModule *)module;

/**
 * Returns Factory for creating VIC settings and VIC devices.
 *
 * @return EMVicFactory object.
 * @since 4.0
 */
- (EMVicFactory *)vicFactory;

/**
 * Returns object which confirms to EMVicTokenManager protocol for CAP tokens.
 *
 * @param error pointer to *NSError object
 * @return object which confirms to EMVicTokenManager protocol.
 * @since 4.0
 */
- (id <EMVicTokenManager>)tokenManager:(NSError **)error;

@end

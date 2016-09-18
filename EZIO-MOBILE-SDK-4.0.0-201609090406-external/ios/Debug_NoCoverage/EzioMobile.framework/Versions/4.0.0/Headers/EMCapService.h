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
#import "EMCapTokenManager.h"
#import "EMCapFactory.h"

/**
 * CAP Service
 *
 * @since 4.0
 */
@interface EMCapService : NSObject

/**
 * Designated constructor.
 * Returns the EMCapService object created using the EMOtpModule
 *
 * @param module an instance of EMOtpModule
 * @return EMCapService module instance.
 *
 * @since 4.0
 */
+ (EMCapService *)serviceWithModule:(EMOtpModule *)module;

/**
 * Returns Factory for creating CAP settings and CAP devices.
 *
 * @return EMCapFactory object.
 *
 * @since 4.0
 */
- (EMCapFactory *)capFactory;

/**
 * Returns object which confirms to EMCapTokenManager protocol for CAP tokens.
 *
 * @param error if error occurs, relevant information shall be stored here.
 * @return object which confirms to EMCapTokenManager protocol.
 * @since 4.0
 */
- (id <EMCapTokenManager>)tokenManager:(NSError **)error;

@end

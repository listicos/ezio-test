/* -----------------------------------------------------------------------------
 *
 *     Copyright (c) 2015  GEMALTO DEVELOPPEMENT - R&D
 *
 * ------------------------------------------------------------------------------
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
 * ------------------------------------------------------------------------------
 */

#import "AppDelegate.h"
#import <EzioMobile/EzioMobile.h>


@interface ViewController : UIViewController <UIAlertViewDelegate, UITextViewDelegate, NSURLConnectionDelegate, UITableViewDelegate, UITableViewDataSource>

- (void) loginEzio;
- (void) internalInit;
- (void) initializeOob;
- (void) registerEzio:(NSString *) userId userAlias:(NSString *)userAlias regCode:(NSString *) regCode;
- (void) fetchMessage;
- (void) fetchMessageWithId:(NSString*) msgId;
- (void) handleIncomingMessage:(id<EMOobIncomingMessage>)message;
- (void) acknowledgeMessage:(id<EMOobIncomingMessage>) message;
- (void) handleErrorResponse:(id<EMOobResponse>)message;
- (void) replyUserMessage:(id<EMOobProviderToUserMessage>)message;
- (void) handleTransactionVerification:(id<EMOobTransactionVerifyRequest>)message response:(EMOobTransactionVerifyResponseValue)value;
- (void) createErrorResponse:(id<EMOobIncomingMessage>)message;
- (void) setNotificationProfile;

@end


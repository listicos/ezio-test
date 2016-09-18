/* -----------------------------------------------------------------------------
 *
 *     Copyright (c)  2015  -  GEMALTO DEVELOPMENT - R&D
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
#import "EMSecureString.h"

/**
 * Attachment object that can be sent and received by user messages.
 * This comes along with either EMOobProviderToUserMessage or EMOobUserToProviderMessage object
 * in its `attachments` property.
 *
 * Locale of the content is defined by the message container.
 *
 * @since 3.0
 */
@protocol EMOobUserMessageAttachment <NSObject>

/**
 * Gets the subject.
 *
 * @return The subject.
 *
 * @since 3.0
 */
@property (nonatomic, copy, readonly) id<EMSecureString> subject;

/**
 * Gets the content type.
 *
 * @return The content type.
 *
 * @since 3.0
 */
@property (nonatomic, copy, readonly) NSString *contentType;

/**
 * Gets the content as secure byte array.
 *
 * @return The content.
 *
 * @since 3.0
 */
@property (nonatomic, strong, readonly) id<EMSecureByteArray> content;

/**
 * Gets message content in form of secure string.
 *
 * @return The content.
 *
 * @since 3.0
 */
@property (nonatomic, strong, readonly) id<EMSecureString> contentString;

/**
 * Gets the meta-data.
 *
 * @return The meta-data.
 *
 * @since 3.0
 */
@property (nonatomic, copy, readonly) NSDictionary *meta;

/**
 * Gets message content in form of secure string in a specific encoding format.
 *
 * @param encoding A string encoding.
 *
 * @return The content.
 *
 * @since 3.0
 */
- (id<EMSecureString>)contentStringWithEncoding:(NSStringEncoding)encoding;

/**
 * Wipes all the sensitive data from memory
 *
 * @since 3.0
 */
- (void)wipe;

@end

/* -----------------------------------------------------------------------------
 *
 *     Copyright (c) 2013  -  GEMALTO DEVELOPPEMENT - R&D
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
#import "EMSecureByteArray.h"

/** The defined anti-cloning types. */
typedef NS_ENUM(NSUInteger, EMDeviceFingerprintType)
{
/**
  * Seals the user's credentials. A factory reset/initialization of the device will make the credentials unusable.
  * Requirements: None
  * @warning If `EMDeviceFingerprintTypeSoft` is used, user cannot use the
  * restored data after doing a factory reset and re-initializing to the
  * same device.
  */
    EMDeviceFingerprintTypeSoft         = 0x04
};

/**
 This class is used to create device fingerprint source settings.
 */
@interface EMDeviceFingerprintSource : NSObject

/**
 List for anti-cloning sources to use.
 */
@property (nonatomic, copy, readonly) NSSet* deviceFingerprintType;

/**
 Application custom fingerprint data to integrate into anti-cloning.
 */
@property (nonatomic, strong, readonly) NSData * customData;

/**
 Gets the default device fingerprint source (`EMDeviceFingerprintTypeSoft`). See EMDeviceFingerprintType.
 */
+ (id)defaultDeviceFingerprintSource;

/**
 Initializes a new device fingerprint source.
 
 @param aDft Set of sources to use, see EMDeviceFingerprintType.
 
 @return An instance of EMDeviceFingerprintSource.
 */
- (id)initWithDeviceFingerprintType:(NSSet *)aDft;

/**
 Initializes a new device fingerprint source with some application's custom data.
 @param aCustomData Application's custom data.
 
 @return An instance of EMDeviceFingerprintSource.
 */
- (id)initWithCustomData:(NSData *)aCustomData;

/**
 Initializes a new device fingerprint source with some application's custom data.
 @param aCustomData Application's custom data.
 @param aDft Set of sources to use, see EMDeviceFingerprintType.
 
 @return An instance of EMDeviceFingerprintSource.
 */
- (id)initWithCustomData:(NSData *)aCustomData deviceFingerprintType:(NSSet *)aDft;

/**
 Checks if the provided device fingerprint type is activated.
 @param aDeviceFingerprintType The source to be verified.
 
 @return `YES` if source is active, `NO` otherwise.
 */
- (BOOL)isActive:(EMDeviceFingerprintType)aDeviceFingerprintType;


@end

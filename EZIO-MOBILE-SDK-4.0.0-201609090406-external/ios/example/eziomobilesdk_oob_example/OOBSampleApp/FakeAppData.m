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

#import "FakeAppData.h"

#import <UIKit/UIKit.h>

/**
 * This class provides application specific data. These values must not be used
 * by a real application because they are not universal settings.
 */
@implementation FakeAppData

/**
 * Get domain
 */

+ (NSString *) domain {
    return @"TestDomain";
}

/**
 * Get applicationId
 */
+ (NSString *) applicationId {
    return @"TestApp";
}

/**
 * Get providerId
 */
+ (NSString *) providerId {
    return @"TestProvider";
}

/**
 * Replace this URL with your EPS URL.
 */

+ (NSString *) oobClientUrl {
    NSString *clientUrl;
    clientUrl =  @"https://localhost/clientapi";
    
    NSString *model = [[UIDevice currentDevice] model];
    if ([model isEqualToString:@"iPhone Simulator"]) {
        clientUrl = @"https://localhost/clientapi";
    }
    
    return clientUrl;
}

/**
 * Replace this byte array with your own EPS key modulus unless you are
 * using the EPS 2.X default key pair.
 *
 * The EPS' RSA modulus. This is specific to the configuration of the
 * bank's system.  Therefore other values should be used here.
 */
+ (NSData *) rsaModulus{
    // Security Guideline: GEN13. Integrity of public keys
    // Since this example hard codes the key and does not load it from a
    // file, this guideline is skipped.
    
    // Security Guideline: GEN17. RSA key length
    // 2048 bit key
    unsigned char rawRsa[] = {
        0x00, 0xde, 0x87, 0x01, 0x3d, 0x33,
    };
    
    return [NSData dataWithBytes:rawRsa length:sizeof(rawRsa)];
}


/**
 * Replace this byte array with your own EPS key exponent.
 *
 * The EPS' RSA exponent. This is specific to the configuration of the
 * bank's system.  Therefore other values should be used here.
 */
+ (NSData *) rsaExponent{
    // Security Guideline: GEN13. Integrity of public keys
    // Since this example hard codes the key and does not load it from a
    // file, this guideline is skipped.
    unsigned char raw[] = { 0x01, 0x01};
    return [NSData dataWithBytes:raw length:sizeof(raw)];
}


/**
 * Get userId
 */
+(NSString *) userId{
    return @"TestUser";
}

/**
 * Get userAlias
 */
+(NSString *) userAlias{
    return @"TestUser";
}

+ (NSData*) activationCode {
    // This activation code would enable the Oob feature,
    // Put the correct value of activationCode and pass it
    // when initialize EzioMobileContext
    unsigned char raw[] = { 0x01,  0x47,
        0x54,  0x4f,  0x52,  0x6e,
        0x44,  0x30,  0x31,  0xff,
        0xff,  0xff,  0xff,  0x42,
        0x92,  0xbb,  0x8d,  0xae,
        0x24,  0xfb,  0x2b,  0xd4,
        0xe6,  0xfa,  0xc9,  0xad,
        0x26,  0xef,  0xbe,  0x7e,
        0x54,  0x26,  0x2c,  0x91,
        0xa2,  0x0c,  0xf4,  0xcb,
        0x1e,  0x90,  0xea,  0x87,
        0x95,  0xeb,  0x5d,  0x40,
        0x9d,  0x4e,  0xd1,  0x11,
        0x1b,  0x24,  0xcd,  0x4c,
        0x6f,  0xc9,  0x72,  0x79,
        0x09,  0xf1,  0xda,  0xeb,
        0x15,  0x3c,  0xff,  0xae,
        0x9a,  0x49,  0x9d,  0x92,
        0xc0,  0x62,  0xb0,  0x7a,
        0xc1,  0xe1,  0xf0,};
    return [NSData dataWithBytes:raw length:sizeof(raw)];
}

// Meta data for the message. Can be `nil`.
+ (NSDictionary *) meta {
    return @{@"A KEY" : @"A VALUE", @"B KEY" : @"B VALUE"};
}

@end
/* -----------------------------------------------------------------------------
 *
 *     Copyright (c)  2014  -  GEMALTO DEVELOPEMENT - R&D
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
#import <EzioMobile/EzioMobile.h>

@protocol ExampleProgressDelegate;
@protocol ExampleInputDelegate;


@interface Example : NSObject

@property (weak, atomic) id<ExampleProgressDelegate> progressDelegate;
@property (weak, atomic) id<ExampleInputDelegate> inputDelegate;

@property (nonatomic, strong, readonly) EMCore *core;

/**
 * The registration code should come from the user input. When
 */
- (void)provisionWithRegCode:(id<EMSecureString>)regCode;

- (BOOL)isMultiAuthModeEnabled;

- (void)upgradeAndActivateAllModesWithPinAuthInput:(id<EMPinAuthInput>)authInput;

- (void) generateOtpWithAuthInput:(id<EMAuthInput>)authInput;

- (void)resetAllTokens;

@end


@protocol ExampleProgressDelegate <NSObject>

// If error is nil, then the provisioning has been successful.
- (void)provisioningCompleteWithError:(NSString*)error;

// Activate multi auth mode completed.
- (void)upgradeToMultiAuthModeCompleted;

- (void)reportProgressWithTitle:(NSString *)title message:(NSString *)message;

@end
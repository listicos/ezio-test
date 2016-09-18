/** -----------------------------------------------------------------------------
 
 Copyright (c) 2013  -  GEMALTO DEVELOPMENT - R&D
 
 -----------------------------------------------------------------------------
 GEMALTO MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 PARTICULAR PURPOSE, OR NON-INFRINGEMENT. GEMALTO SHALL NOT BE
 LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 
 THIS SOFTWARE IS NOT DESIGNED OR INTENDED FOR USE OR RESALE AS ON-LINE
 CONTROL EQUIPMENT IN HAZARDOUS ENVIRONMENTS REQUIRING FAIL-SAFE
 PERFORMANCE, SUCH AS IN THE OPERATION OF NUCLEAR FACILITIES, AIRCRAFT
 NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL, DIRECT LIFE
 SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH THE FAILURE OF THE
 SOFTWARE COULD LEAD DIRECTLY TO DEATH, PERSONAL INJURY, OR SEVERE
 PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH RISK ACTIVITIES"). GEMALTO
 SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR
 HIGH RISK ACTIVITIES.
 
 -----------------------------------------------------------------------------
 */

#import <Foundation/Foundation.h>
#import "EMGemaltoOathDevice.h"
#import "EMOathDevice.h"
#import "EMOathToken.h"
#import "EMSoftOathToken.h"
#import "EMSoftGemaltoOathSettings.h"
#import "EMMutableSoftGemaltoOathSettings.h"
#import "EMMutableSoftOathSettings.h"
#import "EMSelectableKey.h"

/**
 A factory for creating objects that produce or affect OATH (or its relatives) OTPs.
 
 @since 2.2
 */
@interface EMOathFactory : NSObject

///////////////////////////////////////////////////////////////////////////////////////
/// @name Create GemaltoOathDevice
///////////////////////////////////////////////////////////////////////////////////////


/**
 Creates a Gemalto OATH device with default settings returned from [EMOathFactory defaultSoftGemaltoOathSettings].
 
 @param token The token.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @exception NSInternalInconsistencyException When the token suppports more than one key (e.g. a token with `EMTokenCapabilityDUAL_SEED`), and its key has not been selected. See EMTokenCapability.
 
 @return A Gemalto OATH device object.
 */
- (id<EMGemaltoOathDevice>)createGemaltoOathDeviceWithToken:(id<EMOathToken>)token error:(NSError **)error;

/**
 Creates a customized soft Gemalto OATH device.
 
 @param token The token.
 @param settings The Gemalto OATH settings.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @exception NSInternalInconsistencyException When the token suppports more than one key (e.g. a token with `EMTokenCapabilityDUAL_SEED`), and its key has not been selected. See EMTokenCapability.
 
 @return A Gemalto OATH device.
 */
- (id<EMGemaltoOathDevice>)createSoftGemaltoOathDeviceWithToken:(id<EMSoftOathToken>)token settings:(id<EMSoftGemaltoOathSettings>)settings error:(NSError **)error;

/**
 Creates a mutable Gemalto OATH settings.
 
 @return New mutable settings based on the default settings returned from [EMOathFactory defaultSoftGemaltoOathSettings].
 */
- (id<EMMutableSoftGemaltoOathSettings>)mutableSoftGemaltoOathSettings;

/**
 Gets the default settings for Gemalto OATH devices.
 
 @return The default settings.
 */
- (id<EMSoftGemaltoOathSettings>)defaultSoftGemaltoOathSettings;

///////////////////////////////////////////////////////////////////////////////////////
/// @name Create OathDevice
///////////////////////////////////////////////////////////////////////////////////////

/**
 Creates a customized soft OATH device using the specified settings.
 
 @param token The token.
 @param settings The OATH settings.
 @param error If an error occurs, upon return contains an NSError object that describes the problem. If you are not interested in possible errors, you may pass in `NULL`.
 @exception NSInternalInconsistencyException When the token suppports more than one key (e.g. a token with `EMTokenCapabilityDUAL_SEED`), and its key has not been selected. See EMTokenCapability.
 
 @return The OATH device.
 */
-(id<EMOathDevice>)createSoftOathDeviceWithToken:(id<EMSoftOathToken>)token settings:(id<EMSoftOathSettings>)settings error:(NSError **)error;

/**
 Creates a mutable OATH settings.
 
 @return New mutable OATH settings based on the default OATH settings returned from [EMOathFactory defaultSoftOathSettings].
 */
-(id<EMMutableSoftOathSettings>)mutableSoftOathSettings;

/**
 Gets the default settings for OATH devices.
 
 @return The default settings.
 */
-(id<EMSoftOathSettings>)defaultSoftOathSettings;


@end

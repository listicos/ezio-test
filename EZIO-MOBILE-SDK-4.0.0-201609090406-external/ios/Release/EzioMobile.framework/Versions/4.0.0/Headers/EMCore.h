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

#import "EMModule.h"
#import "EMPasswordManager.h"
#import "EMSecureContainerFactory.h"
#import "EMModuleConfiguration.h"

/**
 * The Core module
 * @since 4.0
 */
@interface  EMCore : NSObject

/**
 * Singleton instance of EMCore
 *
 * @return The singleton EMCore instance. This method requires Core to be configured before.
 * @since 4.0
 */
+ (instancetype)sharedInstance;

/**
 * Configures the core with module configurations. It is the entry point of the SDK. 
 * All other features should not be used without invoking this method.
 * @param configurations The set of module configurations.
 * @since 4.0
 */
+ (instancetype)configureWithConfigurations:(NSSet *)configurations;

/**
 * Configures the core with activation code and module configurations. It is the entry point of the SDK. 
 * All other features should not be used without invoking this method.
 * @param activationCode The activation code.
 * @param configurations The set of EMModuleConfiguration module configurations.
 * @throws NSException if core is already configured
 * @since 4.0
 */
+ (instancetype)configureWithActivationCode:(NSData *)activationCode configurations:(NSSet *)configurations;

/**
 * Tells if the core has been configured or not
 *
 * @return YES if configured, NO otherwise.
 * @since 4.0
 */
+ (BOOL)isConfigured;

/**
 * The version of the core.
 *
 * @return Version of the core.
 * @since 4.0
 */
+ (NSString *)version;

/**
 * The password manager
 *
 * @return The password manager.
 * @since 4.0
 */
- (id <EMPasswordManager>)passwordManager;

/**
 * The factory of secure containers.
 *
 * @return Secure container factory.
 * @since 4.0
 */
- (id <EMSecureContainerFactory>)secureContainerFactory;

@end

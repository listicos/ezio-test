
/** ----------------------------------------------------------------------------
 *
 *     Copyright (c)  2012  -  GEMALTO DEVELOPEMENT - R&D
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

#ifndef libmobilesdk_libmobilesdk_h
#define libmobilesdk_libmobilesdk_h

#ifndef NS_ENUM
#define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#endif
#import "EMAuthInput.h"
#import "EMAuthMode.h"
#import "EMAuthModule.h"
#import "EMAuthService.h"
#import "EMAuthenticatable.h"
#import "EMBioFingerprintAuthInput.h"
#import "EMBioFingerprintAuthMode.h"
#import "EMBioFingerprintAuthService.h"
#import "EMBioFingerprintContainer.h"
#import "EMCapDevice.h"
#import "EMCapFactory.h"
#import "EMCapService.h"
#import "EMCapSettings.h"
#import "EMCapToken.h"
#import "EMCapTokenManager.h"
#import "EMCapTools.h"
#import "EMCore.h"
#import "EMDecimalInputDialogPrimitive.h"
#import "EMDeviceFingerprintSource.h"
#import "EMDeviceFingerprintTokenPolicy.h"
#import "EMDsCapParameters.h"
#import "EMDsFormattingDevice.h"
#import "EMDsFormattingFactory.h"
#import "EMDsFormattingService.h"
#import "EMDsFormattingTools.h"
#import "EMDsTransactionData.h"
#import "EMDualSeedOathToken.h"
#import "EMDualSeedSoftOathToken.h"
#import "EMEnumSet.h"
#import "EMErrorDomain.h"
#import "EMException.h"
#import "EMFreeTextPrimitive.h"
#import "EMGemaltoOathDevice.h"
#import "EMGpfDsDevice.h"
#import "EMGpfDsFactory.h"
#import "EMGpfDsService.h"
#import "EMGroupedInputDialogPrimitive.h"
#import "EMHiddenTextPrimitive.h"
#import "EMInformationPrimitive.h"
#import "EMInputDialogPrimitive.h"
#import "EMInputPrimitive.h"
#import "EMJailbreakDetector.h"
#import "EMMessageDialogPrimitive.h"
#import "EMModule.h"
#import "EMModuleConfiguration.h"
#import "EMMutableSoftCapSettings.h"
#import "EMMutableSoftGemaltoOathSettings.h"
#import "EMMutableSoftGpfDsSettings.h"
#import "EMMutableSoftOathSettings.h"
#import "EMNumericInputDialogPrimitive.h"
#import "EMOathDevice.h"
#import "EMOathFactory.h"
#import "EMOathService.h"
#import "EMOathToken.h"
#import "EMOathTokenManager.h"
#import "EMOobConfiguration.h"
#import "EMOobErrorMessage.h"
#import "EMOobException.h"
#import "EMOobFetchMessageResponse.h"
#import "EMOobGenericIncomingMessage.h"
#import "EMOobGenericOutgoingMessage.h"
#import "EMOobIncomingMessage.h"
#import "EMOobIncomingMessageBase.h"
#import "EMOobIncomingMessageHandler.h"
#import "EMOobJailbreakPolicy.h"
#import "EMOobManager.h"
#import "EMOobMessage.h"
#import "EMOobMessageBase.h"
#import "EMOobMessageHandler.h"
#import "EMOobMessageHandlerRegistry.h"
#import "EMOobMessageManager.h"
#import "EMOobMessageMeta.h"
#import "EMOobMessageResponse.h"
#import "EMOobModule.h"
#import "EMOobNotificationManager.h"
#import "EMOobNotificationProfile.h"
#import "EMOobNotificationProfilesResponse.h"
#import "EMOobOutgoingMessage.h"
#import "EMOobOutgoingMessageBase.h"
#import "EMOobOutgoingMessageHandler.h"
#import "EMOobProviderToUserMessage.h"
#import "EMOobRegistrationManager.h"
#import "EMOobRegistrationRequest.h"
#import "EMOobRegistrationResponse.h"
#import "EMOobResponse.h"
#import "EMOobTransactionVerifyRequest.h"
#import "EMOobTransactionVerifyResponse.h"
#import "EMOobUnregistrationManager.h"
#import "EMOobUserMessageAttachment.h"
#import "EMOobUserToProviderMessage.h"
#import "EMOtpConfiguration.h"
#import "EMOtpException.h"
#import "EMOtpModule.h"
#import "EMOtpTools.h"
#import "EMPasswordManager.h"
#import "EMPinAuthInput.h"
#import "EMPinAuthMode.h"
#import "EMPinAuthService.h"
#import "EMPinRule.h"
#import "EMPinRuleIdentical.h"
#import "EMPinRuleLength.h"
#import "EMPinRulePalindrome.h"
#import "EMPinRuleSeries.h"
#import "EMPinRuleUniform.h"
#import "EMPrimitive.h"
#import "EMPrimitiveTags.h"
#import "EMPrimitiveValue.h"
#import "EMPropertyStorage.h"
#import "EMProvisioningConfiguration.h"
#import "EMSecureByteArray.h"
#import "EMSecureContainer.h"
#import "EMSecureContainerFactory.h"
#import "EMSecureInputBuilder.h"
#import "EMSecureInputService.h"
#import "EMSecureStorageManager.h"
#import "EMSecureStorageModule.h"
#import "EMSecureString.h"
#import "EMSelectableKey.h"
#import "EMSelectionInputDialogPrimitive.h"
#import "EMSoftCapSettings.h"
#import "EMSoftCapToken.h"
#import "EMSoftGemaltoOathSettings.h"
#import "EMSoftGpfDsSettings.h"
#import "EMSoftOathSettings.h"
#import "EMSoftOathToken.h"
#import "EMSoftVicToken.h"
#import "EMTagValue.h"
#import "EMTemplate.h"
#import "EMTextPrimitive.h"
#import "EMTlsConfiguration.h"
#import "EMToken.h"
#import "EMTokenCapability.h"
#import "EMTokenJailbreakPolicy.h"
#import "EMTokenManager.h"
#import "EMUIModule.h"
#import "EMVicDevice.h"
#import "EMVicFactory.h"
#import "EMVicService.h"
#import "EMVicToken.h"
#import "EMVicTokenManager.h"
#import "EMWipeable.h"
#import "EzioMobile.h"
#import "common.h"
#import "em_status.h"


#endif


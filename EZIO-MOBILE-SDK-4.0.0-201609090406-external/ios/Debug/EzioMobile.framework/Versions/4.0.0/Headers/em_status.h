/** -----------------------------------------------------------------------------
 
 Copyright (c) 2014  -  GEMALTO DEVELOPMENT - R&D
 
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

#ifndef libmobilesdk_io_EMStatus_h
#define libmobilesdk_io_EMStatus_h

#import <CoreFoundation/CFData.h>


#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef NS_ENUM
#define NS_ENUM(_type, _name) CF_ENUM(_type, _name)
#endif
    
    /**
     * General status sodes for EzioMobileSDK operations.
     *
     * Group: Common STATUS CODE, starting from 101
     * Group: Database STATUS CODE, starting from 300
     * Group: OOB STATUS CODE, starting from 400
     * Group: OOB SEND CODES, starting from 500
     * Group: PASSWORD MANAGER CODES, starting from 600
     * Group: SECURE STORAGE CODES, starting from 700
     * Group: Bio fingerprint STORAGE CODES, starting from 800
     *
     * @since 3.0
     */
    typedef NS_ENUM(int, EMStatus)
    {
        /** Operation has succeeded. */
        EM_STATUS_SUCCESS = 0,
        
        /** Unspecified error. */
        EM_STATUS_UNSPECIFIED_ERROR = -100,
        
        /////////////////////////////////////////////////////////////////////////////
        /// Group: Common STATUS CODE
        /////////////////////////////////////////////////////////////////////////////
        
        /** One or more arguments are invalid. */
        EM_STATUS_INVALID_ARGUMENT = -101,
        
        /** An output buffer has insufficient size. */
        EM_STATUS_BUFFER_TOO_SMALL = -102,
        
        /** An input buffer is larger than the supported size. */
        EM_STATUS_BUFFER_TOO_LARGE = -103,
        
        /** The response body is malformed. */
        EM_STATUS_BODY_PARSE_ERROR = -104,
        
        /** A cryptographic operation could not be performed. */
        EM_STATUS_CRYPTO_ERROR = -105,
        
        /** Occurs when the counter has reached its max value. */
        EM_STATUS_WRAPPED_COUNTER = -106,
        
        /** Out of memory. */
        EM_STATUS_OOM = -107,
        
        /** A check digit failed, e.g. verhoeff. */
        EM_STATUS_INVALID_CHECK_DIGIT = -108,
        
        /** Secure Random error. */
        EM_STATUS_SEC_RAND_ERROR = -109,
        
        /** Value for Token IO key is not set yet. */
        EM_STATUS_IO_UNINITIALIZED_KEY = -110,
        
        /** Unknown key value for Token IO. */
        EM_STATUS_IO_UNEXPECTED_KEY = -111,
        
        /** Keychain element is already present. */
        EM_STATUS_EXISTING_KEYCHAIN_ELEMENT = -112,
        
        /** Unknown keychain element. */
        EM_STATUS_UNKNOWN_KEYCHAIN_ELEMENT = -113,
        
        /** An error occured during keychain operation. */
        EM_STATUS_UNEXPECTED_KEYCHAIN_ERROR = -114,
        
        /** Invalid IV length for the corresponding algorithm. */
        EM_STATUS_CRYPTO_INVALID_IV_LENGTH = -115,
        
        /** Unknown mode of operation for crypto. */
        EM_STATUS_CRYPTO_UNKNOWN_MODE = -116,
        
        /** Unknown crypto algorithm */
        EM_STATUS_CRYPTO_UNKNOWN_ALGO = -117,
        
        /** Secure scheme version for EEK is not supported. */
        EM_STATUS_SECURE_SCHEME_INVALID_FOR_EEK = -118,
        
        /** Secure scheme version for SEK is not supported. */
        EM_STATUS_SECURE_SCHEME_INVALID_FOR_SEK = -119,
        
        /** Secure scheme version for SAK is not supported. */
        EM_STATUS_SECURE_SCHEME_INVALID_FOR_SAK = -120,
        
        /** An error occured when copying a CFType. */
        EM_STATUS_FAIL_TO_COPY_AN_OBJECT = -121,
        
        /** Legacy fingerprint generated an error. */
        EM_STATUS_FAIL_TO_COMPUTE_LEGACY_FP = -122,
        
        /** Object is in illegal state. */
        EM_STATUS_ILLEGAL_STATE = -123,
        
        /** A native constructor has failed. */
        EM_STATUS_FAIL_NATIVE_CTOR = -124,
        
        /** The token type is invalid for the requested operation. */
        EM_STATUS_INVALID_TOKEN_TYPE = -125,
        
        /** HMAC verification failed. */
        EM_STATUS_INVALID_HMAC = -126,
        
        /** Operation is not supported in dual seeds mode. */
        EM_STATUS_OPERATION_NOT_SUPPORTED_IN_DUAL_SEED_MODE = -127,
        
        /** Invalid input character in PIN. */
        EM_STATUS_INVALID_CHARACTER_IN_PIN = -128,
        
        /** Invalid index character in PIN data. */
        EM_STATUS_INVALID_INDEX_IN_PIN = -129,
        
        /** Mother key not valid */
        EM_STATUS_INVALID_MOTHER_KEY = -130,
        
        /*!< Data corruption reprovision needed */
        EM_STATUS_MOTHER_KEY_COLLISION = -131,
        
        /** Invalid uuid length */
        EM_STATUS_INVALID_UUID_LENGTH = -132,
        
        /////////////////////////////////////////////////////////////////////////////
        /// Group: Database STATUS CODE
        /////////////////////////////////////////////////////////////////////////////
        
        /** Database error. */
        EM_STATUS_DATABASE_ERROR = -300,
        
        /** Database no record found.. */
        EM_STATUS_DATABASE_NO_RECORD_FOUND = -301,
        
        /////////////////////////////////////////////////////////////////////////////
        /// Group: OOB STATUS CODE
        /////////////////////////////////////////////////////////////////////////////
        
        /** The registration request failed. Something wrong with IPMS (see OOB_SUB_CODE). */
        EM_STATUS_OOB_REGISTRATION_FAILED = -400,
        
        /** Invalide OOB Registration data.  Some data may be `nil` method may be unsupported. */
        EM_STATUS_OOB_INVALID_REGISTRATION_DATA = -401,
        
        /** The unregistration request failed. Something wrong with IPMS (see OOB_SUB_CODE). */
        EM_STATUS_OOB_UNREGISTRATION_FAILED = -402,
        
        /** The notification profile request failed. Something wrong with IPMS (see OOB_SUB_CODE). */
        EM_STATUS_OOB_NOTIFICATION_FAILED = -403,
        
        /** The message request failed. Something wrong with IPMS (see OOB_SUB_CODE). */
        EM_STATUS_OOB_MESSAGE_FAILED = -404,
        
        
        /////////////////////////////////////////////////////////////////////////////
        /// Group: OOB SEND CODES
        /////////////////////////////////////////////////////////////////////////////
        
        /** An error occured when serializing the message in JSON. */
        EM_STATUS_OOB_SEND_JSON_CREATION = -500,
        
        /////////////////////////////////////////////////////////////////////////////
        /// Group: PASSWORD MANAGER CODES
        /////////////////////////////////////////////////////////////////////////////
        
        /** Generic password failure, e.g. error in operation such as wiping password that does not exist, etc.  */
        EM_STATUS_PASSWORD_MANAGER_GENERIC_FAILURE = -600,
        
        /** Operation could not proceed correctly because the password was not set. */
        EM_STATUS_PASSWORD_MANAGER_PASSWORD_NOT_SET = -601,
        
        /** The password supplied was not correct, or was trying to perform operation while not logged in. */
        EM_STATUS_PASSWORD_MANAGER_INCORRECT_PASSWORD = -602,
        
        /** Unexpected error in password storage access even if conditions are met. */
        EM_STATUS_PASSWORD_MANAGER_UNKNOWN_INTERNAL_ERROR = -603,
        
        /** Duplicate Password Id Exists.  */
        EM_STATUS_PASSWORD_MANAGER_DUPLICATE_PASSWORDID = -604,
        
        /////////////////////////////////////////////////////////////////////////////
        /// Group: SECURE STORAGE CODES
        /////////////////////////////////////////////////////////////////////////////
        
        /** Generic secure storage failure, e.g.  */
        EM_STATUS_SECURE_STORAGE_GENERIC_FAILURE = -701,
        
        /** Property not exist*/
        EM_STATUS_SECURE_STORAGE_PROPERTY_NOT_EXIST = -702,
        
        /** Property storage with different security level exist*/
        EM_STATUS_SECURE_STORAGE_WITH_IDENTIFIER_EXISTS_WITH_DIFFERENT_SECURITY = -703,
        
        /////////////////////////////////////////////////////////////////////////////
        /// Group: Bio fingerprint STORAGE CODES
        /////////////////////////////////////////////////////////////////////////////
        
        /** Biomatric fingerprint is not supported */
        EM_STATUS_BIO_FINGERPRINT_API_NOT_SUPPORTED = -800,
        
        /** User can not be authenticate */
        EM_STATUS_AUTHENTICATION_FAILED = -801,
        
        /** User cancel the authentication */
        EM_STATUS_AUTHENTICATION_CANCEL = -802,
        
        /** Bio fingerprintis already activate for this token and user*/
        EM_STATUS_AUTHENTICATION_ALREADY_REGISTERED = -803,
        
        /** Authentication was canceled, because the user tapped the fallback button (Enter Password).*/
        EM_STATUS_AUTHENTICATION_CANCELED_USER_FALLBACK = -804,
        
        /** Authentication was canceled by system (e.g. another application went to foreground).*/
        EM_STATUS_AUTHENTICATION_CANCELED_BY_SYSTEM = -805,
        
        /** Authentication could not start, because passcode is not set on the device.*/
        EM_STATUS_AUTHENTICATION_ERROR_PASSCODE_NOT_SET = -806,
        
        /** Authentication could not start, because BIO fingerprint is not available on the device.*/
        EM_STATUS_AUTHENTICATION_ERROR_NOT_AVAILABLE = -807,
        
        /** Authentication could not start, because  BIO fingerprint has no enrolled fingers.*/
        EM_STATUS_AUTHENTICATION_ERROR_NOT_ENROLLED = -808,
        
        /** Authentication was not successful, because there were too many failed  BIO fingerprint attempts and
         api is now locked. Passcode is required to unlock it, e.g. using bio fingerprint api
         will ask for passcode as a prerequisite.*/
        EM_STATUS_AUTHENTICATION_ERROR_API_LOCKED = -809,
        
        /** Change pin action is forbiden while BioFpMode is active*/
        EM_STATUS_AUTHENTICATION_CHANGEPIN_NOT_AVAILABLE = -810
        
    };
    
#ifdef __cplusplus
}
#endif


#endif
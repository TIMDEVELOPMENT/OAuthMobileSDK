/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
   OMDefinitions.h - Oracle Mobile constant Definitions
 
 DESCRIPTION
   This header file is just for definitions.
 
 RELATED DOCUMENTS
   None
 
 PROTOCOLS
   None
 
 EXAMPLES
   None
 
 NOTES
   None
 
 MODIFIED   (MM/DD/YY)
 vismishr    01/30/15 - Corrected typo in Identity domain header
 vismishr    01/17/14 - OAuth SIM V3.1 Support
 vismishr    12/29/14 - Bug 20274517
 vismishr    08/06/14 - Added session active on restart flag
 vismishr    06/02/14 - OAuth client credentials flow
 vismishr    05/14/14 - OAuth PS3 enhancements
 vismishr    03/18/14 - MAF logout enhancement
 vismishr    12/23/13 - Added Resorce Owner flow for OAuth
 vismishr    12/11/13 - Made config parameters consistent with android
 asashiss    11/26/13 - Added connectivity modes
 vismishr    10/22/13 - Property for OAuth client secret
 sativenk    09/13/25 - Property for authentication time-out 
 asashiss    08/28/13 - Support for custom tokens and headers
 msadasiv    11/20/12 - Bug 14836655 - set ksecattraccessible to a secure 
                                       by default value
 msadasiv    10/17/12 - Added AES crypto scheme and fingerprint deviceclaim
 sativenk    04/02/12 - Bug 13912701
 sativenk    10/03/12 - Creation
 */


#import <Foundation/Foundation.h>


/*
 * Macro for logging error message only in debug mode and not in release
 * mode
 */
#ifdef DEBUG
#   define OMDebugLogF(fmt, ...) NSLog((@"%s:%s[Line #:%d]: " fmt), __FILE__, \
                                       __PRETTY_FUNCTION__, __LINE__, \
                                       ##__VA_ARGS__);
#   define OMDebugLogNF(fmt, ...) NSLog((@"%s[Line #:%d]: " fmt), \
                                        __PRETTY_FUNCTION__, __LINE__, \
                                        ##__VA_ARGS__);
#   define OMDebugLog  OMDebugLogNF
#   define OMDebugLogError(err)  NSLog(@"%s:%s[Line #:%d]: Error %@-%05ld:%@", \
                                       __FILE__, __PRETTY_FUNCTION__, \
                                       __LINE__,  [(err) domain], \
                                      (long)[(err) code], \
                                      [(err) localizedDescription] );
#else
#   define OMDebugLogF(...)
#   define OMDebugLogNF(...)
#   define OMDebugLog(...)
#   define OMDebugLogError(...)
#endif

/*
 * Macro for logging error message with file name, function name, line #,
 * error domain, error code, and error message. File name will not be used
 * if logged using this macro.
 */
#define OMLogWithOutF(fmt, ...)  NSLog((@"%s[Line #:%d]: " fmt), \
                                       __PRETTY_FUNCTION__, __LINE__, \
                                       ##__VA_ARGS__);

/*
 * Macro for logging error message with file name, function name, line #,
 * error domain, error code, and error message.
 */
#define OMLogWithF(fmt, ...) NSLog((@"%s:%s[Line #:%d]: " fmt), __FILE__, \
                                   __PRETTY_FUNCTION__, __LINE__, \
                                   ##__VA_ARGS__);

/*
 * All functions will be using OMLog to log message. OMLog is defined to use
 * OMLogWithF - Log with file name, function name, line #, and message.
 */
#define OMLog   OMLogWithOutF


/*
 * Macro for logging error message with file name, function name, line #,
 * error domain, error code, and error message
 */
#define OMLogError(err)  NSLog(@"%s:%s[Line #:%d]: Error %@-%05ld:%@", __FILE__,\
                                          __PRETTY_FUNCTION__, __LINE__,  \
                                         [(err) domain], (long)[(err) code], \
                                         [(err) localizedDescription] );


///////////////////////////////////////////////////////////////////////////////
// DEVICE HEIGHT AND WIDTH
///////////////////////////////////////////////////////////////////////////////
#define omScreenWidth  [[UIScreen mainScreen] bounds].size.width
#define omScreenHeight [[UIScreen mainScreen] bounds].size.height
///////////////////////////////////////////////////////////////////////////////
// DEVICE FINGERPRINTING OR IDENTITY CONTEXT RELATED DEFINITIONS
///////////////////////////////////////////////////////////////////////////////
#define OM_NEXT_AUTH_STEP_NONE                       0
#define OM_NEXT_AUTH_STEP_AUTH_FAILED                1
#define OM_NEXT_AUTH_STEP_DEVICE_REGISTRATION        2
#define OM_NEXT_AUTH_STEP_REST                       3
#define OM_NEXT_AUTH_STEP_KBAAUTH                    4
#define OM_NEXT_AUTH_STEP_AUTHSCHEME                 5
#define OM_NEXT_REG_STEP_NONE                        6
#define OM_NEXT_AUTH_STEP_CLIENTAPP_REG              7
#define OM_NEXT_AUTH_STEP_RP_AUTH                    8
#define OM_NEXT_POSTAUTH_STEP_KBAAUTH                9

#define OM_HTTP_STATUS_OK                          200
#define OM_HTTP_STATUS_CREATED                     201
#define OM_HTTP_STATUS_AUTH_DENIED                 401

///////////////////////////////////////////////////////////////////////////////
// DEVICE FINGERPRINTING OR IDENTITY CONTEXT RELATED DEFINITIONS
///////////////////////////////////////////////////////////////////////////////
// Version Properties
extern NSString *const OM_CLIENT;
extern NSString *const OM_CLIENT_SDK_NAME;
extern NSString *const OM_CLIENT_SDK_NAME_VALUE;
extern NSString *const OM_CLIENT_SDK_VERSION;
extern NSString *const OM_CLIENT_SDK_VERSION_VALUE;
extern NSString *const OM_KEY_APP_NAME;
extern NSString *const OM_KEY_APP_VERSION;

// Operationg System Properties
extern NSString *const OM_OPERATINGSYSTEM;
extern NSString *const OM_OS_TYPE;
extern NSString *const OM_OS_VERSION;

// Device System Properties
extern NSString *const OM_DEVICE;
extern NSString *const OM_DEVICE_UNIQUE_ID;
extern NSString *const OM_DEVICE_NAME;
extern NSString *const OM_DEVICE_MODEL;
extern NSString *const OM_DEVICE_LOCALIZED_MODEL;
extern NSString *const OM_DEVICE_ORIENTAION;

// Hardware Properties
extern NSString *const OM_HARDWARE;
extern NSString *const OM_HARDWARE_PAGE_SIZE;
extern NSString *const OM_HARDWARE_PHYSICAL_MEMORY;
extern NSString *const OM_HARDWARE_CPU_FREQ;
extern NSString *const OM_HARDWARE_BUS_FREQ;
extern NSString *const OM_HARDWARE_SYSTEM;
extern NSString *const OM_HARDWARE_NODE;
extern NSString *const OM_HARDWARE_RELEASE;
extern NSString *const OM_HARDWARE_VERSION;
extern NSString *const OM_HARDWARE_MACHINE;

// Network Properties
extern NSString *const OM_NETWORK;
extern NSString *const OM_IP_ADDRESS;
extern NSString *const OM_MACADDR;

// Locale Properties
extern NSString *const OM_LOCALE;
extern NSString *const OM_LOCALE_NAME;
extern NSString *const OM_LANGUAGE_CODE;
extern NSString *const OM_COUNTRY_CODE;
extern NSString *const OM_LOCALE_MEASUREMENT;
extern NSString *const OM_CURRENCY_SYMBOL;
extern NSString *const OM_CURRENCY_CODE;

// Location Properties
extern NSString *const OM_GEOLOCATION;
extern NSString *const OM_LONGITUDE;
extern NSString *const OM_LATITUDE;

//Device Properties
extern NSString *const OM_HARDWAREIDS;
extern NSString *const OM_IMEI;
extern NSString *const OM_PHONENUM;
extern NSString *const OM_ISJAILBROKEN;
extern NSString *const OM_NETWORKTYPE;
extern NSString *const OM_PHONECARRIER_NAME;
extern NSString *const OM_ISVPNENABLED;
extern NSString *const OM_FINGERPRINT;

// GENERIC DEFINITIONS USED ACROSS IDM MOBILE SDK
extern NSString *const OM_KBA;
extern NSString *const OM_CHALLENGE_TYPE;
extern NSString *const OM_KBA_ANSWER_STR;
extern NSString *const OM_KBA_QUESTION;
extern NSString *const OM_OIC_REST_AUTHN;
extern NSString *const OM_OIC_REST_AUTHENTICATION;
extern NSString *const OM_REST_AUTHENTICATION;
extern NSString *const OM_REST_AUTHN;
extern NSString *const OM_DEVICE_AUTHENTICATION;
extern NSString *const OM_KBA_AUTHENTICATION;
extern NSString *const OM_SSO_AUTHENTICATION;
extern NSString *const OM_RP_AUTHENTICATION;
extern NSString *const OM_CLIENT_APP_REGISTRATION;
extern NSString *const OM_AUTH_MANAGER_VIEW_LOADED;
extern NSString *const OM_AUTH_MANAGER_VIEW_UNLOADED;
extern NSString *const OM_USERNAME;
extern NSString *const OM_PASSWORD;
extern NSString *const OM_IDENTITY_DOMAIN;

extern NSString *const OM_ERROR_DOMAIN_NAME;
extern NSString *const OM_CONTENT_TYPE;
extern NSString *const OM_APP_JSON;
extern NSString *const OM_TOKEN;
extern NSString *const OM_AUTHORIZATION;
extern NSString *const OM_USERCREDENTIAL;
extern NSString *const OM_CLIENTREGHANDLE;
extern NSString *const OM_USERTOKEN;
extern NSString *const OM_REST_SUBJECT_USER;
extern NSString *const OM_REST_SUBJECT_PASS;
extern NSString *const OM_REST_SUBJECT;
extern NSString *const OM_REST_TOKEN_TO_CREATE;
extern NSString *const OM_REST_AUTH;
extern NSString *const OM_REST_TOKEN_VALUE;
extern NSString *const OM_REST_SUBJECT_TYPE;
extern NSString *const OM_REST_SUBJECT_VALUE;
extern NSString *const OM_REST_TOKEN_TYPE;
extern NSString *const OM_SERVICE_DOMAIN;
extern NSString *const OM_REST_APP_CTX;
extern NSString *const OM_REST_APP_URL;
extern NSString *const OM_ROLE_NAME;
extern NSString *const OM_USER_UNIQUE_NAME;
extern NSString *const OM_CREATE_ROLE_ATTRS;
extern NSString *const OM_CREATE_ROLE_VALS;
extern NSString *const OM_SEARCH_URL;
extern NSString *const OM_SEARCH_FILTER;
extern NSString *const OM_SEARCH_FILTER_VALS;
extern NSString *const OM_AUTHENTICATION_REQUEST;
extern NSString *const OM_INVOKING_THREAD;
extern NSString *const OM_SEARCH_PARAMS;
extern NSString *const OM_SEARCH_ATTRS_FETCH;
extern NSString *const OM_HTML;
extern NSString *const OM_CONNECTION_ISSUE;
extern NSString *const OM_OIC_ERROR_CODE;
extern NSString *const OM_OIC_ERROR_MSG;
extern NSString *const OM_CONNECTION_PROB;
extern NSString *const OM_JAILBREAK_POLICY;
extern NSString *const OM_CONTENT_TYPE;
extern NSString *const OM_APP_JSON;
extern NSString *const OM_USERCREDENTIAL;
extern NSString *const OM_CLIENTREGHANDLE;
extern NSString *const OM_USERTOKEN;
extern NSString *const OM_CLIENT_ID;
extern NSString *const OM_HANDLES;
extern NSString *const OM_CREATION_DATE;
extern NSString *const OM_VALUE;
extern NSString *const OM_EXPIRY;
extern NSString *const OM_APP_PROFILE;
extern NSString *const OM_CONTENT_TYPE;
extern NSString *const OM_APP_JSON;
extern NSString *const OM_CLIENT;
extern NSString *const OM_OPERATINGSYSTEM;
extern NSString *const OM_DEVICE;
extern NSString *const OM_DEVICE_PROFILE;
extern NSString *const OM_APP_CONFIG;
extern NSString *const OM_URL_REQUIRED;
extern NSString *const OM_URL_ISSUE;

extern NSString *const OM_AUTHENTICATION_SCHEME;
extern NSString *const OM_MOBILE_AUTH_STYLE;
extern NSString *const OM_RESTAUTHENTICATION;
extern NSString *const OM_REGISTRATIONSERVICE;
extern NSString *const OM_USERAUTHSERVICE;
extern NSString *const OM_USERPROFILESERVICE;
extern NSString *const OM_USERACCESSSERVICE;
extern NSString *const OM_DELETESERVICE;
extern NSString *const OM_VALIDATESERVICE;
extern NSString *const OM_RPLOGINPAGE;
extern NSString *const OM_RPAPPID;
extern NSString *const OM_RPWEBVIEW;
extern NSString *const OM_CONTENT_TYPE;
extern NSString *const OM_APP_JSON;
extern NSString *const OM_USERCREDENTIAL;
extern NSString *const OM_CLIENTREGHANDLE;
extern NSString *const OM_USERTOKEN;
extern NSString *const OM_USERPASSWORD;
extern NSString *const OM_OAMTOKEN;
extern NSString *const OM_USER_N_OAM_TOKEN;
extern NSString *const OM_OAMTOKEN_TYPE;
extern NSString *const OM_CLIENT_ID;
extern NSString *const OM_APPLICATION_ID;
extern NSString *const OM_SESSION_EXPIRY;
extern NSString *const OM_TOKENS;
extern NSString *const OM_OAM_ID;
extern NSString *const OM_OBSSOCOOKIE;
extern NSString *const OM_OAM11G;
extern NSString *const OM_APP_PROFILE_CONFIG;
extern NSString *const OM_MOBILE_APP_CONFIG;
extern NSString *const OM_REQUIRED;
extern NSString *const OM_HEADER;
extern NSString *const OM_STATUS;
extern NSString *const OM_STATUS_DENIED;
extern NSString *const OM_REQUIRE_KBA;
extern NSString *const OM_KBA_QUESTIONS;
extern NSString *const OM_KBA_HANDLE;
extern NSString *const OM_OLD_KBA_QUESTIONS;
extern NSString *const OM_CURRENT_KBA_QUESIONS;
extern NSString *const OM_KBA_QUESTION_STR;
extern NSString *const OM_MULTI_STEP_ANSWER;
extern NSString *const OM_KBA_QUESTION_ID;
extern NSString *const OM_ADDITIONAL_AUTH_ANSWER;
extern NSString *const OM_ADDITIONAL_AUTH_REQD;
extern NSString *const OM_OAAM_DEVICE_HANDLE;
extern NSString *const OM_OAAM_SESSION_HANDLE;
extern NSString *const OM_PROCESS_URL_RESPONSE;
extern NSString *const OM_RESPONSE_URL;
extern NSString *const OM_OICMOBILE_ASSERTION_TOKEN;
extern NSString *const OM_OICMOBILE_APP_REQUEST_ID;
extern NSString *const OM_PAYLOAD;
extern NSString *const OM_USERPROFILE;
extern NSString *const OM_MAIL;
extern NSString *const OM_EMAIL;
extern NSString *const OM_IOS_URL_SCHEME;
extern NSString *const OM_IOS_BUNDLE_ID;
extern NSString *const OM_HTTP_BASIC_AUTH_SCHEME;
extern NSString *const OM_HTTP_ERROR;
extern NSString *const OM_TOKENSLIST;
extern NSString *const OM_MOBILE_CRED_LEVEL_FOR_REG;
extern NSString *const OM_CLIENT_APP_ID;
extern NSString *const OM_MOBILE_SERVICE_AUTH;
extern NSString *const OM_SSO_CONFIG;
extern NSString *const OM_SSO_PRIORITY;
extern NSString *const OM_SSO_INCLUSION;
extern NSString *const OM_OAUTH_ACCESS_TOKEN;
extern NSString *const OM_ACCESS_TOKEN;
extern NSString *const OM_ACCESS_TOKEN_EXPIRY;
extern NSString *const OM_SERVICE_DOMAIN;
extern NSString *const OM_INTERNET_IDENTITY_AUTH;
extern NSString *const OM_CLAIM_ATTRIBUTES;
extern NSString *const OM_DETECTION_LOCATION;
extern NSString *const OM_FILE_PATH;
extern NSString *const OM_IS_REGISTERED;
extern NSString *const OM_SSO_REQUEST;
extern NSString *const OM_RESOURCE_URL;
extern NSString *const OM_RETURN_URL;
extern NSString *const OM_WIPE_OUT;
extern NSString *const OM_OIC_ERR_STR;
extern NSString *const OM_ACCESSTOKEN;
extern NSString *const OM_REQUEST_CTX;
extern NSString *const OM_WWW_AUTHENTICATE;
extern NSString *const OM_OAM_AUTH_REALM;
extern NSString *const OM_COOKIE;
extern NSString *const OM_REST_REQ_URL;
extern NSString *const OM_IS_JSON;
extern NSString *const OM_ERROR;
extern NSString *const OM_AUTHORIZATION_HEADER_VAL;
extern NSString *const OM_TOKEN_PROVIDER;

extern NSString *const OM_OAM_HOST_NAME;
extern NSString *const OM_OAM_PORT_NUMBER;
extern NSString *const OM_OAM_SERVICEDOMAIN_NAME;
extern NSString *const OM_OAM_HOST_PARAMETER;
extern NSString *const OM_OAM_PORT_PARAMETER;
extern NSString *const OM_OAM_SERVICEDOMAIN_PARAMETER;
extern NSString *const OM_OAM_PORT_IS_SSL;
extern NSString *const OM_OAM_SSL_PARAMETER;
extern NSString *const OM_APPLICATION_NAME;
extern NSString *const OM_APP_NAME_PARAMETER;
extern NSString *const OM_APP_OPEN_PARAMETER;

extern NSString *const OM_ALLOW_OFFLINE_AUTH;
extern NSString *const OM_LOCAL;
extern NSString *const OM_REMOTE;
extern NSString *const OM_AUTH_MODE;
extern NSString *const OM_OFFLINE_TOKEN_VALIDITY;
extern NSString *const OM_DEFAULT_OFFLINE_TOKEN_VALIDITY;

extern NSString *const OM_PROP_AUTHSERVER_TYPE;
extern NSString *const OM_PROP_AUTHSERVER_OAMMS;
extern NSString *const OM_PROP_OAMMS_HOST;
extern NSString *const OM_PROP_OAMMS_PORT;
extern NSString *const OM_PROP_OAMMS_PORT_IS_SSL;
extern NSString *const OM_PROP_OAMMS_URL;
extern NSString *const OM_PROP_OAMMS_SERVICE_DOMAIN;
extern NSString *const OM_PROP_APPNAME;
extern NSString *const OM_PROP_AUTHSERVER_HTTPBASIC;
extern NSString *const OM_PROP_OFFLINE_AUTH_ALLOWED;
extern NSString *const OM_PROP_LOGIN_URL;
extern NSString *const OM_PROP_LOGOUT_URL;
extern NSString *const OM_PROP_COLLECT_IDENTITY_DOMAIN;
extern NSString *const OM_PROP_IDENTITY_DOMAIN_NAME;
extern NSString *const OM_PROP_LOGIN_TIMEOUT_VALUE;
extern NSString *const OM_PROP_AUTH_KEY;
extern NSString *const OM_PROP_SESSION_TIMEOUT_VALUE;
extern NSString *const OM_PROP_IDLE_TIMEOUT_VALUE;
extern NSString *const OM_PROP_MAX_LOGIN_ATTEMPTS;
extern NSString *const OM_PROP_REQUIRED_TOKENS;
extern NSString *const OM_PROP_CRYPTO_SCHEME;
extern NSString *const OM_PROP_CRYPTO_PLAINTEXT;
extern NSString *const OM_PROP_CRYPTO_SHA1;
extern NSString *const OM_PROP_CRYPTO_SHA224;
extern NSString *const OM_PROP_CRYPTO_SHA256;
extern NSString *const OM_PROP_CRYPTO_SHA384;
extern NSString *const OM_PROP_CRYPTO_SHA512;
extern NSString *const OM_PROP_CRYPTO_SSHA1;
extern NSString *const OM_PROP_CRYPTO_SSHA224;
extern NSString *const OM_PROP_CRYPTO_SSHA256;
extern NSString *const OM_PROP_CRYPTO_SSHA384;
extern NSString *const OM_PROP_CRYPTO_SSHA512;
extern NSString *const OM_PROP_CRYPTO_AES;
extern NSString *const OM_PROP_LOCATION_UPDATE_DISTANCE_FILTER;
extern NSString *const OM_PROP_LOCATION_UPDATE_ENABLED;
extern NSString *const OM_PROP_AUTHSERVER_FEDERATED;
extern NSString *const OM_PROP_BROWSERMODE;
extern NSString *const OM_PROP_BROWSERMODE_EMBEDDED;
extern NSString *const OM_PROP_BROWSERMODE_EXTERNAL;
extern NSString *const OM_PROP_LOGIN_SUCCESS_URL;
extern NSString *const OM_PROP_LOGIN_FAILURE_URL;
extern NSString *const OM_FED_AUTH_USER_COOKIE_NAME;
extern NSString *const OM_PROP_USERNAME_PARAM_NAME;
extern NSString *const OM_PROP_LOGIN_VIEW_HTML_URL;
extern NSString *const OM_PROP_KBA_VIEW_HTML_URL;
extern NSString *const OM_OAUTH_AUTH_SCHEME;
extern NSString *const OM_PROP_OAUTH_OAUTH20_SERVER;
extern NSString *const OM_PROP_OAUTH_AUTHORIZATION_ENDPOINT;
extern NSString *const OM_PROP_OAUTH_TOKEN_ENDPOINT;
extern NSString *const OM_PROP_OAUTH_REVOKE_ENDPOINT;
extern NSString *const OM_PROP_OAUTH_AUTH_MODE;
extern NSString *const OM_PROP_OAUTH_REDIRECT_ENDPOINT;
extern NSString *const OM_PROP_OAUTH_CLIENT_ID;
extern NSString *const OM_PROP_OAUTH_CLIENT_SECRET;
extern NSString *const OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE;
extern NSString *const OM_OAUTH_AUTHORIZATION_CODE;
extern NSString *const OM_OAUTH_IMPLICIT;
extern NSString *const OM_PROP_OAUTH_SCOPE;
extern NSString *const OM_OAUTH_RESOURCE_OWNER;
extern NSString *const OM_OAUTH_CLIENT_CREDENTIALS;
extern NSString *const OM_OAUTH_ASSERTION;
extern NSString *const OM_OAUTH_OAM_CREDENTIAL;
extern NSString *const OM_PROP_LOGOUT_TIMEOUT_VALUE;
extern NSString *const OM_PROP_OAUTH_OAM_SERVICE_ENDPOINT;
extern NSString *const OM_PROP_OAUTH_ASSERTION_SAML2;
extern NSString *const OM_PROP_OAUTH_ASSERTION_JWT;
extern NSString *const OM_PROP_SESSION_ACTIVE_ON_RESTART;
extern NSString *const OM_PROP_OAUTH_INCLUDE_CLIENT_AUTH_HEADER;
extern NSString *const OM_PROP_OAUTH_CLIENT_ASSERTION_SAML2;
extern NSString *const OM_PROP_OAUTH_CLIENT_ASSERTION_JWT;
extern NSString *const OM_PROP_IDENTITY_DOMAIN_NAME_IN_HEADER;
extern NSString *const OM_PROP_IDENTITY_DOMAIN_HEADER_NAME;

extern NSString *const OM_PROP_CUSTOM_TOKENS;
extern NSString *const OM_PROP_CUSTOM_AUTH_HEADERS;

extern NSString *const OM_PROP_CONNECTIVITY_MODE;
extern NSString *const OM_CONNECTIVITY_AUTO;
extern NSString *const OM_CONNECTIVITY_OFFLINE ;
extern NSString *const OM_CONNECTIVITY_ONLINE;

extern NSString *const OM_CLIENT_CERT;
extern NSString *const OM_PROP_AUTHSERVER_CLIENT_CERT;
extern NSString *const OM_CLIENT_CERT_AUTH_SCHEME;
extern NSString *const OM_PROP_PRESENT_CLIENT_IDENTITY_ON_DEMAND;


///////////////////////////////////////////////////////////////////////////////
// Remember Credentials
///////////////////////////////////////////////////////////////////////////////
extern NSString *const OM_PROP_AUTO_LOGIN_ALLOWED; 
extern NSString *const OM_PROP_REMEMBER_CREDENTIALS_ALLOWED;
extern NSString *const OM_PROP_REMEMBER_USERNAME_ALLOWED;
extern NSString *const OM_AUTO_LOGIN_DEFAULT;
extern NSString *const OM_REMEMBER_CREDENTIALS_DEFAULT;
extern NSString *const OM_REMEMBER_USERNAME_DEFAULT;
extern NSString *const OM_REMEMBER_CRED_PREF_SET;
extern NSString *const OM_AUTO_LOGIN_PREF;
extern NSString *const OM_REMEMBER_CREDENTIALS_PREF;
extern NSString *const OM_REMEMBER_USERNAME_PREF;

///////////////////////////////////////////////////////////////////////////////
// KEYCHAIN DATA PROTECTION LEVELS
///////////////////////////////////////////////////////////////////////////////
extern NSString *const OM_PROP_KEYCHAIN_DATA_PROTECTION;
extern NSString *const OM_KEYCHAIN_DATA_ACCESSIBLE_WHEN_UNLOCKED;
extern NSString *const OM_KEYCHAIN_DATA_ACCESSIBLE_AFTER_FIRST_UNLOCK;
extern NSString *const OM_KEYCHAIN_DATA_ACCESSIBLE_ALWAYS;
extern NSString *const OM_KEYCHAIN_DATA_ACCESSIBLE_WHEN_UNLOCKED_THIS_DEVICE_ONLY;
extern NSString *const OM_KEYCHAIN_DATA_ACCESSIBLE_AFTER_FIRST_UNLOCK_THIS_DEVICE_ONLY;
extern NSString *const OM_KEYCHAIN_DATA_ACCESSIBLE_ALWAYS_THIS_DEVICE_ONLY;

///////////////////////////////////////////////////////////////////////////////
// End of OMDefinitions.h
///////////////////////////////////////////////////////////////////////////////

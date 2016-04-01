/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
   OMErrorCodes.h - Oracle Mobile Error Codes
 
 DESCRIPTION
   No class declaration. This file is only for defining error codes.
 
 RELATED DOCUMENTS
   None
 
 PROTOCOLS
   None
 
 EXAMPLES
   None
 
 NOTES
   None
 
 MODIFIED   (MM/DD/YY)
 asashiss    11/07/14 - Synced with internal OMErrorCodes.h
 msadasiv    11/20/12 - Bug 14836655 - set ksecattraccessible to a secure 
                                       by default value
 sativenk    11/06/12 - Bugs 14841041 and 14692298
 msadasiv    09/26/12 - OMCryptoService errors
 sativenk    10/03/12 - Creation
 */

///////////////////////////////////////////////////////////////////////////////
// Define all error codes here. It shall be of the format given below. Assign
// the error codes in sequence. Do not jump or start assign error codes in new
// series. Number of digits shall not exceed five digits. For each error code,
// make corresponding error message entry in resource bundle 
// OMLocalizable.strings file. Error look up key shall also be the same number
// but in string format. When you add string look up key in
// OMLocalizable.strings file, ensure that it is added in 5 digit format. For
// example, if you are error code is 7, resource bundle look-up key is "00007".
//
//      OMERR_ERROR_CODE_NAME                                          ERROR
//                                                                      CODE
//----- -------------------------------------------------------------- ----- --
///////////////////////////////////////////////////////////////////////////////
#define OMERR_SUCCESS                                                      0
#define OMERR_COULD_NOT_CONNECT_TO_SERVER                                  1
#define OMERR_OIC_SERVER_RETURNED_ERROR                                    2
#define OMERR_INVALID_URL                                                  3
#define OMERR_OIC_SERVER_URL_REQUIRED                                      4
#define OMERR_USER_CANCELLED_LOGIN_OPERATION                               5
#define OMERR_DEVICE_IS_NOT_AUTHENTICATED                                  6
#define OMERR_AUTHN_SERVICE_CLASS_NOT_FOUND                                7
#define OMERR_NO_AUTHENTICATION_SCHEME                                     8
#define OMERR_DEVICE_REGISTRATION_FAILED                                   9
#define OMERR_USER_AUTHENTICATION_FAILED                                  10
#define OMERR_UNKNOWN_AUTHENTICATION_SCHEME                               11
#define OMERR_UNABLE_TO_OPEN_RP_AUTHENTICATION_URL                        12
#define OMERR_UNABLE_TO_OPEN_SSO_AUTHENTICATION_URL                       13
#define OMERR_NOT_AUTHORIZED_TO_PARTICIPATE_IN_SSO                        14
#define OMERR_INVALID_APP_PROFILE                                         15
#define OMERR_USER_DENIED_ACCESS_TO_LOCATION_UPDATE                       16
#define OMERR_PRESENTER_VIEW_CONTROLLER_IS_NIL                            17
#define OMERR_INVALID_REQUEST                                             18
#define OMERR_USER_IS_NOT_AUTHENTICATED                                   19
#define OMERR_ACCESS_TOKEN_ERROR                                          20
#define OMERR_SETUP_NOT_INVOKED                                           21
#define OMERR_KEY_IS_NIL                                                  22
#define OMERR_INVALID_INPUT                                               23

///////////////////////////////////////////////////////////////////////////////
// OMCryptoService Messages
///////////////////////////////////////////////////////////////////////////////
#define OMERR_MEMORY_ALLOCATION_FAILURE                                   24
#define OMERR_RANDOM_GENERATOR_SYSTEM_ERROR                               25
#define OMERR_REQUESTED_LENGTH_TOO_SHORT                                  26
#define OMERR_INPUT_TEXT_CANNOT_BE_EMPTY                                  27
#define OMERR_UNKNOWN_OR_UNSUPPORTED_ALGORITHM                            28
#define OMERR_KEY_CANNOT_BE_EMPTY                                         29
#define OMERR_KEY_SIZE_NOT_SUPPORTED_BY_ALGORITHM                         30
#define OMERR_IV_LENGTH_MUST_MATCH_ALGORITHM_BLOCK_SIZE                   31
#define OMERR_PADDING_REQUIRED                                            32
#define OMERR_UNKNOWN_OR_UNSUPPORTED_PADDING                              33
#define OMERR_ENCRYPTION_SYSTEM_ERROR                                     34
#define OMERR_REQUESTED_LENGTH_NOT_A_MULTIPLE_OF_4                        35
#define OMERR_SALT_REQUIRED_FOR_CHOSEN_ALGORITHM                          36
#define OMERR_SALT_NOT_SUPPORTED_FOR_CHOSEN_ALGORITHM                     37
#define OMERR_CANNOT_PREFIX_SALT_IN_NON_SALTED_ALGORITHM                  38
#define OMERR_INPUT_NOT_PREFIXED_WITH_ALGORITHM_NAME                      39
#define OMERR_INPUT_MUST_BE_NSSTRING_WHEN_BASE64_IS_ENABLED               40
#define OMERR_UNKNOWN_INPUT_TYPE                                          41
#define OMERR_INPUT_LENGTH_MUST_BE_LESS_THAN_OR_EQUAL_TO                  42
#define OMERR_KEYPAIR_GENERATION_SYSTEM_ERROR                             43
#define OMERR_TAG_REQUIRED_TO_IDENTIFY_KEY_IN_KEYCHAIN                    44
#define OMERR_KEYCHAIN_SYSTEM_ERROR                                       45
#define OMERR_KEYCHAIN_ITEM_NOT_FOUND                                     46
#define OMERR_SIGNING_SYSTEM_ERROR                                        47
#define OMERR_INPUT_SIGN_CANNOT_BE_EMPTY                                  48
#define OMERR_VERIFICATION_SYSTEM_ERROR                                   49
#define OMERR_DECRYPTION_SYSTEM_ERROR                                     50
#define OMERR_KEYCHAIN_ITEM_ALREADY_FOUND                                 51
#define OMERR_UNKNOWN_OR_UNSUPPORTED_KEY_TYPE                             52
#define OMERR_INVALID_KEYCHAIN_DATA_PROTECTION_LEVEL                      53

#define OMERR_INVALID_CREDENTIALS                                        100
#define OMERR_USER_NOT_AUTHORIZED                                        101
#define OMERR_LOGIN_URL_IS_INVALID                                       102
#define OMERR_OFFLINE_LOCAL_AUTH_NOT_ALLOWED                             103
#define OMERR_SSO_NOT_ALLOWED                                            104
#define OMERR_EXTERNAL_BROWSER_NOT_SUPPORTED                             105
#define OMERR_HTML_ERROR                                                 106
#define OMERR_LOGOUT_IS_IN_PROGRESS                                      107
#define OMERR_OAUTH_INVALID_REQUEST                                      108
#define OMERR_OAUTH_UNAUTHORIZED_CLIENT                                  109
#define OMERR_OAUTH_ACCESS_DENIED                                        110
#define OMERR_OAUTH_UNSUPPORTED_RESPONSE_TYPE                            111
#define OMERR_OAUTH_INVALID_SCOPE                                        112
#define OMERR_OAUTH_SERVER_ERROR                                         113
#define OMERR_OAUTH_TEMPORARILY_UNAVAILABLE                              114
#define OMERR_OAUTH_OTHER_ERROR                                          115
#define OMERR_AUTHENTICATION_IS_IN_PROGRESS                              116
#define OMERR_OAUTH_INVALID_TOKEN_ENDPOINT                               117
#define OMERR_OAUTH_BAD_REQUEST                                          118
#define OMERR_EMPTY_USERNAME                                             119
#define OMERR_AUTHENTICATION_TIMED_OUT                                   120

#define OMERR_RESOURCE_FILE_PATH                                         121
#define OMERR_EMPTY_IDENTITY_DOMAIN                                      122
#define OMERR_EMPTY_USERNAME_AND_IDENTITY_DOMAIN                         123
#define OMERR_USER_REJECTED_CERTIFICATE                                  124
#define OMERR_INVALID_USERNAME_PASSWORD_IDDOMAIN                         125

#define OMERR_INVALID_APP_RESPONSE                                       126
#define OMERR_INVALID_RP_RESPONSE                                        127
#define OMERR_EMPTY_USER_TOKEN                                           128
#define OMERR_EMPTY_REGISTRATION_HANDLE                                  129

#define OMERR_DENIED_ACTION                                              130
#define OMERR_WIPE_ACTION                                                131

#define OMERR_NOT_FOUND                                                  132
#define OMERR_UNSUPPORTED_URL                                            133
#define OMERR_NETWORK_UNAVAILABLE                                        134
#define OMERR_SERVER_UNREACHABLE                                         135
#define OMERR_SERVER_ERROR                                               136
#define OMERR_INVALID_LOGOUT_URL                                         137
#define OMERR_INVALID_PASSWORD                                           138
#define OMERR_NO_IDENTITY                                                139
#define OMERR_USER_CANCELLED_IMPORT                                      140
#define OMERR_OAUTH_GRANT_NOT_ALLOWED                                    141
#define OMERR_OAUTH_SERVER_SSO_NOT_SUPPORTED                             142
#define OMERR_OAUTH_CLIENT_ASSERTION_REVOKED                             143
///////////////////////////////////////////////////////////////////////////////
// End of OMErrorCodes.h
///////////////////////////////////////////////////////////////////////////////

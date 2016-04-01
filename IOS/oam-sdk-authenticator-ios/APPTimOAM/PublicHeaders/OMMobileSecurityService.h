/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
   OMMobileSecurityService.h - Mobile Security Service
 
 DESCRIPTION
   MobileSecurityService object that holds the details to perform authentication
   against OIC server
 
 RELATED DOCUMENTS
   None
 
 PROTOCOLS
   None
 
 EXAMPLES
   None
 
 NOTES
   None
 
 MODIFIED   (MM/DD/YY)
 vismishr    10/27/14 - updateCookies should add new cookies
 vismishr    01/20/14 - Added API to get and delete config dictionary
 asashiss    10/18/13 - Added parseConfigurationURL:persistInUserDefaults:
                        withKey:andFilters:
 asashiss    09/27/13 - Bug 17204663
 sativenk    06/06/13 - Bug 16907007
 sativenk    05/12/13 - Additional Initialization Methods
 vismishr    12/13/12 - Added Functions to process SSO request
 sativenk    04/02/12 - Added startAuthenticationProcess method
 sativenk    01/03/12 - Added header
 kerajago    10/02/11 - Creation
 */

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "OMUserRoleProfileService.h"
#import "OMAuthenticationContext.h"
#import "OMAuthenticationRequest.h"

/**
 @mainpage IDM Mobile SDK for iOS Platform
 
 IDMMobileSDK is a set of APIs to secure mobile application access using IDM
 products deployed in customer environment. This SDK is mainly for enterprises
 developing mobile applications. This framework provides in this release provides
 three major functionality
 1. Authentication APIs.
 2. Secure Storage APIs
 3. User and Role APIs
 
 This framework relies on Oracle Identity Connect functionality of Access
 Management server for authentication and user/role APIs. For secure storage,
 it relies on KeyChainItem.
 
 @section Links
 
 @li <a href="https://stbeehive.oracle.com/teamcollab/overview/Mobile+Development">Project home page</a>.
 @li Online version of the <a href="https://stbeehive.oracle.com/teamcollab/overview/Mobile+Development">API documentation</a>. 
 
 */

@protocol OMMobileServiceDelegate;
@class OMAuthenticationManager;
@class OMAuthenticationService;
@class OMMobileSecurityConfiguration;
@class OMCredentialStoreService;
@class OMCredentialStore;

/** 
 * The MobileSecurityService class is the top-level class which provides 
 * Security Service leveraging Oracle Identity Connect (OIC) server. The
 * mobile application initializes OMMobileSecurityService by passing the
 * OIC URL and a delegate to which asynchronous operation results shall be
 * sent. The delegate shall implement OMMobileServiceDelegate protocol to
 * receive the results.
 *
 * The application initializes OMMobileSecurityService by calling its
 * initWithURL: appName: domain: delegate: method. Right after that, the
 * application calls "setup" method to download the application profile from
 * OIC server. After the profile is downloaded, this object calls
 * delegate's didReceiveApplicationProfile. Thereafter the application calls
 * startAuthenticationProcess: method to start the authenticatin process.
 * 
 */
@interface OMMobileSecurityService : NSObject  
{
@private
    OMMobileSecurityConfiguration *_appProfileConfiguration;
    OMUserRoleProfileService      *_userRoleService;
    OMCredentialStoreService      *_credentialStoreService;
    OMCredentialStore             *_credStore;
    OMAuthenticationManager       *_authManager;
    NSMutableDictionary           *_cacheDict;
    NSString                      *_keyChainItemKey;
    OMAuthenticationService       *_authService;
    id<OMMobileServiceDelegate>    _delegate;
}

@property (nonatomic, readonly, retain) OMCredentialStoreService *credentialStoreService;
@property (nonatomic, readonly, assign) OMCredentialStore *credStore;
@property (nonatomic, readonly, retain) OMMobileSecurityConfiguration *appProfileConfiguration;
@property (nonatomic, readwrite, assign) id<OMMobileServiceDelegate> delegate;


/**
 * Returns MobileSecurityService object initialized using initialization
 * properties available in standard user defaults (NSUserDefaults) object
 * stored with key OM_PROP_NSUSERDEFAULTS_KEY (string constant name).
 * Configuration object returned for this key shall be NSDictionary object.
 * If there is no object with OM_PROP_NSUSERDEFAULTS_KEY key or if the returned
 * object is not NSDictionary or returned NSDictionary object does not have
 * all mandatory properties, initialization fails. Application using this
 * method to initialize shall make sure that they set delegate property after
 * successful initialization.
 *
 * @return OMMobileSecurityService object if initialization succeeds;
 *         nil otherwise
 */
- (id)init;

/**
 * Returns MobileSecurityService object initialized using initialization
 * properties available in standard user defaults (NSUserDefaults) object
 * stored with key name passed as parameter to this function.
 * Configuration object returned for this key shall be NSDictionary object.
 * If there is no object for the given key or if the returned object is not
 * NSDictionary object or returned NSDictionary object does not have all
 * mandatory properties, initialization fails. Application using this method
 * to initialize shall make sure that they set delegate property after
 * successful initialization.
 *
 * @return OMMobileSecurityService object if initialization succeeds;
 *         nil otherwise
 */
- (id)initWithPropertiesAvailableInNSUserDefaultsWithKey: (NSString *)key;

/**
 * Returns MobileSecurityService object initialized using initialization
 * properties available in standard user defaults (NSUserDefaults) object
 * stored with key key OM_PROP_NSUSERDEFAULTS_KEY (string constant name).
 * Configuration object returned for this key shall be NSDictionary object.
 * If there is no object with OM_PROP_NSUSERDEFAULTS_KEY key or if the returned
 * object is not NSDictionary or returned NSDictionary object does not have
 * all mandatory properties, initialization fails.
 *
 * @param  delegate  Object that implements OMMobileServiceDelegate protocol
 * @return OMMobileSecurityService object if initialization succeeds;
 *         nil otherwise
 */
- (id)initWithDelegate: (id<OMMobileServiceDelegate>) delegate;

/**
 * Returns a MobileSecurityService object initialized using the properties
 * set in dictionary.
 *
 *  @param properties - Dictionary containing properties required to
 *                      initialize OMMobileSecurityService
 *  @param delegate - Object that conforms to OMMobileServiceDelegate protocol
 *  @return OMMobileSecurityService object if initialization is successful
 */
- (id)initWithProperties: (NSDictionary *)properties
                delegate: (id<OMMobileServiceDelegate>) delegate;

/** 
 *  Returns a MobileSecurityService object initialized by passing OIC Server
 *  URL from where this API can down load consuming application's profile.
 *
 *  @param url OIC Server's URL
 *  
 *  @param applicationName Name of the application consuming this API
 *
 *  @param domain Domain name with which application is registered in OIC
 */
- (id)initWithURL:(NSURL *)url
          appName:(NSString *)applicationName 
           domain:(NSString *)domain
         delegate:(id<OMMobileServiceDelegate>) delegate;

/** 
 *   Returns a MobileSecurityService object initialized by passing 
 *   MobileSecurityConfiguration Instance and delegate
 *
 */
- (id)initWithAppProfileConfiguration:(OMMobileSecurityConfiguration *)appProfileConfiguration
                             delegate:(id<OMMobileServiceDelegate>)delegate;


/** 
 * Connects to OIC URL passed during initialization and downloads security 
 * policies and application profile. This also includes the list of service
 * endpoints that are required for connecting to other OIC services like 
 * authentication, authorization, user profiles etc.
 * 
 */
- (OMAsyncOpHandle *)setup;

/** 
 * Returns a UINavigationController object that needs to be presented by the
 * application using presentModalViewController method. Upon presenting the
 * view controller, it triggers the authentication.
 *
 * @param authenticationRequest used for customizating authentication request
 * @param delegate              Delegate to which authentication success /
 *                              failure details shall be passed to
 * @param error                 Returns error object if there is any error
 * @return Returns an instance of UINavigationController to be presented by
 *         the application as ModalViewController
 */
- (UINavigationController *)getAuthenticationViewController: (OMAuthenticationRequest *)authnRequest
                                                      error: (NSError **)error;

/** 
 * Returns a UINavigationController object that needs to be presented by the
 * application using presentModalViewController method. Upon presenting the
 * view controller, it triggers the registration. This method should be
 * used only by application that is going to act as an SSOAgent application
 *
 * @param applicationID         Client application ID which 
 * @param bundleID              iOS bundle ID of the client application
 * @param error                 Returns error object if there is any error
 * @return Returns an instance of UINavigationController to be presented by
 *         the application as ModalViewController
 */
- (UINavigationController *)getAuthenticationViewControllerForAppRegistration: (NSString *)applicationID 
                                                                  iOSBundleID:(NSString*)bundleID
                                                                        error: (NSError **)error;
/** 
 * Starts authentication process if the user is not already authenticated.  
 * This method uses the presenterViewController to display the view controller
 * that takes user's name and password. presenterViewContoller cannot be NULL.
 * If so, it returns error.
 *
 * @param authenticationRequest used for customizating authentication request
 * @return Returns error if the authentication request could not be started
 */
- (NSError *)startAuthenticationProcess: (OMAuthenticationRequest *)authnRequest
                presenterViewController: (UIViewController *)presenter;


/** 
 * Authenticates the user against given authentication method identified by 
 * request object with username and password provided. This method returns 
 * immediately after placing authentication request. Authenticaton success or 
 * failure status is returned through OMMobileServiceDelegate.
 *
 * @param userName     identifies User Name
 * @param userPassword identifies User password
 * @param request      OMAuthenticationRequest object that holds the user 
 *                     authentication URL, Logout URL, and session expiry 
 *                     details, and etc.
 */
-(void) authenticate:(NSString*)userName 
            password:(NSString*)userPassword 
   authenticationReq:(OMAuthenticationRequest*)request 
        credStoreKey:(NSString*)key;

/** 
 * Returns UserProfileService instance that can be used for managing Users & 
 * Roles through OIC server.
 *
 * @return UserProfileService instance
 */
- (OMUserRoleProfileService*)userRoleProfileService;

/**
 * Returns application ID
 *
 * @return applicationID sent by the app at the time of initialzing this
 *         application
 */
- (NSString *)applicationID;

/**
 * Returns domain name
 *
 * @return domain name sent by the app at the time of initialzing this
 *         application
 */
- (NSString *)domainName;

/**
 * Returns the default authentication scheme configured in Oracle Access
 * suite server for the mobile app.
 *
 * @return the default authentication scheme associated with the mobile app.
 */
- (NSString *)authenticationScheme;

/**
 * Returns the application profile associated with the mobile app.
 *
 * @return the application profile associated with the mobile app
 */
- (NSDictionary *)applicationProfile;

/**
 * Returns the authentication context, if it is available in cache or in
 * keychain item, and if it is valid. Otherwise, it returns nil.
 *
 * @return OMAuthenticationContext object
 */
- (OMAuthenticationContext *)authenticationContext: (BOOL)validateToken;

/**
 * Checks whether an application can participate in SSO or not
 * @return true, if application can participate in SSO. Otherwise returns
 *         false
 */
- (BOOL) canAppParticipateInSSO:(NSString*) appID iOSBundleID:(NSString*)bundleID;

/**
 * Logs out the user. Since there is no session concept in OIC server, log out
 * acutally clears the authentication handle stored in keychain item. However
 * device registration handle is not cleared from keychain item. If it has to
 * be cleared, the user has to pass TRUE to clearRegistrationHandle parameter
 *
 * @param clearRegistrationHandle - If TRUE is passed, registration handle is
 *                                  also cleared along with authentication
 *                                  token(s)/handle
 * @return error - Error object if there is any error during logout
 */
- (NSError*)logout: (BOOL)clearRegistrationHandle;

/**
 * Returns a symmetric encryption key
 * @return Returns key for symmetric encryption
 */
- (NSData *)symmetricEncryptionKey;

/**
 * Inspects the query parameters and determines whether this is a
 * SSO request from a native iOS application 
 *
 * @param queryParams - Query parameter name and values
 *
 * @return true if a native iOS app is requesting SSO flow
 */
- (BOOL) isNativeSSOFlow:(NSDictionary *)queryParams;

/**
 * @deprecated
 * This class method extracts query component from NSURL, and reads OAM
 * server settings from query string. The query string has to be of expected
 * format as shown below. 
 * dmv://xyz/?oamconfig=true&host=<host>&port=<port>&servicedomain=<servicedomain>&SSL=<TRUE/FALSE>
 * If the query string containts all components - oamconfig, host, port,
 * servicedomain, and SSL as given above, it stores OAM server settings 
 * in NSUserDefaults with following key
 *
 * OM_OAM_HOST_NAME for OAM server's host name
 * OM_OAM_PORT_NUMBER for OAM server's port number
 * OM_OAM_SERVICEDOMAIN_NAME for Service Domain Name
 * OM_OAM_PORT_IS_SSL for SSL setting
 *
 * Query string can optionally contain appname as shown below. If it is
 * available, it will be stored in NSUserDefaults with key OM_APPLICATION_NAME.
 * dmv://xyz/?oamconfig=true&host=<host>&port=<port>&servicedomain=<servicedomain>&SSL=<TRUE/FALSE>&appname=<Name>
 *
 * This utility method can be used by applications using IDM Mobile SDK to
 * store OAM settings. At the moment, OMMobileSecurityService does not
 * provide a init method that reads OAM server settings from NSUserDefaults
 * to initialize OMMobileSecurityService object. It may be added later.
 *
 * @param  url - NSURL object sent to the app using openURL method
 * @return TRUE if NSUserDefaultSettings is updated with server settings
 *         FALSE otherwise
 */
+ (BOOL)storeOAMServerSettingsInNSUserDefaults:(NSURL *)url;


/**
 * This class method extracts query component from NSURL, and reads
 * configuration settings from query string. It returns configuration settings
 * as NSDictionary object with parameter name as the key and parameter value as
 * value. Optionally it persists the information in NSUserDefaults. All
 * configuration properties are stored in NSUserDefaults as NSDictionary object
 * using key OM_PROP_NSUSERDEFAULTS_KEY (String constant) by default. The
 * application can choose to store using different key. The query string has
 * to be of format shown below (parameter and value shall be separated using
 * string "::="). This function does not trim trailing or preceding whitespace
 * characters both in parameter name and value. All URL parameters have to be
 * URL encoded using UTF8 Encoding. If URLs are not encoded, query parameters
 * will not be parsed correctly.
 *
 * <urlscheme>://[host][:port]/?<parameter1>::=<value1>&<parameter2>::=<value2>&...&<parameterN>::=<valueN>
 *
 * This function helps application consuming OAMMS SDK to get configuration
 * at runtime and store it in NSUserDefaults or in properties file. Information
 * persisted in NSUserDefaults or properties file can be used to initialize the
 * SDK. If the configuration is stored in NSUserDefaults, OAMMS SDK can be
 * initialized without passing any parameter using init or initWithDelegate
 * methods. If the configuration is stored in properties file, the application
 * has to read the properties file and pass NSDictionary object OAMMS SDK to
 * initialize it.
 * Refer to product documentation for valid parameter names and values.
 *
 * This function does not validate any configuration settings but SDK
 * initialization logic validates configuration settings.
 *
 * @param   configURL  NSURL object that contains configuration in query
 *                     parameters
 * @param   persist    Persists in NSUserDefaults if this parameter is TRUE
 * @param   key        Key name with which to store. If this parameter is nil,
 *                     it will be stored using OM_PROP_NSUSERDEFAULTS_KEY
 *                     key
 * @return  NSDictionary object containing configuration settings obtained from
 *          configuration URL. Returns nil if URL did not contain have query
 *          parameter or if query parameter format is invalid
 */
+ (NSDictionary *)parseConfigurationURL: (NSURL *)configURL
                  persistInUserDefaults: (BOOL)persist
                                withKey: (NSString *)key;
/*
 * This function is same as +parseConfigurationURL:persistInUserDefaults:withKey
 * but adds a filter on values that are to be returned to caller.
 *
 * @param   configURL  NSURL object that contains configuration in query
 *                     parameters
 * @param   persist    Persists in NSUserDefaults if this parameter is TRUE
 * @param   key        Key name with which to store. If this parameter is nil,
 *                     it will be stored using OM_PROP_NSUSERDEFAULTS_KEY
 *                     key
 * @param filters      A set which contins properties whose values should be 
 *                     returned to caller
 * @return  NSDictionary object containing configuration settings obtained from
 *          configuration URL. Returns nil if URL did not contain have query
 *          parameter or if query parameter format is invalid
 */
+ (NSDictionary *)parseConfigurationURL: (NSURL *)configURL
                  persistInUserDefaults: (BOOL)persist
                                withKey: (NSString *)key
                             andFilters:(NSSet *) filters;

/*
 * Retrieves stored config in NSUserDefaults for a given key.
 * If key is nil default key will be used.
 
 * @param key The key for which configuration has to be retrieved.
 * @return NSDictionary object containing configuration settings stored with the
 passed key
 */
+ (NSDictionary *)initializationConfigurationForKey:(NSString *)key;

/*
 * Deletes a configuration stored against the passed key.
 * If key is nil configuration stored with default key will be deleted.
 *
 * @param key The key for which configuration has to be retrieved.
 * @return TRUE if a configuration was stored with the passed key and was
 *         deleted. FALSE if no configuration was stored with teh passed key.
 */
+ (BOOL)deleteInitializationConfigurationForKey:(NSString *)key;

/**
 * Checks if the provided token is valid or not.
 * @param tokenValue - Token
 *
 * @return true if token is valid else false
 */
- (BOOL) isTokenValid:(NSString*) tokenValue;
/**
 * Returns the requested NSHTTPCookie
 *
 * @param cookieName - Name of the cookie to be retrieved
 * @param url - URL to be used while retrieving the cookie
 *
 * @return NSHTTPCookie object
 */
-(NSHTTPCookie*) getCookie:(NSString*)cookieName forURL:(NSURL*)url;

/**
 * Returns all cookies associated with a given URL
 *
 * @param theURL - Cookies applicable for this URL will be returned
 *                 If this is nil, all cookies in cookie store will be sent
 * @return An array of cookies whose URL matches given URL. If given URL is
 *         nil, all cookies are returned.
 */
- (NSArray *) getCookiesForURL: (NSURL *)theURL;

/**
 * Updates value of cookies in NSHTTPCookieStorage. If the cookie is not
 * present the passed cookie will be added as a new cookie.
 *
 * @param cookies     NSArray of NSHTTPCookie objects
 * @param url         URL to be used to store cookies. This is not the loginURL
 *                    for HTTP Basic, but the URL value of the cookie as set by
 *                    server
 * @return            TRUE if atleast one cookie was updated/added. FALSE if
 *                    error occured or no cookie was updated/added.
 
 */
- (BOOL)updateCookies:(NSArray*)cookies forURL:(NSURL*)url;

/**
 * Parses the incoming request URL and populates a dictionary with 
 * query parameter name and values
 *
 * @param url - Request URL
 * @param appID -- Identifier of the application which sent this request
 * 
 * @return NSDictionary object
 */
- (NSDictionary *) parseURL:(NSURL *) url fromApp:(NSString*)appBundleID;

/**
 * Inspects the query parameters and determines whether this is a 
 * SSO request
 *
 * @param queryParams - Query parameter name and values
 * 
 * @return true if SSO flow else false
 */
- (BOOL) isSSORequest:(NSDictionary *)queryParams;

/**
 * Creates a return URL to send control back to native app or browser app 
 * that requested SSO
 *
 * @param isValidForSSO - Param indicating whether a client app can participate in SSO
 * @param ssoType - Native to native SSO or Browser to Native SSO
 * @param queryParams - Query parameters sent by the application or browser
 * @param regHandles - Client Application registration handles
 * @param err - Error object if any
 * @return NSURL object to be opened
 */
- (NSURL *) createReturnURL:(BOOL)isValidForSSO 
                  nativeSSO:(BOOL)isNativeSSO
                inputParams:(NSDictionary *) queryParams
           clientRegHandles:(NSDictionary *)regHandles
                      error:(NSError*) err;
 
/**
 * Processes SSO authentication request coming from SSO agent
 *
 * @param queryParams - NSDictionary containing the SSO request parameters
 * @param presenter - UIViewController to present the login screen
 *
 * @return void 
 */
- (void)processSSORequest:(NSDictionary *)queryParams presenter:(UIViewController*)presenter;

/**
 * Registers Client App registration handle
 *
 * @param queryParams - NSDictionary containing the SSO request parameters
 * @param presenter - UIViewController to present the login screen
 *
 * @return void
 *
 */
- (void)doClientAppRegistration:(NSDictionary *)queryParams presenter:(UIViewController*)presenter;

/**
 * Returns whether a client registration handle is registered or not
 *
 * @param queryParams - NSDictionary containing the SSO request parameters
 *
 * @return TRUE if client registration handle is registered FALSE otherwise
 *
 */
- (BOOL)isClientApplicationRegistered:(NSDictionary *)queryParams;

/**
 * Sends the SSO request response back to the calling application
 *
 * @param handles - NSDictionary containing client registration handle if any
 * @param err - NSError containing any error that might have occured during authentiction
 * @param queryParams - NSDictionary containing the SSO request parameters
 *
 * @return void
 *
 */
- (void)sendSSOResponseWithHandles:(NSDictionary *)handles error:(NSError *)err params:(NSDictionary *)queryParams;

/**
 * Checks whether client application is registered or not. If not it starts the registration process and exits. Otherwise it sends response back to the calling application. 
 * @param queryParams - NSDictionary containing the SSO request parameters
 * @param presenter - UIViewController to present the login screen
 * @param err - NSError containing any error that might have occured during authentication
 *
 * @return void
 *
 */
- (void)completeSSORequest:(NSDictionary *)queryParams presenter:(UIViewController*)presenter error:(NSError *)err;

/**
 * This function is deprecated. Use
 *'(BOOL) areRegistrationHandlesValid' instead.
 */
- (BOOL)isRegistrationHandlesValid;

/**
 * Checks if registration handle is available in cache or in key chain item.
 * If it is available and is valid, it returns true. Otherwise, it returns
 * false.
 *
 * @return true if this object has valid handles; otherwise false
 */
- (BOOL)areRegistrationHandlesValid;

@end

/** 
 * The OMMobileServiceDelegate is the protocol that has to be implemented by
 * the delegate of OMMobileSecurityService. OMMobileSecurityService calls the
 * delegate's methods to pass the results of application profile download,
 * device registration, and user authentication operations.
 */
@protocol OMMobileServiceDelegate <NSObject>

@optional
/** 
 * Called when the application profile is downloaded from the server.
 *
 * @param applicationProfile NSDictionary object returned by Access
 *                           Suite Server
 * @param error              NSError object is returned if this SDK is unable 
 *                           to retrieve application profile from Access Server
 */

- (void)didReceiveApplicationProfile:(NSDictionary *)applicationProfile
                               error:(NSError *)error;

/** 
 * Called after the registration flow is complete. This method will be 
 * invoked for pure Native mobile application.
 *
 * @param registrationHandle Registration handles if client app registration is 
 *                           successful
 * @param loginError NSError object if authentication failed.
 */
-(void) didFinishRegistration:(NSDictionary *) registrationHandle 
                        error:(NSError *)loginError;

/**
 * Called after completing logout operation
 *
 * @param mobileSecurityService - Mobile Security Service that completed logout
 * @param error                 - Error object if logout operation has failed
 *                                It will be nil if logout operation is
 *                                successful
 *
 */
- (void) mobileSecurityService: (OMMobileSecurityService *)mobileSecurityService
               didFinishLogout: (NSError *)error;

/**
 * Called when the application profile is downloaded from the server.
 *
 * @param mobileSecurityService Mobile Security Service object that downloaded 
 *                              application profile
 * @param applicationProfile    NSDictionary object returned by Access
 *                              Suite Server
 * @param error                 NSError object is returned if this SDK is unable
 *                              to retrieve application profile from Access 
 *                              Server
 */
- (void)mobileSecurityService: (OMMobileSecurityService *)mobileSecurityService
 didReceiveApplicationProfile:(NSDictionary *)applicationProfile
                        error:(NSError *)error;
/**
 * Called after the registration flow is complete. This method will be
 * invoked for pure Native mobile application.
 *
 * @param mobileSecurityService Mobile Security object Service that completed 
 *                              registration flow
 * @param registrationHandle    Registration handles if client app registration
 *                              is successful
 * @param loginError NSError object if authentication failed.
 */
-(void) mobileSecurityService: (OMMobileSecurityService *)mobileSecurityService
        didFinishRegistration:(NSDictionary *) registrationHandle
                        error:(NSError*)loginError;
/**
 * OMMobileSecurityService returns OMAuthenticationContext object after
 * successful authentication through this delegate
 *
 * @param mobileSecurityService Mobile Security Service object that completed
 *                              registration flow
 * @param context OMAuthenticationContext having authentication details
 * @param error   NSError object is returned if authentication could not be
 *                performed
 */
- (void)mobileSecurityService: (OMMobileSecurityService *)mobileSecurityService
      didFinishAuthentication: (OMAuthenticationContext *)context
                        error: (NSError *)error;

@required
/** 
 * OMMobileSecurityService returns OMAuthenticationContext object after
 * successful authentication through this delegate
 *
 * @param context OMAuthenticationContext having authentication details
 * @param error   NSError object is returned if authentication could not be
 *                performed
 */
- (void)didFinishAuthentication: (OMAuthenticationContext *)context
                          error: (NSError *)error;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMMobileSecurityService.h
///////////////////////////////////////////////////////////////////////////////

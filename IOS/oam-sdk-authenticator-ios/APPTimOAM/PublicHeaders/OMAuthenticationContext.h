/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
   OMAuthenticationContext.h - Authentication Context Object
 
 DESCRIPTION
   Oracle Mobile Authentication Context object
 
 RELATED DOCUMENTS
   None
 
 PROTOCOLS
   None
 
 EXAMPLES
   None
 
 NOTES
   None
 
 MODIFIED   (MM/DD/YY)
 vismishr    08/04/14 - Changed name of isValid async API
 vismishr    07/31/14 - Async API for isValid
 vismishr    06/05/14 - Added API to return requested credentials
 vismishr    04/07/14 - Added online check option for isValid
 vismishr    12/12/13 - Added offline cred key property
 asashiss    12/05/13 - Bug 17470677
 vismishr    09/11/13 - Changed scope from NSArray to NSSet
 asashiss    08/21/13 - Added identity domain property
 sativenk    07/25/13 - Added visited hosts so that APEX apps can use them
 vismishr    02/03/13 - XbranchMerge vismishr_logout_merge from
                        st_ngam_11.1.2.1.0
 vismishr    01/29/13 - Moved logout to OMMobileSecurityService
 sativenk    01/03/12 - Added header
 kerajago    10/02/11 - Creation
 */


#import <Foundation/Foundation.h>

@protocol OMAuthenticationContextDelegate;
@class OMMobileSecurityService;
@class OMUserRoleProfileService;
@class OMAuthenticationRequest;
@class OMIdentityProvider;

/** 
 * OMAuthenticationContext instance contains the authenticated User session and
 * is returned to the application after the authentication flow is complete.
 * The mobile application calls OMMobileSecurityService's 
 * startAuthenticationProcess method to start the authentication. After
 * completing authentication, it calls its delegate's didFinishAuthentication
 * method to return OMAuthenticationContext object. The application can call
 * OMMobileSecurityService's authenticationContext to get the object any time
 * after successful authentication.
 * This class also provides mechanism to authorize the Resource URL by
 * retrieving access token for the URL.
 */
@interface OMAuthenticationContext : NSObject 
{
}


@property (nonatomic, readonly, retain) NSString *keyChainItem DEPRECATED_ATTRIBUTE;
@property (nonatomic, readonly, retain) NSString *applicationID;
@property (nonatomic, readonly, retain) NSString *credentialKey;
@property (nonatomic, readonly, retain) NSString *tokenValue;
@property (nonatomic, readonly, retain) NSString *authenticatedMode;
@property (nonatomic, readonly, retain) NSString *userName;
@property (nonatomic, readonly, retain) NSString *tokenProvider;
@property (nonatomic, readonly, retain) NSString *identityDomain;
@property (nonatomic, readonly, retain) NSDate   *sessionExpiryDate;
@property (nonatomic, readonly, retain) NSDate   *idleTimeExpiryDate;
@property (nonatomic, readonly, retain) NSArray  *registrationHandles;
@property (nonatomic, readonly, retain) NSMutableDictionary     *accessTokens;
@property (nonatomic, readonly, retain) OMAuthenticationRequest *authenticationRequest;
@property (nonatomic, readonly, retain) NSSet *visitedHosts;
@property (nonatomic) BOOL status;
@property (nonatomic) int expiryTimeInSeconds;
@property (nonatomic, retain) NSMutableArray *tokens;
@property (nonatomic, retain) OMIdentityProvider *identityProvider;
@property (nonatomic, readonly, retain) NSString *qualifiedUserName;
@property (nonatomic, retain) NSString *offlineCredentialKey;
@property (nonatomic, assign) id<OMAuthenticationContextDelegate> delegate;

/** 
 * Returns access token after authorizing the specified URL.
 * @return Access token scoped to the authorization URL.
 * @param authorizationURL The resource URL for which the access token is 
 * required.
 */
- (NSString*)authorizeURL:(NSString*)authorizationURL;

/** 
 * Returns if this AuthenticationContext is valid on the OIC Server end.
 * For example, the lifetime of user session could have expired or would have 
 * been deleted from the server.
 *
 * @return true if the user session is valid; false otherwise
 */
- (BOOL)isValid;

/**
 * Returns whether an authentication context is valid or not. Check will either
 * be local or online depending on the BOOL parameter passed
 * @param validateOnline BOOL value to tell whether to validate context online
 * @return true if the user session is valid; false otherwise
 */
- (BOOL)isValid:(BOOL)validateOnline;

/**
 * This is an asynchronous call which will return whether authentication context
 * is valid or not. It will check the validity of token online.
 */
- (void)checkValidityAsynchronously;

/**
 * Returns if a valid access token exists for specified scopes.
 *@return true if a valid access token exists; false otherwise
 *@param scopes List of scopes for which access token is required.
 *@param refresh Whether to refresh the access token if a valid refresh token
 *exists.
 */
- (BOOL)isValidForScopes:(NSSet *)scopes refreshExpiredToken:(BOOL)refresh;

/**
 * An asynchronous call to check if a valid access token exists for specified
 * scopes. If a refresh token is available then access token will be refresh
 * depending upon the passed parameters.
 *@return void
 *@param scopes List of scopes for which access token is required.
 *@param refresh Whether to refresh the access token if a valid refresh token
 *exists.
 */
- (void)checkValidityAsynchronouslyForScopes:(NSSet*)scopes
                     andRefreshExpiredTokens:(BOOL)refresh;

/**
 * Returns array of access token for specified scopes. To get all the available
 * access tokens pass only "*" in the scopes set.
 * @return Array of access token for specified scopes.
 * @param scopes List of scopes for which access token is required.
 */
- (NSArray *)tokensForScopes:(NSSet *)scopes;

/**
 * Returns credentials for the passed key.
 * @param keys Array of keys for which credential information is required
 * @return NSDictionary containing values against the passed keys
 */
- (NSDictionary *)credentialInformationForKeys:(NSArray *)keys;

/**
 * Sets the credentials passed in credInfo dictionary.
 * @param credInfo Dictionary containing credential information
 * @return void
 */
- (void)setCredentialInformation:(NSDictionary *)credInfo;

@end

@protocol OMAuthenticationContextDelegate <NSObject>

@optional
@optional
/** Called after checking validity of authentication context
 * @param authenticationContext OMAuthenticationContext object on which isValid
 *                              was invoked
 * @param valid TRUE if authentication context is valid, FALSE otherwise
 * @param mobileSecurityService OMMobileServiceSecurity object with which the
 *                              authentication context is tied.
 * @param error any error that occurs during valodation process
 */
- (void)authenticationContext:(OMAuthenticationContext *)authenticationContext
          didFinishValidation:(BOOL)valid
     forMobileSecurityService:(OMMobileSecurityService *)mobileSecurityService
                     andError:(NSError *)error;
@end
///////////////////////////////////////////////////////////////////////////////
// End of OMAuthenticationContext.h
///////////////////////////////////////////////////////////////////////////////

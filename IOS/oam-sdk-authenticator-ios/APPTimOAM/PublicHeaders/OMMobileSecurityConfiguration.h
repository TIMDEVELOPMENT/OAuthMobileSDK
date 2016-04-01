/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMMobileSecurityConfiguration.m - Oracle Mobile Security Configuration
 
 DESCRIPTION
 Mobile Security Configuration object
 
 RELATED DOCUMENTS
 None
 
 INHERITS FROM
 NSObject
 
 PROTOCOLS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 vismishr    03/24/12 - MAF Logout Enhancement
 sativenk    01/03/12 - Refactoring
 keragago    11/16/11 - Creation
 */

#import <Foundation/Foundation.h>

/**
 * OMMobileSecurityConfiguration object needs to be created and initialized by
 * the application requiring HTTP Basic authentication service. Then this
 * object can be used to initialize OMMobileSecurityService object.
 *
 * To use OIC SDK for iOS, you will have to initialize OMMobileSecurityService
 * object. OMMobileSecurityService can be initialized to provide HTTP Basic
 * Authentication support for which you will have to create this object and 
 * pass to to OMMobileSecurityService's init method. 
 
 * Alternatively you can initialize it to provide authentication against OIC
 * server. To do so, you can either create OMOICMobileSecurityConfiguration
 * object, which is derived from this object and pass it to OMMobileSecurityService
 * initializer method or you provide OIC server details to OMMobileSecurityService's
 * initializer method which takes care of creating OMOICMobileSecurityConfiguration
 * and getting security settings.
 */
@interface OMMobileSecurityConfiguration : NSObject 
{
@private
    NSString             *_applicationID;
    int                   _maximumFailureAttempts;
}

/* Returns application name */
@property (nonatomic, readonly) NSString *applicationID;
/* Returns maximum login failure attempts */
@property (nonatomic, readonly) int maximumFailureAttempts;
/* Returns logoutTimeOut value */
@property (nonatomic, readonly) int logoutTimeOut;

/**
 * Initializer method for configuring OMMobileSecurityConfiguration for
 * HTTP Basic Authentication scheme.
 *
 * @param applicationID - name of the mobile application
 * @param maxFailureAttempts - Maximum number of login failure attempts
 * @param authenticationScheme - Authentication scheme. For HTTP Basic
 *                               authentication, pass OM_HTTP_BASIC_AUTH_SCHEME
 *
 * @return OMMobileSecurityConfiguration object
 */
- (id)initWithApplicationID: (NSString *)applicationID
         maxFailureAttempts: (int)maxFailureAttempts
       authenticationScheme: (NSString *)authenticationScheme;

/**
 * Returns URLScheme for an application given it's application ID.
 *
 * @param applicationID - name of the mobile application
 *
 * @return URLScheme of the given application
 */
- (NSString *)getURLSchemeforApplicationID:(NSString *)applicationID;

@end

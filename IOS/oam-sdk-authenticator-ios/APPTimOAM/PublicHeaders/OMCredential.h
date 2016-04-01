/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMCredential.h - Oracle Mobile Credential Object
 
 DESCRIPTION
 Credential object
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 sativenk    01/03/12 - Added header
 kerajago    10/02/11 - Creation
 */
#import <Foundation/Foundation.h>

/**
 * OMCredential object is used by the applications to pass user credentials
 * to OMCredentialStore to store in KeyChainItem. Also OMCredentialStore
 * returns OMCredential object, when the application retrieves the credentials
 * from KeyChainItem.
 */

@interface OMCredential : NSObject 
{
    NSString *_userName;
    NSString *_userPassword;
    NSString *_tenantName;
    NSDictionary *_properties;
}

@property (nonatomic, readonly, retain) NSString *userName;
@property (nonatomic, readonly, retain) NSString *userPassword;
@property (nonatomic, readonly, retain) NSString *tenantName;
@property (nonatomic, readonly, retain) NSDictionary *properties;

/**
 * Initializer method of OMCredential, which initializes
 * this object by taking username, password, tenantName
 * and custom user objects
 *
 * @param userName - Username
 * @param userPassword - Password for user
 * @param tenantName - Tenant name where the user belongs
 * @param properties - Custom user properties
 *
 * @return OMCredential object
 */
- (id) initWithUserName:(NSString*)userName 
               password:(NSString*)userPassword 
             tenantName:(NSString*)tenantName 
             properties:(NSDictionary *)properties;
@end

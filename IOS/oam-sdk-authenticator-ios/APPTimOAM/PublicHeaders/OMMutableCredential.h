/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMMutableCredential.h - Oracle Mobile Credential Object - Mutable Version
 
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
 sativenk    05/15/12 - Creation
 */


#import <Foundation/Foundation.h>
#import "OMCredential.h"

/**
 * OMMutableCredential class is mutable version of OMCredential. It is used by
 * the applications to pass user credentials to OMCredentialStore class to
 * store credentials in KeyChainItem.
 */
@interface OMMutableCredential : OMCredential
{
    
}

@property (nonatomic, readwrite, retain) NSString *userName;
@property (nonatomic, readwrite, retain) NSString *userPassword;
@property (nonatomic, readwrite, retain) NSString *tenantName;
@property (nonatomic, readwrite, retain) NSDictionary *userObjects;

/**
 * Initializes a newly allocated OMMutableCredential by placing credentials
 * contained in another given OMCredential object.
 *
 * @param credential - OMCredential whose credential has to be copied to the
 *                     new OMMutableCredential object
 *
 * @return OMMutableCredential object
 *
 */
- (id)initWithCredential: (OMCredential *)credential;

@end

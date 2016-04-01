/* Copyright (c) 2011, 2012, Oracle and/or its affiliates. 
All rights reserved. */

/*
 NAME
    OMCredentialStoreService.h - Oracle Mobile Credential Store Service
 
 DESCRIPTION
    Credential Store service that takes care of returning cred store
 
 RELATED DOCUMENTS
    None
 
 PROTOCOLS
    None
 
 EXAMPLES
    None
 
 NOTES
    None
 
 MODIFIED   (MM/DD/YY)
 msadasiv    11/20/12 - Bug 14836655 - set ksecattraccessible to a secure 
                                       by default value
 sativenk    01/03/12 - Added header
 kerajago    10/02/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMCredentialStore.h"

/**
 * OMCredentialStoreService is used to get OMCredentialStore object.
 */
@interface OMCredentialStoreService : NSObject 
{
@private
    OMCredentialStore *_credStore;    
}

@property (nonatomic, retain) OMCredentialStore *credStore;

/**
 * @brief Default protection level for keychain data entries
 *
 * Any keychain entry gets this protection level if not overrided by protection
 * parameter.
 * @param keychainDataProtection   String value of protection level.
 * @return                         Returns nil if keychainDataProtection provided
 *                                 is not valid.
 */
- (id)initWithDefaultKeychainDataProtection:(NSString *)keychainDataProtection;

@end

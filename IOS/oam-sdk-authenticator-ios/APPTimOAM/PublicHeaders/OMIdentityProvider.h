/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMIdentityProvider.h - Stores Relying Party Authentication Information
 
 DESCRIPTION
 Stores Relying Party Authentication Information
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS DEFINED
 None
 
 PROTOCOLS IMPLEMENTED
 NSCoding
 
 CATEGORIES/EXTENSIONS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 asashiss    09/16/13 - manually adding OMIdentityProvider in PublicHeaders
 asashiss    09/05/13 - Creation
 */

#import <Foundation/Foundation.h>

@class OMUser;

@interface OMIdentityProvider : NSObject<NSCoding>
{
@protected
    NSString    *_name;
    NSString    *_protocol;
    NSString    *_token;
    OMUser      *_user;
}
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *protocol;
@property (nonatomic, retain) NSString *token;
@property (nonatomic, retain) OMUser *user;

@end

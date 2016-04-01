/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMToken.h - Stores Tokens returned by server
 
 DESCRIPTION
 Stores Tokens
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS DEFINED
 None
 
 PROTOCOLS IMPLEMENTED
 
 CATEGORIES/EXTENSIONS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 vismishr    07/29/13 - Creation
 */

#import <Foundation/Foundation.h>

@interface OMToken : NSObject<NSCoding>
{
    NSString *_tokenName;
    NSString *_tokenValue;
    int _expiryTimeInSeconds;
}

@property (nonatomic, retain) NSString *tokenName;
@property (nonatomic, retain) NSString *tokenValue;
@property (nonatomic) int expiryTimeInSeconds;

@end

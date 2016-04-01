/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 NSDictionary+OMJSON.h - NSDictionary category
 
 DESCRIPTION
 NSDictionary category to support to/from JSON operations
 
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
 vismishr    06/26/14 - Creation
 */

#import <Foundation/Foundation.h>

@interface NSDictionary (OMJSON)

/**
 * Return JSON representation for NSDictionary
 * @return NSString JSON represntation for the calling NSDictionary object
 */
- (NSString *)toJSON;

/**
 * Return NSDictionary object for the passed json string
 * @param jsonString NSString object for which NSDictionary has to generated
 * @return NSString JSON represntation for the calling NSDictionary object
 */
+ (NSDictionary *)fromJSON:(NSString *)jsonString;

@end

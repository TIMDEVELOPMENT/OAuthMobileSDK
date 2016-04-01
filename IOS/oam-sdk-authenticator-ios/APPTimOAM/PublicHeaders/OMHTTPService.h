/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMHTTPService.h - Services HTTP requests
 
 DESCRIPTION
 Services HTTP requests
 
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
 vismishr    09/11/13 - Changed scope from NSArray to NSSet
 vismishr    07/29/13 - Creation
 */
#import "OMRESTRequest.h"

@interface OMHTTPService : OMRESTRequest


- (id)initWithMobileSecurityService: (OMMobileSecurityService *)mobileService
                           delegate: (id<OMRESTRequestDelegate>)delegate;

- (OMAsyncOpHandle *)executeRESTRequestAsynchronously: (NSMutableURLRequest *)request
                                            forScopes: (NSSet *)scopes
                                    convertDataToJSON: (BOOL)isJsonRepresentation;

@end

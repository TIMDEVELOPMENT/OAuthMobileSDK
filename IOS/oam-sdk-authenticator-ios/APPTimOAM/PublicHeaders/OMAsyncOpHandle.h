/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
    OMAsyncOpHandle.m - Oracle Mobile Async Operation Handler
 
 DESCRIPTION
    This class is the handle that will be returned to all async operations.
 
 RELATED DOCUMENTS
    None
 
 PROTOCOLS DEFINED
    None
 
 PROTOCOLS IMPLEMENTED
    None
 
 CATEGORIES/EXTENSIONS
    None
 
 EXAMPLES
    None
 
 NOTES
    None
 
 MODIFIED   (MM/DD/YY)
 vismishr    09/24/13 - Bug 17462120
 sativenk    01/03/12 - Creation
 */
#import <Foundation/Foundation.h>
#import "OMObject.h"

/**
 * All asychronous methods of IDM Mobile SDK return a OMAsyncOpHandle object
 * which can be used by the application to cancel the asynchronous operation.
 * The actual result of the asynchronous operation is returned through the
 * delegate.
 */
@interface OMAsyncOpHandle : NSObject 
{
@private
    NSInvocationOperation *_invocationOperation;
    NSMutableDictionary   *_dictionary;
    NSUInteger             _tag;
}

/**
 * Applications to set custom tag which can be used by the app when the
 * result is returned through delegate
 */
@property (nonatomic, readwrite) NSUInteger tag;

/**
 * Returns the result of the asynchronous operation. If the asynchronous
 * operation has returned any object, it returns the same. If the asynchronous
 * operation returns void or if it has been cancelled, it returns NSNull
 * object. If the operation is in progress, it returns nil.
 *
 * @return   The object returned by the asynchronous method or an NSValue
 *           object containing the return value if it is not an object. If the
 *           method or invocation is not finished executing, this method
 *           returns nil.
 *           If the method returned void then an NSNumber with value 0 will be
 *           returned
 *           If an exception was raised during the execution of the method or
 *           invocation, or if the operation was cancelled, it returns NSNull
 *           object.
 */
- (id)result;

/**
 * Places a request to cancel the asynchronous operation
 */
- (void)cancel;

/**
 * Returns true if the operation has cancelled
 */
- (BOOL)isCancelled;
 

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMAsyncOpHandle.h
///////////////////////////////////////////////////////////////////////////////

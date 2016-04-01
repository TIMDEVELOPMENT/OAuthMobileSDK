/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
  OMEntity.h - Oracle Mobile base object for Entity
 
 DESCRIPTION
   Oracle Mobile base object for Entity
 
 RELATED DOCUMENTS
   None
 
 PROTOCOLS
   EntityDelegate
 
 EXAMPLES
   None
 
 NOTES
   None
 
 MODIFIED   (MM/DD/YY)
 sativenk    05/12/12 - Change delegate to OMEntityDelegate
 sativenk    01/03/12 - Enhanced to used NSInvocationObject
 kerajago    06/13/11 - Creation
 */

#import <Foundation/Foundation.h>

@protocol OMEntityDelegate;
@class OMUser;

/**
 * OMEntity is the base class for OMUser and OMRole. OMUser object represents
 * the user. OMRole object represents the group or role. The delegate of
 * OMEntity, OMUser, OMRole have to implement OMEntityDelegate protocol to 
 * receive the results of asynchronous calls.
 * OMUser or OMRole objects are returned by OMUserManager or OMRoleManager
 * object.  OMRole objects or OMUser objects are returned from the Identity
 * Store associated with OAM server and service domain details passed at the
 * time of initalizing OMMobileSecurityService object.
 */
@interface OMEntity : NSObject 
{
@protected
    NSDictionary         *_entityDetails;
    id<OMEntityDelegate>  _delegate;
    NSUInteger            _tag;
}

@property (nonatomic, readwrite, retain) NSDictionary *entityDetails;
/**
 * Sets/gets the delegate of this object
 */
@property (nonatomic, readwrite, assign) id<OMEntityDelegate> delegate;
/**
 * Applications can set a tag for its own use
 */
@property (nonatomic, readwrite) NSUInteger tag;


/**
 * Returns the value of given attribute name
 *
 * @param attrName - Attribute name
 *
 * @return attribute value
 */
- (id)valueForAttribute:(NSString*) attrName;


@end
///////////////////////////////////////////////////////////////////////////////
// End of OMEntity.h
///////////////////////////////////////////////////////////////////////////////
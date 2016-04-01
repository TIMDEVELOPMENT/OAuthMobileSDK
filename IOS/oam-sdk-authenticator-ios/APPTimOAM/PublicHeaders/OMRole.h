/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMRole.h - Oracle Mobile Role object
 
 DESCRIPTION
 Oracle Mobile Role object
 
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
 kerajago    10/12/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMEntity.h"

/**
 * OMRole represents groups in the Identity store. When you search for roles
 * using OMRoleManager, OMRoleManager returns OMRole objects. Usually the 
 * developer does not instantiate OMRole object directly. The developer uses
 * OMRoleManager, which returs the roles from the Identity Store associated
 * with OAM server and service domain details passed at the time of initalizing
 * OMMobileSecurityService object.
 */
@interface OMRole : OMEntity 
{
@private
    NSArray *_roleMembers;
}

@property (nonatomic, readonly, retain) NSArray *roleMembers;

/**
 * Returns the role name
 *
 * @return role name
 */
- (id)roleName;

/**
 * Returns the role description
 *
 * @return role description
 */
- (id)roleDescription;

/**
 * Returns the role members as an array of OMUser objects. It fetches the
 * role member details asynchronously. The results are returned through
 * "didReceiveEntities: error: from: withAsynchronousHandle:" method of
 * id<OMEntityDelegate> delegate of this object.
 *
 * @return Handle to asynchronous request
 */
- (OMAsyncOpHandle *)getRoleMembersAsynchronously;

/**
 * Returns the role members as an array of OMUser objects. This is a synchronous
 * call. If the role members already cached, it returns it immediately.
 * Otherwise, it fetches from the identity store.
 *
 * @return Handle to asynchronous request
 */
- (NSArray *)getRoleMembers: (NSError **)error;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMRole.h
///////////////////////////////////////////////////////////////////////////////

/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMEntityManager.h - Oracle Mobile base object for Entity Manager
 
 DESCRIPTION
 Oracle Mobile base object for Entity
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS
 EntityManagerDelegate
 
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
#import "OMUser.h"
#import "OMAsyncOpHandle.h"

@protocol OMEntityDelegate;
@class OMEntity;
@class OMMobileSecurityService;

/**
 * OMEntityManager is the base object for OMUserManager and OMRoleManager.
 * OMUserManager allows the application to create/update/search/delete users.
 * OMRoleManager allows the application to create/update/search/delete Roles.
 *
 * To get OMUserManager or OMRoleManager object, you need to get
 * OMUserRoleProfileService object from OMMobileSecurityService object's
 * userRoleProfileService method or from userRoleService property. 
 * OMUserRoleProfileService returned by a OMMobileSecurityService object
 * will always fetch user and role details from the Identity Store associated
 * with OAM server and service domain details passed at the time of initalizing
 * OMMobileSecurityService object.
 */
@interface OMEntityManager : NSObject 
{
@protected
    OMMobileSecurityService    *_mobileSecurityService;
    NSString                   *_peopleServiceURL;
    NSOperationQueue           *_opQueue;
    id <OMEntityDelegate>       _delegate;
}

/**
 * Property to set/get the delegate of OMEntityManager
 */
@property (nonatomic, readwrite, assign) id<OMEntityDelegate> delegate;

@end

///////////////////////////////////////////////////////////////////////////////
// OMEntityDelegate
///////////////////////////////////////////////////////////////////////////////
/**
 * This protocol has to be implemented by the objects invoking asynchronous
 * operation of OMUserManager/OMRoleManager/OMUser/OMRole objects. These
 * object return their result through these protocol methods.
 */
@protocol OMEntityDelegate

/**
 * This protocol method is called by OMUserManager/OMRoleManager/OMUser/OMRole
 * objects to pass the result of asynchronous call. This method is called when
 * the result will be one or more OMUser or OMRole objects.
 *
 * @param entities    - The result object if the request is successful.
 *                      The result will be a NSArray object [An array of OMUser
 *                      or OMRole objects].
 * @param error       - Error object if the request has failed
 * @param omObject    - The object returning this result
 * @param asyncHandle - Asynchronous object handle that was returned while
 *                      initiating asynchronous request
 *
 * @return void
 */
- (void)didReceiveEntities: (id)entities
                     error: (NSError *)error
                      from: (id)omObject
    withAsynchronousHandle: (OMAsyncOpHandle *)asyncHandle;

/**
 * This protocol method is called by OMUserManager/OMRoleManager/OMUser/OMRole
 * objects to pass the result of asynchronous call. This method is called when
 * the asynchronous call does not return any object (OMUser/OMRole) but it 
 * returns success or failure notification. 
 *
 * @param error       - Error object if the request has failed; Nil is returned
 *                      if the asynchronous operation is successful
 * @param omObject    - The object returning this result
 * @param asyncHandle - Asynchronous object handle that was returned while
 *                      initiating asynchronous request
 *
 * @return void
 */
- (void)didFinishEntityOperation: (NSError *)error
                              by: (id)object
          withAsynchronousHandle: (OMAsyncOpHandle *)asyncHandle;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMEntityManager.h
//////////////////////////////////////////////////////////////////////////////
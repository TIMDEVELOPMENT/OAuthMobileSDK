/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMUserManager.h - Oracle Mobile Role Manager Object
 
 DESCRIPTION
 Oracle Mobile Role Manager Object
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS
 None
 
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
#import "OMEntityManager.h"

@class OMUser;

/**
 * OMUserManager allows the application to perform create/update/search/delete
 * operation on users.
 *
 * To get OMUserManager object, you need to get OMUserRoleProfileService object
 * from OMMobileSecurityService object's userRoleProfileService method or from
 * userRoleService property. OMUserManager operates on the users available in
 * Identity Store associated with OAM server and service domain passed to 
 * OMMobileSecurityService object.
 *
 * OMUserManager should not be directly instantiated by the application.
 */
@interface OMUserManager : OMEntityManager
{
}


/**
 * Searches for users with given filter. The caller will be blocked till the
 * server returns the results.
 *
 * @param filter - Search filter criteria
 * @param simpleSearch - Identifies whether to use "and" or "or" filter criteria
 * @param attributesToFetch - Attributes to be fetched
 * @param pageSize - Page size of the search
 * @param pagePosition - Page position
 * @param error - Returns error object if the search operation has failed
 *
 * @return Array of OMUser object, if the operation is successful.
 * 
 */
- (NSArray *)searchUsersWithFilter: (NSDictionary *)filter 
                    isSimpleSearch: (BOOL)simpleSearch 
             attributesToBeFetched: (NSArray *)attributesToFetch
                          pageSize: (NSInteger)pageSize 
                      pagePosition: (NSInteger)pagePosition
                             error: (NSError **)error;

/**
 * Searches for user with given filter asynchronously. The result is returned
 * through delegate's "didReceiveEntities: error: from: withAsynchronousHandle:"
 * method.
 *
 * @param filter - Search filter criteria
 * @param simpleSearch - Identifies whether to use "and" or "or" filter criteria
 * @param attributesToFetch - Attributes to be fetched
 * @param pageSize - Page size of the search
 * @param pagePosition - Page position
 *
 * @return Array of OMUser object, if the operation is successful.
 * 
 */
- (OMAsyncOpHandle *)searchUsersAsynchronouslyWithFilter:(NSDictionary *)filter 
                                          isSimpleSearch:(BOOL)simpleSearch 
                                   attributesToBeFetched:(NSArray *)attributesToFetch
                                                pageSize:(NSInteger)pageSize 
                                            pagePosition:(NSInteger)pagePosition;

/**
 * Searches for user using unique id of the user
 *
 * @param user - Unique id of the user
 * @param attributes - Attributes to be fetched
 * @param preFetch - Specifies whether it shall prefetch manager and reportee
 *                   details
 * @param error - Returns error if the request has failed
 *
 * @return Array of OMUser object, if the operation is successful.
 * 
 */
- (OMUser *)searchUser: (NSString *)user
            attributes: (NSArray *)attributes
        shouldPreFetch: (BOOL)preFetch
                 error: (NSError **)error;


/**
 * Searches for a given user's unique id asynchronously. It returns the OMUser
 * object delegate's "didReceiveEntities: error: from: withAsynchronousHandle:"
 * method.
 *
 * @param user       - Name of the user
 * @param attributes - Attributes to be fetched
 * @param preFetch   - Specifies whether it shall prefetch manager and reportee
 *                     details
 * @param error      - Returns error if the request has failed
 *
 * @return Array of OMUser object, if the operation is successful.
 * 
 */
- (OMAsyncOpHandle *)searchAsynchronouslyUser: (NSString*)user 
                                   attributes: (NSArray *)attributes
                               shouldPreFetch: (BOOL)preFetch;
/**
 * Deletes a user synchronously
 *
 * @param userName - Name of the user to be deleted
 *
 * @return Error object
 */
- (NSError *)deleteUser: (NSString *)userName;

/**
 * Deletes a user asynchronously. The result is returned through delegate's
 * "didFinishEntityOperation: by: withAsynchronousHandle:" method.
 *
 * @param userName - Unique id of the user to be deleted
 *
 * @return Handle to asynchronous object OMAsyncOpHandle
 * 
 */
- (OMAsyncOpHandle *)deleteAsynchronouslyUser:(NSString*)userName;

/**
 * Creates a given user synchronously
 *
 * @param attributes - Attribute name value pairs of the user to be created
 *
 * @return NSError object if the operation has failed
 * 
 */
- (NSError *)createUserWithAttributes: (NSDictionary *)attributes;

/**
 * Creates a given user asynchronously. The result is returned through
 * delegate's "didFinishEntityOperation: by: withAsynchronousHandle:" method.
 *
 * @param attributes - Attribute name value pairs of the user to be created
 *
 * @return Handle to asynchronous object OMAsyncOpHandle
 * 
 */
- (OMAsyncOpHandle *)createUserAsynchronouslyWithAttributes:(NSDictionary *)attributes;

/**
 * Modifies a given user asynchronously. The result is returned through
 * delegate's "didFinishEntityOperation: by: withAsynchronousHandle:" method.
 *
 * @param user - Unique id of the user to be modified
 * @param attributes - Attribute name value pairs to be modified
 *
 * @return Handle to asynchronous object OMAsyncOpHandle
 * 
 */
- (OMAsyncOpHandle *)modifyAsynchronouslyUser: (NSString*)user 
                                   attributes: (NSDictionary *)attributes;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMUserManager.h
///////////////////////////////////////////////////////////////////////////////
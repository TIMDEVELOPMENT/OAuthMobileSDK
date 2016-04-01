/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMRoleManager.h - Oracle Mobile Role Manager Object
 
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
 kerajago    10/12/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMEntityManager.h"

@class OMRole;
@class OMUser;

/**
 * OMRoleManager allows the application to perform create/update/search/delete
 * operation on Roles.
 *
 * To get OMRoleManager object, you need to get OMUserRoleProfileService object
 * from OMMobileSecurityService object's userRoleProfileService method or from
 * userRoleService property. OMRoleManager operates on the roles from the
 * Identity Store associated with OAM server and service domain passed to 
 * OMMobileSecurityService object.
 */
@interface OMRoleManager : OMEntityManager 
{
}

/**
 * @brief Returns a role
 *
 * Returns the role identified by roleName
 * @param roleName - Name of the role
 * @param Error    - Returns error if the operation has failed
 *
 * @return OMRole object if the operation is successful.
 */
- (OMRole *)getRoleByName: (NSString *)roleName
                    error: (NSError **)error;

/**
 * @brief Returns a role asynchronously
 *
 * Returns the role identified by roleName asynchronously. The result is
 * returned through its delegate's 
 * "didReceiveEntities: error: from: withAsynchronousHandle:" method.
 *
 * @param roleName - Name of the role
 * @param Error    - Returns error if the operation has failed
 *
 * @return OMRole object if the operation is successful.
 */
- (OMAsyncOpHandle *)getAsynchronouslyRoleByName: (NSString *)roleName;

/**
 * @brief Deletes a role
 *
 * Returns the role identified by roleName asynchronously. The result is
 * returned through its delegate's
 * "didReceiveEntities: error: from: withAsynchronousHandle:" method. 
 *
 * @param roleName - Name of the role to be deleted
 * @param Error    - Returns error if the operation has failed
 *
 * @return OMRole object if the operation is successful.
 */
- (NSError *)deleteRoleByName: (NSString *)roleName;

/**
 * @brief Deletes a role asynchronously
 *
 * Deletes the role identified by roleName asynchronously. The result is
 * returned through its delegate's 
 * "didFinishEntityOperation: by: withAsynchronousHandle:"
 *
 * @param roleName - Name of the role to be deleted
 *
 * @return handle of asynchronous operation object OMAsyncOpHandle
 */
- (OMAsyncOpHandle *)deleteAsynchronouslyRoleByName:(NSString*)name;

/**
 * @brief Gets the details of given user from the group
 *
 * Gets the details of given user from the group.
 *
 * @param userName - Name of the user
 * @param roleName - Name of the role
 * @param error    - Returns error if the operation has failed
 *
 * @return OMUser object, if the operation is successful
 */
- (OMUser *)getUserInfo: (NSString *)userName
               fromRole: (NSString *)roleName 
                  error: (NSError **)error;

/**
 * @brief Gets the details of given user from the group asynchronously
 *
 * Gets the details of given user from the group asynchronously. The result is
 * returned through its delegate's
 * "didReceiveEntities: error: from: withAsynchronousHandle:" method.
 *
 * @param userName - Name of the user
 * @param roleName - Name of the role
 *
 * @return OMUser object, if the operation is successful
 */
- (OMAsyncOpHandle *)getAsynchronouslyUserInfo:(NSString *)user 
                                      fromRole:(NSString *)roleName;

/**
 * @brief Removes a member from the role
 *
 * Removes a member from the role identified by roleName synchronously.
 *
 * @param memberName - Name of the member to be removed
 * @param roleName - Name of the role
 *
 * @return Error object if the operation is unsuccessful.
 */
- (NSError *)deleteMember: (NSString *)memberName 
                 fromRole: (NSString *)roleName;

/**
 * @brief Deletes a member from the role asynchronously
 *
 * Removes a member from the role identified by roleName asynchronously. The 
 * result is returned through its delegate's 
 * "didFinishEntityOperation: by: withAsynchronousHandle:"
 *
 * @param memberName - Name of the member to be removed
 * @param roleName - Name of the role
 *
 * @return Error object if the operation is unsuccessful.
 */
- (OMAsyncOpHandle *)deleteAsynchronouslyMember:(NSString *)memberName
                                       fromRole:(NSString*)roleName;

/**
 * @brief Creates a role asynchronously
 *
 * Creates a role asynchronously.
 *
 * @param attributes - Attributes of the role
 * @param values - Values of the attributes
 *
 * @return Handle to asynchronous operation OMAsyncOpHandle
 */
- (OMAsyncOpHandle *)createAsynchronouslyRoleWithAttributes:(NSDictionary *)attributes;

/**
 * @brief Modifies a role asynchronously
 *
 * Modifies the role asynchronously. The result is returned through its
 * delegate's "didFinishEntityOperation: by: withAsynchronousHandle:"
 *
 * @param roleName - Name of the role
 * @param attributes - Attributes of the role
 * @param values - Values of the attributes
 *
 * @return Handle to asynchronous operation OMAsyncOpHandle
 */
- (OMAsyncOpHandle *)modifyAsynchronouslyRole:(NSString*)role 
                                   attributes: (NSDictionary *)attributes;

/**
 * DO NOT DOCUMENT THIS AS THE API SIGNATURE DOES NOT SEEM TO BE CORRECT
 *
 * Adds a member to the role
 *
 */
- (OMAsyncOpHandle *)addUserAsynchronouslyToRole:(NSString *)roleName
                                  withAttributes:(NSDictionary*)attributes;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMRoleManager.h
///////////////////////////////////////////////////////////////////////////////

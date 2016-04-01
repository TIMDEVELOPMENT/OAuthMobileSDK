/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMUser.h - Oracle Mobile User object
 
 DESCRIPTION
 Oracle Mobile User object
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 vismishr    12/18/12 - Added API to fetch value of a given attribute
 sativenk    05/12/12 - Change delegate to OMEntityDelegate
 sativenk    01/03/12 - Enhanced to used NSInvocationObject
 kerajago    10/12/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMEntity.h"

@class OMAsyncOpHandle;

/**
 * OMUser represents users in the Identity store. When you search for users
 * using OMUserManager, OMUserManager returns OMUser objects. Usually the 
 * developer does not instantiate OMUser object directly. Instead the developer
 * uses OMUserManager, which returs the users from the Identity Store
 * associated with OAM server and service domain details passed at the time of
 * initalizing OMMobileSecurityService object.
 */
@interface OMUser : OMEntity 
{
@private
    NSArray *_reportees;
    OMUser  *_manager;
}

@property (nonatomic, readonly, retain) NSArray *reportees;

/**
 * Returns the first name of the user
 *
 * @return first name of the user
 */
- (id)firstName;

/**
 * Returns the last name of the user
 *
 * @return last name of the user
 */
- (id)lastName;

/**
 * Returns the mobile number of the user
 *
 * @return mobile number
 */
- (id)mobile;

/**
 * Returns the telephone number of the user
 *
 * @return User's work telephone number
 */
- (id)telephoneNumber;

/**
 * Returns the photo of the user
 *
 * @return User's photo
 */
- (id)photo;

/**
 * Returns the description property of the user
 *
 * @return description property
 */
- (id)description;

/**
 * Returns the display name of the user
 *
 * @return display name of the user
 */
- (id)displayName;

/**
 * Returns the email id of the user
 *
 * @return email id of the user
 */
- (id)mail;

/**
 * Returns the postal address of the user
 *
 * @return postal address
 */
- (id)postalAddress;

/**
 * Returns the title of the user
 *
 * @return the title of the user
 */
- (id)title;

/**
 * Returns the manager's URI
 *
 * @return Manager's REST URI
 */
- (id)managerURI;

/**
 * Returns the unique id of the user
 *
 * @return UID of the user
 */
- (id)uid;

/**
 * Returns the URI of user
 *
 * @return URI of the user
 */
- (id)uri;

/**
 * This method is same as calling getReportees. If there is an error while
 * returning reportees list, this method does not return the error. Hence
 * use getReporteesWithAttributes: returningError: method.
 *
 * @return reportees' list
 */
- (id)reports;

/**
 * Returns the country in which the user resides
 *
 * @return the country in which the user resides
 */
- (id)country;

/**
 * Returns the manager of the user. If the manager details are not prefetched
 * or not already cached, manager details are fetched from identity server and
 * returns the OMUser object having manager details. If the manager object is
 * already fetched, it immediately returns the object.
 *
 * @return OMUser object having manager details
 */
- (OMUser *)getManager: (NSError **)error;

/**
 * Returns the manager of the user through the delegate. If the manager details
 * are not prefetched or not already cached, manager details are fetched from
 * identity server in different thread and returns the OMUser object having
 * manager details through id<OMEntityDelegate> delegate's 
 * "didReceiveEntities: error: from: withAsynchronousHandle:" method.
 *
 * @return the handle to asynchronous request
 */
- (OMAsyncOpHandle *)getManagerAsynchronously;

/**
 * Returns the reportees list
 *
 * @return NSArray object containing OMUser objects containing reportees list
 */
- (NSArray *)getReporteesWithAttributes: (NSArray *)attributes 
                         returningError: (NSError **)error;

/**
 * Returns the list of employees reporting to this user through the delegate. 
 * If the list of reporting employees is not already fetched, reportees details
 * are fetched from identity server in different thread and returns an array of
 * OMUser object having reportees details through id<OMEntityDelegate>
 * delegate's "didReceiveEntities: error: from: withAsynchronousHandle:" method.
 *
 * @return handle to Asynchronous request
 */
- (OMAsyncOpHandle *)getReporteesAsynchronouslyWithAttributes:(NSArray *)attributes;

/**
 * Returns the attribute value given the attribute name. It fetches the value from the server if it is not pre-feched.
 * @param attrName - Name of the attribute whose value is required.
 * @param error - Any error that might have occured while fetching the attribute.
 *
 * @return value of the attribute
 */
- (id)getAttribute:(NSString *)attrName returningError:(NSError **)error;

/**
 * Fetches value of an attribte asynchronously.
 * @param attrName - Name of the attribute whose value is required.
 *
 * @return the handle to asynchronous request
 */
- (OMAsyncOpHandle *)getAttributeAsynchronously:(NSString *)attrName;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMUser.h
///////////////////////////////////////////////////////////////////////////////

/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMUserProfileService.h - Oracle Mobile User Profile Service object
 
 DESCRIPTION
 Oracle Mobile User Profile Role Service Object
 
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
 sativenk    01/03/12 - Refactoring
 kerajago    11/10/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMAuthenticationContext.h"
#import "OMUserManager.h"
#import "OMRoleManager.h"

/** 
 * The UserRoleProfileService class allows lookup & management of Users & Roles
 * using OIC REST service endpoint associated with this application. You can 
 * get reference to UserRoleProfileService from OMMobileSecurityService's
 * getUserRoleProfileService method. From this object, you can get handle to
 * OMUserManager to look up users or to perform CRUD operations on users.
 * You can also get handle to OMRoleManager to look up groups and to perform
 * CRUD operations on groups.
 */
@interface OMUserRoleProfileService : NSObject 
{
@private
    OMMobileSecurityService *_mobileSecurityService;
}

/**
 * Initializes OMUserRoleProfileService with mobileSecurityService object.
 */
- (id)initWithMobileSecurityService: (OMMobileSecurityService *)mobileSecurityService;

/**
 * Creates a new OMUserManager object initialized with delegate and returns
 * to the app to perform Create/Read/Update/Delete operations on the user objects.
 * 
 * @return OMUserManager object
 */
- (OMUserManager *)getUserManagerInitializedWithDelegate: (id<OMEntityDelegate>)delegate;

/**
 * Creates a new OMUserManager object and returns to the app to perform
 * Create/Read/Update/Delete operations on the user objects. The delegate
 * property has to be set by the calling application after getting this object.
 * 
 * @return OMUserManager object
 */
- (OMUserManager *)getUserManager;


/**
 * Creates a new OMRoleManager object initialized with delegate and returns
 * to the app to perform Create/Read/Update/Delete operations on the role objects.
 * 
 * @return OMRoleManager object
 */
- (OMRoleManager *)getRoleManagerInitializedWithDelegate: (id<OMEntityDelegate>)delegate;

/**
 * Creates a new OMRoleManager object and returns to the app to perform 
 * Create/Read/Update/Delete operations on the user objects. The delegate 
 * property has to be set by the calling application after getting this object.
 * 
 * @return OMUserManager object
 */
- (OMRoleManager *)getRoleManager;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMUserRoleProfileService.h
///////////////////////////////////////////////////////////////////////////////

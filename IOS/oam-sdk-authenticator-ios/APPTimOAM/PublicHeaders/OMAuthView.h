/* Copyright (c) 2012, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMAuthView.h - Oracle Mobile Authentication View
 
 DESCRIPTION
 Base View class to collect credentials
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS
 None
 
 CATEGORIES/EXTENSIONS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 asashiss    08/21/13 - Added viewLoaded method
                        Documentation Update : Accessing credentials and 
                        preference of Remember Credential
 sativenk    06/11/13 - Support to get login attempt count & error
 sativenk    03/10/13 - Federated Authentication Support Changes
                        Changed base class to UIView to conform to ADA
 sativenk    07/22/12 - Support for view customization
 cdonley     04/10/12 - Move to UIView from UIViewController
 sativenk    02/03/12 - Creation
 */

#import <UIKit/UIKit.h>

/**
 * OMAuthView serves as the base class for applications wanting to customize
 * login screen and Knowledge Based Authentication (KBA) screens.
 */
@interface OMAuthView : UIView
{
@private
    NSMutableDictionary             *_authData;
@protected
    NSString                        *_title;
    BOOL                             _showLoginButton;
    BOOL                             _showCancelButton;
    BOOL                             _showNavigationBar;
    BOOL                             _showNavigationToolBar;
}

/**
 * In case of Knowledge based authentication, authData will contain the
 * question for key OM_KBA_QUESTION_STR. This dictionary also needs to be
 * used by the custom view to fill credentials, when the SDK calls 
 * retrieveAuthData method of this object.
 */
@property (nonatomic, readwrite, assign) NSMutableDictionary *authData;
@property (nonatomic, readwrite, retain) NSString *title;
@property (nonatomic, readwrite) BOOL showLoginButton;
@property (nonatomic, readwrite) BOOL showCancelButton;
@property (nonatomic, readwrite) BOOL showNavigationBar;
@property (nonatomic, readwrite) BOOL showNavigationToolBar;
@property (nonatomic, readonly) NSUInteger loginAttemptCount;
@property (nonatomic, readonly, retain) NSError *loginError;

/**
 * This method will be invoked by SDK to get the credentials entered by the
 * user. This method will be invoked only when the custom view indicates to
 * the SDK that the user has entered authentication data by invoking
 * userEnteredAuthData method of this object. The custom view has to
 * populate user credentials and Remember Credential preferences in
 * NSMutableDictionary authData, which is a property of this object, using
 * following keys:
 *
 * User Name        - OM_USERNAME
 * Password         - OM_PASSWORD
 * Identity Domain  - OM_IDENTITY_DOMAIN
 * Auto Login Preference - OM_AUTO_LOGIN_PREF
 * Remember Credentials Preference - OM_REMEMBER_CREDENTIALS_PREF
 * Remember Username Preference - OM_REMEMBER_USERNAME_PREF
 * Answer to Knowledge Based Authentication Question - OM_KBA_ANSWER_STR
 * Answer to One Time Password - OM_KBA_ANSWER_STR
 */
- (NSDictionary *)retrieveAuthData;

/**
 * This method shall be invoked by the custom views implemented by the
 * application when the user completes entering credentials. This method shall
 * not be overridden in the custom view. Before invoking this method to
 * notify SDK that the user has entered credentials, it has to populate
 * user credentials and Remember Credential preferences in NSMutableDictionary
 * authData, which is a property of this object, using following keys:
 *
 * User Name        - OM_USERNAME
 * Password         - OM_PASSWORD
 * Identity Domain  - OM_IDENTITY_DOMAIN
 * Auto Login Preference - OM_AUTO_LOGIN_PREF
 * Remember Credentials Preference - OM_REMEMBER_CREDENTIALS_PREF
 * Remember Username Preference - OM_REMEMBER_USERNAME_PREF
 * Answer to Knowledge Based Authentication Question - OM_KBA_ANSWER_STR
 * Answer to One Time Password - OM_KBA_ANSWER_STR
 * Query parameter in case of Fed Auth - OM_QUERY_PARAMS
 * HTTP Header Fields in case of Fed Auth - OM_FED_AUTH_HEADERS
 */
- (void)userEnteredAuthData;

/**
 * This method shall be invoked by the custom views implemented by the
 * application when the usercompletes entering credentials. This method shall
 * not be overridden in the custom view.
 */
- (void)userCancelledAuthenticationOperation;

/**
 * If the application wants to add toolbar items to Navigation Tool Bar from
 * the application's custom view, they have to call this method to add the
 * same.
 */
- (void)setToolbarItems: (NSArray *)items animated: (BOOL)animated;

/**
 * When the view is loaded by super view/view controller, this method is
 * is invoked so that custom view can do its specific activities.
 * User credentials and Remember Credential preferences are populated in
 * NSMutableDicationary authData, which is a property of this object. To access
 * these values following keys should be used:
 *
 * User Name        - OM_USERNAME
 * Password         - OM_PASSWORD
 * Identity Domain  - OM_IDENTITY_DOMAIN
 * Auto Login Allowed - OM_PROP_AUTO_LOGIN_ALLOWED
 * Remember Credentials Allowed - OM_PROP_REMEMBER_CREDENTIALS_ALLOWED
 * Remember Username Allowed - OM_PROP_REMEMBER_USERNAME_ALLOWED
 * Auto Login Preference - OM_AUTO_LOGIN_PREF
 * Remember Credentials Preference - OM_REMEMBER_CREDENTIALS_PREF
 * Remember Username Preference - OM_REMEMBER_USERNAME_PREF
 */
- (void)viewLoaded;
@end

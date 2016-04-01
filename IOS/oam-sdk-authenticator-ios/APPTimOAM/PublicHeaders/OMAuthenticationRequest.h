/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
    OMAuthenticationRequest.h - Oracle Mobile Authentication Request
 
 DESCRIPTION
    Authentication Request object that can be sent by client to customize
    authentication
 
 RELATED DOCUMENTS
    None
 
 PROTOCOLS
    None
 
 EXAMPLES
    None
 
 NOTES
    None
 
 MODIFIED   (MM/DD/YY)
 vismishr    03/18/14 - MAF logout enhancement
 asashiss    11/26/13 - Manually numbered connectivity modes
 asashiss    09/12/13 - Moved OMConnectivityAuto to first postion in enumeration
 sativenk    05/21/13 - Support for progress view customization
 vijanaki    10/02/11 - Creation
 */


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class OMAuthView;
@class OMAuthProgressView;

/*!
 @enum       OMConnectivityMode
 @abstract   Authentication connectivity mode to determine if authentication
             happens by connecting to server or locally or a mix of both.
 
 @constant   OMConnectivityOnline  Always authenticate with the server
 @constant   OMConnectivityOffline Authenticate with locally cached credentials
                                   without connecting to server.
 @constant   OMConnectivityAuto    Authenticate with server if device is online
                                   Authenticate locally if device is offline.
*/
enum
{
    OMConnectivityAuto = 1,
    OMConnectivityOnline = 2,
    OMConnectivityOffline = 3,
};
typedef NSUInteger OMConnectivityMode;

@interface OMAuthenticationRequest : NSObject
{
    NSString             *_identityDomain;
    OMAuthView           *_authView;
    OMAuthView           *_kbaView;
    OMAuthProgressView   *_authProgressView;
    NSString             *_userName;
    NSString             *_password;
    NSDictionary         *_kbaAnswers;
    NSUInteger            _connectivityMode;
    NSURL                *_loginHTMLURL;
    NSURL                *_kbaHTMLURL;
    NSSet                *_oauthScope;
    int                  _logoutTimeOutValue;
}

@property (nonatomic, retain) NSString *identityDomain;
@property (nonatomic, retain) OMAuthView *authView;
@property (nonatomic, retain) OMAuthView *kbaView;
@property (nonatomic, retain) OMAuthProgressView *authProgressView;

@property (nonatomic, retain) NSString *userName;
@property (nonatomic, retain) NSString *password;
@property (nonatomic, retain) NSDictionary *kbaAnswers;

@property (nonatomic, assign) NSUInteger connectivityMode;
@property (nonatomic, retain) NSURL *loginHTMLURL;
@property (nonatomic, retain) NSURL *kbaHTMLURL;
@property (nonatomic, retain) NSSet *oauthScope;
@property (nonatomic) int logoutTimeOutValue;

@end

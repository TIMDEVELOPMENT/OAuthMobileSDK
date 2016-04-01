//
//  AppDelegate.h
//  APPTimOAM
//
//  Created by Mobility on 8/12/15.
//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "OMMobileSecurityService.h"
#import "OMMobileSecurityConfiguration.h"
#import "OMAuthView.h"
#import "IDMMobileSDK.h"
#import "AuthenticationViewController.h"


@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (nonatomic) BOOL setupDone;
@property (nonatomic) BOOL profileError;
@property (strong, nonatomic) NSDictionary *queryParams;
@property (strong, nonatomic) NSString *token;
@property (strong, nonatomic) OMMobileSecurityService *mss;
@property (strong, nonatomic) AuthenticationViewController *uiv;
@property (strong, nonatomic) NSMutableDictionary* sdkProps;

@end


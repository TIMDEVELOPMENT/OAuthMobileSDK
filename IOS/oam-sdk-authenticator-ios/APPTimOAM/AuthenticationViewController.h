//
//  ViewController.h
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

enum authTypes{
    APPLICATION = 1,
    INSIDE = 2,
    OUTSIDE = 3,
    AUTHCODE=4
};

@interface AuthenticationViewController : UIViewController <OMMobileServiceDelegate>
@property (weak, nonatomic) IBOutlet UILabel *authAppLabel;
@property (weak, nonatomic) IBOutlet UILabel *authBrowserIn;
@property (weak, nonatomic) IBOutlet UILabel *authBrowserOut;
@property (weak, nonatomic) IBOutlet UIButton *checkAppButton;
@property (weak, nonatomic) IBOutlet UIButton *checkInButton;
@property (weak, nonatomic) IBOutlet UIButton *checkOutButton;
@property (weak, nonatomic) IBOutlet UIButton *goButton;

- (IBAction)checkAppAction:(id)sender;
- (IBAction)checkInAction:(id)sender;
- (IBAction)checkOutAction:(id)sender;
- (void) setupService;
- (IBAction)goAction:(id)sender;
- (void) handleRequestWithURL:(NSURL *)url bundleID:(NSString *)appBundleID;
@property (weak, nonatomic) IBOutlet UIButton *testesimples;

@end


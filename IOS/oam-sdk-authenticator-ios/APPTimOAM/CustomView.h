//
//  CustomView.h
//  APPTimOAM
//
//  Created by Thiago Pastor on 3/8/16.
//  Copyright © 2016 Accenture. All rights reserved.
//


#import <UIKit/UIKit.h>
#import "OMAuthView.h"
#import "OMAuthenticationRequest.h"
#import "IDMMobileSDK.h"

@interface CustomView : UIView
@property (weak, nonatomic) IBOutlet UIButton *seguir;
@property (weak, nonatomic) IBOutlet UITextField *pass;
@property (weak, nonatomic) IBOutlet UITextField *user;

@property OMAuthView* oamview;

-(IBAction)clickseguir:(id)sender;
-(NSDictionary *)retrieveAuthData;
@end
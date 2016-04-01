    //
//  LoginViewController.m
//  APPTimOAM
//
//  Created by Mobility on 8/13/15.
//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import "LoginViewController.h"
#import "CustomView.h"//;

@interface LoginViewController ()

@end

@implementation LoginViewController
CustomView* cv;

-(void)viewLoaded{
    
    //creating a view from the xib and adding as a subview (can use InterfaceBuilder this way ....)
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSArray *views = [mainBundle loadNibNamed:@"CustomView"
                                         owner:nil
                                       options:nil];
    
    cv = ((CustomView *)views[0]);
    cv.oamview = self;
    
    
    [self addSubview:cv];
}
	

-(NSDictionary *)retrieveAuthData{    
    return cv.retrieveAuthData;
}






@end

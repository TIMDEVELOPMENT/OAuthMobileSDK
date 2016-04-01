//
//  CustomView.m
//  APPTimOAM
//
//  Created by Thiago Pastor on 3/8/16.
//  Copyright © 2016 Accenture. All rights reserved.
//

#import "CustomView.h"


@interface CustomView ()



@end

//use @protocol to pass this event instead of having a instance from oamview
@implementation CustomView

-(BOOL)stringIsNilOrEmpty:(NSString*)aString {
    return !(aString && aString.length);
}

- (IBAction)clickseguir:(id)sender {
    NSString *utex = _user.text;
    NSString *upass = _pass.text;
    BOOL hasNoTex = [ self stringIsNilOrEmpty:utex];
    BOOL hasNoPass = [ self stringIsNilOrEmpty:upass];
    
    if(hasNoTex || hasNoPass)
    {
        UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Error" message:@"Invalid data" delegate:self cancelButtonTitle:@"Ok" otherButtonTitles:nil, nil];
        [alert show];
    }					
    else
    {
      [_oamview userEnteredAuthData];
    }
}

-(NSDictionary *)retrieveAuthData{
    
    NSString *utex = _user.text;
    NSString *upass = _pass.text;
    [_oamview.authData setObject:utex forKey:OM_USERNAME];
    [_oamview.authData setObject:upass forKey:OM_PASSWORD];
    
    return _oamview.authData;
}
@end

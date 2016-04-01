
//
//  CellNumberViewController.h
//  APPTimOAM
//
//  Created by Mobility on 8/28/15.
//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "IDMMobileSDK.h"

@interface CellNumberViewController : UIViewController <UITextFieldDelegate, OMRESTRequestDelegate>

@property (weak, nonatomic) IBOutlet UITextField *numberTextField;
@property (weak, nonatomic) IBOutlet UIButton *sendOutlet;
- (IBAction)sendAction:(id)sender;
@end

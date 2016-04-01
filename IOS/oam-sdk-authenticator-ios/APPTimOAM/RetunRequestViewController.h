//
//  RetunRequestViewController.h
//  APPTimOAM
//
//  Created by Mobility on 8/31/15.
//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RetunRequestViewController : UIViewController

@property (weak, nonatomic) IBOutlet UILabel *msgReturn;
@property (weak, nonatomic) IBOutlet UITextView *textReturn;
@property (nonatomic) BOOL sucess;
@property (strong, nonatomic) NSError *erroReturn;
@end

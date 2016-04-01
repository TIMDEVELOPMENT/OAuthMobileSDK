//
//  RetunRequestViewController.m
//  APPTimOAM
//
//  Created by Mobility on 8/31/15.
//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import "RetunRequestViewController.h"

@interface RetunRequestViewController ()

@end

@implementation RetunRequestViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    if (_sucess) {
        _msgReturn.text = @"Sucesso!";
        _msgReturn.textColor = [UIColor greenColor];
    } else{
        _msgReturn.text = @"ERRO";
        _msgReturn.textColor = [UIColor redColor];
    }
    
    _textReturn.text = [NSString stringWithFormat:@"Erro - %@", _erroReturn];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

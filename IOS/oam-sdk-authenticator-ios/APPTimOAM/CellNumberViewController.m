//
//  CellNumberViewController.m
//  APPTimOAM
//
//  Created by Mobility on 8/28/15.
//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import "CellNumberViewController.h"
#import "OMMobileSecurityService.h"
#import "OMRESTRequest.h"
#import "AppDelegate.h"
#import "RetunRequestViewController.h"

@interface CellNumberViewController ()

@end

@implementation CellNumberViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _sendOutlet.layer.cornerRadius = 5;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)sendAction:(id)sende {
    
    [self resquestREST:_numberTextField.text];
    
}

-(void)resquestREST:(NSString*)msisdn {
    
    OMMobileSecurityService *mss = [OMMobileSecurityService new];
    OMRESTRequest *restReq = [OMRESTRequest new];
    restReq.delegate = self;
    restReq.mobileService = mss;
    
    NSURL *url = [[NSURL alloc] initWithString:@"http://10.171.135.31:8000/webSubscription/"];
    NSMutableDictionary *dictionary = [[NSMutableDictionary alloc] initWithCapacity:1];
    NSMutableDictionary *objDictionary = [NSMutableDictionary new];
    NSMutableDictionary *webSubscriptionDic = [NSMutableDictionary new];
    
    NSMutableURLRequest *urlRequest = [[NSMutableURLRequest alloc] initWithURL:url];
    [urlRequest setAllHTTPHeaderFields:dictionary];
    [urlRequest setValue:@"Content-Type" forKey:@"application/json"];
    [urlRequest addValue:@"Authorization" forHTTPHeaderField:@"Basic dGltc2RwOnExdzJlMw=="];
    [urlRequest setHTTPMethod:@"POST"];
    
    NSString *appID = @"11241";
    AppDelegate *delegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
    NSString *token = delegate.token;
    
    [objDictionary setObject:msisdn forKey:@"msisdn"];
    [objDictionary setObject:appID forKey:@"applicationId"];
    [objDictionary setObject:token forKey:@"token"];
    [webSubscriptionDic setObject:objDictionary forKey:@"webSubscription"];
    
    NSData *bodyData = [NSKeyedArchiver archivedDataWithRootObject:webSubscriptionDic];
    [urlRequest setHTTPBody:bodyData];
    
    OMAsyncOpHandle *opHandle = [restReq executeRESTRequestAsynchronously:urlRequest
                                                        convertDataToJSON:FALSE];
    OMLog(@"%@", opHandle);
}

-(void)didFinishExecutingRESTRequest:(OMRESTRequest *)RESTRequest
                                data:(id)data
                         urlResponse:(NSURLResponse *)urlResponse
                               error:(NSError *)error
                         asyncHandle:(OMAsyncOpHandle *)handle{
    
    RetunRequestViewController *returnRequest = [RetunRequestViewController new];
    
    if (error) {
        returnRequest.erroReturn = error;
    }
    else{
        returnRequest.sucess = YES;
    }
    
    [self.navigationController pushViewController:returnRequest animated:YES];
    
}
@end

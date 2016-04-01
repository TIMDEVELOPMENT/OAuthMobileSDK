//
//  AppDelegate.m
//  APPTimOAM
//
//  Created by Mobility on 8/12/15.
//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import "AppDelegate.h"
#import "AuthenticationViewController.h"
#import "CellNumberViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

NSMutableData *mutableData;

- (BOOL)connection:(NSURLConnection *)connection canAuthenticateAgainstProtectionSpace:(NSURLProtectionSpace *)protectionSpace {
    return [protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust];
}

- (void)connection:(NSURLConnection *)connection didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge {
    if ([challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust])
             [challenge.sender useCredential:[NSURLCredential credentialForTrust:challenge.protectionSpace.serverTrust] forAuthenticationChallenge:challenge];
    
    [challenge.sender continueWithoutCredentialForAuthenticationChallenge:challenge];
}

#pragma mark NSURLConnection delegates

-(void) connection:(NSURLConnection *) connection didReceiveResponse:(NSURLResponse *)response
{
    [mutableData setLength:0];
}

-(void) connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [mutableData appendData:data];
}

-(void) connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
   
    return;
}

-(void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    NSString *responseStringWithEncoded = [[NSString alloc] initWithData: mutableData encoding:NSUTF8StringEncoding];
    //NSLog(@"Response from Server : %@", responseStringWithEncoded);
    NSAttributedString * attrStr = [[NSAttributedString alloc] initWithData:[responseStringWithEncoded dataUsingEncoding:NSUnicodeStringEncoding] options:@{ NSDocumentTypeDocumentAttribute: NSHTMLTextDocumentType } documentAttributes:nil error:nil];
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Token" message:responseStringWithEncoded delegate:nil cancelButtonTitle:@"Close" otherButtonTitles:nil];
    [alert show];
    
    UIStoryboard *st = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    CellNumberViewController *cellNumber = (CellNumberViewController*) [ st instantiateViewControllerWithIdentifier:@"CellNumberViewController" ];
    self.window.rootViewController = cellNumber;

 
}



- (BOOL) application:(UIApplication *)application openURL:(nonnull NSURL *)url sourceApplication:(nullable NSString *)sourceApplication annotation:(nonnull id)annotation
{
    
    NSString *queryString = [url query];
    NSString *host = [url host];
    if ([queryString hasPrefix:@"oamconfig=true&"])
    {
        //do something
    }	
    else if([host isEqualToString:@"settings"])
    {
        //do Something
    }
    else if ([queryString rangeOfString:@"authenticate"].location != NSNotFound) {
    
        UIViewController *parentViewController = [[[UIApplication sharedApplication] delegate] window].rootViewController;
        
        while (parentViewController.presentedViewController != nil){
            parentViewController = parentViewController.presentedViewController;
        }
        UIViewController *currentViewController = parentViewController;
        AuthenticationViewController * vc = (AuthenticationViewController*) currentViewController;
        
        [vc handleRequestWithURL:url bundleID:sourceApplication];
    }
    else
    {
    NSMutableDictionary* dic =  [[NSMutableDictionary alloc] initWithCapacity:1];
    [dic setObject:url forKey:OM_RESPONSE_URL];
    
    [[NSNotificationCenter defaultCenter]
     postNotificationName:OM_PROCESS_URL_RESPONSE object:self userInfo:dic];
    }
    /*
    if(1==1)
        return YES;
    
    UIStoryboard *st = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    AuthenticationViewController *cellNumber = (AuthenticationViewController*) [ st instantiateViewControllerWithIdentifier:@"AuthenticationViewController" ];
    self.window.rootViewController = cellNumber;
    
    NSArray *ar = [url.absoluteString componentsSeparatedByString:@"="];
    if([ar count] == 0 ) return YES; //dummy checks
    NSString *code = [ar objectAtIndex:1];
    if([code length] == 0) return YES; //dummy checks
    
    
     NSString *parameter = [NSString stringWithFormat:@"redirect_uri=timoampoc%%3A%%2F%%2F&scope=&grant_type=authorization_code&code=%@",code] ;
    NSData *parameterData = [parameter dataUsingEncoding:NSASCIIStringEncoding allowLossyConversion:YES];
    
    url = [NSURL URLWithString: @"https://authsandbox.tim.com.br/ms_oauth/oauth2/endpoints/oauthservice/tokens"];
    NSMutableURLRequest *request  = [NSMutableURLRequest requestWithURL:url]	;
    
    [request setHTTPBody:parameterData];
    [request setHTTPMethod:@"POST"];
    [request addValue: @"application/x-www-form-urlencoded; charset=utf-8" forHTTPHeaderField:@"Content-Type"];


    [request setValue:[NSString stringWithFormat:@"Basic %@", @"MTU0YjQ5YTE3MTczNGI2MGE4NzQwZDNkMzU0OTE3Mzk6VXI3dm5uMk45RmJDUHo="] forHTTPHeaderField:@"Authorization"];
    
    mutableData = [ NSMutableData new];
    NSURLConnection *con = [[NSURLConnection alloc] initWithRequest:request delegate:self];
    
    */
                                                                             
// Send your request asynchronously
    /*
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse *responseCode, NSData *responseData, NSError *responseError) {
        if ([responseData length] > 0 && responseError == nil){
    	
            NSString *mes = [ [NSString alloc] initWithData:responseData encoding:NSUTF8StringEncoding];
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Token" message:mes delegate:nil cancelButtonTitle:@"Close" otherButtonTitles:nil];
            [alert show];
            
            UIStoryboard *st = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
            CellNumberViewController *cellNumber = (CellNumberViewController*) [ st instantiateViewControllerWithIdentifier:@"CellNumberViewController" ];
            self.window.rootViewController = cellNumber;
            
            //logic here
        }else if ([responseData length] == 0 && responseError == nil){
            NSLog(@"data error: %@", responseError);
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"Error accessing the data" delegate:nil cancelButtonTitle:@"Close" otherButtonTitles:nil];
            [alert show];
            
        }else if (responseError != nil && responseError.code == NSURLErrorTimedOut){
            NSLog(@"data timeout");
                  UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"connection timeout" delegate:nil cancelButtonTitle:@"Close" otherButtonTitles:nil];
                  [alert show];
            
                  }else if (responseError != nil){
                      NSLog(@"data download error: %@",responseError);
                            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:@"data download error" delegate:nil cancelButtonTitle:@"Close" otherButtonTitles:nil];
                            [alert show];
                            }
    }];
    */
    
    return YES;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
       return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end

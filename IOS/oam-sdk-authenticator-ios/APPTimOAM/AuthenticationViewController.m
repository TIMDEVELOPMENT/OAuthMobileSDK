//
//  ViewController.m
//  APPTimOAM
//
//  Created by Mobility on 8/12/15.

//  Copyright (c) 2015 Accenture. All rights reserved.
//

#import "AuthenticationViewController.h"
#import "AppDelegate.h"
#import "LoginViewController.h"
#import "CellNumberViewController.h"

@interface AuthenticationViewController ()

@end

@implementation AuthenticationViewController{
    
    BOOL _setupDone; //Indicates if the application profile was downloaded successfully
    NSString *_ssoAppBundleID; //Store the bundle ID of the SSO client app
    NSURL *_ssoRequestURL; // Stores the request URL sent by the client app
    BOOL _profileError; //Indicates if an error occurred in the profile download
    NSDictionary *_queryParams; // Stores query parameters from the SSO request URL
    
    OMMobileSecurityService *mss;
    NSUserDefaults *userDef;
    NSString *tipeOfAuthentication;
    NSMutableDictionary *sdkProps;
    NSDictionary *profile;
    BOOL isApplication;
    NSString *authType;
    BOOL setupDone; //Para saber o que setup foi concluído
    NSString *ssoAppBundleID; //Para armazenar bundle ID do browser
    NSURL *ssoRequestURL; //Para armazenar request URL enviado pelo client app
    BOOL profileError; //Para saber se ocorreu algum erro no download do profile
    NSDictionary *queryParams;	//Para armazenar query parameters da SSO request URL
}

- (void) handleRequestWithURL:(NSURL *)url bundleID:(NSString *)appBundleID
{
    if (!_setupDone)
    {
        ssoRequestURL = url;
        ssoAppBundleID = appBundleID;
        return;
    }
    [self ssoRequestWithURL:url fromApp:appBundleID];
}

/* This function invokes the SDK to process the SSO request. */

- (void)ssoRequestWithURL:(NSURL *)url fromApp:(NSString *)appBundleID
{
    if(_profileError)
    {
        _profileError = FALSE;
        ssoAppBundleID = nil;
        ssoRequestURL = nil;
        return;
    }
    NSDictionary *params = [mss parseURL:url fromApp:appBundleID];
    ssoRequestURL = nil;
    ssoAppBundleID = nil;
    queryParams = params;
    
    /* If this is an SSO request coming from either a native app or a browser
     * then do the SSO flow. Else do application specific logic. */
    
    if ([mss isSSORequest:queryParams])
    {
        [mss processSSORequest:queryParams presenter:self]; //It is assumed that the class also extends UIViewController.
    }
}

- (IBAction)clicou:(id)sender {
    NSString *st = @"Main";
    UIStoryboard *story = [UIStoryboard storyboardWithName:st bundle:nil];
    UIViewController *cont = [story instantiateViewControllerWithIdentifier:@"LoginViewController"    ];
    [self presentViewController:cont animated:YES completion:nil];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self defineLayout];
    isApplication = NO;
}

-(void)defineLayout{
    
    _goButton.layer.cornerRadius = 5;
    _authAppLabel.layer.borderColor = [[[UIColor alloc]initWithRed:21/250.0 green:27/250.0 blue:102/250.0 alpha:1] CGColor];
    _authBrowserIn.layer.borderColor = [[[UIColor alloc]initWithRed:21/250.0 green:27/250.0 blue:102/250.0 alpha:1] CGColor];
    _authBrowserOut.layer.borderColor = [[[UIColor alloc]initWithRed:21/250.0 green:27/250.0 blue:102/250.0 alpha:1] CGColor];
    _authAppLabel.layer.borderWidth = 1;
    _authBrowserIn.layer.borderWidth = 1;
    _authBrowserOut.layer.borderWidth = 1;
    _authAppLabel.layer.cornerRadius = 5;
    _authBrowserIn.layer.cornerRadius = 5;
    _authBrowserOut.layer.cornerRadius = 5;
}

- (void) setMapConfig{
    		
    NSMutableArray *scope = [[NSMutableArray alloc] init];
    [scope addObject:@"UserProfile.users"];
    [scope addObject:@"TIM.autoatendimento"];
    [scope addObject:@"TIM.servico"];
    sdkProps = [[NSMutableDictionary alloc] init];
    [sdkProps setObject:OM_PROP_OAUTH_OAUTH20_SERVER forKey:OM_PROP_AUTHSERVER_TYPE];
    [sdkProps setObject:@"https://authsandbox.tim.com.br/ms_oauth/oauth2/endpoints/oauthservice/tokens" forKey:OM_PROP_OAUTH_TOKEN_ENDPOINT];
    [sdkProps setObject:@"https://authsandbox.tim.com.br/ms_oauth/oauth2/endpoints/oauthservice/authorize" forKey:OM_PROP_OAUTH_AUTHORIZATION_ENDPOINT];
    [sdkProps setObject:@"154b49a171734b60a8740d3d35491739" forKey:OM_PROP_OAUTH_CLIENT_ID];
    [sdkProps setObject:@"Ur7vnn2N9FbCPz" forKey:OM_PROP_OAUTH_CLIENT_SECRET];
    [sdkProps setObject:scope forKey:OM_PROP_OAUTH_SCOPE];
    [sdkProps setObject:[NSSet setWithArray:scope] forKey:OM_PROP_OAUTH_SCOPE];

   
    [sdkProps setObject:@"timoampoc://" forKey:OM_PROP_OAUTH_REDIRECT_ENDPOINT];
        [sdkProps setObject:@"DefaultDomain" forKey:OM_PROP_OAMMS_SERVICE_DOMAIN];  
    [sdkProps setObject:@"PocAppMeuTim" forKey:OM_PROP_APPNAME];

    
    
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    
}

- (IBAction)checkAppAction:(id)sender {
    
    [_checkAppButton setImage:[UIImage imageNamed:@"Checked-32"] forState:UIControlStateNormal];
    [_checkInButton setImage:[UIImage imageNamed:@"Unchecked-32"] forState:UIControlStateNormal];
    [_checkOutButton setImage:[UIImage imageNamed:@"Unchecked-32"] forState:UIControlStateNormal];
    isApplication = YES;
    [self configurationAuth:APPLICATION];
}

- (IBAction)checkInAction:(id)sender {
    
    [_checkAppButton setImage:[UIImage imageNamed:@"Unchecked-32"] forState:UIControlStateNormal];
    [_checkInButton setImage:[UIImage imageNamed:@"Checked-32"] forState:UIControlStateNormal];
    [_checkOutButton setImage:[UIImage imageNamed:@"Unchecked-32"] forState:UIControlStateNormal];
    
    [self configurationAuth:INSIDE];
}

- (IBAction)checkOutAction:(id)sender {
    
    [_checkAppButton setImage:[UIImage imageNamed:@"Unchecked-32"] forState:UIControlStateSelected];
    [_checkInButton setImage:[UIImage imageNamed:@"Unchecked-32"] forState:UIControlStateNormal];
    [_checkOutButton setImage:[UIImage imageNamed:@"Checked-32"] forState:UIControlStateNormal];
    
    [self configurationAuth:OUTSIDE];
}

- (IBAction)goAction:(id)sender {
    
    [self setupService];
}

- (void) configurationAuth:(enum authTypes)typeOfConfiguration{
    
    switch (typeOfConfiguration) {
        case APPLICATION:
            [self setMapConfig];
            [sdkProps setObject:OM_OAUTH_RESOURCE_OWNER forKey:OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE];
            break;
            
        case INSIDE:
            [self setMapConfig];
            [sdkProps setObject:OM_OAUTH_AUTHORIZATION_CODE forKey:OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE];
            [sdkProps setObject: OM_PROP_BROWSERMODE_EMBEDDED forKey:OM_PROP_BROWSERMODE];
            break;
            
        case OUTSIDE:
            [self setMapConfig];
            [sdkProps setObject:OM_OAUTH_AUTHORIZATION_CODE forKey:OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE];
            [sdkProps setObject: OM_PROP_BROWSERMODE_EXTERNAL forKey:OM_PROP_BROWSERMODE];
            break;
        case AUTHCODE:
            [self setMapConfig];
            [sdkProps setObject:OM_PROP_OAUTH_AUTHORIZATION_GRANT_TYPE	 forKey: OM_OAUTH_AUTHORIZATION_CODE  ];
            break;
        default:
            break;
    }
}

- (void) setupService {
    
    
    NSHTTPCookieStorage *storage = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    for(NSHTTPCookie *cookie in [storage cookies])
    {
        [storage deleteCookie:cookie];
    }
    [[NSUserDefaults standardUserDefaults ] synchronize];
    
     mss = [[OMMobileSecurityService alloc]
                                    initWithProperties:sdkProps
                                    delegate:self	];
    AppDelegate *app =  (AppDelegate*) [[UIApplication sharedApplication] delegate];
    app.mss = mss;
    app.uiv = self;
    app.sdkProps = sdkProps;
    [mss setup];
}

- (void)didFinishAuthentication: (OMAuthenticationContext *)context
                          error: (NSError *)error
{
       NSLog(@"Erro: %@", error);
}
-(void)mobileSecurityService:(OMMobileSecurityService *)mobileSecurityService didReceiveApplicationProfile:(NSDictionary *)applicationProfile error:(NSError *)error{
    
    NSLog(@"Profile: %@", applicationProfile);
    NSLog(@"Erro: %@", error);
    
    OMAuthenticationRequest *req = [[OMAuthenticationRequest alloc] init];

    NSMutableArray *scope = [[NSMutableArray alloc] init];
    [scope addObject:@"TIM.autoatendimento"];
  
    req.oauthScope = [NSSet setWithArray:scope];
    
    if (isApplication) {
        isApplication = NO;
        LoginViewController *login = [[LoginViewController alloc] init ];
        req.authView = login;
        
        
        }
    
    if(ssoRequestURL != nil && ssoAppBundleID != nil)
    {
        [self ssoRequestWithURL:ssoRequestURL fromApp:ssoAppBundleID];
        return;
    }
    else
     [mss startAuthenticationProcess:req presenterViewController:self];
}

- (void)completeSSOAuthentication:(id)object
{
    NSError *error = (NSError *)object;
    [mss completeSSORequest:queryParams presenter:self error:error];
}


-(void)mobileSecurityService:(OMMobileSecurityService *)mobileSecurityService didFinishAuthentication:(OMAuthenticationContext *)context error:(NSError *)error{
    
    if (context == nil || error != nil) {
        NSString *msg = [[NSString alloc] initWithFormat:@"%@-%ld: %@",
                         [error domain],
                            (long)[error code], [error localizedDescription]];
        UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:msg delegate:self
                                                  cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
        return;
    } else {
        
        if([mss isSSORequest:queryParams])
        {
            [self dismissModalViewControllerAnimated:NO];
            [self performSelector:@selector(completeSSOAuthentication:)
                       withObject:(id)error afterDelay:0];
            return;
        }
        
            		
        NSMutableArray *scopes = [NSMutableArray new];
        [scopes addObject:@"UserProfile.users"];
        [scopes addObject:@"TIM.autoatendimento"];
        NSSet *setScopes = [NSSet setWithArray:scopes];
        
        AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication]delegate];
        delegate.token = [[context tokensForScopes:setScopes]lastObject];
        
        NSMutableArray* array = context.tokens;
        OMToken* token =  array[0];
        
        NSString * msg = [NSString stringWithFormat: @"%@ %@", token.tokenName, token.tokenValue];
        
        UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:@"Token" message:msg delegate:self
                                                  cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
        
        
        UIStoryboard *st = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        CellNumberViewController *cellNumber = (CellNumberViewController*) [ st instantiateViewControllerWithIdentifier:@"CellNumberViewController" ];
        [self presentViewController:cellNumber animated:FALSE completion:nil];
        
        
        
        
    }
}

@end

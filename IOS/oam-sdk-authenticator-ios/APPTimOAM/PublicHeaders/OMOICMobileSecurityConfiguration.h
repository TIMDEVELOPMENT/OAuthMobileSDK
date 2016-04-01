/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMOICMobileSecurityConfiguration.m - Oracle Mobile OIC Mobile Security
                                      Configuration object
 
 DESCRIPTION
 MobileSecurityConfiguration object for applications using OIC as security
 service provide
 
 RELATED DOCUMENTS
 None
 
 INHERITS FROM
 NSObject
 
 PROTOCOLS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 sativenk    01/03/12 - Refactoring
 keragago    11/16/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMMobileSecurityConfiguration.h"
#import "OMMobileSecurityService.h"

/**
 * To use OIC SDK for iOS, you will have to initialize OMMobileSecurityService
 * object. OMMobileSecurityService can be initialized to provide authentication
 * against OIC server. To do so, you can either create OMOICMobileSecurityConfiguration
 * object, which is derived from OMMobileSecurityConfiguration object and pass
 * it to OMMobileSecurityService initializer method or you provide OIC server
 * details to OMMobileSecurityService's initializer method which takes care of
 * creating OMOICMobileSecurityConfiguration and getting security settings.
 */
@interface OMOICMobileSecurityConfiguration : OMMobileSecurityConfiguration
{
@private
    id<OMMobileServiceDelegate>  _delegate;
}

@property (nonatomic, readonly, assign) id<OMMobileServiceDelegate> delegate;
@property (nonatomic, readonly) NSString* oicURL;
@property (nonatomic, readonly) NSString* serviceDomain;

/** 
 * Initializer method that takes OIC URL, mobile application's name and 
 * service domain name configured in OIC server.
 * 
 * @param url - OIC server URL
 * @param applicationID - name of the mobile application
 * @param domain - service domain name
 *
 * @return OICAppProfileServiceConfiguration object initialized by with
 *         OIC URL, Application ID and Service Domain.
 */
- (id)initWithURL:(NSURL*)url 
            appID:(NSString*)applicationID 
           domain:(NSString*)serviceDomain 
         delegate:(id<OMMobileServiceDelegate>)delegate;

/**
 * Downloads the security configuration from OIC server and stores the
 * properties in this object. After successful completion of download,
 * it also passes application profile to the application through the delegate.
 *
 * @return Reference to OMAsyncOpHandle object, which can be used to cancel
 *         this asynchronous request any time before it terminates
 */
- (OMAsyncOpHandle *)setUpMobileSecurityConfigAsynchronously;

@end

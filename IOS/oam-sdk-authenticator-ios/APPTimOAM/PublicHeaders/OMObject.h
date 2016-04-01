/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMObject.h - Oracle Mobile base Object
 
 DESCRIPTION
   Base object for IDMMobileSDK
 
 RELATED DOCUMENTS
   None
 
 PROTOCOLS
   None
 
 EXAMPLES
   None
 
 NOTES
   None
 
 MODIFIED   (MM/DD/YY)
 sativenk    10/03/12 - Creation
 */


#import <Foundation/Foundation.h>

/**
 * OMObject provides SDK version details and SDK behavior settings. Most of
 * these methods are class methods. OMObject instance by itself does not
 * provide any functionality.
 */
@interface OMObject : NSObject 
{
}

/**
 * Returns the version number of the SDK
 *
 * @return Version number of OAM Mobile and Social SDK
 */
+ (NSString *)getVersion;

/**
 * Returns the version number of the SDK with Banner
 *
 * @return Version number of OAM Mobile and Social SDK with Banner
 */
+ (NSString *)getVersionWithBanner;

/**
 * Returns the version number of the SDK with Banner and ADE label details
 *
 * @return Version number of OAM Mobile and Social SDK with Banner and ADE
 * label details
 */
+ (NSString *)getVersionWithLabel;

/**
 * OAM M&S SDK gets location update to propogate user context details to OAM
 * server. This option allows the application to disallow location update.
 *
 * @param allowed - Flag to allow or disallow SDK to get location update
 *
 * @return void
 */
+ (void)allowSDKToGetLocationUpdate: (BOOL)allowed;

/**
 * This function allows or disallows SDK to log its version during 
 * initialization of OMMobileSecurityService object, which is the entry point
 * to use this SDK
 *
 * @param logVersion - Flag to allow or disallow SDK to log its version
 *
 * @return void
 */
+ (void)logSDKVersionDuringInitializationOfSDK: (BOOL)logVersion;

@end
///////////////////////////////////////////////////////////////////////////////
// End of OMObject.h
///////////////////////////////////////////////////////////////////////////////
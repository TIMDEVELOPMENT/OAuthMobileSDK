/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMADFMobileSecurityConfiguration.m - Oracle ADF Mobile Security Profile
 
 DESCRIPTION
 MobileSecurityConfiguration Object for ADF use case. This class is only for
 ADF team's consumption.
 
 RELATED DOCUMENTS
 None
 
 INHERITS FROM
 OMMobileSecurityConfiguration
 
 PROTOCOLS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 vijanaki    11/16/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMMobileSecurityConfiguration.h"


/**
 * MobileSecurityConfiguration Object for ADF use case. This class is only for
 * ADF team's consumption.
 */
@interface OMADFMobileSecurityConfiguration : OMMobileSecurityConfiguration 
{
}

/**
 * Initializer method of OMADFMobileSecurityConfiguration, which initializes
 * this object by taking application ID and max login failure attempts
 *
 * @param appID - name of the application using this SDK
 * @param maxFailCount - Number of invalid login attempts allowed
 *
 * @return OMADFMobileSecurityConfiguration object
 */
-(id) initWithAppID:(NSString*)appID maxFailureAttempts:(int)maxFailCount;

@end
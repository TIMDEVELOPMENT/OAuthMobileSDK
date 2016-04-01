/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMCertService.h - Oracle Mobile Certificate Service
 
 DESCRIPTION
 Takes care of certificate operations
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS DEFINED
 None
 
 PROTOCOLS IMPLEMENTED
 
 CATEGORIES/EXTENSIONS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 asashiss    08/11/14 - Client certificate authentication changes 
 asashiss    12/06/13 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMCertInfo.h"

@protocol OMCertServiceDelegate;
@interface OMCertService : NSObject

/**
 * Reads a DER encoded certficate available at file path and adds it to
 * keychain. If a server is using self signed certificates then adding
 * certificates will suppress the trust warning shown by SDK.
 * @param filePath  A string containing location of certificate file
 * @param error     NSError object if any error was encountered while importing
 *                  certificate from file to keychain
 * @return          Returns true if certificate is successfully read and added
 *                  to keychain. Returns false if there was any error either in
 *                  reading certificate or adding it to keychain.
 */
+(BOOL) importServerCertificateFromFilePath:(NSURL *)filePath
                                      error:(NSError **)error;

/*
 * Adds a certficate object to keychain. If a server is using self signed
 * certificates then adding certificates will suppress the trust warning shown
 * by SDK.
 * @param certRef Certificate reference to be added to keychain
 * @param error   NSError object if any error was encountered while importing
 *                certificate to keychain
 * @return        Returns true if certificate is added successfully else false.
 */
+(BOOL) importServerCertificateFromRef:(SecCertificateRef)certificate
                                    error:(NSError **)error;

/*
 * Extracts client identity from a file, imports it to the keychain and deletes
 * the client certifiacte file.
 * @param fileURL Local file URL of client certificate file
 * @param password String to decrypt the file
 * @param error NSError object if any error was encountered while importing
 *              certificate to keychain
 * @return Returns a NSArray of CertInfo objects
 */
+(NSDictionary *) importClientCertificateFromFile:(NSURL *)fileURL
                               password:(NSString *)password
                                  error:(NSError **)error;

/*
 * Removes all client identities from the keychain.
 * @param error A NSError reference that will be populated if any error happens
 *              while removing the identities from keychain
 * @return Number of identities removed
 */
+(int) clearAllClientCertificates:(NSError **)error;

/*
 * Removes all server certificates from the keychain.
 * @param error A NSError reference that will be populated if any error happens
 *              while removing the identities from keychain
 * @return Number of certificates removed
 */
+(int) clearAllServerCertificates:(NSError **)error;

/*
 * Presents a UI to extract client identity from a file. Asynchronous method 
 * returns immediately and the result is delivered through OMCertServiceDelegate
 * didImportClientCertificate:error: method.
 * @param fileURL Local file URL of client certificate file
 * @param presenter ViewController in which the password will be collected.
 * @param delegate OMCertServiceDelegate object whose
 *                 didImportClientCertificate:error: method will be called when
 *                 the import is completed.
 */
+(void) importClientCertificateFromFile:(NSURL *)fileURL
                              presenter:(UIViewController *)presenter
                               delegate:(id<OMCertServiceDelegate>)delegate;
/*
 * Information about all client certificates installed by the app
 * @return Returns a NSArray of OMCertInfo objects
 */
+(NSArray *)infoForAllClientCertificates;

/*
 * Deletes a client certificate from keychain corresponding to OMCertInfo object 
 * @param certInfo An OMCertInfo object that is the client identity to be 
 *                 removed from keychain
 * @param error A NSError reference that will be populated if any error happens
 *              while removing the identity from keychain
 */
+(BOOL)deleteClientCertificate:(OMCertInfo *)certInfo error:(NSError **)error;
@end

@protocol OMCertServiceDelegate <NSObject>
@required
-(void)didImportClientCertificate:(NSArray *)certInfo
                            error:(NSError *)error;
@end


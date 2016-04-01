/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
    OMCredentialStore.h - Oracle Mobile Credential Store
 
 DESCRIPTION
    Wrapper class on top of KeyChainItemWrapper
 
 RELATED DOCUMENTS
    None
 
 PROTOCOLS
    None
 
 EXAMPLES
    None
 
 NOTES
    None
 
 MODIFIED   (MM/DD/YY)
 msadasiv    11/20/12 - Bug 14836655 - set ksecattraccessible to a secure 
                                       by default value
 sativenk    01/03/12 - Added header
 kerajago    10/02/11 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMCredential.h"

@interface OMCredentialStore : NSObject 
{
}

/**
 * @brief Adds an entry in KeyChainItem
 *
 * Adds username, password against a given key in KeyChainItem
 * @param username - User name
 * @param password - Password
 * @param properties - Custom properties
 * @param key - key that needs to be used to store in KeyChainItem; While
 *              retrieving user name and password, the application has to
 *              pass this key.
 * @return NSError object if the KeyChainItem key passed is nil
 */
- (NSError *)addCredential:(NSString *)userName
                       pwd:(NSString *)password 
                properties:(NSDictionary *)properties
                       url:(NSString *)key;

/**
 * @brief Adds an entry in KeyChainItem
 * Adds username, password, and tenant name against a given key in KeyChainItem
 * @param username - User name
 * @param password - Password
 * @param tenantName - Tenant to which this user belongs to
 * @param properties - Custom properties
 * @param key - key that needs to be used to store in KeyChainItem; While
 *              retrieving user name and password, the application has to
 *              pass this key.
 * @return NSError object if the KeyChainItem key passed is nil
 */
- (NSError *)addCredential:(NSString *)userName
                       pwd:(NSString *)password 
                tenantName:(NSString *)tenantName
                properties:(NSDictionary *)properties
                       url:(NSString *)key;

/**
 * @brief Deletes an entry in KeyChainItem
 *
 * Delets all details stored in KeyChainItem against given key
 *
 * @param key - key using secure details are stored
 * @return NSError object if the KeyChainItem key passed is nil
 */
- (NSError *)deleteCredential:(NSString*)key;

/**
 * @brief Updates an entry in KeyChainItem
 *
 * @param username - User name
 * @param password - Password
 * @param properties - Custom properties
 * @param key - key that needs to be used to store in KeyChainItem; While
 *              retrieving user name and password, the application has to
 *              pass this key.
 * @return NSError object if the KeyChainItem key passed is nil
 *
 */
- (NSError *)updateCredential:(NSString*)userName
                          pwd:(NSString*)password
                   properties:(NSDictionary *)properties
                          url:(NSString*)key;

/**
 * @brief Updates an entry in KeyChainItem
 *
 * @param username - User name
 * @param password - Password
 * @param tenantName - Name of the tenant to which this user belongs to
 * @param properties - Custom properties
 * @param key - key that needs to be used to store in KeyChainItem; While
 *              retrieving user name and password, the application has to
 *              pass this key.
 * @return NSError object if the KeyChainItem key passed is nil
 *
 */
- (NSError *)updateCredential: (NSString*)userName
                          pwd: (NSString*)password
                   tenantName: (NSString *)tenantName
                   properties: (NSDictionary *)properties
                          url: (NSString*)key;

/**
 * @brief Returns the credential
 *
 * @param key - Key of the KeyChainItem to be retrieved
 *
 * @return OMCredential object
 */
- (OMCredential *)getCredential:(NSString*)key;

/**
 * @brief Stores a property in KeyChainItem
 *
 * Stores a given property securely in KeyChainItem
 *
 * @param property - Property to be stored
 * @param key - key that needs to be used to store in KeyChainItem; While
 *              retrieving user name and password, the application has to
 *              pass this key.
 * @return NSError object if the KeyChainItem key passed is nil
 */
- (NSError *)storeProperty: (NSString *)property
                   withKey: (NSString *)key;

/**
 * @brief Stores a property in KeyChainItem
 *
 * Stores a given property securely in KeyChainItem with given label and
 * description
 *
 * @param property - Property to be stored
 * @param key - key that needs to be used to store in KeyChainItem; While
 *              retrieving user name and password, the application has to
 *              pass this key.
 * @param Label - Label to be stored
 * @param Description - Description of the property
 * @return NSError object if the KeyChainItem key passed is nil
 */
- (NSError *)storeProperty: (NSString *)property
                   withKey: (NSString *)key
                 withLabel: (NSString *)label
           withDescription: (NSString *)description;

/**
 * @brief Deletes a property in KeyChainItem
 *
 * Deletes a given property stored in KeyChainItem. All details stored with
 * property are wiped off.
 *
 * @param key - key of the property
 * @return NSError object if the KeyChainItem key passed is nil
 */
- (NSError *)deletePropertyWithKey: (NSString *)key;

/**
 * @brief Returns a property from KeyChainItem
 *
 * Retrieves a given property stored in KeyChainItem.
 *
 * @param key - key of the property
 * @return property
 */
- (id)getPropertyForKey: (NSString *)key;

/**
 * @brief Returns a property, label, description from KeyChainItem
 *
 * Returns a given property and its label and description from KeyChainItem
 * as an Array. The first element in the array is property followed by label
 * and description.
 *
 * @param key - key of the property
 * @return Property, label, and description in NSArray object
 * @li The element at index "0" of the array is Property
 * @li The element at index "1" of the array is Label
 * @li The element at index "2" of the array is Description 
 */
- (NSArray *)getPropertyLabelDescriptionAsArrayForKey: (NSString *)key;

/**
 * @brief Modify protection level of a KeyChainItem
 *
 * Modifies the protection level of a KeyChainItem. Can be used if default
 * protection level needs to be modified.
 *
 * @param key - KeyChainItem key
 * @param protection - Name of the property
 * @return NSError object if the KeyChainItem key passed is nil or if 
 *         protection level is invalid
 */
- (NSError *)modifyProperty:(NSString*)key
                 protection:(NSString *)protection;

@end

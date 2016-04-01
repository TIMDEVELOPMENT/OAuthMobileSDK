/* Copyright (c) 2011, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMRESTRequest.m - Oracle Mobile REST Request execution class
 
 DESCRIPTION
 This class takes care of executing REST request synchronously
 or asynchronously
 
 RELATED DOCUMENTS
 None
 
 INHERITS FROM
 NSObject
 
 PROTOCOLS
 OMRESTRequestDelegate
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 vismishr    01/28/15 - Bug 20421856
 sativenk    05/21/13 - Support for storing object & setting tag
 sativenk    05/21/12 - Bug 14074553
 sativenk    04/03/12 - Creation
 */

#import <Foundation/Foundation.h>
#import "OMAsyncOpHandle.h"

@protocol OMRESTRequestDelegate;
@class OMMobileSecurityService;

/**
 * This class provides methods to execute REST request synchronously or
 * asynchronously. This is mainly used for fetching OAM 11g Webgate protected
 * non-WEB resources such as REST web services and etc. The reason why the
 * application has to use this class to execute the request is that this
 * class takes care of getting webgate scoped token, if required. This class
 * also can be used to invoke any Web requests that is not webgate protected.
 * In cases where you are accessing non-webgate protected request, this class
 * acts as a wrapper on top of NSURLConnection.
 *
 * If you want to use same OMRESTRequest object for executing multiple REST
 * requests, it has to be sequential. They cannot be parallelized. If you
 * would like to execute multiple requests concurrently, create one object per
 * request.
 */
@interface OMRESTRequest : NSObject
{
@private
    OMMobileSecurityService      *_mobileService;
    id<OMRESTRequestDelegate>     _delegate;
    id                            _object;
    NSUInteger                    _tag;
}

@property(nonatomic, readwrite, retain) OMMobileSecurityService *mobileService;
@property(nonatomic, readwrite, assign) id<OMRESTRequestDelegate> delegate;
@property(nonatomic, readwrite, retain) id object;
@property(nonatomic, readwrite) NSUInteger tag;

/**
 * Initializer method that takes OMMobileSecurityService and delegate as the
 * parameters
 *
 * @param mobileService - OMMobileSecurityService object. If mobileService
 *                        parameter is nil, initialization still succeeds. 
 *                        If mobileService is nil, this class just acts as
 *                        a wrapper on top of NSURLConnection.
 * @param delegate      - delegate to which asynchronous requests have to
 *                        return the result. It can be nil if you want to use
 *                        only synchronous requests.
 * @return OMRESTRequest object
 */
- (id)initWithMobileSecurityService: (OMMobileSecurityService *)mobileService
                           delegate: (id<OMRESTRequestDelegate>)delegate;

/**
 * Executes the given REST request synchronously and returns the data as
 * JSON object (NSDictionary or NSArrary) or Raw Data (NSData).
 *
 * You can use this method non-REST requests as well.
 *
 * @param request - NSURLRequest object that represents the REST request
 *                  to be executed
 * @param isJsonRepresetnation - Identifies whether this function shall
 *                               convert the data to JSON object or not
 * @param urlResponse - NSURLReponse returned by the server
 * @param error   - If this method encounters any error while executing given
 *                  request, error is returned through this parameter
 *
 * @return NSDictionary or NSArray object if isJsonRepresentation is true
 *         NSData if isJsonRepresentation is false. Returns nil if the request
 *         has failed or if request parameter is nil.
 */
- (id)executeRESTRequest: (NSMutableURLRequest *)request
       convertDataToJSON: (BOOL)isJsonRepresentation
       returningResponse: (NSURLResponse **)urlResponse
                   error: (NSError **)error;

/**
 * @brief Executes the REST request asynchronously
 *
 * Executes the given REST request synchronously and returns a handle to 
 * asynchronous operation. Caller can abort the asynchronous request using
 * this handle any time before the request is completed. The REST request is
 * executed in separate thread and the result is returned through the delegate
 * OMRESTRequestDelegate.
 *
 * If you have to execute multiple REST requests simultaneously, you will
 * have to create OMRESTRequest object for each request. Same object cannot
 * be shared for executing multiple asynchronous requests simultaneously.
 *
 * @param request - NSURLRequest object that represents the REST request
 *                  to be executed
 * @param isJsonRepresetnation - Identifies whether this function shall
 *                               convert the data to JSON object or not
 *
 * @return OMAsyncOpHandle object, which can be used to cancel asynchronous
 *         request. Nil is returned if request parameter is nil.
 */
- (OMAsyncOpHandle *)executeRESTRequestAsynchronously: (NSMutableURLRequest *)request
                                    convertDataToJSON: (BOOL)isJsonRepresentation;

/**
 * @brief Executes the REST request asynchronously for OAUTH protected resources
 *
 * Executes the given REST request synchronously after adding access tokens to
 * header for given scopes and returns a handle to
 * asynchronous operation. Caller can abort the asynchronous request using
 * this handle any time before the request is completed. The REST request is
 * executed in separate thread and the result is returned through the delegate
 * OMRESTRequestDelegate.
 *
 * If you have to execute multiple REST requests simultaneously, you will
 * have to create OMRESTRequest object for each request. Same object cannot
 * be shared for executing multiple asynchronous requests simultaneously.
 *
 * @param request - NSURLRequest object that represents the REST request
 *                  to be executed
 * @param forScopes - Set of scopes for which access token has to be inserted
 * @param isJsonRepresentation - Identifies if result of this request needs to 
 *                               be converted as JSON (NSDictionary) or not
 *
 * @return OMAsyncOpHandle object, which can be used to cancel asynchronous
 *         request. Nil is returned if request parameter is nil.
 */
- (OMAsyncOpHandle *)executeRESTRequestAsynchronously: (NSMutableURLRequest *)request
                                            forScopes: (NSSet *)scopes
                                    convertDataToJSON: (BOOL)isJsonRepresentation;

@end

/**
 *
 * @brief The protocol to be implemented by the delegate of OMRESTRequest
 *
 * The delegate of a OMRESTRequest object must adopt the OMRESTRequestDelegate
 * protocol. OMRESTRequest object returns the result through 
 * didFinishExecutingRESTRequest method.
 */
@protocol OMRESTRequestDelegate <NSObject>

@required
/**
 * Tells the delegate that OMRESTRequest object completed executing the request
 * and returns the result to the delegate object. Note that the OMRESTRequest
 * object returns the result to thread from where the request was invoked.
 *
 * @prarm RESTRequest - OMRESTRequest object which is returning the result
 * @param data - If the REST request is completed successfully, it returns
 *               @li NSDictionary or NSArray object if isJsonRepresentation is true
 *               @li NSData if isJsonRepresentation is false
 * @param urlReponse - NSURLReponse object returned by the server
 * @param error - If this method encounters any error before executing given
 *                request, error is returned through this parameter
 * @param asyncHandle - OMAsyncOpHandle that was returned while initiating this
 *                      asynchronous request
 */
-(void) didFinishExecutingRESTRequest: (OMRESTRequest *)RESTRequest
                                 data: (id)data
                          urlResponse: (NSURLResponse *)urlResponse
                                error: (NSError *)error
                          asyncHandle: (OMAsyncOpHandle *)handle;


@end

/* Copyright (c) 2013, 2015, Oracle and/or its affiliates. 
All rights reserved.*/

/*
 NAME
 OMAuthProgressView.h - Oracle Mobile Authentication Progress View
 
 DESCRIPTION
 Base View class to show progress of authentication
 
 RELATED DOCUMENTS
 None
 
 PROTOCOLS
 None
 
 CATEGORIES/EXTENSIONS
 None
 
 EXAMPLES
 None
 
 NOTES
 None
 
 MODIFIED   (MM/DD/YY)
 sativenk    05/21/12 - Creation
 */

#import <UIKit/UIKit.h>
#import "OMObject.h"
#import "OMCredential.h"

@class OMContainerViewController;

/**
 * OMAuthProgressView serves as the base class for applications wanting to
 * customize authentication progress indicator
 */
@interface OMAuthProgressView : UIView
{
@private
    OMContainerViewController       *_containerViewController;
@protected
    NSString                        *_title;
    BOOL                             _showCancelButton;
    BOOL                             _showNavigationBar;
    BOOL                             _showNavigationToolBar;
    UIViewAnimationOptions           _animateTransitionFromAuthToProgressView;
    UIViewAnimationOptions           _animateTransitionFromProgressToAuthView;
    NSTimeInterval                   _animationDuration;
}

@property (nonatomic, readwrite, assign) OMContainerViewController *containerViewController;
@property (nonatomic, readwrite, retain) NSString *title;
@property (nonatomic, readwrite) BOOL showCancelButton;
@property (nonatomic, readwrite) BOOL showNavigationBar;
@property (nonatomic, readwrite) BOOL showNavigationToolBar;
@property (nonatomic, readwrite) UIViewAnimationOptions animateTransitionFromAuthToProgressView;
@property (nonatomic, readwrite) UIViewAnimationOptions animateTransitionFromProgressToAuthView;
@property (nonatomic, readwrite) NSTimeInterval animationDuration;

/**
 * This method shall be invoked by the custom views implemented by the
 * application when the usercompletes entering credentials. This method shall
 * not be overridden in the custom view.
 */
- (void)userCancelledAuthenticationOperation;

/**
 * When the view is loaded by super view/view controller, this method is
 * is invoked so that custom view can do its specific activities.
 */
- (void)progressViewLoaded;

/**
 * This method will be called by view controller to notify this view that
 * device orientation has changed. This can be used by custom views to resize
 * their views, if required.
 */
- (void)deviceOrientationHasChanged;

@end
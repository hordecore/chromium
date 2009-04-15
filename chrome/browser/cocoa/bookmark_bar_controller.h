// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_COCOA_BOOKMARK_BAR_CONTROLLER_H_
#define CHROME_BROWSER_COCOA_BOOKMARK_BAR_CONTROLLER_H_

#import <Cocoa/Cocoa.h>

#include "base/scoped_nsobject.h"

@class BookmarkBarStateController;
class BookmarkModel;
class Profile;
@class ToolbarView;

// A controller for the bookmark bar in the browser window. Handles showing
// and hiding based on the preference in the given profile.

@interface BookmarkBarController : NSObject {
 @private
  BookmarkModel* bookmarkModel_;  // weak; part of the profile owned by the
                                  // top-level Browser object.

  // Controller for bookmark bar state, shared among all TabContents.
  scoped_nsobject<BookmarkBarStateController> bookmarkBarStateController_;
  BOOL contentAreaHasOffset_;

  // TODO(jrg): write a BookmarkView
  IBOutlet ToolbarView* /* BookmarkView* */ bookmarkView_;
  IBOutlet NSView* contentArea_;
}

// Initializes the controller with the given browser profile and content view.
- (id)initWithProfile:(Profile*)profile
          contentArea:(NSView*)content;

// Change the visibility state of the bookmark bar to |enable|.
- (void)showBookmarkBar:(BOOL)enable;

// Toggle the state of the bookmark bar.
- (void)toggleBookmarkBar;

// Returns whether or not the bookmark bar is visible.
- (BOOL)isBookmarkBarVisible;

@end

#endif  // CHROME_BROWSER_COCOA_BOOKMARK_BAR_CONTROLLER_H_
// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_RENDER_VIEW_TEST_H_
#define CHROME_TEST_RENDER_VIEW_TEST_H_

#include "base/scoped_ptr.h"
#include "chrome/renderer/mock_render_process.h"
#include "chrome/renderer/mock_render_thread.h"
#include "chrome/renderer/render_view.h"
#include "chrome/renderer/renderer_webkitclient_impl.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "webkit/glue/webframe.h"

class RenderViewTest : public testing::Test {
 public:
  RenderViewTest() {}
  ~RenderViewTest() {}

 protected:
  // Spins the message loop to process all messages that are currently pending.
  void ProcessPendingMessages();

  // Returns a pointer to the main frame.
  WebFrame* GetMainFrame();

  // Executes the given JavaScript in the context of the main frame. The input
  // is a NULL-terminated UTF-8 string.
  void ExecuteJavaScript(const char* js);

  // Loads the given HTML into the main frame as a data: URL.
  void LoadHTML(const char* html);

  // testing::Test
  virtual void SetUp();

  virtual void TearDown();

  MessageLoop msg_loop_;
  MockRenderThread render_thread_;
  scoped_ptr<MockProcess> mock_process_;
  scoped_refptr<RenderView> view_;
  RendererWebKitClientImpl webkitclient_;
};

#endif  // CHROME_TEST_RENDER_VIEW_TEST_H_
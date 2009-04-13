// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/test/chrome_process_util.h"

#include <vector>

#include "base/process_util.h"
#include "base/time.h"
#include "chrome/common/result_codes.h"

using base::Time;
using base::TimeDelta;

void TerminateAllChromeProcesses(const FilePath& data_dir) {
  // Total time the function will wait for chrome processes
  // to terminate after it told them to do so.
  const TimeDelta kExitTimeout = TimeDelta::FromMilliseconds(5000);

  ChromeProcessList process_pids(GetRunningChromeProcesses(data_dir));

  std::vector<base::ProcessHandle> handles;
  {
    ChromeProcessList::const_iterator it;
    for (it = process_pids.begin(); it != process_pids.end(); ++it) {
      base::ProcessHandle handle;
      // Ignore processes for which we can't open the handle. We don't guarantee
      // that all processes will terminate, only try to do so.
      if (base::OpenProcessHandle(*it, &handle))
        handles.push_back(handle);
    }
  }

  std::vector<base::ProcessHandle>::const_iterator it;
  for (it = handles.begin(); it != handles.end(); ++it)
    base::KillProcess(*it, ResultCodes::TASKMAN_KILL, false);

  const Time start = Time::Now();
  for (it = handles.begin();
       it != handles.end() && Time::Now() - start < kExitTimeout;
       ++it) {
    // TODO(phajdan.jr): Fix int/int64 problems with TimeDelta::InMilliseconds.
    int wait_time_ms = static_cast<int>((Time::Now() - start).InMilliseconds());
    base::WaitForSingleProcess(*it, wait_time_ms);
  }

  for (it = handles.begin(); it != handles.end(); ++it)
    base::CloseProcessHandle(*it);
}
/*
 * Copyright (c) 2014-2015, Siemens AG. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <embb/base/condition_variable.h>
#include <embb/base/c/condition_variable.h>

namespace embb {
namespace base {

ConditionVariable::ConditionVariable() : condition_var_() {
  int status = embb_condition_init(&condition_var_);
  if (status == EMBB_ERROR) {
    EMBB_THROW(ErrorException, "Condition variable could not be initialized");
  }
}

void ConditionVariable::NotifyOne() {
  int status = embb_condition_notify_one(&condition_var_);
  if (status == EMBB_ERROR) {
    EMBB_THROW(ErrorException, "Condition variable: NotifyOne failed");
  }
}

void ConditionVariable::NotifyAll() {
  int status = embb_condition_notify_all(&condition_var_);
  if (status == EMBB_ERROR) {
    EMBB_THROW(ErrorException, "Condition variable: NotifyAll failed");
  }
}

void ConditionVariable::Wait(UniqueLock<Mutex>& lock) {
  int status = embb_condition_wait(&condition_var_, &(lock.mutex_->mutex_));
  if (status == EMBB_ERROR) {
    EMBB_THROW(ErrorException, "Condition variable: Wait failed");
  }
}

bool ConditionVariable::WaitUntil(UniqueLock<Mutex>& lock, const Time& time) {
  int status = embb_condition_wait_until(
    &condition_var_, &(lock.mutex_->mutex_), &(time.rep_));
  if (status == EMBB_ERROR) {
    EMBB_THROW(ErrorException, "Condition variable: WaitUntil failed");
  }
  if (status == EMBB_TIMEDOUT) return false;
  return true;
}

} // namespace base
} // namespace embb

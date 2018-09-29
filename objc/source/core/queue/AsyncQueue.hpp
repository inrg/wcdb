/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AsyncQueue_hpp
#define AsyncQueue_hpp

#include <mutex>
#include <string>

namespace WCDB {

class AsyncQueue {
public:
    AsyncQueue(const std::string &name);
    ~AsyncQueue();

    AsyncQueue() = delete;
    AsyncQueue(const AsyncQueue &) = delete;
    AsyncQueue &operator=(const AsyncQueue &) = delete;

    void run();

    const std::string name;

protected:
    void lazyRun();
    virtual void loop() = 0;
    static bool exit();

private:
    std::mutex m_lock;
    std::condition_variable m_cond;

    bool m_started;
    std::atomic<bool> m_running;

    void willRun();
};

} // namespace WCDB

#endif /* AsyncQueue_hpp */

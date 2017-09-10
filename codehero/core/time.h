// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TIME_H_
#define CODEHERO_CORE_TIME_H_

#include "core/system.h"
#include <chrono>

namespace CodeHero {

// Forward declaration
class EngineContext;

class Time : public System {
public:
    OBJECT(Time, System)

    Time(const std::shared_ptr<EngineContext>& iContext);
    ~Time();

    Error Initialize();
    Error Cleanup() { return OK; }

    uint64_t GetTime() const;
    uint64_t GetTimeMilliseconds() const;
    uint64_t GetTimeMicroseconds() const;
    void Reset();

private:
    std::chrono::steady_clock m_Clock;
    std::chrono::steady_clock::time_point m_StartTime;
};

} // namespace CodeHero

#endif // CODEHERO_CORE_TIME_H_
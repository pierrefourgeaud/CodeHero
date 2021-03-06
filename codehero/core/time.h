// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TIME_H_
#define CODEHERO_CORE_TIME_H_

#include <chrono>
#include "core/system.h"

namespace CodeHero {

// Forward declaration
class EngineContext;

class Time : public System {
public:
    OBJECT(Time, System)

    explicit Time(const std::shared_ptr<EngineContext>& iContext);
    ~Time() override;

    Error Initialize() override;
    Error Cleanup() override { return OK; }

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
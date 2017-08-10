// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/time.h"

namespace CodeHero {

Time::Time(const std::shared_ptr<EngineContext>& iContext)
    : System(iContext)
{}

Time::~Time() {}

Error Time::Initialize() {
    Reset();
    return OK;
}

uint64_t Time::GetTime() const {
    auto currentTime = m_Clock.now();

    std::chrono::steady_clock::duration time = currentTime - m_StartTime;
    return time.count();
}

uint64_t Time::GetTimeMilliseconds() const {
    auto currentTime = m_Clock.now();

    std::chrono::steady_clock::duration time = currentTime - m_StartTime;
    return std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
}

uint64_t Time::GetTimeMicroseconds() const {
    auto currentTime = m_Clock.now();

    std::chrono::steady_clock::duration time = currentTime - m_StartTime;
    return std::chrono::duration_cast<std::chrono::microseconds>(time).count();
}

void Time::Reset() {
    m_StartTime = m_Clock.now();
}

} // namespace CodeHero
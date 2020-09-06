// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <functional>

namespace CodeHero {

template <class T>
class ScopeCleaner {
 public:
    ScopeCleaner(T&& iAction) : m_Action(std::move(iAction)) {}
    ~ScopeCleaner() {
        if (!m_Cancelled) {
            m_Action();
        }
    }

    void Cancel() { m_Cancelled = true; }

 private:
    T m_Action;
    bool m_Cancelled = false;
};

// Needed to have simple template deduction
template <class T>
ScopeCleaner<T> Cleanup(T&& iAction) {
    return ScopeCleaner<T>(std::forward<T>(iAction));
}

} // namespace CodeHero
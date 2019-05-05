// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_SCOPECLEANER_H_
#define CODEHERO_CORE_SCOPECLEANER_H_

#include <functional>

namespace CodeHero {

template <class T>
class ScopeCleaner {
   public:
    ScopeCleaner(T&& iAction) : m_Action(std::move(iAction)) {}
    ~ScopeCleaner() { m_Action(); }

   private:
    T m_Action;
};

// Needed to have simple template deduction
template <class T>
ScopeCleaner<T> Cleanup(T&& iAction) {
    return ScopeCleaner<T>(std::forward<T>(iAction));
}

} // namespace CodeHero

#endif // CODEHERO_CORE_SCOPECLEANER_H_
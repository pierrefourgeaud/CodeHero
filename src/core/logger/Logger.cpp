// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "core/logger/Logger.h"

#include <vector>

namespace CodeHero {

static std::vector<ILogListener*>& Listeners() {
    static std::vector<ILogListener*> listeners;
    return listeners;
}

// static
bool SimpleLogger::AddListener(ILogListener* iListener) {
    std::vector<ILogListener*>::iterator tmp =
        std::find(Listeners().begin(), Listeners().end(), iListener);

    // Return false if the listener is already in the vector. This is not expected
    // but there is nothing really wrong either.
    if (tmp != Listeners().end()) {
        return false;
    }

    Listeners().push_back(iListener);
    return true;
}

// static
bool SimpleLogger::RemoveListener(ILogListener* iListener) {
    std::vector<ILogListener*>::iterator tmp =
        std::find(Listeners().begin(), Listeners().end(), iListener);

    // Return false if the listener could not be found
    if (tmp == Listeners().end()) {
        return false;
    } else {
        Listeners().erase(std::remove(Listeners().begin(), Listeners().end(), iListener));
        return true;
    }
}

bool SimpleLogger::_NotifyListeners() {
    String tmp = m_Os.str();
    std::for_each(Listeners().begin(), Listeners().end(), Notifier(tmp, m_Level));

    // Return false if there are no listeners in the vector
    return (Listeners().size() > 0);
}

} // namespace CodeHero
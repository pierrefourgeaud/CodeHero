// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <algorithm>
#include <string>
#include <vector>

#include "./logger.h"
#include "../utils.h"

namespace CodeHero {

Logger::~Logger() {
    _NotifyListeners();
}

std::ostringstream& Logger::Get(ELogLevel iLevel /* = ELogLevel::Info */) {
    m_Os << NowTime();
    m_Os << " " << Logger::ToString(iLevel) << ": ";
    m_Os << std::string(iLevel > ELogLevel::Debug ? to_i(iLevel) - to_i(ELogLevel::Debug) : 0, '\t');
    m_Level = iLevel;
    return m_Os;
}

bool Logger::AddListener(ILogListener* iListener) {
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

bool Logger::RemoveListener(ILogListener* iListener) {
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

ELogLevel Logger::FromString(const std::string& iLevel) {
    if (iLevel == "DEBUG2") {
        return ELogLevel::Debug2;
    } else if (iLevel == "DEBUG1") {
        return ELogLevel::Debug1;
    } else if (iLevel == "DEBUG") {
        return ELogLevel::Debug;
    } else if (iLevel == "INFO") {
        return ELogLevel::Info;
    } else if (iLevel == "WARNING") {
        return ELogLevel::Warning;
    } else if (iLevel == "ERROR") {
        return ELogLevel::Error;
    } else if (iLevel == "CRITICAL") {
        return ELogLevel::Critical;
    }

    // If the log level is not found, we return the default one (Info)
    LOGW << "Unknown logging level '" << iLevel << "'. Using INFO level as default.";
    return ELogLevel::Info;
}

bool Logger::_NotifyListeners() {
    std::string tmp = m_Os.str();
    std::for_each(Listeners().begin(), Listeners().end(), Notifier(tmp, m_Level));

    // Return false if there are no listeners in the vector
    return (Listeners().size() > 0);
}

}  // namespace CodeHero

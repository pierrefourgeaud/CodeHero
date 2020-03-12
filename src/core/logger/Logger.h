// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#include <time.h>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <string>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#else
#include <sys/time.h>
#endif // WIN32

#include "core/CoreAPI.h"
#include "core/Macros.h"
#include "core/String.h"
#include "core/logger/ILogListener.h"

namespace CodeHero {

enum class ELogLevel { Fatal, Error, Warning, Info, Debug, Debug1, Debug2 };

#ifdef LOGGING_DISABLED
#define _LOG(level) \
    {}
#else
#define _LOG(level)                               \
    if (level > SimpleLogger::ReportingLevel()) { \
    } else                                        \
        SimpleLogger().Get(level, TEXT(MODULE_NAME))
#endif

#define LOGF _LOG(ELogLevel::Fatal)
#define LOGE _LOG(ELogLevel::Error)
#define LOGW _LOG(ELogLevel::Warning)
#define LOGI _LOG(ELogLevel::Info)
#define LOGD _LOG(ELogLevel::Debug)
#define LOGD1 _LOG(ELogLevel::Debug1)
#define LOGD2 _LOG(ELogLevel::Debug2)

template <typename E>
constexpr typename std::underlying_type<E>::type to_i(E e) {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

// Forward declarations.
inline String NowTime();

class SimpleLogger {
    // Forward declaration.
    class Notifier {
     public:
        Notifier(const String& iLog, ELogLevel iLevel) : m_Log(iLog), m_Level(iLevel) {}

        void operator()(ILogListener* iListener) { iListener->Notify(m_Log, m_Level); }

     private:
        String m_Log;
        ELogLevel m_Level;
    };

 public:
    SimpleLogger() {}

    virtual ~SimpleLogger() { _NotifyListeners(); }

    std::wostringstream& Get(ELogLevel iLevel = ELogLevel::Info,
                             const String& moduleName = TEXT("")) {
        m_Os << NowTime();
        String level = SimpleLogger::ToString(iLevel);
        m_Os << " " << level << ":";
        if (level.size() < 7) {
            m_Os << "\t";
        }
        m_Os << " [" << moduleName << "] ";
        m_Level = iLevel;
        return m_Os;
    }

    static bool AddListener(ILogListener* iListener);
    static bool RemoveListener(ILogListener* iListener);

    static inline ELogLevel& ReportingLevel() {
        static ELogLevel reportingLevel = ELogLevel::Info;
        return reportingLevel;
    }

    static inline String ToString(ELogLevel iLevel) {
        static const String buffer[] = {TEXT("FATAL"), TEXT("ERROR"), TEXT("WARNING"),
                                        TEXT("INFO"),  TEXT("DEBUG"), TEXT("DEBUG1"),
                                        TEXT("DEBUG2")};
        return buffer[to_i(iLevel)];
    }

    static ELogLevel FromString(const String& iLevel) {
        if (iLevel == TEXT("DEBUG2")) {
            return ELogLevel::Debug2;
        } else if (iLevel == TEXT("DEBUG1")) {
            return ELogLevel::Debug1;
        } else if (iLevel == TEXT("DEBUG")) {
            return ELogLevel::Debug;
        } else if (iLevel == TEXT("INFO")) {
            return ELogLevel::Info;
        } else if (iLevel == TEXT("WARNING")) {
            return ELogLevel::Warning;
        } else if (iLevel == TEXT("ERROR")) {
            return ELogLevel::Error;
        } else if (iLevel == TEXT("FATAL")) {
            return ELogLevel::Fatal;
        }

        // If the log level is not found, we return the default one (Info)
        LOGW << "Unknown logging level '" << iLevel << "'. Using INFO level as default.";
        return ELogLevel::Info;
    }

 protected:
    std::wostringstream m_Os;
    ELogLevel m_Level = ELogLevel::Info;

    bool CORE_API _NotifyListeners();
};

inline String NowTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    wchar_t buffer[20] = {0};
    tm r;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    // No using localtime_s here because we want to support MinGW/MSYS compilation too
    r = *localtime(&in_time_t);
    static DWORD first = GetTickCount();
    int tick = static_cast<int>(GetTickCount() - first) % 1000;
#else
    localtime_r(&in_time_t, &r);
    struct timeval tv;
    gettimeofday(&tv, 0);
    int tick = static_cast<int>(tv.tv_usec) / 1000;
#endif // WIN32
    wcsftime(buffer, sizeof(buffer), TEXT("%F %T"), &r);

    wchar_t result[100] = {0};
    std::swprintf(result, sizeof(result), TEXT("%s.%03d"), buffer, tick);

    return result;
}

} // namespace CodeHero

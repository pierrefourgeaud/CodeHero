// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

// Logging code initially based on Petru Marginean's design
// http://www.drdobbs.com/cpp/201804215?pgno=1

#ifndef CODEHERO_CORE_LOGGING_LOGGER_H_
#define CODEHERO_CORE_LOGGING_LOGGER_H_

#include <sstream>
#include <string>
#include <vector>

#include "../typedefs.h"
#include "../utils.h"
#include "./iloglistener.h"

namespace CodeHero {

enum class ELogLevel {
    Critical,
    Error,
    Warning,
    Info,
    Debug,
    Debug1,
    Debug2
};

#ifdef LOGGING_DISABLED
#define LOG(level) {}
#else
#define LOG(level)                          \
    if (level > Logger::ReportingLevel()) {}\
    else\
        Logger().Get(level)
#endif

#define LOGC  LOG(ELogLevel::Critical)
#define LOGE  LOG(ELogLevel::Error)
#define LOGW  LOG(ELogLevel::Warning)
#define LOGI  LOG(ELogLevel::Info)
#define LOGD  LOG(ELogLevel::Debug)
#define LOGD1 LOG(ELogLevel::Debug1)
#define LOGD2 LOG(ELogLevel::Debug2)

// Forward declarations.
inline std::string NowTime();

class Logger {
    // Forward declaration.
    class Notifier {
    public:
        Notifier(const std::string& iLog, ELogLevel iLevel)
            : m_Log(iLog)
            , m_Level(iLevel) {}

        void operator()(ILogListener* iListener) {
            iListener->Notify(m_Log, m_Level);
        }

    private:
        std::string m_Log;
        ELogLevel   m_Level;
    };

public:
    Logger() {}

    virtual ~Logger();

    std::ostringstream& Get(ELogLevel iLevel = ELogLevel::Info);

    static bool AddListener(ILogListener* iListener);
    static bool RemoveListener(ILogListener* iListener);

    static inline std::vector<ILogListener*>& Listeners() {
        static std::vector<ILogListener*> listeners;
        return listeners;
    }

    static inline ELogLevel& ReportingLevel() {
        static ELogLevel reportingLevel = ELogLevel::Debug2;
        return reportingLevel;
    }

    static inline std::string ToString(ELogLevel iLevel) {
        static const char* const buffer[] = {
            "CRITICAL",
            "ERROR",
            "WARNING",
            "INFO",
            "DEBUG",
            "DEBUG1",
            "DEBUG2"};
        return buffer[to_i(iLevel)];
    }

    static ELogLevel FromString(const std::string& iLevel);

protected:
    std::ostringstream m_Os;
    ELogLevel          m_Level;

    // TODO(pierrefourgeaud): Convert to C++11
    // Prevent against copy
    Logger(const Logger&);
    Logger& operator=(const Logger&);

    bool _NotifyListeners();
};

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)

#include <windows.h>

inline std::string NowTime() {
    const int32 MAX_LEN = 200;
    char buffer[MAX_LEN];
    if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", buffer, MAX_LEN) == 0) {
        return "Error in NowTime()";
    }

    char result[100] = {0};
    static DWORD first = GetTickCount();
    std::snprintf(result, sizeof(result), "%s.%03d", buffer, static_cast<int32_t>(GetTickCount() - first) % 1000);
    return result;
}

#else

#include <sys/time.h>

inline std::string NowTime() {
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::snprintf(result, sizeof(result), "%s.%03d", buffer, static_cast<int32_t>(tv.tv_usec) / 1000);
    return result;
}

#endif  // WIN32

}  // namespace CodeHero

#endif  // CODEHERO_CORE_LOGGING_LOGGER_H_

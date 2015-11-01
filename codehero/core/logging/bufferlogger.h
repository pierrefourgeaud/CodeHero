// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_LOGGING_BUFFERLOGGER_H_
#define CODEHERO_CORE_LOGGING_BUFFERLOGGER_H_

#include "./iloglistener.h"

namespace CodeHero {

class BufferLogger : public ILogListener {
public:
    BufferLogger() {}
    virtual ~BufferLogger() {}

    std::string GetBuffer(bool iClearBuffer = true) {
        std::string buffer = m_Buffer.str();

        if (iClearBuffer) {
            ClearBuffer();
        }

        return buffer;
    }

    void ClearBuffer() {
        m_Buffer.str("");
        m_Buffer.clear();
    }

    virtual void Notify(const std::string& iMsg, ELogLevel iLevel) {
        m_Buffer << iMsg;
    }

private:
    std::ostringstream m_Buffer;
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_LOGGING_BUFFERLOGGER_H_

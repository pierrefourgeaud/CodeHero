// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_LOGGING_FILELOGGER_H_
#define CODEHERO_CORE_LOGGING_FILELOGGER_H_

#include <iostream>
#include <fstream>
#include <string>

#include "./iloglistener.h"

namespace CodeHero {

const std::string DEFAULT_FILENAME = "log.txt";

class FileLogger : public ILogListener {
public:
    explicit FileLogger(const std::string iFileName = "", const std::string iPath = "")
        : m_FileName(iFileName)
        , m_Path(iPath)
        , m_IsCreated(false) {
        if (m_FileName == "") {
            m_FileName = DEFAULT_FILENAME;
        }

        // Just check if there is a slash at the end of the path
        // Because it has to be there to create a valid path
        if (m_Path != "" && m_Path[m_Path.length() - 1] == '/') {
            m_Path += "/";
        }

        _OpenFile();
    }

    virtual ~FileLogger() {
        if (m_File.is_open()) {
            m_File.close();
        }
    }

    void Notify(const std::string& iLog, ELogLevel iLevel) {
        if (m_File.is_open()) {
            m_File << iLog;
            m_File.flush();
        }
    }

    inline std::string GetFileName() const {
        return m_FileName;
    }

    bool ChangeFile(const std::string& iFileName) {
        if (m_File.is_open()) {
            m_File.close();
        }

        m_FileName = iFileName;

        _OpenFile();
        return m_IsCreated;
    }

private:
    std::string m_FileName;
    std::string m_Path;
    bool        m_IsCreated;

    std::ofstream m_File;

    void _OpenFile() {
        m_File.open(m_Path + m_FileName);

        if (m_File.is_open()) {
            m_IsCreated = true;
        }
    }
};

}  // namespace CodeHero

#endif  // CODEHERO_CORE_LOGGING_FILELOGGER_H_

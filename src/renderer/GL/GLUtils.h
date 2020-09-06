// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

namespace CodeHero {

void GLCheckErr(const char* location, const char* call);

/**
 *  INTERNAL_STRING makes a string of X where X is expanded before conversion to a string
 *  if X itself contains macros.
 */
#define INTERNAL_STRING(X) INTERNAL_STRING_IMPL(X)
#define INTERNAL_STRING_IMPL(X) #X

/**
 *  Creates a string of the form "<filename>(<linenumber>) : "
 */
#define INTERNAL_FILE_AND_LINE_STR __FILE__ "(" INTERNAL_STRING(__LINE__) ")"

// Macro to conditionally call glGetError based on compile-time and flag.
#if GL_CHECK_ERROR
#define GL_CHECK_ERROR_IMPL(X) \
    CodeHero::GLCheckErr(INTERNAL_FILE_AND_LINE_STR + SOURCE_PATH_SIZE, #X)
#else
#define GL_CHECK_ERROR_IMPL(X)
#endif

// Macro to conditionally log the gl call based on compile-time flags.
#if GL_LOG_CALLS
#define GL_LOG_CALLS_IMPL(X)                                                            \
    LOGD << "[DEBUG_GL " << (INTERNAL_FILE_AND_LINE_STR + SOURCE_PATH_SIZE) << "]: " #X \
         << std::endl;
#else
#define GL_LOG_CALLS_IMPL(X)
#endif

// makes a GL call on the interface and does any error checking and logging
#define GL_CALL(X)              \
    do {                        \
        X;                      \
        GL_LOG_CALLS_IMPL(X);   \
        GL_CHECK_ERROR_IMPL(X); \
    } while (false)

// same as GL_CALL but stores the return value of the gl call in RET
#define GL_CALL_RET(RET, X)     \
    do {                        \
        (RET) = X;              \
        GL_LOG_CALLS_IMPL(X);   \
        GL_CHECK_ERROR_IMPL(X); \
    } while (false)

} // namespace CodeHero

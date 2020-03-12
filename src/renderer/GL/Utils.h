// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

namespace CodeHero {

void GLCheckErr(const char* location, const char* call);

/**
 *  CH_INTERNAL_STRING makes a string of X where X is expanded before conversion to a string
 *  if X itself contains macros.
 */
#define CH_INTERNAL_STRING(X) CH_INTERNAL_STRING_IMPL(X)
#define CH_INTERNAL_STRING_IMPL(X) #X

/**
 *  Creates a string of the form "<filename>(<linenumber>) : "
 */
#define CH_INTERNAL_FILE_AND_LINE_STR __FILE__ "(" CH_INTERNAL_STRING(__LINE__) ")"

// Macro to conditionally call glGetError based on compile-time and flag.
#if CH_GL_CHECK_ERROR
#define CH_GL_CHECK_ERROR_IMPL(X) \
    CodeHero::GLCheckErr(CH_INTERNAL_FILE_AND_LINE_STR + SOURCE_PATH_SIZE, #X)
#else
#define CH_GL_CHECK_ERROR_IMPL(X)
#endif

// Macro to conditionally log the gl call based on compile-time flags.
#if CH_GL_LOG_CALLS
#define CH_GL_LOG_CALLS_IMPL(X)                                                            \
    LOGD << "[DEBUG_GL " << (CH_INTERNAL_FILE_AND_LINE_STR + SOURCE_PATH_SIZE) << "]: " #X \
         << std::endl;
#else
#define CH_GL_LOG_CALLS_IMPL(X)
#endif

// makes a GL call on the interface and does any error checking and logging
#define CH_GL_CALL(X)              \
    do {                           \
        X;                         \
        CH_GL_LOG_CALLS_IMPL(X);   \
        CH_GL_CHECK_ERROR_IMPL(X); \
    } while (false)

// same as CH_GL_CALL but stores the return value of the gl call in RET
#define CH_GL_CALL_RET(RET, X)     \
    do {                           \
        (RET) = X;                 \
        CH_GL_LOG_CALLS_IMPL(X);   \
        CH_GL_CHECK_ERROR_IMPL(X); \
    } while (false)

} // namespace CodeHero

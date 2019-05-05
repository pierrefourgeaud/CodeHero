// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_ERRORS_H_
#define CODEHERO_CORE_ERRORS_H_

namespace CodeHero {

enum Error {
    OK,
    FAILED, // Generic error
    ERR_INVALID_PARAMETER,
    ERR_CANT_CREATE,
    ERR_CANT_OPEN,
    ERR_FILE_NOT_FOUND,
    ERR_NO_FILE_OPENED,
    ERR_FILE_EOF,
    ERR_IMAGE_FORMAT_UNRECOGNIZED,
    ERR_IMAGE_INVALID,
    ERR_PARSING_FAILED,
    ERR_COMPILATION_FAILED
};

} // namespace CodeHero

#endif // CODEHERO_CORE_ERRORS_H_

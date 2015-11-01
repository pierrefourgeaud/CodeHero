// Copyright (c) 2015 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_TYPEDEFS_H_
#define CODEHERO_CORE_TYPEDEFS_H_

namespace CodeHero {

#ifdef _MSC_VER

typedef signed   __int8   int8;
typedef unsigned __int8   uint8;
typedef signed   __int16  int16;
typedef unsigned __int16  uint16;
typedef signed   __int32  int32;
typedef unsigned __int32  uint32;
typedef signed   __int64  int64;
typedef unsigned __int64  uint64;

#else

typedef signed   char      int8;
typedef unsigned char      uint8;
typedef signed   short     int16;
typedef unsigned short     uint16;
typedef signed   int       int32;
typedef unsigned int       uint32;
typedef signed   long long int64;
typedef unsigned long long uint64;

#endif  // _MSC_VER

}  // namespace CodeHero

#endif  // CODEHERO_CORE_TYPEDEFS_H_

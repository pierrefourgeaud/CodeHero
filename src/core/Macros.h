// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

namespace CodeHero {

// If the platform doesn't already define the TEXT Macro
#if !defined(TEXT)
#define TEXT2(s) L##s
#define TEXT(s) TEXT2(s)
#endif // !defined(TEXT)

} // namespace CodeHero
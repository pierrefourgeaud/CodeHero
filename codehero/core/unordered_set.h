// Copyright (c) 2019 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_CORE_UNORDERED_SET_H_
#define CODEHERO_CORE_UNORDERED_SET_H_

#include <unordered_set>

namespace CodeHero
{

template <class Key>
using HashType = typename std::conditional<std::is_enum<Key>::value, std::hash<typename std::underlying_type<Key>::type>, std::hash<Key>>::type;
template <class K>
using UnorderedSet = std::unordered_set<K, HashType<K>>;

} // namespace CodeHero

#endif // CODEHERO_CORE_UNORDERED_SET_H_

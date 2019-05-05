// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "graphics/indexbuffer.h"

namespace CodeHero {

void IndexBuffer::SetData(const void* iData, uint32_t iIndexSize, bool iIsDynamic /* = false*/) {
    m_IndexSize = iIndexSize;
    m_IsDynamic = iIsDynamic;

    _SetDataImpl(iData);
}

} // namespace CodeHero

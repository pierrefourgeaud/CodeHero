// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <pugixml.hpp>
#include "drivers/xml/serializablecodec_xml.h"
#include "core/serializable.h"
#include "core/fileaccess.h"
#include <logger.h>

namespace CodeHero {

    SerializableCodecXML::SerializableCodecXML(const std::shared_ptr<EngineContext>& iContext)
    : ResourceCodec<Serializable>(iContext) {
    std::vector<std::string> ext{"xml", "XML"};
    for (auto& e : ext) {
        _AddExtension(e);
    }
}

SerializableCodecXML::~SerializableCodecXML() {}

Error SerializableCodecXML::Load(FileAccess& iF, Serializable& oObject) {
    const int32_t size = iF.GetSize();
    // ImageData buffer(size);
    // iF.Read(&buffer[0], size);


    return OK;
}

}  // namespace CodeHero

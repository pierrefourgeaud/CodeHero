// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_XML_SERIALIZABLECODEC_XML_H_
#define CODEHERO_DRIVERS_XML_SERIALIZABLECODEC_XML_H_

#include "core/errors.h"
#include "core/resourcecodec.h"

// Forward declaration
namespace pugi {
class xml_node;
}

namespace CodeHero {

// Forward declaration
class Serializable;
class FileAccess;
class ObjectDefinition;

class SerializableCodecXML : public ResourceCodec<Serializable> {
public:
    OBJECT(SerializableCodecXML, ResourceCodec<Serializable>)

    SerializableCodecXML(const std::shared_ptr<EngineContext>& iContext);
    ~SerializableCodecXML();

    Error Load(FileAccess& iF, Serializable& oObject) override;

private:
    Error _Load(const std::shared_ptr<ObjectDefinition>& iDefinition,
                const pugi::xml_node& iNode,
                Serializable& oObject) const;
};

}  // namespace CodeHero

#endif  // CODEHERO_DRIVERS_XML_SERIALIZABLECODEC_XML_H_

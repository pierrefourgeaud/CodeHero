// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef CODEHERO_DRIVERS_XML_SERIALIZABLECODEC_XML_H_
#define CODEHERO_DRIVERS_XML_SERIALIZABLECODEC_XML_H_

#include "core/errors.h"
#include "core/resourcecodec.h"

namespace CodeHero {

class Serializable;
class FileAccess;

class SerializableCodecXML : public ResourceCodec<Serializable> {
public:
    OBJECT(SerializableCodecXML, ResourceCodec<Serializable>)

    SerializableCodecXML(const std::shared_ptr<EngineContext>& iContext);
    ~SerializableCodecXML();

    Error Load(FileAccess& iF, Serializable& oObject) override;
};

}  // namespace CodeHero

#endif  // CODEHERO_DRIVERS_XML_SERIALIZABLECODEC_XML_H_

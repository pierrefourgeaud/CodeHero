// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <pugixml.hpp>
#include "drivers/xml/serializablecodec_xml.h"
#include "core/image.h"
#include "core/serializable.h"
#include "core/fileaccess.h"
#include "core/objectdefinition.h"
#include "core/utils.h"
#include <cstring>
#include <logger.h>

namespace CodeHero {

// Standard parsing
float ParseFloat(const std::string& iInput) {
    float res = 0.0f;
    try {
        res = std::stof(iInput);
    } catch (const std::exception& e) {
        LOGE << "XML: Fail to parse float argument, got: " << e.what() << std::endl;
    }

    return res;
}

Vector3 ParseVector3(const std::string& iInput) {
    Vector3 res;
    auto nums = Split(iInput, ' ');
    if (nums.size() != 3) {
        LOGE << "XML: Fail to parse Vector3 argument. Got " << nums.size() << " members, expected 3." << std::endl;
        return res;
    }
    try {
        res.SetX(ParseFloat(nums[0]));
        res.SetY(ParseFloat(nums[1]));
        res.SetZ(ParseFloat(nums[2]));
    } catch (const std::exception& e) {
        LOGE << "XML: Fail to parse Vector3 argument, got: " << e.what() << std::endl;
    }

    return res;
}

VariantHashMap ParseHashMap(const pugi::xml_object_range<pugi::xml_node_iterator>& iChildren) {
    VariantHashMap res;

    for (pugi::xml_node_iterator it = iChildren.begin(); it != iChildren.end(); ++it) {
        if (std::strcmp(it->name(), "Define") == 0) {
            std::string attr = it->attribute("name").as_string();
            std::string attrVal = it->attribute("value").as_string();

            res[attr] = attrVal;
        } else {
            LOGE << "[SerializableCodeXML]: Failed to parse hashmap attribute with name '" << it->name() << "'" << std::endl;
        }
    }

    return std::move(res);
}

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
    char* buffer = new char[size];
    iF.Read(reinterpret_cast<uint8_t*>(buffer), size);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(buffer);
    
    if (!result) {
        LOGE << "XML [" << buffer << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]" << std::endl;
        LOGE << "Error description: " << result.description() << std::endl;
        LOGE << "Error offset: " << result.offset << " (error at [..." << (buffer + result.offset) << "]" << std::endl;
        return ERR_PARSING_FAILED;
    }

    const std::string rootTypeName = oObject.GetTypeName();
    pugi::xml_node root = doc.child(rootTypeName.c_str());
    if (!root) {
        LOGE << "Failed to find root node " << rootTypeName << ". Object not imported." << std::endl;
        return ERR_PARSING_FAILED;
    }

    auto rootDef = Object::GetDefinition(rootTypeName);
    if (!rootDef) {
        LOGE << "No definition was declared for object '" << rootTypeName << "'. Object not imported." << std::endl;
        return ERR_INVALID_PARAMETER;
    }

    oObject.BeginLoad();

    for (pugi::xml_node_iterator it = root.begin(); it != root.end(); ++it) {
        // If the current node is attribute, then it is an attribute for the current object
        if (std::strcmp(it->name(), "attribute") == 0) {
            // No need to check for neither if name or value exists, the GetAttribe and then the parsers will fail
            // if no value where passed
            std::string attr = it->attribute("name").as_string();
            std::string attrVal = it->attribute("value").as_string();
            auto attrInfo = rootDef->GetAttribute(attr);
            if (attrInfo.IsNull()) {
                LOGE << "Attribute '" << attr << "' not registered for object '" << rootTypeName
                     << "', ignored." << std::endl;
            } else {
                switch (attrInfo.GetType()) {
                case Variant::Value::VVT_Float:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseFloat(attrVal)));
                    break;
                case Variant::Value::VVT_String:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(std::string(attrVal)));
                    break;
                case Variant::Value::VVT_Vector3:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseVector3(attrVal)));
                    break;
                case Variant::Value::VVT_HashMap:
                    // HashMap in variant for now does support only <string, string>
                    // When the type will evolve in a more complicated/complete version
                    // we will need to revise this parsing
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseHashMap(it->children())));
                    break;
                default:
                    // Should not be here...
                    CH_ASSERT(false);
                    break;
                }
            }
        }
    }

    oObject.EndLoad();

    delete [] buffer;

    return OK;
}

}  // namespace CodeHero

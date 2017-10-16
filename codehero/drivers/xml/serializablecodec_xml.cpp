// Copyright (c) 2017 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "drivers/xml/serializablecodec_xml.h"
#include "core/enginecontext.h"
#include "core/fileaccess.h"
#include "core/resourceloader.h"
#include "core/serializable.h"
#include "core/type_traits/attributeaccessor.h"
#include "core/type_traits/objectdefinition.h"
#include "core/utils.h"
#include <cstring>
#include <logger.h>

namespace CodeHero {

// Standard parsing
bool ParseBool(const std::string& iInput) {
    bool res = false;

    if (iInput == "true") {
        res = true;
    } else if (iInput == "false") {
        res = false;
    } else {
        LOGE << "[SerializableCodecXML]: Faile to parse bool argument: '" << iInput << "' is not valid." << std::endl;
    }

    return res;
}

float ParseFloat(const std::string& iInput) {
    float res = 0.0f;
    try {
        res = std::stof(iInput);
    } catch (const std::exception& e) {
        LOGE << "XML: Fail to parse float argument, got: " << e.what() << std::endl;
    }

    return res;
}

Vector2 ParseVector2(const std::string& iInput) {
    Vector2 res;
    auto nums = Split(iInput, ' ');
    if (nums.size() != 2) {
        LOGE << "[SerializableCodexXML]: Fail to parse Vector2 argument. Got " << nums.size() << " members, expected 2." << std::endl;
        return res;
    }
    try {
        res.SetX(ParseFloat(nums[0]));
        res.SetY(ParseFloat(nums[1]));
    } catch (const std::exception& e) {
        LOGE << "[SerializableCodexXML]: Fail to parse Vector2 argument, got: " << e.what() << std::endl;
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

Quaternion ParseQuaternion(const std::string& iInput) {
    Quaternion res;
    auto nums = Split(iInput, ' ');
    if (nums.size() == 3) {
        try {
            res.FromEulerAngles(ParseFloat(nums[0]), ParseFloat(nums[1]), ParseFloat(nums[2]));
        } catch (const std::exception& e) {
            LOGE << "[SerializableCodexXML]: Fail to parse Quaternion argument, got: " << e.what() << std::endl;
        }
    } else {
        LOGE << "[SerializableCodexXML]: Fail to parse Quaternion argument. Got " << nums.size() << " members." << std::endl;
    }

    return res;
}

VariantArray ParseArray(const pugi::xml_object_range<pugi::xml_node_iterator>& iChildren) {
    VariantArray res;

    for (pugi::xml_node_iterator it = iChildren.begin(); it != iChildren.end(); ++it) {
        if (std::strcmp(it->name(), "subattribute") == 0) {
            std::string attrVal = it->attribute("value").as_string();

            res.push_back(attrVal);
        } else {
            LOGE << "[SerializableCodeXML]: Failed to parse array attribute with name '" << it->name() << "'" << std::endl;
        }
    }

    return std::move(res);
}

VariantHashMap ParseHashMap(const pugi::xml_object_range<pugi::xml_node_iterator>& iChildren) {
    VariantHashMap res;

    for (pugi::xml_node_iterator it = iChildren.begin(); it != iChildren.end(); ++it) {
        if (std::strcmp(it->name(), "subattribute") == 0) {
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
    std::string content = iF.ReadAll();

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(content.c_str());
    
    if (!result) {
        LOGE << "XML [" << content << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]" << std::endl;
        LOGE << "Error description: " << result.description() << std::endl;
        LOGE << "Error offset: " << result.offset << " (error at [..." << (&content[result.offset]) << "]" << std::endl;
        return ERR_PARSING_FAILED;
    }

    const std::string rootTypeName = oObject.GetTypeName();
    pugi::xml_node root = doc.child(rootTypeName.c_str());

    if (!root) {
        LOGE << "Failed to find node " << rootTypeName << ". Object not imported." << std::endl;
        return ERR_PARSING_FAILED;
    }

    auto rootDef = Object::GetDefinition(rootTypeName);
    if (!rootDef) {
        LOGE << "No definition was declared for object '" << rootTypeName << "'. Object not imported." << std::endl;
        return ERR_INVALID_PARAMETER;
    }

    Error loadResult = _Load(rootDef, root, oObject);

    return loadResult;
}

Error SerializableCodecXML::_Load(const std::shared_ptr<ObjectDefinition>& iDefinition,
                                  const pugi::xml_node& iNode,
                                  Serializable& oObject) const {
    oObject.BeginLoad();

    for (pugi::xml_node_iterator it = iNode.begin(); it != iNode.end(); ++it) {
        // If the current node is attribute, then it is an attribute for the current object
        if (std::strcmp(it->name(), "attribute") == 0) {
            // No need to check for neither if name or value exists, the GetAttribe and then the parsers will fail
            // if no value where passed
            std::string attr = it->attribute("name").as_string();
            std::string attrVal = it->attribute("value").as_string();
            auto attrInfo = iDefinition->GetAttribute(attr);
            if (attrInfo.IsNull()) {
                LOGE << "Attribute '" << attr << "' not registered for object '" << iDefinition->GetName()
                     << "', ignored." << std::endl;
            } else {
                switch (attrInfo.GetType()) {
                case Variant::Value::VVT_Bool:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseBool(attrVal)));
                    break;
                case Variant::Value::VVT_Float:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseFloat(attrVal)));
                    break;
                case Variant::Value::VVT_String:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(std::string(attrVal)));
                    break;
                case Variant::Value::VVT_Vector2:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseVector2(attrVal)));
                    break;
                case Variant::Value::VVT_Vector3:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseVector3(attrVal)));
                    break;
                case Variant::Value::VVT_Quaternion:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseQuaternion(attrVal)));
                    break;
                case Variant::Value::VVT_Array:
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseArray(it->children())));
                    break;
                case Variant::Value::VVT_HashMap:
                    // HashMap in variant for now does support only <string, string>
                    // When the type will evolve in a more complicated/complete version
                    // we will need to revise this parsing
                    attrInfo.GetAccessor()->Set(&oObject, Variant(ParseHashMap(it->children())));
                    break;
                case Variant::Value::VVT_SerializablePtr:
                    // If the tag is attribute and the type is shared_ptr<Serializable>
                    // we consider that we expect a collection of SerializablePtr object
                    // the attribute tag being a way to group those elements together
                    if (_ParseCollection(it->children(), attrInfo, oObject) != Error::OK) {
                        LOGE << "[SerializableCodeXML]: Failed to parse collection '" << attr << "'." << std::endl;
                    }
                    break;
                default:
                    // Should not be here...
                    CH_ASSERT(false);
                    break;
                }
            }
        } else {
            auto attrInfo = iDefinition->GetAttribute(it->name());
            if (attrInfo.IsNull()) {
                LOGE << "Attribute '" << it->name() << "' not registered for object '" << iDefinition->GetName()
                    << "', ignored." << std::endl;
                continue;
            }

            _LoadObject(it, attrInfo, oObject);
        }
    }

    oObject.EndLoad();

    return OK;
}

Error SerializableCodecXML::_ParseCollection(const pugi::xml_object_range<pugi::xml_node_iterator>& iChildren,
                                             const AttributeInfo& iAttrInfo,
                                             Serializable& oObject) const {
    Error ret = Error::OK;

    for (pugi::xml_node_iterator it = iChildren.begin(); it != iChildren.end(); ++it) {
        ret = _LoadObject(it, iAttrInfo, oObject);
        if (ret != Error::OK) {
            LOGE << "[SerializableCodecXML]: Failed to load object '" << it->name() << "'." << std::endl;
            break;
        }
    }

    return ret;
}

Error SerializableCodecXML::_LoadObject(const pugi::xml_node_iterator& iNode, const AttributeInfo& iAttrInfo, Serializable& oObject) const {
    auto def = Object::GetDefinition(iNode->name());
    if (!def) {
        LOGE << "[SerializableCodecXML]: No definition was declared for object '" << iNode->name()
             << "'. Object not imported." << std::endl;
        return Error::ERR_PARSING_FAILED;
    }

    auto attr = iNode->attribute("path");

    // Whatever path we take next, we will need this object
    std::shared_ptr<Serializable> obj = std::static_pointer_cast<Serializable>(def->Create());

    // If it has a path to file, we use the resource loader
    if (attr) {
        m_pContext->GetSubsystem<ResourceLoader<Serializable>>()->Load(attr.as_string(), *obj.get());
    } else { // Or we load it here
        // TODO(pierre) All object here can be serializable
        // but we should add a test. We can at least do a IsA (to be added soon)
        Error res = _Load(def, *iNode, *obj.get());
        if (res != Error::OK) {
            LOGE << "[SerializableCodecXML]: Failed to import " << iNode->name() << " object. Continuing..."
                 << std::endl;
            return res;
        }
    }

    iAttrInfo.GetAccessor()->Set(&oObject, Variant(obj));

    return Error::OK;
}

}  // namespace CodeHero

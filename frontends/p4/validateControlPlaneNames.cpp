#include "validateControlPlaneNames.h"

namespace P4 {

ValidateControlPlaneNames::ValidateControlPlaneNames() { setName("ValidateControlPlaneNames"); }

void ValidateControlPlaneNames::validate(type_t type, const IR::IDeclaration* decl) {
    auto& declMap = declMaps[type];
    const auto* anno = decl->getAnnotation(IR::Annotation::nameAnnotation);
    if (anno == nullptr) {
        return;
    }

    const auto name = anno->getName();
    const auto it = declMap.find(name);

    LOG1("type " << static_cast<int>(type) << " name " << name);
    if (it != declMap.end()) {
        // ::error(
        //     "Multiple objects of the same type %3% with the same control plane name %4%: %1% %2%",
        //     decl->getSourceInfo(), it->second->getSourceInfo(), decl->node_type_name(), name);
    } else {
        declMap[name] = decl;
    }
}

bool ValidateControlPlaneNames::preorder(const IR::P4Action* act) {
    validate(ACTION, act);
    return false;
}

bool ValidateControlPlaneNames::preorder(const IR::P4Table* tbl) {
    validate(TABLE, tbl);
    return false;
}

bool ValidateControlPlaneNames::preorder(const IR::P4ValueSet* vs) {
    validate(VALUE_SET, vs);
    return false;
}

bool ValidateControlPlaneNames::preorder(const IR::Type_Header* hdr) {
    if (hdr->getAnnotation("controller_header") != nullptr) {
        validate(CONTROLLER_HEADER, hdr);
    }
    return false;
}

}  // namespace P4

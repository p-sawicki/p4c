#ifndef _FRONTENDS_P4_VALIDATECONTROLPLANENAMES_H_
#define _FRONTENDS_P4_VALIDATECONTROLPLANENAMES_H_

#include "ir/ir.h"

namespace P4 {
class ValidateControlPlaneNames : public Inspector {
    enum type_t {ACTION, TABLE, VALUE_SET, CONTROLLER_HEADER};

    using DeclMap = std::unordered_map<cstring, const IR::IDeclaration*>;
    std::unordered_map<type_t, DeclMap> declMaps;

 public:
    ValidateControlPlaneNames();

    void validate(type_t type, const IR::IDeclaration* decl);

    bool preorder(const IR::P4Action* act) override;
    bool preorder(const IR::P4Table* tbl) override;
    bool preorder(const IR::P4ValueSet* vs) override;
    bool preorder(const IR::Type_Header* hdr) override;
};
}  // namespace P4

#endif /* _FRONTENDS_P4_VALIDATECONTROLPLANENAMES_H_ */
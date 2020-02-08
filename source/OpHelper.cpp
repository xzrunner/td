#include "td/OpHelper.h"
#include "td/Operator.h"

namespace td
{

OpPtr OpHelper::GetInputOp(const Operator& op, size_t idx)
{
    auto& imports = op.GetImports();
    if (idx < 0 || idx >= imports.size()) {
        return nullptr;
    }

    auto& conns = imports[idx].conns;
    if (conns.empty()) {
        return nullptr;
    }

    assert(imports[idx].conns.size() == 1);
    auto in_comp = imports[idx].conns[0].node.lock();
    assert(in_comp->get_type().is_derived_from<Operator>());
    return std::static_pointer_cast<Operator>(in_comp);
}

ParamPtr OpHelper::GetInputParam(const Operator& op, size_t idx)
{
    auto& imports = op.GetImports();
    if (idx < 0 || idx >= imports.size()) {
        return nullptr;
    }

    auto& conns = imports[idx].conns;
    if (conns.empty()) {
        return nullptr;
    }

    assert(imports[idx].conns.size() == 1);
    auto& conn = imports[idx].conns[0];
    auto in_comp = conn.node.lock();
    assert(in_comp->get_type().is_derived_from<Operator>());
    return std::static_pointer_cast<Operator>(in_comp)->GetValue(conn.idx);
}

}
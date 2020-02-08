#include "td/Evaluator.h"
#include "td/Operator.h"
#include "td/typedef.h"

#include <dag/Evaluator.h>

namespace td
{

void Evaluator::ComponentChaged(const OpPtr& op)
{
    dag::Evaluator::SetTreeDirty<ParamType>(op);

    m_dirty = true;
}

void Evaluator::AddComponent(const OpPtr& op)
{
    auto name = op->GetName();
    while (name.empty() || m_op_map.find(name) != m_op_map.end())
    {
        if (op->GetName().empty()) {
            name = "op" + std::to_string(m_next_id++);
        } else {
            name = op->GetName() + std::to_string(m_next_id++);
        }
    }
    op->SetName(name);

    m_op_map.insert({ name, op });

    m_dirty = true;
}

void Evaluator::RemoveComponent(const OpPtr& op)
{
    if (m_op_map.empty()) {
        return;
    }

    auto itr = m_op_map.find(op->GetName());
    if (itr == m_op_map.end()) {
        return;
    }

    dag::Evaluator::SetTreeDirty<ParamType>(op);

    m_op_map.erase(itr);

    m_dirty = true;
}

void Evaluator::ClearAllComponents()
{
    if (m_op_map.empty()) {
        return;
    }

    m_op_map.clear();

    m_dirty = true;
}

void Evaluator::PropChanged(const OpPtr& op)
{
    dag::Evaluator::SetTreeDirty<ParamType>(op);

    m_dirty = true;
}

void Evaluator::Connect(const dag::Node<ParamType>::PortAddr& from, const dag::Node<ParamType>::PortAddr& to)
{
    dag::make_connecting<ParamType>(from, to);

    auto op = to.node.lock();
    assert(op && op->get_type().is_derived_from<Operator>());
    dag::Evaluator::SetTreeDirty<ParamType>(std::static_pointer_cast<Operator>(op));

    m_dirty = true;
}

void Evaluator::Disconnect(const dag::Node<ParamType>::PortAddr& from, const dag::Node<ParamType>::PortAddr& to)
{
    dag::disconnect<ParamType>(from, to);

    auto op = to.node.lock();
    assert(op && op->get_type().is_derived_from<Operator>());
    dag::Evaluator::SetTreeDirty<ParamType>(std::static_pointer_cast<Operator>(op));

    m_dirty = true;
}

void Evaluator::RebuildConnections(const std::vector<std::pair<dag::Node<ParamType>::PortAddr, dag::Node<ParamType>::PortAddr>>& conns)
{
    // update dirty
    for (auto itr : m_op_map) {
        if (dag::Evaluator::HasNodeConns<ParamType>(itr.second)) {
            dag::Evaluator::SetTreeDirty<ParamType>(itr.second);
        }
    }

    // remove conns
    for (auto itr : m_op_map) {
        itr.second->ClearConnections();
    }

    // add conns
    for (auto& conn : conns)
    {
        auto op = conn.second.node.lock();
        assert(op && op->get_type().is_derived_from<Operator>());
        dag::Evaluator::SetTreeDirty<ParamType>(std::static_pointer_cast<Operator>(op));
        dag::make_connecting<ParamType>(conn.first, conn.second);
    }

    m_dirty = true;
}

void Evaluator::MakeDirty()
{
    m_dirty = true;

    for (auto& itr : m_op_map) {
        itr.second->SetDirty(true);
    }
}

void Evaluator::Update()
{
    if (m_op_map.empty()) {
        return;
    }

    std::vector<std::shared_ptr<dag::Node<ParamType>>> devices;
    devices.reserve(m_op_map.size());
    for (auto itr : m_op_map) {
        devices.push_back(itr.second);
    }
    auto sorted_idx = dag::Evaluator::TopologicalSorting(devices);

    for (auto& idx : sorted_idx)
    {
        auto op = devices[idx];
        if (op->IsDirty()) {
            std::static_pointer_cast<Operator>(op)->Execute();
            op->SetDirty(false);
        }
    }
}

}
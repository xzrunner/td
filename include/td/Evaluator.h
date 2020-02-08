#pragma once

#include "td/typedef.h"
#include "td/ParamType.h"

#include <dag/Node.h>

#include <map>

namespace td
{

class Evaluator
{
public:
    // update op
    void ComponentChaged(const OpPtr& op);

    // update devices
    void AddComponent(const OpPtr& op);
    void RemoveComponent(const OpPtr& op);
    void ClearAllComponents();

    // update op prop
    void PropChanged(const OpPtr& op);

    // update op conn
    void Connect(const dag::Node<ParamType>::PortAddr& from, const dag::Node<ParamType>::PortAddr& to);
    void Disconnect(const dag::Node<ParamType>::PortAddr& from, const dag::Node<ParamType>::PortAddr& to);
    void RebuildConnections(const std::vector<std::pair<dag::Node<ParamType>::PortAddr, dag::Node<ParamType>::PortAddr>>& conns);

    void MakeDirty();

    void Update();

    auto& GetAllOps () const { return m_op_map; }

private:
    std::map<std::string, OpPtr> m_op_map;

    bool m_dirty = false;

    size_t m_next_id = 0;

}; // Evaluator

}
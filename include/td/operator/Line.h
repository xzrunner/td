#pragma once

#include "td/Operator.h"

#include <SM_Vector.h>

namespace td
{
namespace op
{

class Line : public Operator
{
public:
    Line()
        : Operator(1)
    {
        m_exports = {
            {{ ParamType::Geo, "Geo" }},
        };
    }

    virtual void Execute(const std::shared_ptr<dag::Context>& ctx = nullptr) override;

    RTTR_ENABLE(Operator)

#define PARM_FILEPATH "td/operator/Line.parm.h"
#include <dag/node_parms_gen.h>
#undef PARM_FILEPATH

}; // Line

}
}
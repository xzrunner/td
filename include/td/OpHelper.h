#pragma once

#include "td/typedef.h"

namespace td
{

class OpHelper
{
public:
    static OpPtr GetInputOp(const Operator& op, size_t idx);
    static ParamPtr GetInputParam(const Operator& op, size_t idx);

}; // OpHelper

}
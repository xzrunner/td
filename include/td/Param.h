#pragma once

#include "td/ParamType.h"

namespace td
{

class Param
{
public:
    virtual ParamType Type() const = 0;

}; // Param

}
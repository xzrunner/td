#pragma once

#include <memory>

namespace td
{

class Operator;
using OpPtr = std::shared_ptr<Operator>;

class Param;
using ParamPtr = std::shared_ptr<Param>;

}
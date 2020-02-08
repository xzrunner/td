#pragma once

#include <dag/Variable.h>

namespace test
{

void init();

void check_value_approx(const dag::Variable& v0, const dag::Variable& v1);

}
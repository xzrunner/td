#include "utility.h"

#include <vop/VOP.h>

#include <catch/catch.hpp>

namespace
{

void InitVOP()
{
    vop::VOP::Instance();
}

}

namespace test
{

void init()
{
    static bool inited = false;
    if (!inited)
    {
        InitVOP();

        inited = true;
    }
}

void check_value_approx(const dag::Variable& v0, const dag::Variable& v1)
{
    REQUIRE(v0.type == v1.type);
    switch (v0.type)
    {
    case dag::VarType::Invalid:
        break;
    case dag::VarType::Bool:
        REQUIRE(v0.b == v1.b);
        break;
    case dag::VarType::Int:
        REQUIRE(v0.i == v1.i);
        break;
    case dag::VarType::Float:
        REQUIRE(v0.f == Approx(v1.f));
        break;
    case dag::VarType::Float3:
    {
        auto f0 = static_cast<const float*>(v0.p);
        auto f1 = static_cast<const float*>(v1.p);
        for (int i = 0; i < 3; ++i) {
            REQUIRE(f0[i] == Approx(f1[i]));
        }
        break;
    }
    case dag::VarType::Double:
        REQUIRE(v0.d == Approx(v1.d));
        break;
    case dag::VarType::String:         
        REQUIRE(strcmp(
            static_cast<const char*>(v0.p), 
            static_cast<const char*>(v1.p)
        ) == 0);
        break;
    default:
        assert(0);
    }
}

}
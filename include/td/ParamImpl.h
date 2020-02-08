#pragma once

#include "td/Param.h"
#include "td/GeoDetail.h"

namespace td
{

class GeoParam : public Param
{
public:
    explicit GeoParam(const GeoDetail& geo)
        : m_geo(geo) {}

    virtual ParamType Type() const override {
        return ParamType::Geo;
    }

    auto& GetGeo() const { return m_geo; }

private:
    GeoDetail m_geo;

}; // GeoParam

}
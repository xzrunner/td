#pragma once

#include <SM_Vector.h>

#include <vector>

namespace td
{

class GeoDetail
{
public:
    struct Point
    {
        Point() {}
        Point(const sm::vec3& pos);

        sm::vec3 pos;
    };

    struct Primitive
    {
        std::vector<size_t> points;
    };

public:
    GeoDetail(const std::vector<sm::vec3>& pts,
        const std::vector<std::vector<size_t>>& prims);

    auto& GetPoints() const { return m_pts; }
    auto& GetPrimitives() const { return m_prims; }

private:
    std::vector<Point>     m_pts;
    std::vector<Primitive> m_prims;

}; // GeoDetail

}
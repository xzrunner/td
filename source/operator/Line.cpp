#include "td/operator/Line.h"
#include "td/ParamImpl.h"

namespace td
{
namespace op
{

void Line::Execute()
{
    if (m_points < 2) {
        m_vals[0] = nullptr;
        return;
    }

    std::vector<sm::vec3> pts;
    pts.resize(m_points);
    pts[0] = m_pa;
    pts[pts.size() - 1] = m_pb;
    auto offset = (m_pb - m_pa) / static_cast<float>(m_points);
    for (size_t i = 0, n = m_points - 2; i < n; ++i) {
        pts[1 + i] = m_pa + offset * static_cast<float>(i + 1);
    }

    std::vector<size_t> prim;
    prim.resize(m_points);
    for (int i = 0; i < m_points; ++i) {
        prim[i] = i;
    }

    GeoDetail geo(pts, { prim });
    m_vals[0] = std::make_shared<GeoParam>(geo);
}

}
}
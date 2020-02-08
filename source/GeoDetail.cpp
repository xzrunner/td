#include "td/GeoDetail.h"

namespace td
{

GeoDetail::GeoDetail(const std::vector<sm::vec3>& pts,
                     const std::vector<std::vector<size_t>>& prims)
{
    m_pts.resize(pts.size());
    for (size_t i = 0, n = pts.size(); i < n; ++i) {
        m_pts[i].pos = pts[i];
    }

    m_prims.resize(prims.size());
    for (size_t i = 0, n = prims.size(); i < n; ++i) {
        m_prims[i].points = prims[i];
    }
}

}
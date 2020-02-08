#ifndef PARAM_INFO
#error "You must define PARAM_INFO macro before include this file"
#endif

PARAM_INFO(PointA,    Float3, pa,     m_pa,     (0, 0, 0))
PARAM_INFO(PointB,    Float3, pb,     m_pb,     (1, 0, 0))
PARAM_INFO(PointsNum, Int,    points, m_points, (2))

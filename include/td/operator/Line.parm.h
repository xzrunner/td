#ifndef PARAM_INFO
#error "You must define PARAM_INFO macro before include this file"
#endif

PARAM_INFO(PointA,    sm::vec3, pa,     m_pa,     (0, 0, 0))
PARAM_INFO(PointB,    sm::vec3, pb,     m_pb,     (1, 0, 0))
PARAM_INFO(PointsNum, int,      points, m_points, (2))

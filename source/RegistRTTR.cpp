// sop
#include "td/operator/Line.h"

#include <rttr/registration>

RTTR_REGISTRATION
{

// base

rttr::registration::class_<dag::Node<td::ParamType>::Port>("td::Operator::Port")
	.property("var", &dag::Node<td::ParamType>::Port::var)
;

rttr::registration::class_<td::Operator>("td::Operator")
	.method("GetImports", &td::Operator::GetImports)
	.method("GetExports", &td::Operator::GetExports)
;

// sop

rttr::registration::class_<td::op::Line>("td::line")
.constructor<>()
#define PARM_FILEPATH "td/operator/Line.parm.h"
#define PARM_NODE_CLASS td::op::Line
#include <dag/rttr_prop_gen.h>
#undef PARM_NODE_CLASS
#undef PARM_FILEPATH
;

}

namespace td
{

void regist_rttr()
{
}

}
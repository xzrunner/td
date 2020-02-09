#define EXE_FILEPATH "td/op_include_gen.h"
#include "td/op_regist_cfg.h"
#undef EXE_FILEPATH

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

#define EXE_FILEPATH "td/op_rttr_gen.h"
#include "td/op_regist_cfg.h"
#undef EXE_FILEPATH

}

namespace td
{

void regist_rttr()
{
}

}
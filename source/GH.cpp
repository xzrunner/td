#include "td/GH.h"

namespace td
{

CU_SINGLETON_DEFINITION(GH);

extern void regist_rttr();

GH::GH()
{
	regist_rttr();
}

}
#include "td/TD.h"

namespace td
{

CU_SINGLETON_DEFINITION(TD);

extern void regist_rttr();

TD::TD()
{
	regist_rttr();
}

}
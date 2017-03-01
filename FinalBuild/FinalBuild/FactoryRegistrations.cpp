#include "ArgListFactoryHelper.h"
#include "PayOff.h"
#include <string>

namespace
{
	FactoryHelper<PayOff, PayOffCall> callHelper("call");
	FactoryHelper<PayOff, PayOffPut> putHelper("put");
	FactoryHelper<PayOff, PayOffSpread> spreadHelper("spread");
	FactoryHelper<PayOff, PayOffDigitalCall> digitalCallHelper("digital-call");
	FactoryHelper<PayOff, PayOffDigitalPut> digitalPutHelper("digital-put");
	FactoryHelper<PayOff, PayOffDoubleDigital> digitalDoubleHelper("double-digital");

}
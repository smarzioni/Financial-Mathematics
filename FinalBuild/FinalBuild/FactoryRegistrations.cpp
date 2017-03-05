#include "ArgListFactoryHelper.h"
#include "PayOff.h"
#include "PayOffDefs.h"
#include "PayOffInputs.h"
#include "Options.h"
#include "OptionsInput.h"
#include <string>

//PayOff derived classes
namespace
{
	FactoryHelper<PayOff, PayOffCall> callHelper("call");
	FactoryHelper<PayOff, PayOffPut> putHelper("put");
	FactoryHelper<PayOff, PayOffSpread> spreadHelper("spread");
	FactoryHelper<PayOff, PayOffDigitalCall> digitalCallHelper("digital-call");
	FactoryHelper<PayOff, PayOffDigitalPut> digitalPutHelper("digital-put");
	FactoryHelper<PayOff, PayOffDoubleDigital> digitalDoubleHelper("double-digital");
}


//POInputs derived classes;

namespace
{
	FactoryHelper<POInputs, POCallInputs> InputCallHelper("call");
	FactoryHelper<POInputs, POPutInputs> InputPutHelper("put");
	FactoryHelper<POInputs, PODCallInput> InputDCallHelper("digital-call");
	FactoryHelper<POInputs, PODPutInput> InputDPutHelper("digital-put");
	FactoryHelper<POInputs, PODoubleDInputs> InputDDHelper("double-digital");
	FactoryHelper<POInputs, POSpreadInputs> InputSpreadHelper("spread");

}


//Options (PathDependent) derived classes

namespace
{
	FactoryHelper<PathDependent, European> europeanHelper("european");
	FactoryHelper<PathDependent, ArithmeticAsian> arithmeticHelper("arithmetic-asian");
	FactoryHelper<PathDependent, GeometricAsian> geometricHelper("geometric-asian");
	FactoryHelper<PathDependent, DiscreteKnockDownOut> DownOutHeper("knock-down-n-out");
	FactoryHelper<PathDependent, DiscreteKnockUpIn> UpInHelper("knock-up-n-in");
	FactoryHelper<PathDependent, DiscreteKnockUpOut> UpOutHeper("knock-up-n-out");
	FactoryHelper<PathDependent, DiscreteKnockDownIn> DownInHelper("knock-down-n-in");
}

//OptionsInput derived classes

namespace
{
	FactoryHelper<OptionsInput, EuropeanInput> europeanInputHelper("european");
	FactoryHelper<OptionsInput, ArithmeticAsianInput> arithmeticInputHelper("arithmetic-asian");
	FactoryHelper<OptionsInput, GeometricAsianInput> geometricInputHelper("geometric-asian");
	FactoryHelper<OptionsInput, UpAndOutInput> UpOutInput("knock-up-n-out");
	FactoryHelper<OptionsInput, UpAndInInput> UpInInput("knock-up-n-in");
	FactoryHelper<OptionsInput, DownAndOutInput> DownOutInput("knock-down-n-out");
	FactoryHelper<OptionsInput, DownAndInInput> DownInInput("knock-down-n-in");
}

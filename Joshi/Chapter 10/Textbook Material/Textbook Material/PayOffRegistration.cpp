#include "PayOffConstructible.h"

namespace
{
	PayOffHelper<PayOffCall> RegisterCall("call");
	PayOffHelper<PayOffPut> RegisterPut("put");
}
//This is an unnamed namespace, i.e. these variables are global but invisible. 
// we only want to register "call" and "put" into the Factory with the right type of PayOffs 
// associated. The name of the objects performing this registration are not needed.
import stk.hash;
import stk.log;

#pragma warning(push)
#pragma warning(disable: 5050) // _M_FP_PRECISE is defined in current command line and not in module command line
import std.core;
#pragma warning(pop)

using namespace NStk;
using namespace NLog;
using namespace stk::hash;

int main(int argc, char* argv[])
{
	hash hash1(std::string("Hello World!"));
	Log("The hash of Hello World! is %u\n", hash1);

	if (argc > 1)
	{
		hash hash2(argv[1], std::strlen(argv[1]));
		Log("The hash of %s is %u\n", argv[1], hash2);
	}

	return 0;
}

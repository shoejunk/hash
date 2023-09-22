import stk.hash;
import stk.log;
import std.core;

using namespace NStk;
using namespace NLog;
using namespace NHash;
using namespace std;

int main(int argc, char* argv[])
{
	CHash oHash1(string("Hello World!"));
	Log("The hash of Hello World! is %u\n", oHash1);

	if (argc > 1)
	{
		CHash oHash2(argv[1], strlen(argv[1]));
		Log("The hash of %s is %u\n", argv[1], oHash2);
	}

	return 0;
}

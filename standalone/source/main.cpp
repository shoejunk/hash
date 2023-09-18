import stk.hash;
import stk.log;

using namespace NStk;
using namespace NLog;
using namespace NHash;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		CHash oHash(argv[1], strlen(argv[1]));
		Log("The hash of %s is %u\n", argv[1], oHash);
	}

	return 0;
}

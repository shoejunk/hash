#include <iostream>
#include <hash/hash.h>

using namespace NStk;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::cout << NHash::Hash(argv[1]) << std::endl;
	}
	return 0;
}

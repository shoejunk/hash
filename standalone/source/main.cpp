#include <iostream>

#include <hash/hash.h>

using namespace NStk;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		NHash::CHashTable oHashTable;
		std::cout << oHashTable.Insert(argv[1]) << std::endl;
		return 0;
	}

	return 0;
}

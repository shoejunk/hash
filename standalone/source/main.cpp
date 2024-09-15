import std;
import stk.hash;
import stk.log;

using namespace stk;

class c_test
{
public:
	void go()
	{
		log("test go!\n");
	}
};

template<>
constexpr stk::c_hash stk::hash<c_test>()
{
	return stk::c_hash("test");
}

int main(int argc, char* argv[])
{
	c_hash hash1(std::string("Hello World!"));
	log("The hash of Hello World! is %u\n", hash1);

	if (argc > 1)
	{
		c_hash hash2(argv[1], std::strlen(argv[1]));
		log("The hash of %s is %u\n", argv[1], hash2);
	}

	c_test t;
	std::unordered_map<c_hash, std::any, s_hash_hasher> class_map;
	class_map[hash<c_test>()] = t;
	c_test& t2 = std::any_cast<c_test&>(class_map[hash<c_test>()]);
	t2.go();

	return 0;
}

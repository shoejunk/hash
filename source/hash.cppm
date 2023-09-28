export module stk.hash;

#pragma warning(push)
#pragma warning(disable: 5050) // _M_FP_PRECISE is defined in current command line and not in module command line
import std.core;
#pragma warning(pop)
 
export namespace stk::hash
{
	constexpr uint32_t murmur_hash3(const char* key, uint32_t len, uint32_t seed = 0)
	{
		constexpr uint32_t c1 = 0xcc9e2d51;
		constexpr uint32_t c2 = 0x1b873593;
		constexpr uint32_t r1 = 15;
		constexpr uint32_t r2 = 13;
		constexpr uint32_t m = 5;
		constexpr uint32_t n = 0xe6546b64;

		uint32_t hash = seed;

		const int numBlocks = len / 4;
		const uint32_t* blocks = (const uint32_t*)key;

		for (int i = 0; i < numBlocks; i++) {
			uint32_t k = blocks[i];
			k *= c1;
			k = (k << r1) | (k >> (32 - r1)); // Rotate left
			k *= c2;

			hash ^= k;
			hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
		}

		const uint8_t* tail = (const uint8_t*)(key + numBlocks * 4);
		uint32_t k1 = 0;

		switch (len & 3) {
		case 3: k1 ^= tail[2] << 16;
		case 2: k1 ^= tail[1] << 8;
		case 1: k1 ^= tail[0];
			k1 *= c1; k1 = (k1 << r1) | (k1 >> (32 - r1)); k1 *= c2; hash ^= k1;
		}

		hash ^= len;
		hash ^= (hash >> 16);
		hash *= 0x85ebca6b;
		hash ^= (hash >> 13);
		hash *= 0xc2b2ae35;
		hash ^= (hash >> 16);

		return hash;
	}

	constexpr uint32_t fnv1a_hash(const char* key, uint32_t len, uint32_t seed=0)
	{
		constexpr uint32_t fnv_prime = 16777619;
		uint32_t hash = seed;

		for (uint32_t i = 0; i < len; i++)
		{
			hash ^= key[i];
			hash *= fnv_prime;
		}

		return hash;
	}

	constexpr uint32_t universal_hash(const char* str, uint32_t seed = 0)
	{
		constexpr uint32_t mod = 1'000'000'009;  // Some large prime number
		constexpr uint32_t base = 257;           // Prime larger than the size of the ASCII character set

		uint32_t hash = seed;
		for (uint32_t i = 0; str[i] != '\0'; ++i)
		{
			hash = (hash * base + str[i]) % mod;
		}
		return hash;
	}

	class hash
	{
	public:
		constexpr hash() : m_hash(0) {}
		constexpr hash(uint32_t h) : m_hash(h) {}
		constexpr hash(char const* key, uint32_t len)
			: hash(fnv1a_hash(key, len))
		{
		}

		constexpr hash(std::string const& key)
			: hash(fnv1a_hash(key.c_str(), key.size()))
		{
		}

		operator uint32_t() const { return m_hash; }

		constexpr bool operator==(const hash& rhs) const
		{
			return m_hash == rhs.m_hash;
		}

		constexpr bool operator==(uint32_t rhs) const
		{
			return m_hash == rhs;
		}

		constexpr hash operator+(std::string const& key) const
		{
			return hash(fnv1a_hash(key.c_str(), key.size(), m_hash));
		}

	public:
		// Intentionally make this public to allow CHashes to be used as non-type template parameters.
		uint32_t m_hash;
	};
	constexpr hash foo_hash = hash("foo", 3);
	static_assert(foo_hash == fnv1a_hash("foo", 3));
	static_assert(hash("foobaz", 6) == hash("foo", 3) + std::string("baz"));
	static_assert(hash("foobaz", 6) == hash("foobaz"));

	// This can be used as a hash function for std::unordered_map
	struct hash_hasher
	{
		std::size_t operator()(const hash& h) const
		{
			return h.m_hash; // Use the m_hash member as the hash value
		}
	};

	constexpr hash operator "" _h(const char* key, size_t len)
	{
		return hash(key, len);
	}
	static_assert("foo"_h == hash("foo"));
}

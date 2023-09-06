#pragma once

#include <cstdint>

namespace NStk::NHash
{
	constexpr uint32_t MurmurHash3(const char* key, uint32_t len, uint32_t seed = 0)
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

	constexpr uint32_t FNV1aHash(const char* key, uint32_t len, uint32_t seed=0)
	{
		constexpr uint32_t FNV_prime = 16777619;
		constexpr uint32_t FNV_offset_basis = 2166136261;

		uint32_t hash = FNV_offset_basis ^ seed;

		for (uint32_t i = 0; i < len; i++)
		{
			hash ^= key[i];
			hash *= FNV_prime;
		}

		return hash;
	}

	constexpr uint32_t UniversalHash(const char* sStr, uint32_t uSeed = 0)
	{
		constexpr uint32_t uMod = 1'000'000'009;  // Some large prime number
		constexpr uint32_t uBase = 257;           // Prime larger than the size of the ASCII character set

		uint32_t uHash = uSeed;
		for (uint32_t i = 0; sStr[i] != '\0'; ++i)
		{
			uHash = (uHash * uBase + sStr[i]) % uMod;
		}
		return uHash;
	}

	constexpr uint32_t Hash(const char* key, uint32_t len, uint32_t seed = 0)
	{
		return FNV1aHash(key, len, seed);
	}

	class CHashTable
	{
	public:
		constexpr uint32_t Insert(char const* ksStr)
		{
			uint32_t uHash = UniversalHash(ksStr);
			uint32_t uIndex = uHash % 8;
			m_aTable[uIndex].m_uHash = uHash;
			m_aTable[uIndex].m_ksStr = ksStr;
			return uIndex;
		}

	private:
		struct SHashEntry
		{
			uint32_t m_uHash;
			char const* m_ksStr;
		};

		SHashEntry m_aTable[8];
	};

	static_assert(CHashTable().Insert("foo") == 4);
}

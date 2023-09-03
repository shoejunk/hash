#pragma once

#include <cstdint>

namespace NStk::NHash
{
	constexpr uint32_t Hash(char const* ksText)
	{
		uint32_t h = 1;
		for (char const* pkcC = ksText; *pkcC != 0; pkcC++)
		{
			h *= *pkcC;
		}
		return h;
	}
}

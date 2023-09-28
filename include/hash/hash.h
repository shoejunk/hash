#pragma once

#define CLASS_HASH(cls) (stk::hash::hash("class "#cls, sizeof(#cls) - 1))

#pragma once

#define CLASS_HASH(cls) (stk::hash::hash(#cls, sizeof(#cls) - 1))

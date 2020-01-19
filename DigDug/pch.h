#ifndef PCH_H
#define PCH_H
#include "FlginPCH.h"
template <typename T>
inline int Sign(T value)
{
	return (T{ 0 } < value) - (value < T{ 0 });
}
#endif
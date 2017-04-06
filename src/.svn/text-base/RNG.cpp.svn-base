#include "RNG.h"

RNG::RNG(unsigned long long seed) :
	_seed(seed) {
	_mult = 62089911ULL;
	_llongMax = 4294967295ULL;
	_floatMax = 4294967295.0f;
}

RNG::~RNG() {
}

float RNG::operator()() {
	_seed *= _mult;
	return float(_seed % _llongMax) / _floatMax;
}

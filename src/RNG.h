#ifndef RNG_H_
#define RNG_H_

class RNG {
public:
	unsigned long long _seed;
	unsigned long long _mult;
	unsigned long long _llongMax;
	float _floatMax;

	RNG(unsigned long long seed = 7564231ULL);
	virtual ~RNG();

	float operator()();
};

#endif /* RNG_H_ */

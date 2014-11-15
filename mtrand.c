#include <limits.h>
#include "mtrand.h"

#define N 624UL
#define M 397UL
#define MATRIX_A 0x9908b0dfUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7fffffffUL

static unsigned long mti = N+1, mt[N];

void smtrand(unsigned long s) {
	mt[0] = s & 0xffffffffUL;
	for (mti = 1; mti < N; mti++) mt[mti] = (1812433253UL*(mt[mti-1] ^ (mt[mti-1] >> 30))+mti) & 0xffffffffUL;
}

unsigned long mtrand(void) {
unsigned long i, y;
static unsigned long mag01[2] = { 0x0UL, MATRIX_A };
	if (mti >= N) {
		if (mti == N+1) smtrand(5489UL);
		for (i = 0; i < N-M; i++) {
			y = (mt[i] & UPPER_MASK) | (mt[i+1] & LOWER_MASK);
			mt[i] = mt[i+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (; i < N-1; i++) {
			y = (mt[i] & UPPER_MASK) | (mt[i+1] & LOWER_MASK);
			mt[i] = mt[i+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];
		mti = 0;
	}
	y = mt[mti];
	mti++;
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);
	return y;
}

unsigned long emtrand(unsigned long v) {
	return (unsigned long)(mtrand()/(ULONG_MAX+1.0)*v);
}

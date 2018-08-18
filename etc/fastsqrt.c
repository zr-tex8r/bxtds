#include <stdio.h>
#include <stdlib.h>

//-------------------------------------- ilog

#define ILOG_THRES_FIRST  (1<<8)
#define ILOG_THRES_SECOND (1<<16)
#define ILOG_THRES_THIRD  (1<<24)
static int ilog_table[ILOG_THRES_FIRST + 31];

static void init_ilog(void) {
	ilog_table[0] = 0;
	for (int value = 0, t = 1; value < 8; ++value, t *= 2) {
		for (int i = t; i < t*2; i++)
			ilog_table[i] = value;
	}
	for (int i = 0, t = 1; i < 31; ++i, t *= 2) {
		ilog_table[ILOG_THRES_FIRST + i]  = t;
	}
}

int ilog(int x) {
	if (x < 0) {
		return 0;
	} else if (x < ILOG_THRES_FIRST) {
		return ilog_table[x];
	} else if (x < ILOG_THRES_SECOND) {
		return 8 + ilog_table[x / ILOG_THRES_FIRST];
	} else if (x < ILOG_THRES_THIRD) {
		return 16 + ilog_table[x / ILOG_THRES_SECOND];
	} else {
		return 24 + ilog_table[x / ILOG_THRES_THIRD];
	}
}

int exp(int x) {
	if (x < 0) {
		return 0;
	} else if (x < 31) {
		return ilog_table[x + ILOG_THRES_FIRST];
	} else {
		return 0;
	}
}

//-------------------------------------- isqrt

#define ISQRT_HLLIMIT 10
#define ISQRT_LLIMIT (ISQRT_HLLIMIT*2)
#define ISQRT_LIMIT (1<<ISQRT_LLIMIT)
#define ISQRT_TABLE_SIZE (2<<ISQRT_HLLIMIT)

static int isqrt_table[ISQRT_TABLE_SIZE];

static void init_isqrt(void) {
	int t = ISQRT_TABLE_SIZE / 4;
	for (int i = ISQRT_TABLE_SIZE / 4; i < ISQRT_TABLE_SIZE; i++) {
		if ((t+1) * (t+1) <= i << (ISQRT_HLLIMIT - 1))
			++t;
		isqrt_table[i] = t;
	}
}

int isqrt(int x) {
	int ilx = ilog(x);
	int hlu = (ISQRT_LLIMIT - 1 - ilx) / 2;
	int ux = x << (hlu * 2);
	int t = ux >> (ISQRT_HLLIMIT - 1);
	if (t < ISQRT_TABLE_SIZE / 4) {
		fprintf(stderr, "FAILURE(TI,%d,%d)\n", x, t);
		exit(1);
	}
	t = isqrt_table[t] >> hlu;
	if ((t+1) * (t+1) <= x) t++;
	if ((t+1) * (t+1) <= x) t++;
	if (!(t * t <= x && x < (t+1) * (t+1))) {
		fprintf(stderr, "FAILURE(SV,%d(0x%X))\n", x, x);
		exit(1);
	}
	return t;
}

int main() {
	init_ilog();
	init_isqrt();

	for (int i = 1; i < ISQRT_LIMIT; i++) {
		isqrt(i);
	}

	return EXIT_SUCCESS;
}


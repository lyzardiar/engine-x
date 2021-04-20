#pragma once 

#include<cmath>

class _Double {
public: const double POSITIVE_INFINITY = HUGE_VAL;
public: const double NEGATIVE_INFINITY = -HUGE_VAL;
public: const double NaN = NAN;

public: const double MAX_VALUE = 1.79E+308;
public: const double MIN_VALUE = 5.00E-324;

public: const double EPSILON = 2.2204460492503130808472633361816e-16;

public: long long doubleToLongBits(double val) {
	union {
		double dval;
		long long lval;
	}a;

	a.dval = val;
	return a.lval;
}

public: double longBitsToDouble(long long val) {
	union {
		double dval;
		long long lval;
	}a;

	a.lval = val;
	return a.dval;
}
};

extern _Double Double;

/*
const double Double::POSITIVE_INFINITY = INFINITY;
const double Double::NEGATIVE_INFINITY = -INFINITY;
const double Double::NaN = NAN;

const double Double::MAX_VALUE = 1.79E+308;
const double Double::MIN_VALUE = 5.00E-324;
const double Double::EPSILON = 2.2204460492503130808472633361816e-16;
*/
#ifndef _TMOCK_H_
#define _TMOCK_H_

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "hook.h"

using ::testing::Invoke;
using ::testing::_;

#define TMOCK_INC0 1
#define TMOCK_INC1 2
#define TMOCK_INC2 3
#define TMOCK_INC3 4
#define TMOCK_INC4 5
#define TMOCK_INC5 6
#define TMOCK_INC6 7
#define TMOCK_INC7 8
#define TMOCK_INC8 9
#define TMOCK_INC9 10
#define TMOCK_INC10 11

#define TMOCK_INC(n) TMOCK_INC##n

#define TMOCK_S(s) s
#define TMOCK_CAT_(x, y) x##y
#define TMOCK_CAT(x, y) TMOCK_CAT_(x, y)


#define TMOCK_METHOD_IMPL(hooklib, oldmethod, method, result, params, argscount, ...) \
	static result TMOCK_CAT(Hooked, method)params \
	{\
		return MockClass::Instance()->method(__VA_ARGS__); \
	} \
	static void Mock##method(...) \
	{ \
		static bool s_mocked##method = false; \
		if (s_mocked##method == false) \
		{ \
			s_mocked##method = true; \
			Hook::HookFunction((void*)::method, (void*)&MockClass::Hooked##method); \
		} \
	} \
	\
	TMOCK_CAT(MOCK_METHOD, argscount)(method, TMOCK_S(result)params);


// _,_,_,_
#define TMOCK_ANY_ARGS_0
#define TMOCK_ANY_ARGS_1 _
#define TMOCK_ANY_ARGS_2 _,_
#define TMOCK_ANY_ARGS_3 _,_,_
#define TMOCK_ANY_ARGS_4 _,_,_,_
#define TMOCK_ANY_ARGS_5 _,_,_,_,_
#define TMOCK_ANY_ARGS_6 _,_,_,_,_,_
#define TMOCK_ANY_ARGS_7 _,_,_,_,_,_,_
#define TMOCK_ANY_ARGS_8 _,_,_,_,_,_,_,_
#define TMOCK_ANY_ARGS_9 _,_,_,_,_,_,_,_,_
#define TMOCK_ANY_ARGS_10 _,_,_,_,_,_,_,_,_,_

#define TMOCK_ANY_ARGS(n) TMOCK_ANY_ARGS_##n

// TMOCK_ARGSN
#define TMOCK_ARGS_0
#define TMOCK_ARGS_1 p1
#define TMOCK_ARGS_2 p1,p2
#define TMOCK_ARGS_3 p1,p2,p3
#define TMOCK_ARGS_4 p1,p2,p3,p4
#define TMOCK_ARGS_5 p1,p2,p3,p4,p5
#define TMOCK_ARGS_6 p1,p2,p3,p4,p5,p6
#define TMOCK_ARGS_7 p1,p2,p3,p4,p5,p6,p7
#define TMOCK_ARGS_8 p1,p2,p3,p4,p5,p6,p7,p8
#define TMOCK_ARGS_9 p1,p2,p3,p4,p5,p6,p7,p8,p9
#define TMOCK_ARGS_10 p1,p2,p3,p4,p5,p6,p7,p8,p9,p10

#define TMOCK_ARGS(n) TMOCK_ARGS_##n

// TMOCK_PARAMS
#define TMOCK_PARAMS_0(...)

// Need to implement self
#define TMOCK_PARAMS_1(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1

#define TMOCK_PARAMS_2(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2

#define TMOCK_PARAMS_3(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3

#define TMOCK_PARAMS_4(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3, \
	GMOCK_ARG_(, 4, __VA_ARGS__) p4

#define TMOCK_PARAMS_5(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3, \
	GMOCK_ARG_(, 4, __VA_ARGS__) p4, \
	GMOCK_ARG_(, 5, __VA_ARGS__) p5

#define TMOCK_PARAMS_6(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3, \
	GMOCK_ARG_(, 4, __VA_ARGS__) p4, \
	GMOCK_ARG_(, 5, __VA_ARGS__) p5, \
	GMOCK_ARG_(, 6, __VA_ARGS__) p6

#define TMOCK_PARAMS_7(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3, \
	GMOCK_ARG_(, 4, __VA_ARGS__) p4, \
	GMOCK_ARG_(, 5, __VA_ARGS__) p5, \
	GMOCK_ARG_(, 6, __VA_ARGS__) p6, \
	GMOCK_ARG_(, 7, __VA_ARGS__) p7

#define TMOCK_PARAMS_8(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3, \
	GMOCK_ARG_(, 4, __VA_ARGS__) p4, \
	GMOCK_ARG_(, 5, __VA_ARGS__) p5, \
	GMOCK_ARG_(, 6, __VA_ARGS__) p6, \
	GMOCK_ARG_(, 7, __VA_ARGS__) p7, \
	GMOCK_ARG_(, 8, __VA_ARGS__) p8

#define TMOCK_PARAMS_9(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3, \
	GMOCK_ARG_(, 4, __VA_ARGS__) p4, \
	GMOCK_ARG_(, 5, __VA_ARGS__) p5, \
	GMOCK_ARG_(, 6, __VA_ARGS__) p6, \
	GMOCK_ARG_(, 7, __VA_ARGS__) p7, \
	GMOCK_ARG_(, 8, __VA_ARGS__) p8, \
	GMOCK_ARG_(, 9,__VA_ARGS__) p9

#define TMOCK_PARAMS_10(...) \
	GMOCK_ARG_(, 1, __VA_ARGS__) p1, \
	GMOCK_ARG_(, 2, __VA_ARGS__) p2, \
	GMOCK_ARG_(, 3, __VA_ARGS__) p3, \
	GMOCK_ARG_(, 4, __VA_ARGS__) p4, \
	GMOCK_ARG_(, 5, __VA_ARGS__) p5, \
	GMOCK_ARG_(, 6, __VA_ARGS__) p6, \
	GMOCK_ARG_(, 7, __VA_ARGS__) p7, \
	GMOCK_ARG_(, 8, __VA_ARGS__) p8, \
	GMOCK_ARG_(, 9, __VA_ARGS__) p9, \
	GMOCK_ARG_(, 10, __VA_ARGS__) p10

#define TMOCK_PARAMS(n, ...) (TMOCK_PARAMS_##n(__VA_ARGS__))

// TMOCK_METHODNN
#define TMOCK_METHOD_(argscount, hooklib, oldmethod, method, ...) \
	TMOCK_METHOD_IMPL(hooklib, oldmethod, method, \
		GMOCK_RESULT_(, __VA_ARGS__), TMOCK_PARAMS(argscount, __VA_ARGS__), \
		argscount, TMOCK_ARGS(argscount))

// oldmethod: method to be hooked
// example: TMOCK_METHOD1("Foo::Turtle::Run", Run, void(int));
#define TMOCK_METHOD0(oldmethod, method, ...) TMOCK_METHOD_(0, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD1(method, ...) TMOCK_METHOD_(1, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD2(oldmethod, method, ...) TMOCK_METHOD_(2, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD3(oldmethod, method, ...) TMOCK_METHOD_(3, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD4(oldmethod, method, ...) TMOCK_METHOD_(4, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD5(oldmethod, method, ...) TMOCK_METHOD_(5, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD6(oldmethod, method, ...) TMOCK_METHOD_(6, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD7(oldmethod, method, ...) TMOCK_METHOD_(7, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD8(oldmethod, method, ...) TMOCK_METHOD_(8, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD9(oldmethod, method, ...) TMOCK_METHOD_(9, _lib, oldmethod, method, __VA_ARGS__)
#define TMOCK_METHOD10(oldmethod, method, ...) TMOCK_METHOD_(10, _lib, oldmethod, method, __VA_ARGS__)

#define TMOCK_DL_METHOD0(oldmethod, method, ...) TMOCK_METHOD_(0,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD1(oldmethod, method, ...) TMOCK_METHOD_(1,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD2(oldmethod, method, ...) TMOCK_METHOD_(2,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD3(oldmethod, method, ...) TMOCK_METHOD_(3,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD4(oldmethod, method, ...) TMOCK_METHOD_(4,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD5(oldmethod, method, ...) TMOCK_METHOD_(5,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD6(oldmethod, method, ...) TMOCK_METHOD_(6,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD7(oldmethod, method, ...) TMOCK_METHOD_(7,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD8(oldmethod, method, ...) TMOCK_METHOD_(8,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD9(oldmethod, method, ...) TMOCK_METHOD_(9,, oldmethod, method, __VA_ARGS__)
#define TMOCK_DL_METHOD10(oldmethod, method, ...) TMOCK_METHOD_(10,, oldmethod, method, __VA_ARGS__)



#define TMOCK_CLASS(cls) \
	typedef cls MockClass; \
	static cls* Instance() \
	{ \
	    static cls s_cls; \
		return &s_cls; \
	}

#define TEXPECT_CALL(mockCls, call) \
    mockCls::Mock##call; \
	EXPECT_CALL(*mockCls::Instance(), call)

#define TMOCK_CLEAR(mockCls) ::testing::Mock::VerifyAndClearExpectations(mockCls::Instance())

#endif // _TMOCK_H_

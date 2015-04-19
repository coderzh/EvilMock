#include <windows.h>
#include "../sut/demo.h"

#include "hook.h"
#include "hookmock.h"

using ::testing::Return;

bool MyConnect(const char* url)
{

	return true;
}

int MyPrintf(const char* format, ...)
{
	Hook::UnHookFunction(printf);

	return printf(format);
}

class MockGlobal
{
public:
	TMOCK_CLASS(MockGlobal);

	TMOCK_METHOD1(Connect, bool(const char* url));
};

TEST(GlobalMethodTest, NoNamespace)
{
	TEXPECT_CALL(MockGlobal, Connect(_))
		.Times(1).WillOnce(Return(true));
	ASSERT_TRUE(Connect("127.0.0.1"));

	Hook::UnHookFunction(Connect);
	ASSERT_FALSE(Connect("127.0.0.1"));

	Hook::HookFunction(printf, MyPrintf);
	printf("abc");
}
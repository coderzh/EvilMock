#ifndef _HOOK_H_
#define _HOOK_H_

#ifdef _MSC_VER
#include <windows.h>
#endif

#include <map>

class Hook
{
private:
#define SIZE 6

	struct FunctionInfo
	{
		BYTE firstBytes[SIZE];
	};

	Hook()
	{

	}

	static Hook* GetInstance()
	{
		static Hook g_hook;
		return &g_hook;
	}

	std::map<void*, FunctionInfo> m_hookedFunctions;

public:

	bool IsHooked(void* function)
	{
		if (m_hookedFunctions.find(function) == m_hookedFunctions.end())
		{
			return false;
		}

		return true;
	}

	void HookFunctionImp(void* oldFunction, void* newFunction)
	{
		if (IsHooked(oldFunction))
		{
			UnHookFunctionImp(oldFunction);
		}

		FunctionInfo functionInfo;

		DWORD oldProtect;
		BYTE jmp[SIZE] = { 0 };
		BYTE tempJmp[SIZE] = { 0xE9, 0x90, 0x90, 0x90, 0x90, 0xC3 };
		memcpy(jmp, tempJmp, SIZE);
		DWORD jmpSize = ((DWORD)newFunction - (DWORD)oldFunction - 5);
		VirtualProtect(oldFunction, SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(functionInfo.firstBytes, oldFunction, SIZE);
		memcpy(&jmp[1], &jmpSize, 4);
		memcpy(oldFunction, jmp, SIZE);
		VirtualProtect(oldFunction, SIZE, oldProtect, NULL);

		m_hookedFunctions[oldFunction] = functionInfo;
	}

	void UnHookFunctionImp(void* oldFunction)
	{
		if (!IsHooked(oldFunction))
		{
			return;
		}

		FunctionInfo& functionInfo = m_hookedFunctions[oldFunction];

		DWORD oldProtect;
		VirtualProtect(oldFunction, SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(oldFunction, functionInfo.firstBytes, SIZE);
		VirtualProtect(oldFunction, SIZE, oldProtect, NULL);
	}

	static void HookFunction(void* oldFunction, void* newFunction)
	{
		Hook::GetInstance()->HookFunctionImp(oldFunction, newFunction);

	}

	static void UnHookFunction(void* oldFunction)
	{
		Hook::GetInstance()->UnHookFunctionImp(oldFunction);
	}
};


#endif // _HOOK_H_

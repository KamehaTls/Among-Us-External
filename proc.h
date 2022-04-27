#pragma once
#include<vector>
#include<windows.h>
#include<TlHelp32.h>

DWORD GetProcid(const wchar_t* procName);

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName);

uintptr_t FindDMAAddy(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int> offsets);

uintptr_t mainMenu(int playerInp, DWORD procID);
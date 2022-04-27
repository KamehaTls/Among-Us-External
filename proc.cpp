#include<iostream>
#include "proc.h"
#include<tchar.h>

DWORD GetProcid(const wchar_t* procName) {
	DWORD procID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry)) {

			do {
				if (!_wcsicmp(procEntry.szExeFile, procName))
				{
					procID = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procID;
}

uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName)
{
	uintptr_t modBaseaddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, procID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseaddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(hSnap, &modEntry));
		}
	}
	else
	{
		std::cout << "GetModuleBaseAddress() failed\n------------------------------" << std::endl;
		Sleep(5000);
		return EXIT_FAILURE;

	}
	CloseHandle(hSnap);
	return modBaseaddr;
}

uintptr_t FindDMAAddy(HANDLE hproc, uintptr_t ptr, std::vector<unsigned int> offsets)
{
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(hproc, (BYTE*)addr, &addr, sizeof(addr), 0);
		std::cout << "addy" << std::hex << i << " : 0x" << addr << std::endl;
		addr += offsets[i];
	}
	return addr;
}



uintptr_t mainMenu(int playerInp, DWORD procID)
{
	uintptr_t modBase = 0;
	uintptr_t PS_DynamicBaseAddr = 0;
	uintptr_t LS_DynamicBaseAddr = 0;
	uintptr_t imp_DynamicBaseAddr = 0;

	if (playerInp == 0)
	{
		//Getmodulebaseaddress - Player Settings
		wchar_t modName1[] = L"GameAssembly.dll";
		uintptr_t modBase = GetModuleBaseAddress(procID, modName1);
		std::cout << "\nModule Base = " << std::hex << std::uppercase << modBase << "\n----------------------------------------" << std::endl;
		//Resolve base address of the pointer chain
		uintptr_t PL_DynamicBaseAddr = modBase + 0x14688CC;
		std::cout << "Base Address = 0x" << std::hex << std::uppercase << PL_DynamicBaseAddr << std::endl;
		return PL_DynamicBaseAddr;
	}
	else if (playerInp == 1)
	{
		//Getmodulebaseaddress - Lobby Settings
		wchar_t modName2[] = L"GameAssembly.dll";
		uintptr_t modBase = GetModuleBaseAddress(procID, modName2);
		std::cout << "Module Base = " << std::hex << std::uppercase << modBase << "\n----------------------------------------" << std::endl;
		//Resolve base address of the pointer chain
		uintptr_t LS_DynamicBaseAddr = modBase + 0x1468910;
		std::cout << "Base Address = 0x" << std::hex << std::uppercase << LS_DynamicBaseAddr << std::endl;
		return LS_DynamicBaseAddr;
	}
	else if (playerInp == 2)
	{
		//Getmodulebaseaddress - In Game hax
		wchar_t modName3[] = L"UnityPlayer.dll";
		uintptr_t modBase = GetModuleBaseAddress(procID, modName3);
		std::cout << "Module Base = 0x" << std::hex << std::uppercase << modBase << "\n----------------------------------------" << std::endl;
		//Resolve base address of the pointer chain
		uintptr_t imp_DynamicBaseAddr = modBase + 0x012dab4c;
		std::cout << "Base Address = 0x" << std::hex << std::uppercase << imp_DynamicBaseAddr << std::endl;
		return imp_DynamicBaseAddr;
	}

	//return modBase;
}
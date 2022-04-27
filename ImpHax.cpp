#include "ImpHax.h"
#include<iostream>
#include "proc.h"
#include<tchar.h>

//imposter settings
void doImphax(DWORD procID, uintptr_t baseAddress)
{
	do
	{
		//Get Handle to the process
		HANDLE hProcess = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

		//Resolve our imposter chain
		std::vector<unsigned int> impOffset = { 0x4c, 0x34, 0x150, 0x5c, 0x0, 0x34, 0x28 };
		uintptr_t impAddr = FindDMAAddy(hProcess, baseAddress, impOffset);
		std::cout << "current pointer to the Adrress = 0x" << std::hex << impAddr << std::endl;

		//Read imposter value
		int impValue = 0;
		ReadProcessMemory(hProcess, (BYTE*)impAddr, &impValue, sizeof(impValue), nullptr);
		std::cout << "Value stored in address is = " << std::dec << impValue << std::endl;
		impStmnt(impValue);
		std::cout << "\n-----------------------------------------" << std::endl;

		//set whether you want to be imposter or not
		std::cout << "Become crew mate = Z\nBecome Imposter = X\nBecome ghost/dead = C" << std::endl;
		std::cout << "press ESC then BACKSPACE to refresh if it stops working" << std::endl;
		for (;;) {
			if (GetAsyncKeyState(0x5A)) {
				int newIMP = 0;
				WriteProcessMemory(hProcess, (BYTE*)impAddr, &newIMP, sizeof(newIMP), nullptr);
			}
			else if (GetAsyncKeyState(0x58))
			{
				int newIMP = 1;
				WriteProcessMemory(hProcess, (BYTE*)impAddr, &newIMP, sizeof(newIMP), nullptr);
			}
			else if (GetAsyncKeyState(0x43))
			{
				int newIMP = 257;
				WriteProcessMemory(hProcess, (BYTE*)impAddr, &newIMP, sizeof(newIMP), nullptr);

			}
			else if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}
		}

		//Read out again
		ReadProcessMemory(hProcess, (BYTE*)impAddr, &impValue, sizeof(impValue), nullptr);
		std::cout << "new value is = " << std::dec << impValue << std::endl;
		impStmnt(impValue);
		std::cout << "\n-----------------------------------------\n" << std::endl;
		system("pause > null");
	} while (GetAsyncKeyState(VK_BACK));
}

void impStmnt(int impValue) {
	if (impValue == 0) {
		std::cout << "You are a crewmate" << std::endl;
	}
	else if (impValue == 1)
	{
		std::cout << "You are an imposter" << std::endl;
	}
	else if (impValue == 257)
	{
		std::cout << "You are DEAD" << std::endl;
	}
	else {
		std::cout << "You chose outside the given options..." << std::endl;
	}
}

void PLsetting(DWORD procID, int Offset)
{
	//gets the process handle
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	//resolve the offsets
	uintptr_t modbase = GetModuleBaseAddress(procID, L"GameAssembly.dll");
	std::vector<unsigned int> plOffset = { 0x5c };
	plOffset.push_back(Offset);
	uintptr_t pladdr = FindDMAAddy(hProcess, modbase, plOffset);
	std::cout << "current pointer to the Adrress = 0x" << std::hex << pladdr << std::endl;

}
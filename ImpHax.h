#pragma once
#include<vector>
#include<windows.h>
#include<TlHelp32.h>
#include<iostream>
#include<tchar.h>

void doImphax(DWORD procID, uintptr_t baseAddress);

void impStmnt(int impValue);

void PLsetting(DWORD procID, int Offset);
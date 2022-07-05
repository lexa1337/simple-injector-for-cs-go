#include <Windows.h>
#include <iostream>
#include "mem.hpp"
#include <string>

using namespace std;

char namedll[32];

Injector inj;

DWORD pid;

bool DoesFileExist(const char* name) {
	if (FILE* file = fopen(name, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

void bypass()
{
	LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	}
	else
	{
		cout << "Unable to bypass.\n";
	}
}

int main()
{
	SetConsoleTitle("Supreme Injector for CS:GO");

	cout << "Supreme Injector Lexa\n\nVisit github.com/lexa1337\n Owner: lexa\n\n" << endl;
	cout << "Developed by Lexa. All rights reserved.";

	inj.hwndproc = FindWindowA(0, "Counter-Strike: Global Offensive - Direct3D 9");

	GetWindowThreadProcessId(inj.hwndproc, &pid);
	inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	inj.clientDLL = inj.GetModule(pid, "client.dll");

	cout << "Enter DLL name:" << endl;
	
	scanf_s("%s", namedll);

	if (DoesFileExist(namedll)) {
		bypass();
		if (inj.inject(pid, namedll)) {
			cout << "Injection successful! You can close this window\n\n" << endl;
			Sleep(5000);
			exit(0);
			}
		else
		{
			cout << "Injection failed, try run as Administrator.\n\n" << endl;
			system("pause");
		}
	}
	else
	{
		cout << "Cannot Find : " << namedll << "\n";
		system("pause");
	}

	return 0;
}
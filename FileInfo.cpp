// FileInfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

int main(int argc, char* argv[], char* envp[]) {
	// Ensure there are some arguments.
	if (argc != 3) {
		std::cout << "Invalid args.\n";
		return -1;
	}

	if (strcmp(argv[1], "ver") == 0) {
		// Get version info size.
		DWORD handle = 0;
		DWORD size = GetFileVersionInfoSizeA(argv[2], &handle);

		// Get version info.
		BYTE* versionInfo = new BYTE[size];
		if (GetFileVersionInfoA(argv[2], handle, size, versionInfo)) {
			UINT len = 0;
			VS_FIXEDFILEINFO* vsfi = NULL;
			VerQueryValueA(versionInfo, "\\", (void**)& vsfi, &len);
			printf("%d.%d.%d.%d\n",
				HIWORD(vsfi->dwFileVersionMS), LOWORD(vsfi->dwFileVersionMS),
				HIWORD(vsfi->dwFileVersionLS), LOWORD(vsfi->dwFileVersionLS));
			delete[] versionInfo;
			return 0;
		}
		delete[] versionInfo;
	}
	else if (strcmp(argv[1], "arch") == 0) {
		// Get and print arch.
		DWORD exeType = 0;
		if (GetBinaryTypeA(argv[2], &exeType)) {
			std::cout << exeType << "\n";
			return 0;
		}
	}

	std::cout << "Invalid function.\n";
	return -1;
}

// FileInfo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*

Copyright (c) 2019 John Davis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

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

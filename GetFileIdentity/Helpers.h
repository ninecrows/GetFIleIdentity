#pragma once
#include <string>
#include <Windows.h>
#include <fileapi.h>

namespace Helpers
{
	std::wstring IngestFile(const std::wstring &filename)
	{
		std::wstring result;

		HANDLE infile(CreateFileW(filename.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr));
		if (infile != INVALID_HANDLE_VALUE)
		{
			BY_HANDLE_FILE_INFORMATION information;
			BOOL ok(GetFileInformationByHandle(infile, &information));
			if (ok)
			{
				long long totalSize(((long long)information.nFileSizeHigh) << 32 | information.nFileSizeLow);

				char *buffer = new char[totalSize];

				DWORD actualRead(0);
				BOOL readOk(ReadFile(infile, buffer, totalSize, &actualRead, NULL));

				int unicodeSize(MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, buffer, totalSize, nullptr, 0));

				result.resize(unicodeSize);
				int resultSize(MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, buffer, totalSize, &(result[0]), unicodeSize));
			}
		}
		return (result);
	}
}
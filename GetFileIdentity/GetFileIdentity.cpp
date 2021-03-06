// GetFileIdentity.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <regex>
#include <Windows.h>
#include "CommandLineOptions.h"
#include "FIleIdInformation.h"
#include "Item.h"
#include "Helpers.h"

int wmain(int argc, wchar_t *argv[])
{
	CommandLineOptions options(argc, argv);

	Helpers::IngestFile(L"t1.json");

	if (options.ItemCount() > 0)
	{
		std::wstring path(options.Item(0));

		FileIdInformation id(path);
		if (id.isOk())
		{
			std::wcout << L"[" << id.describe() << L"]\n";
		}
	}
}

#pragma once
#include <windows.h>
#include <string>

class FileIdInformation
{
private:
	FILE_ID_INFO info;

	bool valid;

	DWORD m_Status;

	inline
	    bool 
		getInformationInternal(HANDLE handle) 
	{
		memset(&info, 0, sizeof(info));

		BOOL ok(::GetFileInformationByHandleEx(handle,
			FileIdInfo,
			&info,
			sizeof(info)));

		if (!ok)
		{
			m_Status = ::GetLastError();
		}

		return (ok);
	}

public:
	inline
	FileIdInformation(HANDLE handle) :
		valid(false), m_Status(ERROR_SUCCESS)
	{
		valid = getInformationInternal(handle);
	}

	inline
		FileIdInformation(const std::wstring path) :
		valid(false), m_Status(ERROR_SUCCESS)
	{
		HANDLE handle(::CreateFileW(path.c_str(),
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr));
		if (handle != INVALID_HANDLE_VALUE)
		{
			valid = getInformationInternal(handle);
			::CloseHandle(handle);
		}
		else
		{
			m_Status = ::GetLastError();
		}
	}

	inline
	bool
		isOk(void) const
	{
		return valid;
	}

	inline
		DWORD
		status(void) const
	{
		return(m_Status);
	}

	inline
	const FILE_ID_INFO &
		getInformation(void) const
	{
		return (info);
	}

	inline
		const std::wstring 
		describe(void) const 
	{
		std::wstring result;

		{
			wchar_t buffer[32];
			_snwprintf_s(buffer, 32, L"%016lx", info.VolumeSerialNumber);
		
			result += buffer;
			result += L":";
		}

		for (int ct = 0; ct < 16; ct++)
		{
			wchar_t buffer[4];
			_snwprintf_s(buffer, 4, L"%02x", info.FileId.Identifier[ct]);
			result += buffer;
		}

		return (result);
	}
};
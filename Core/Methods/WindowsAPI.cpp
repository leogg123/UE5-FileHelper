#include "WindowsAPI.h"

#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <tchar.h>
#pragma  comment(lib, "shell32.lib")


namespace GLCWindowAPI
{
	bool CreateProgramShortcut(const FString& InWorkFileName, const FString& ToFileName)
	{
		bool result = false;
		HRESULT hr = CoInitialize(NULL);
		if (SUCCEEDED(hr))
		{
			IShellLink* shell_link = NULL;
			hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&shell_link);
			if (SUCCEEDED(hr))
			{
				// 设置程序路径
				hr = shell_link->SetPath(*InWorkFileName);

				wchar_t t[0x100]{ 0 };
				wcscpy_s(t, *InWorkFileName);
				wchar_t* p = wcsrchr(t, L'\\');
				if(p)
				{
					p[1] = 0;
				}

				// 设置工作目录
				hr = shell_link->SetWorkingDirectory(t);

				// 设置参数
				hr = shell_link->SetArguments(nullptr);

				// 设置图标
				hr = shell_link->SetIconLocation(nullptr, 0);

				IPersistFile* persist_file = NULL;
				hr = shell_link->QueryInterface(IID_IPersistFile, (void**)&persist_file);
				if (SUCCEEDED(hr))
				{
					// 创建快捷方式
					hr = persist_file->Save((*ToFileName), FALSE);
					if (SUCCEEDED(hr)) result = true;

					persist_file->Release();
				}
				shell_link->Release();
			}
			CoUninitialize();
		}

		return result;
	}

	FVector2D GetSystemScreenSize()
	{
		float cx = GetSystemMetrics(SM_CXFULLSCREEN);
		float cy = GetSystemMetrics(SM_CYFULLSCREEN);
		return FVector2D(cx,cy);
	}
}

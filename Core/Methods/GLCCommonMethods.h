#pragma once
#include "CoreMinimal.h"
#include <Misc/FileHelper.h>

class UGLCSaveObject;

struct GLCFILEHELPER_API FGLCOutputLog
{
	enum EMessageType
	{
		DISPLAY,
		WARNING,
		ERROR
	};

	FGLCOutputLog();

	void AddNewMessage(const FString& InMessage,EMessageType InType = EMessageType::DISPLAY);
protected:
	TSharedPtr<SScrollBox> ScrollBox;
};

namespace GLCCommonMethods
{
	UGLCSaveObject* GetGLCSaveObject();

	FString GetEnginePath();
	void SetEnginePath(const FString& InEnginePath);

	FString GetLastGenerateProgramPath();
	void SetGenerateProgramPath(const FString& InPath);

	bool CheckPath(const FString& InPath);

	void OpenMessageDialogByString(const FString& InMessage);

	
	//方法
	//
	//修改文件编码
	void ModifyFileCoding(const FString& InSearchPath, FFileHelper::EEncodingOptions CodingType);

	//生成新的程序
	void GenerateNewProgram(const FString& InNewProgramName,bool bIsConsoleApp = true,const FString& InTargetPath = GetLastGenerateProgramPath());

	//
}
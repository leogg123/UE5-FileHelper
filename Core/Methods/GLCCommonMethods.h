#pragma once
#include "CoreMinimal.h"
#include <Misc/FileHelper.h>
#include "GLCFileHelper\Core\GLCSaveObject.h"
#include "GLCFileHelper\Core\Type\GLCCoreMacro.h"

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

	REGISTER_SINGLE_SAVE_OBJECT(GenerateProgramPath);
	REGISTER_SINGLE_SAVE_OBJECT(GenerateCompoundWidgetParam);
	REGISTER_SINGLE_SAVE_OBJECT(EnginePath);
	REGISTER_SINGLE_SAVE_OBJECT(GenerateCompoundWidgetPath);

	bool CheckPath(const FString& InPath);

	void OpenMessageDialogByString(const FString& InMessage);

	//通过Source里的某个文件找到根目录
	bool GetSourceDirAndProgramNameByFileName(const FString& InFileName,FString& OutSourceDir,FString& OutProgramName);
	
	bool GetFileIncludeByClassName(const FString& InClassName, const FString& InProgramName,
		const FString& InSourceDir,FString& OutInclude);

	//方法
	//
	//修改文件编码
	void ModifyFileCoding(const FString& InSearchPath, FFileHelper::EEncodingOptions CodingType);

	//生成新的程序
	void GenerateNewProgram(const FString& InNewProgramName,bool bIsConsoleApp = true,const FString& InTargetPath = GetGenerateProgramPath());

	//生成CompoundWidget
	void GenerateCompoundWidget(const FString& InTargetPath,const FString& InNewSlateName,const FString& OptionalParent = FString());

	//
	//
}



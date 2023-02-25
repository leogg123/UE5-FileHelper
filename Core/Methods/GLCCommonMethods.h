#pragma once
#include "CoreMinimal.h"
#include <Misc/FileHelper.h>
#include "GLCFileHelper\Core\GLCSaveObject.h"
#include "GLCFileHelper\Core\Type\GLCCoreMacro.h"

class UGLCSaveObject;


namespace GLCCommonMethods
{
	UGLCSaveObject* GetGLCSaveObject();

	REGISTER_SINGLE_SAVE_INFO(EnginePath);

	REGISTER_SAVE_INFOS(GenerateProgram);
	REGISTER_SAVE_INFOS(GenerateCompoundWidget);
	REGISTER_SAVE_INFOS(ModifyCharacters);
	REGISTER_SAVE_INFOS(ModifyFileCoding);
	REGISTER_SAVE_INFOS(PackageProgram);
	REGISTER_SAVE_INFOS(AddCopyRight);
	REGISTER_SAVE_INFOS(FixInclude);

	bool CheckPath(const FString& InPath);

	bool CreateDirectory(const FString& InPath);
	
	bool CheckEnginePathAndPath(const FString& InPath);

	void OpenMessageDialogByString(const FString& InMessage);

	//通过Source里的某个文件找到根目录
	bool GetSourceDirAndProgramNameByFileName(const FString& InFileName,FString& OutSourceDir,FString& OutProgramName);

	//根据给定信息找到文件的include(绝对路径)
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

	//遍历给定的文件夹，修改给定的字符
	void ModifyCharactersIteration(const FString& InPath,const FString& InSearch,
		const FString& InReplace,const FString& InOptionalCondition = FString());

	//打包独立程序
	void PackageProgram(const FString& InProgramName,const FString& TargetPath);
	//

	//添加权利声明
	void AddCopyRight(const FString& InSearchPath,FString& InCopyRight);

	//修复头文件包含问题
	void FixInclude(const FString& InSearchDir);
	
	//
}



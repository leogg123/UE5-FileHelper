#pragma once
#include "CoreMinimal.h"

#include "GLCSaveObject.generated.h"


UCLASS(config = "GLCSaveObject")
class GLCFILEHELPER_API UGLCSaveObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config)
	FString EnginePath;

	//生成新程序
	UPROPERTY(Config)
	FString GenerateProgramPath;
	UPROPERTY(Config)
	FString GenerateProgramParam;

	//生成slate控件
	UPROPERTY(Config)
	FString GenerateCompoundWidgetParam;
	UPROPERTY(Config)
	FString GenerateCompoundWidgetPath;

	//修改字符
	UPROPERTY(Config)
	FString ModifyCharactersParam;
	UPROPERTY(Config)
	FString ModifyCharactersPath;

	//修改文件编码
	UPROPERTY(Config)
	FString ModifyFileCodingPath;
	
};
#pragma once
#include "CoreMinimal.h"
#include "Type/GLCCoreType.h"

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
	FGLCSaveInfo GenerateProgram;

	//生成slate控件
	UPROPERTY(Config)
	FGLCSaveInfo GenerateCompoundWidget;

	//修改字符
	UPROPERTY(Config)
	FGLCSaveInfo ModifyCharacters;

	//修改文件编码
	UPROPERTY(Config)
	FGLCSaveInfo ModifyFileCoding;

	//打包独立程序
	UPROPERTY(Config)
	FGLCSaveInfo PackageProgram;

	//添加权利声明
	UPROPERTY(Config)
	FGLCSaveInfo AddCopyRight;
	
};
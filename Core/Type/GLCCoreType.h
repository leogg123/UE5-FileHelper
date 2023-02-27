#pragma once
#include "CoreMinimal.h"
#include "GLCCoreType.generated.h"


USTRUCT()
struct GLCFILEHELPER_API FGLCSaveInfo
{
	GENERATED_BODY()

	UPROPERTY(Config)
	FString Path;
	UPROPERTY(Config)
	FString Param;
};

USTRUCT()
struct GLCFILEHELPER_API FGLCSearchInfo
{
	GENERATED_BODY()
	
	FString Build_cs_Path;
	FString SourceDir_Complete;
	FString ModuleName;
};
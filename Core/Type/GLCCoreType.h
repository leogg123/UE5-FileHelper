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
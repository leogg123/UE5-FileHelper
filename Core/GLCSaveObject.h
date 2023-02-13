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

	UPROPERTY(Config)
	FString LastGenerateProgramPath;

};
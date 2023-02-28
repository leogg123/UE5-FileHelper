#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper/Slate/Main/MethodsSlate/Core/MethodsSlateBase.h"

class SDeleteProgram : public SMethodsSlateBase
{
public:
	SLATE_BEGIN_ARGS(SDeleteProgram )
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	virtual void OnExecuteButtonReleased() override;
	virtual FText GetParamToolTipText() override;

};

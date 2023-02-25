#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper/Slate/Main/MethodsSlate/Core/MethodsSlateBase.h"

class SFixInclude : public SMethodsSlateBase
{
public:
	SLATE_BEGIN_ARGS(SFixInclude )
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	virtual FText GetExplorePathText()override;
	virtual FText GetButtonText()override;
	virtual void OnExploreButtonReleased()override;
	virtual void OnExecuteButtonReleased()override;

};

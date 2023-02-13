#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper\Slate\Core\SlateBase.h"


class SMethodsSlateBase : public SSlateBase
{
public:
	SLATE_BEGIN_ARGS(SMethodsSlateBase )
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void ConstructMySlate();

protected:
	TSharedPtr<SVerticalBox> MyVerticalBox;

	virtual FText GetExplorePathText() = 0;
	virtual FText GetButtonText();
	virtual void OnExploreButtonReleased() = 0;
	virtual void OnExecuteButtonReleased() = 0;

};
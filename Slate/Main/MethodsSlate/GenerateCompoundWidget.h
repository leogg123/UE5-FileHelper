#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper\Slate\Main\MethodsSlate\Core\MethodsSlateBase.h"


class SGenerateCompoundWidget : public SMethodsSlateBase
{
public:
	SLATE_BEGIN_ARGS(SGenerateCompoundWidget)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	virtual FText GetDefaultParamText()override;
	virtual void OnParamTextCommitted(const FText& InText) override;
	virtual FText GetParamToolTipText()override;
	virtual FText GetExplorePathText()override;
	virtual FText GetButtonText()override;
	virtual void OnExploreButtonReleased()override;
	virtual void OnExecuteButtonReleased()override;
};
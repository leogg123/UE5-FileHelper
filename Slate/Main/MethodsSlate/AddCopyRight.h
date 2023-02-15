#pragma once
#include "CoreMinimal.h"
#include "Core/MethodsSlateBase.h"


class SAddCopyRight : public SMethodsSlateBase
{
public:
	SLATE_BEGIN_ARGS(SAddCopyRight )
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

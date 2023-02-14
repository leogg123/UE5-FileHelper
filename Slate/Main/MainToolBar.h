#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper\Slate\Core\SlateBase.h"


class SMainToolBar : public SSlateBase
{
public:
	SLATE_BEGIN_ARGS(SMainToolBar )
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TSharedPtr<SVerticalBox> ToolBarVerticalBox;
	TSharedPtr<SWidget> GetToolBar();
	TSharedRef<SWidget> GetMethodComboButtons();
};
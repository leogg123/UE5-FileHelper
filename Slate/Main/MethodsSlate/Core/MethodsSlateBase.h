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
	TSharedPtr<SEditableTextBox> ParamText;

	virtual FText GetExplorePathText()						    = 0;
	virtual FText GetButtonText()							    = 0;
	virtual void OnExploreButtonReleased()					    = 0;
	virtual FText GetDefaultParamText()						    = 0;
	virtual void OnParamTextCommitted(const FText& InText)	    = 0;
	virtual FText GetParamToolTipText()						    = 0;
	virtual void OnExecuteButtonReleased()					    = 0;

};
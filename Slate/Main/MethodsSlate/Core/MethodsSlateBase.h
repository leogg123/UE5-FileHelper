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

	void ConstructMySlate(bool bSpawnEditableText = true);

protected:
	TSharedPtr<SVerticalBox> MyVerticalBox;
	TSharedPtr<SEditableTextBox> ParamText;

	//Param Text
	virtual FText GetDefaultParamText()						       ;
	virtual void OnParamTextCommitted(const FText& InText)	       ;
	virtual FText GetParamToolTipText()							   ;
	//

	//浏览文件
	virtual FText GetExplorePathText()						    = 0;
	virtual FText GetButtonText()							    = 0;
	virtual void OnExploreButtonReleased()					    = 0;
	//

	//执行按钮
	virtual void OnExecuteButtonReleased()					    = 0;

};
#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper\Slate\Core\SlateBase.h"

#define REGISTER_EXPLORE_BUTTON_RELEASE(SaveInfo,Tip)\
	FString SelectedPath;\
	if (FDesktopPlatformModule::Get()->OpenDirectoryDialog(nullptr,Tip\
		,GLCCommonMethods::Get##SaveInfo##Path(), SelectedPath))\
	{\
		GLCCommonMethods::Set##SaveInfo##Path(SelectedPath);\
	}


class SMethodsSlateBase : public SSlateBase
{
public:
	SLATE_BEGIN_ARGS(SMethodsSlateBase )
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void ConstructMySlate(bool bSpawnEditableText = true, bool bSpawnExploreButton = true);

protected:
	TSharedPtr<SVerticalBox> MyVerticalBox;
	TSharedPtr<SEditableTextBox> ParamText;

	//Param Text
	virtual FText GetDefaultParamText()						       ;
	virtual void OnParamTextCommitted(const FText& InText)	       ;
	virtual FText GetParamToolTipText()							   ;
	//

	//浏览文件
	virtual FText GetExplorePathText()							   ;
	virtual FText GetButtonText()							       ;
	virtual void OnExploreButtonReleased()						   ;
	//

	//执行按钮
	virtual void OnExecuteButtonReleased()					    = 0;

};
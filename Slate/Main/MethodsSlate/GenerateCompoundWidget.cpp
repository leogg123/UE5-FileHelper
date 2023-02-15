#include "GenerateCompoundWidget.h"

#include "GLCFileHelper\Core\Methods\GLCCommonMethods.h"
#include <DesktopPlatformModule.h>

void SGenerateCompoundWidget::Construct(const FArguments& InArgs)
{
	ConstructMySlate();
}

FText SGenerateCompoundWidget::GetDefaultParamText()
{
	return FText::FromString(GLCCommonMethods::GetGenerateCompoundWidgetParam());
}

void SGenerateCompoundWidget::OnParamTextCommitted(const FText& InText)
{
	GLCCommonMethods::SetGenerateCompoundWidgetParam(InText.ToString());
}

FText SGenerateCompoundWidget::GetParamToolTipText()
{
	return FText::FromString(TEXT("填写新Slate的名称，可选(填写父类的完整名称)，用&&分割"));
}

FText SGenerateCompoundWidget::GetExplorePathText()
{
	FString LastPath = GLCCommonMethods::GetGenerateCompoundWidgetPath().IsEmpty() ? TEXT("空")
		: GLCCommonMethods::GetGenerateCompoundWidgetPath();
	return FText::FromString(FString::Printf(TEXT("生成路径 : %s"),*LastPath));
}

FText SGenerateCompoundWidget::GetButtonText()
{
	return FText::FromString(TEXT("浏览路径"));
}

void SGenerateCompoundWidget::OnExploreButtonReleased()
{
	REGISTER_EXPLORE_BUTTON_RELEASE(GenerateCompoundWidget,TEXT("选择生成的路径"));
}

void SGenerateCompoundWidget::OnExecuteButtonReleased()
{
	if(!ParamText) return;

	FString Param = ParamText->GetText().ToString();
	TArray<FString> ParamStrings;

	if (Param.ParseIntoArray(ParamStrings, TEXT("&&")))
	{
		FString NewSlateName;
		FString OptionalParent;
		FString TargetPath = GLCCommonMethods::GetGenerateCompoundWidgetPath();
		if (ParamStrings.Num() == 1)
		{
			NewSlateName = ParamStrings[0];
		}
		else if (ParamStrings.Num() == 2)
		{
			NewSlateName = ParamStrings[0];
			OptionalParent = ParamStrings[1];
		}
		GLCCommonMethods::GenerateCompoundWidget(TargetPath,NewSlateName,OptionalParent);
	}
	else
	{
		GLCCommonMethods::OpenMessageDialogByString(TEXT("请按照提示用正确的格式填写参数"));
	}
}

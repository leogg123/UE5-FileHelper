#include "GenerateProgram.h"

#include "GLCFileHelper\Core\Methods\GLCCommonMethods.h"
#include <DesktopPlatformModule.h>

void SGenerateProgram::Construct(const FArguments& InArgs)
{
	ConstructMySlate();
}

FText SGenerateProgram::GetDefaultParamText()
{
	return FText::FromString(GLCCommonMethods::GetGenerateProgramParam());
}

FText SGenerateProgram::GetParamToolTipText()
{
	return FText::FromString(TEXT("填写生成的新程序名字，是否是独立程序(可选，用于区别控制台应用，如未填写默认为true，用&&分割)"));
}

void SGenerateProgram::OnParamTextCommitted(const FText& InText)
{
	GLCCommonMethods::SetGenerateProgramParam(InText.ToString());
}

FText SGenerateProgram::GetExplorePathText()
{
	FString LastPath = GLCCommonMethods::GetGenerateProgramPath().IsEmpty() ? TEXT("无保存路径")
		: GLCCommonMethods::GetGenerateProgramPath();
	return FText::FromString(FString::Printf(TEXT("生成路径 : %s"),*LastPath));
}

FText SGenerateProgram::GetButtonText()
{
	return FText::FromString(TEXT("浏览路径"));
}

void SGenerateProgram::OnExploreButtonReleased()
{
	REGISTER_EXPLORE_BUTTON_RELEASE(GenerateProgram,TEXT("选择生成的路径"));
}

void SGenerateProgram::OnExecuteButtonReleased()
{
	if (ParamText)
	{
		FString Param = ParamText->GetText().ToString();
		bool bIsConsole = false;

		TArray<FString> NewStrings;
		if(Param.ParseIntoArray(NewStrings,TEXT("&&")) > 1)
		{
			if(NewStrings.Num() == 2)
			{
				Param = NewStrings[0];
				bIsConsole = !NewStrings[1].ToBool();
			}
			else
			{
				GLCCommonMethods::OpenMessageDialogByString(TEXT("请按照提示正确填写参数"));
				return;
			}
		}
		GLCCommonMethods::GenerateNewProgram(Param,bIsConsole);
	}
	
}

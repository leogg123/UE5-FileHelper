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
	return FText::FromString(TEXT("填写生成的新程序名字"));
}

void SGenerateProgram::OnParamTextCommitted(const FText& InText)
{
	GLCCommonMethods::SetGenerateProgramParam(InText.ToString());
}

FText SGenerateProgram::GetExplorePathText()
{
	FString LastPath = GLCCommonMethods::GetGenerateProgramPath().IsEmpty() ? TEXT("无保存路径")
		: GLCCommonMethods::GetGenerateProgramPath();
	return FText::FromString(FString::Printf(TEXT("上次的生成路径 : %s"),*LastPath));
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
		FString NewProgram = ParamText->GetText().ToString();
		GLCCommonMethods::GenerateNewProgram(NewProgram);
	}
	
}

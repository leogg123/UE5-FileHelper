#include "PackageProgram.h"

#include "DesktopPlatformModule.h"
#include "GLCFileHelper\Core\Methods\GLCCommonMethods.h"

void SPackageProgram::Construct(const FArguments& InArgs)
{
	ConstructMySlate();
}

FText SPackageProgram::GetDefaultParamText()
{
	return FText::FromString(GLCCommonMethods::GetPackageProgramParam());
}

void SPackageProgram::OnParamTextCommitted(const FText& InText)
{
	GLCCommonMethods::SetPackageProgramParam(InText.ToString());
}

FText SPackageProgram::GetParamToolTipText()
{
	return FText::FromString(TEXT("填写独立程序的名字"));
}

FText SPackageProgram::GetExplorePathText()
{
	return FText::FromString(GLCCommonMethods::GetPackageProgramPath());
}

FText SPackageProgram::GetButtonText()
{
	return FText::FromString(TEXT("浏览文件夹"));
}

void SPackageProgram::OnExploreButtonReleased()
{
	REGISTER_EXPLORE_BUTTON_RELEASE(PackageProgram,TEXT("选择打包的目标文件夹"));
}

void SPackageProgram::OnExecuteButtonReleased()
{
	if(ParamText)
	{
		const FString TargetProgramName = ParamText->GetText().ToString();
		GLCCommonMethods::PackageProgram(TargetProgramName,GLCCommonMethods::GetPackageProgramPath());
	}
}

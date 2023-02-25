#include "FixInclude.h"

#include "GLCFileHelper/Core/Methods/GLCCommonMethods.h"
#include <DesktopPlatformModule.h>

void SFixInclude::Construct(const FArguments& InArgs)
{
	ConstructMySlate(false);
}

FText SFixInclude::GetExplorePathText()
{
	return FText::FromString(GLCCommonMethods::GetFixIncludePath());
}

FText SFixInclude::GetButtonText()
{
	return FText::FromString(TEXT("选择搜索的文件夹"));
}

void SFixInclude::OnExploreButtonReleased()
{
	REGISTER_EXPLORE_BUTTON_RELEASE(FixInclude,TEXT("选择搜索的文件夹"));
}

void SFixInclude::OnExecuteButtonReleased()
{
	const FString SearchPath = GLCCommonMethods::GetFixIncludePath();
	GLCCommonMethods::FixInclude(SearchPath);
}

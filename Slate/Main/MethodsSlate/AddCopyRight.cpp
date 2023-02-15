#include "AddCopyRight.h"

#include "GLCFileHelper/Core/Methods/GLCCommonMethods.h"
#include <DesktopPlatformModule.h>

void SAddCopyRight::Construct(const FArguments& InArgs)
{
	ConstructMySlate();
}

FText SAddCopyRight::GetDefaultParamText()
{
	return FText::FromString(GLCCommonMethods::GetAddCopyRightParam());
}

void SAddCopyRight::OnParamTextCommitted(const FText& InText)
{
	GLCCommonMethods::SetAddCopyRightParam(InText.ToString());
}

FText SAddCopyRight::GetParamToolTipText()
{
	return FText::FromString(TEXT("填写要加入的权利声明"));
}

FText SAddCopyRight::GetExplorePathText()
{
	FString LastPath = GLCCommonMethods::GetAddCopyRightPath().IsEmpty() ? TEXT("无搜索路径")
		: GLCCommonMethods::GetAddCopyRightPath();
	return FText::FromString(FString::Printf(TEXT("搜索路径 : %s"),*LastPath));
}

FText SAddCopyRight::GetButtonText()
{
	return FText::FromString(TEXT("浏览文件夹"));
}

void SAddCopyRight::OnExploreButtonReleased()
{
	REGISTER_EXPLORE_BUTTON_RELEASE(AddCopyRight,TEXT("选择搜索的文件夹"));
}

void SAddCopyRight::OnExecuteButtonReleased()
{
	if(ParamText)
	{
		FString CopyRight = ParamText->GetText().ToString();
		GLCCommonMethods::AddCopyRight(GLCCommonMethods::GetAddCopyRightPath(),
			CopyRight);
	}
}

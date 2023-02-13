#include "ModifyCharacters.h"

#include "DesktopPlatformModule.h"
#include "GLCFileHelper\Core\Methods\GLCCommonMethods.h"

void SModifyCharacters::Construct(const FArguments& InArgs)
{
	ConstructMySlate();
}

FText SModifyCharacters::GetDefaultParamText()
{
	return FText::FromString(GLCCommonMethods::GetModifyCharactersParam());
}

FText SModifyCharacters::GetParamToolTipText()
{
	return FText::FromString(TEXT("分别填写要搜索的字符，要替换的字符，\
	可选的条件字符(存在此字符才进行替换)，(用&&分割，要替换的字符不填就默认为空)，填写2个参数就是一个搜索一个替换"));
}

void SModifyCharacters::OnParamTextCommitted(const FText& InText)
{
	GLCCommonMethods::SetModifyCharactersParam(InText.ToString());
}

FText SModifyCharacters::GetExplorePathText()
{
	return FText::FromString(GLCCommonMethods::GetModifyCharactersPath());
}

FText SModifyCharacters::GetButtonText()
{
	return FText::FromString(TEXT("浏览文件夹"));
}

void SModifyCharacters::OnExploreButtonReleased()
{
	FString SelectedPath;
	if (FDesktopPlatformModule::Get()->OpenDirectoryDialog(nullptr, TEXT("选择搜索的文件夹")
		, GLCCommonMethods::GetModifyCharactersPath(), SelectedPath))
	{
		GLCCommonMethods::SetModifyCharactersPath(SelectedPath);
	}
}

void SModifyCharacters::OnExecuteButtonReleased()
{
	if(ParamText)
	{
		FString Param = ParamText->GetText().ToString();

		TArray<FString> ParamStrings;
		Param.ParseIntoArray(ParamStrings, TEXT("&&"));

		if(ParamStrings.Num() == 2)
		{
			const FString Search = ParamStrings[0];
			const FString Replace = ParamStrings[1];

			GLCCommonMethods::ModifyCharactersIteration(GLCCommonMethods::GetModifyCharactersPath()
				,Search,Replace);
		}
		else if(ParamStrings.Num() == 3)
		{
			const FString Search = ParamStrings[0];
			const FString Replace = ParamStrings[1];
			const FString Condition = ParamStrings[2];

			GLCCommonMethods::ModifyCharactersIteration(GLCCommonMethods::GetModifyCharactersPath()
				,Search,Replace,Condition);
		}
		else
		{
			const FString Search = Param;
			const FString Replace;

			GLCCommonMethods::ModifyCharactersIteration(GLCCommonMethods::GetModifyCharactersPath()
				,Search,Replace);
		}
	}
}

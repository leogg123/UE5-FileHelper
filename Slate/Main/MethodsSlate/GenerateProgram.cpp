#include "GenerateProgram.h"

#include "GLCFileHelper\Core\Methods\GLCCommonMethods.h"
#include <DesktopPlatformModule.h>

void SGenerateProgram::Construct(const FArguments& InArgs)
{
	ConstructMySlate();

	if(!MyVerticalBox) return;

	MyVerticalBox->InsertSlot(MyVerticalBox->NumSlots() - 1)
	.AutoHeight()
	.HAlign(EHorizontalAlignment::HAlign_Left)
	.VAlign(EVerticalAlignment::VAlign_Top)
	.Padding(3)
	[
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Top)
		.Padding(3)
		[
			SAssignNew(NewProgramName,SEditableTextBox)
			.ToolTipText(FText::FromString(TEXT("填写生成程序的名字")))
			.Text(FText::FromString(TEXT("MyNewProgram")))
		]
	];
}

FText SGenerateProgram::GetTextBlockText()
{
	FString LastPath = GLCCommonMethods::GetLastGenerateProgramPath().IsEmpty() ? TEXT("无保存路径")
		: GLCCommonMethods::GetLastGenerateProgramPath();
	return FText::FromString(FString::Printf(TEXT("上次的生成路径 : %s"),*LastPath));
}

FText SGenerateProgram::GetButtonText()
{
	return FText::FromString(TEXT("浏览路径"));
}

void SGenerateProgram::OnExploreButtonReleased()
{
	FString SelectedPath;
	if (FDesktopPlatformModule::Get()->OpenDirectoryDialog(nullptr, TEXT("选择生成的路径")
		, GLCCommonMethods::GetLastGenerateProgramPath(), SelectedPath))
	{
		GLCCommonMethods::SetGenerateProgramPath(SelectedPath);
	}
}

void SGenerateProgram::OnExecuteButtonReleased()
{
	if (NewProgramName)
	{
		FString NewProgram = NewProgramName->GetText().ToString();
		GLCCommonMethods::GenerateNewProgram(NewProgram);
	}
	
}

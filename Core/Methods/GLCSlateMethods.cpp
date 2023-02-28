#include "GLCSlateMethods.h"
#include "GLCCommonMethods.h"
#include <DesktopPlatformModule.h>

#include "GLCFileHelper/Slate/Main/MethodsSlate/AddCopyRight.h"
#include "GLCFileHelper/Slate/Main/MethodsSlate/DeleteProgram.h"
#include "GLCFileHelper/Slate/Main/MethodsSlate/FixInclude.h"
#include "GLCFileHelper/Slate/Main/MethodsSlate/PackageProgram.h"
#include "GLCFileHelper\Slate\Main\MethodsSlate\GenerateProgram.h"
#include "GLCFileHelper\Slate\Main\MethodsSlate\GenerateCompoundWidget.h"
#include "GLCFileHelper\Slate\Main\MethodsSlate\ModifyCharacters.h"
#include "GLCFileHelper\Slate\Main\MethodsSlate\ModifyFileCoding.h"


static const FVector2D WindowSize = FVector2D(1000,500);

namespace GLCSlateMethods
{
	
	void AddSettingWindow()
	{
		TSharedPtr<SWindow> SettingWindow = 
		SNew(SWindow)
		.Title(FText::FromString(TEXT("设置")))
		.ClientSize(WindowSize)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.Padding(4)
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(EHorizontalAlignment::HAlign_Left)
				.VAlign(EVerticalAlignment::VAlign_Top)
				.Padding(4)
				[
					SNew(STextBlock)
					.Text_Lambda([&]()->FText
					{
						FString EnginePath = TEXT("引擎路径 : ");
						EnginePath += GLCCommonMethods::GetEnginePath();

						return GLCCommonMethods::GetEnginePath().IsEmpty() ? FText::FromString(TEXT("当前未设置引擎路径"))
							: FText::FromString(EnginePath);
					})
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(EHorizontalAlignment::HAlign_Left)
				.VAlign(EVerticalAlignment::VAlign_Top)
				.Padding(4)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("浏览文件夹")))
					.OnReleased_Lambda([&]()
					{
						FString SelectedEnginePath;
						if (FDesktopPlatformModule::Get()->OpenDirectoryDialog(nullptr, TEXT("选择引擎文件夹")
							, GLCCommonMethods::GetEnginePath(), SelectedEnginePath))
						{
							GLCCommonMethods::SetEnginePath(SelectedEnginePath);
						}
					})
				]
			]
		];

		FSlateApplication::Get().AddWindow(SettingWindow.ToSharedRef());
	}

	void AddCommonWindow(const FString& InTitle, const TSharedRef<SWidget>& InWidget)
	{
		TSharedPtr<SWindow> NewWindow =
			SNew(SWindow)
			.Title(FText::FromString(InTitle))
			.ClientSize(WindowSize)
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(EHorizontalAlignment::HAlign_Left)
				.VAlign(EVerticalAlignment::VAlign_Top)
				.Padding(4)
				[
					InWidget
				]
			];

		FSlateApplication::Get().AddWindow(NewWindow.ToSharedRef());
	}

	void AddGenerateNewProgramWindow()
	{
		AddCommonWindow(TEXT("生成新的程序"),SNew(SGenerateProgram));
	}

	void AddGenerateCompoundWidgetWindow()
	{
		AddCommonWindow(TEXT("生成CompoundWidget文件"),SNew(SGenerateCompoundWidget));
	}

	void AddModifyCharactersWindow()
	{
		AddCommonWindow(TEXT("修改文件字符"),SNew(SModifyCharacters));
	}

	void AddModifyFileCodingWindow()
	{
		AddCommonWindow(TEXT("修改文件编码"),SNew(SModifyFileCoding));
	}

	void AddPackageProgramWindow()
	{
		AddCommonWindow(TEXT("打包独立程序"),SNew(SPackageProgram));
	}

	void AddCopyRightWindow()
	{
		AddCommonWindow(TEXT("添加权利声明"),SNew(SAddCopyRight));
	}

	void AddFixIncludeWindow()
	{
		AddCommonWindow(TEXT("修复头文件包含问题"),SNew(SFixInclude));
	}

	void AddDeleteProgramWindow()
	{
		AddCommonWindow(TEXT("删除独立程序"),SNew(SDeleteProgram));
	}
}

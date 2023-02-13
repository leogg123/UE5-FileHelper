#include "GLCSlateMethods.h"
#include "GLCCommonMethods.h"
#include <DesktopPlatformModule.h>
#include "GLCFileHelper\Slate\Main\MethodsSlate\GenerateProgram.h"
#include "GLCFileHelper\Slate\Main\MethodsSlate\GenerateCompoundWidget.h"


namespace GLCSlateMethods
{
	
	void AddSettingWindow()
	{
		TSharedPtr<SWindow> SettingWindow = 
		SNew(SWindow)
		.Title(FText::FromString(TEXT("设置")))
		.ClientSize(FVector2D(700, 800))
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

	void AddGenerateNewProgramWindow()
	{
		TSharedPtr<SWindow> GenerateWindow =
			SNew(SWindow)
			.Title(FText::FromString(TEXT("生成新的程序")))
			.ClientSize(FVector2D(700, 800))
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(EHorizontalAlignment::HAlign_Left)
				.VAlign(EVerticalAlignment::VAlign_Top)
				.Padding(4)
				[
					SNew(SGenerateProgram)
				]
			];

		FSlateApplication::Get().AddWindow(GenerateWindow.ToSharedRef());
	}

	void AddGenerateCompoundWidgetWindow()
	{
		TSharedPtr<SWindow> GenerateWindow =
			SNew(SWindow)
			.Title(FText::FromString(TEXT("生成新的程序")))
			.ClientSize(FVector2D(700, 800))
			[
				SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.AutoHeight()
				.HAlign(EHorizontalAlignment::HAlign_Left)
				.VAlign(EVerticalAlignment::VAlign_Top)
				.Padding(4)
				[
					SNew(SGenerateCompoundWidget)
				]
			];

		FSlateApplication::Get().AddWindow(GenerateWindow.ToSharedRef());
	}

}
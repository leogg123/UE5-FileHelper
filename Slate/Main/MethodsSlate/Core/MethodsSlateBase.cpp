#include "MethodsSlateBase.h"
#include <DesktopPlatformModule.h>
#include <GLCFileHelper/Core/Methods/GLCCommonMethods.h>

void SMethodsSlateBase::Construct(const FArguments& InArgs)
{
	ConstructMySlate();
	return;
}

void SMethodsSlateBase::ConstructMySlate()
{
	ChildSlot
	[
		SAssignNew(MyVerticalBox,SVerticalBox)

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
					return GetExplorePathText();
				})
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.Padding(4)
			[
				SNew(SButton)
				.Text(GetButtonText())
				.OnReleased_Lambda([&]()
				{
					OnExploreButtonReleased();
				})
			]
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Top)
		.Padding(4)
		[
			SNew(SButton)
			.Text(FText::FromString(TEXT("执行")))
			.OnReleased_Lambda([&]()
			{
				OnExecuteButtonReleased();
			})
		]
	];
}

FText SMethodsSlateBase::GetButtonText()
{
	return FText::FromString(TEXT("浏览路径"));
}


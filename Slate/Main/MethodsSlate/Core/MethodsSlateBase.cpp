#include "MethodsSlateBase.h"
#include <DesktopPlatformModule.h>
#include <GLCFileHelper/Core/Methods/GLCCommonMethods.h>

void SMethodsSlateBase::Construct(const FArguments& InArgs)
{
	ConstructMySlate();
	return;
}

void SMethodsSlateBase::ConstructMySlate(bool bSpawnEditableText)
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
	];

	if(MyVerticalBox)
	{
		if(bSpawnEditableText)
		{
			//可编辑的文本框
			MyVerticalBox->AddSlot()
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
				.Padding(3)
				[
					SAssignNew(ParamText,SEditableTextBox)
					.ToolTipText(GetParamToolTipText())
					.Text(GetDefaultParamText())
					.OnTextCommitted_Lambda(
					[&](const FText& InText, ETextCommit::Type InType)
					{
						if (!ParamText) return;
						OnParamTextCommitted(ParamText->GetText());
					})
				]
			];
		}
		//执行按钮
		MyVerticalBox->AddSlot()
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
		];
	}
}

FText SMethodsSlateBase::GetButtonText()
{
	return FText::FromString(TEXT("浏览路径"));
}

FText SMethodsSlateBase::GetDefaultParamText()
{
	return FText();
}

void SMethodsSlateBase::OnParamTextCommitted(const FText& InText)
{
	
}

FText SMethodsSlateBase::GetParamToolTipText()
{
	return FText();
}


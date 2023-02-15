#include "ModifyFileCoding.h"

#include "DesktopPlatformModule.h"
#include "GLCFileHelper\Core\Methods\GLCCommonMethods.h"

void SModifyFileCoding::Construct(const FArguments& InArgs)
{
	ConstructMySlate(false);
	
	ItemsArr.Add((FName(TEXT("ForceAnsi"))));
	ItemsArr.Add((FName(TEXT("ForceUnicode"))));
	ItemsArr.Add((FName(TEXT("ForceUTF8"))));
	ItemsArr.Add((FName(TEXT("ForceUTF8WithoutBOM"))));

	ItemToInit = FName(GLCCommonMethods::GetModifyFileCodingParam());
	if(ItemToInit.IsNone())
	{
		ItemToInit = FName(TEXT("ForceUTF8WithoutBOM"));
	}
	if(MyVerticalBox)
	{
		MyVerticalBox->InsertSlot(MyVerticalBox->NumSlots() - 1)
		.AutoHeight()
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Top)
		.Padding(4)
		[
			SNew(SHorizontalBox)

			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.Padding(4.f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("文件编码类型")))
			]

			+SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.Padding(4.f)
			[
				SAssignNew(ComboBoxPtr,SComboBox<FComboItemType>)
				.OptionsSource(&ItemsArr)
				.InitiallySelectedItem(ItemToInit)
				.OnSelectionChanged_Lambda([&](const FComboItemType& InItem ,ESelectInfo::Type Info)
				{
					GLCCommonMethods::SetModifyFileCodingParam(InItem.ToString());
				})
				.OnGenerateWidget_Lambda([&](const FComboItemType& InItem)->TSharedRef<SWidget>
				{
					return
					SNew(STextBlock)
					.Text(FText::FromName(InItem));
				})
					[
						SNew(STextBlock)
						.Text_Lambda([&]()->FText
							{return FText::FromName(ComboBoxPtr->GetSelectedItem());})
					]
			]
		];
	}
}

FText SModifyFileCoding::GetExplorePathText()
{
	return FText::FromString(GLCCommonMethods::GetModifyFileCodingPath());
}

FText SModifyFileCoding::GetButtonText()
{
	return FText::FromString(TEXT("浏览文件夹"));
}

void SModifyFileCoding::OnExploreButtonReleased()
{
	REGISTER_EXPLORE_BUTTON_RELEASE(ModifyFileCoding,TEXT("选择要搜索的文件夹"));
}

void SModifyFileCoding::OnExecuteButtonReleased()
{
	if(ComboBoxPtr)
	{
		int32 Index = ItemsArr.Find(ComboBoxPtr->GetSelectedItem());
		FFileHelper::EEncodingOptions EncodingOption = FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM;
		if(Index == 0)
		{
			EncodingOption = FFileHelper::EEncodingOptions::ForceAnsi;
		}
		else if(Index == 1)
		{
			EncodingOption = FFileHelper::EEncodingOptions::ForceUnicode;
		}
		else if(Index == 2)
		{
			EncodingOption = FFileHelper::EEncodingOptions::ForceUTF8;
		}
		else if(Index == 3)
		{
			EncodingOption = FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM;
		}
		GLCCommonMethods::ModifyFileCoding(GLCCommonMethods::GetModifyFileCodingPath(),
			EncodingOption);
	}
}

#include "MainSlate.h"

#include "GLCFileHelper\Slate\Main\MainToolBar.h"
#include "GLCFileHelper\Slate\Main\MethodsMenu.h"


#define LOCTEXT_NAMESPACE "SMainSlate"

void SMainSlate::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SVerticalBox)

		/*+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Top)
		.Padding(4.f)
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.Padding(4.f)
			[
				SNew(SMethodsMenu)
			]
		]*/
		
		+SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Top)
		.Padding(4.f)
		[ 
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(EHorizontalAlignment::HAlign_Left)
			.VAlign(EVerticalAlignment::VAlign_Top)
			.Padding(4.f)
			[
				SNew(SMainToolBar)
			]

		]
		
	];
}



#undef  LOCTEXT_NAMESPACE 
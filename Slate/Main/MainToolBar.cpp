#include "MainToolBar.h"

#include <DesktopPlatformModule.h>
#include "GLCFileHelper\Core\Methods\GLCCommonMethods.h"
#include "GLCFileHelper\Slate\Main\Commands\MyMenuCommands.h"
#include <Styling/SlateIconFinder.h>
#include "GLCFileHelper\Core\Methods\GLCSlateMethods.h"


void SMainToolBar::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		GetToolBar().ToSharedRef()
	];
}

TSharedPtr<SWidget> SMainToolBar::GetToolBar()
{
	TSharedPtr<FUICommandList> CommandList = MakeShareable(new FUICommandList());


	TSharedPtr<FUICommandInfo> SettingInfo = MakeShareable(new FUICommandInfo(TEXT("设置")));
	CommandList->MapAction(SettingInfo, FExecuteAction::CreateLambda(
	[&]()
	{
		GLCSlateMethods::AddSettingWindow();
	}));
	
	FString MethodWindowName = TEXT("方法窗口");
	TSharedPtr<FUICommandInfo> MethodsWindow = MakeShareable(new FUICommandInfo(*MethodWindowName));
	CommandList->MapAction(MethodsWindow, FExecuteAction::CreateLambda(
	[&]()
	{
		
	}));

	FToolBarBuilder Builder(CommandList, FMultiBoxCustomization::None);
	Builder.BeginSection(TEXT("MySection"));
	{
		Builder.AddToolBarButton(SettingInfo, TEXT("设置"),
			FText::FromString(TEXT("设置")), FText::FromString(TEXT("设置")));


		Builder.AddSeparator();

		FText SpanNewProgramText = FText::FromString(TEXT("方法窗口"));
		Builder.AddComboButton(FUIAction(),FOnGetContent::CreateLambda(
		[&]()->TSharedRef<SWidget>
		{
			return GetMethodComboButtons();
		}),SpanNewProgramText,SpanNewProgramText, FSlateIconFinder::FindIcon("WidgetReflector.Icon"));
	}
	Builder.EndSection();
	return Builder.MakeWidget();
}

TSharedRef<SWidget> SMainToolBar::GetMethodComboButtons()
{
	return SNew(SVerticalBox)

	+SVerticalBox::Slot()
	.AutoHeight()
	.VAlign(EVerticalAlignment::VAlign_Top)
	.HAlign(EHorizontalAlignment::HAlign_Center)
	.Padding(4.f)
	[
		SNew(SButton)
		.Text(FText::FromString(TEXT("生成新的程序")))
		.OnReleased_Lambda([&]()
		{
			GLCSlateMethods::AddGenerateNewProgramWindow();
		})
	]

	+SVerticalBox::Slot()
	.AutoHeight()
	.VAlign(EVerticalAlignment::VAlign_Top)
	.HAlign(EHorizontalAlignment::HAlign_Center)
	.Padding(4.f)
	[
		SNew(SButton)
		.Text(FText::FromString(TEXT("生成CompoundWidget文件")))
		.OnReleased_Lambda([&]()
		{
			GLCSlateMethods::AddGenerateCompoundWidgetWindow();
		})
	];
}

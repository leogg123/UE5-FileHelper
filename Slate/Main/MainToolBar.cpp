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

#define ADD_MY_SLOT(ButtonStr,FunctionName) \
	ToolBarVerticalBox->AddSlot() \
	.AutoHeight() \
	.VAlign(EVerticalAlignment::VAlign_Top) \
	.HAlign(EHorizontalAlignment::HAlign_Center) \
	.Padding(4.f) \
	[ \
		SNew(SButton) \
		.Text(FText::FromString(ButtonStr)) \
		.OnReleased_Lambda([&]() \
		{ \
			GLCSlateMethods::FunctionName(); \
		}) \
	]
	

TSharedRef<SWidget> SMainToolBar::GetMethodComboButtons()
{
	SAssignNew(ToolBarVerticalBox,SVerticalBox);

	ADD_MY_SLOT(TEXT("生成新的程序"),AddGenerateNewProgramWindow);
	ADD_MY_SLOT(TEXT("生成CompoundWidget文件"),AddGenerateCompoundWidgetWindow);
	ADD_MY_SLOT(TEXT("修改文件字符"),AddModifyCharactersWindow);
	ADD_MY_SLOT(TEXT("修改文件编码"),AddModifyFileCodingWindow);
	ADD_MY_SLOT(TEXT("打包独立程序"),AddPackageProgramWindow);
	
	return ToolBarVerticalBox.ToSharedRef();
}

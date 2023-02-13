#include "MethodsMenu.h"

#include "Framework\MultiBox\SToolBarButtonBlock.h"
#include "GLCFileHelper\Slate\Main\Commands\MyMenuCommands.h"


SMethodsMenu::SMethodsMenu()
{
	FMyMenuCommands::Register();
}

void SMethodsMenu::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		MakeMethodsMenu().ToSharedRef()
	];
}

TSharedPtr<SWidget> SMethodsMenu::MakeMethodsMenu()
{
	/*CommandList->MapAction(SpawnWidget, FExecuteAction::CreateLambda([&](){}));*/
	FMenuBarBuilder MenuBuilder(FMyMenuCommands::Get().CommandList);

	MenuBuilder.AddPullDownMenu(FText::FromString(TEXT("方法栏")), FText::FromString(TEXT("方法栏")),
		FNewMenuDelegate::CreateLambda([&](FMenuBuilder& InMenuBuilder)
		{
			InMenuBuilder.AddMenuEntry(FMyMenuCommands::Get().SpawnWidget);
		}));
	return MenuBuilder.MakeWidget();
}
	
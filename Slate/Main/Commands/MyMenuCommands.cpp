#include "MyMenuCommands.h"

#define LOCTEXT_NAMESPACE "FMyMenuCommands"

FMyMenuCommands::FMyMenuCommands()
	: TCommands<FMyMenuCommands>
	(TEXT("Menu"), NSLOCTEXT("Contexts", "Menu", "Menu"),
		NAME_None, FCoreStyle::Get().GetStyleSetName())
{
	CommandList = MakeShareable(new FUICommandList());

	SpawnWidget = MakeShareable(new FUICommandInfo(TEXT("生成CompoundWidget")));
	CommandList->MapAction(SpawnWidget,FExecuteAction::CreateLambda([&](){}));
}

void FMyMenuCommands::RegisterCommands()
{
	UI_COMMAND(SpawnWidget, "生成CompoundWidget", "生成CompoundWidget", 
		EUserInterfaceActionType::Button, FInputGesture());
}


#undef LOCTEXT_NAMESPACE
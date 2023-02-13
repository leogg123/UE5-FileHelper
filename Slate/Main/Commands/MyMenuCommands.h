#pragma once
#include "CoreMinimal.h"



class FMyMenuCommands : public TCommands<FMyMenuCommands>
{
public:

	FMyMenuCommands();

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandList> CommandList;

	TSharedPtr< FUICommandInfo > SpawnWidget;
};
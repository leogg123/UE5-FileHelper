#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper\Slate\Core\SlateBase.h"

#define LOCTEXT_NAMESPACE "FMyCommandInfo"

class SMethodsMenu : public SSlateBase
{
public:
	SLATE_BEGIN_ARGS(SMethodsMenu )
	{}
	SLATE_END_ARGS()

	SMethodsMenu();
	void Construct(const FArguments& InArgs);

protected:
	TSharedPtr<SWidget> MakeMethodsMenu();

};


#undef LOCTEXT_NAMESPACE
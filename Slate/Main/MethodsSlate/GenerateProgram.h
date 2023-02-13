#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper\Slate\Main\MethodsSlate\Core\MethodsSlateBase.h"


class SGenerateProgram : public SMethodsSlateBase
{
public:
	SLATE_BEGIN_ARGS(SGenerateProgram)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	TSharedPtr<SEditableTextBox> NewProgramName;

	virtual FText GetTextBlockText();
	virtual FText GetButtonText();
	virtual void OnExploreButtonReleased();
	virtual void OnExecuteButtonReleased();
};
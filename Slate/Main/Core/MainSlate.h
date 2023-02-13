#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper\Slate\Core\SlateBase.h"


class SMainSlate :public SSlateBase
{
public:
	SLATE_BEGIN_ARGS(SMainSlate)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

};
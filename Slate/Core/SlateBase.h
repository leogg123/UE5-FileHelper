#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SSlateBase :public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlateBase)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);



};
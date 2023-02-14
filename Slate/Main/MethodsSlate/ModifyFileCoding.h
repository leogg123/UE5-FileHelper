#pragma once
#include "CoreMinimal.h"
#include "GLCFileHelper/Slate/Main/MethodsSlate/Core/MethodsSlateBase.h"

//ForceAnsi,
//ForceUnicode,
//ForceUTF8,
//ForceUTF8WithoutBOM

class SModifyFileCoding : public SMethodsSlateBase
{
public:
	typedef TSharedPtr<FName> FComboItemType;
	
	SLATE_BEGIN_ARGS(SModifyFileCoding )
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	TArray<FComboItemType> ItemsArr;
	TSharedPtr<SComboBox<FComboItemType>> ComboBoxPtr;
	
	//浏览文件
	virtual FText GetExplorePathText()override;
	virtual FText GetButtonText()override;
	virtual void OnExploreButtonReleased()override;
	//

	//执行按钮
	virtual void OnExecuteButtonReleased()override;

};

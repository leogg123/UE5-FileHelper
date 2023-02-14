#pragma once
#include "Coreminimal.h"


namespace GLCSlateMethods
{
	void AddSettingWindow();

	//通用
	void AddCommonWindow(const FString& InTitle,const TSharedRef<SWidget>& InWidget);
	//
	void AddGenerateNewProgramWindow();

	void AddGenerateCompoundWidgetWindow();

	void AddModifyCharactersWindow();

	void AddModifyFileCodingWindow();

	void AddPackageProgramWindow();
}

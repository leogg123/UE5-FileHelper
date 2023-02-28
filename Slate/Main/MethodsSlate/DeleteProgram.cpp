#include "DeleteProgram.h"

#include "GLCFileHelper/Core/Methods/GLCCommonMethods.h"

void SDeleteProgram::Construct(const FArguments& InArgs)
{
	ConstructMySlate(true,false);
}

void SDeleteProgram::OnExecuteButtonReleased()
{
	if(ParamText)
	{
		FText ProgramName = ParamText->GetText();
		GLCCommonMethods::DeleteProgram(ProgramName.ToString());
	}
}

FText SDeleteProgram::GetParamToolTipText()
{
	return SMethodsSlateBase::GetParamToolTipText();
}

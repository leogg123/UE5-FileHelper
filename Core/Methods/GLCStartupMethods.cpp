#include "GLCStartupMethods.h"
#include "Widgets\SWindow.h"
#include "GLCFileHelper\Slate\Main\Core\MainSlate.h"


namespace GLCStartupMethods
{
	void GLCStartupMethods::InitMySlate()
	{
		TSharedPtr<SWindow> MainWindow =
		SNew(SWindow)
		.Title(FText::FromString(TEXT("GLCFileHelper")))
		.ClientSize(FVector2D(900, 600))
		[
			SNew(SMainSlate)
		];

		FOnWindowClosed CloseEven;
		CloseEven.BindLambda([&](const TSharedRef<SWindow>& InWindow) {OnClosed(); RequestEngineExit(TEXT("Main Window is closed !")); });
		MainWindow->SetOnWindowClosed(CloseEven);

		FSlateApplication::Get().AddWindow(MainWindow.ToSharedRef());
	}

	void OnClosed()
	{
		
	}

}
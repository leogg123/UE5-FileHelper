#include "GLCStartupMethods.h"

#include "WindowsAPI.h"
#include "Widgets\SWindow.h"
#include "GLCFileHelper\Slate\Main\Core\MainSlate.h"
#include "Widgets/SViewport.h"


namespace GLCStartupMethods
{
	void GLCStartupMethods::InitMySlate()
	{
		TSharedPtr<SWindow> MainWindow =
		SNew(SWindow)
		.Title(FText::FromString(TEXT("GLCFileHelper")))
		.ClientSize(FVector2D(1100, 600))
		.AutoCenter(EAutoCenter::PreferredWorkArea)
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

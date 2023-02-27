#include "GLCOutPutLog.h"

#include "HAL/RunnableThread.h"

static FGLCOutputInfo OutputInfo;
static bool bIsLogWindowShow = false;

FGLCOutputLog::FGLCOutputLog()
	:bRun(true),
	bWantExit(false)
{
	
}

void FGLCOutputLog::AddNewMessage(const FString& InMessage, EMessageType InType /*= EMessageType::DISPLAY*/)
{
	FString Log = TEXT("GLCFileHelper: ");
	FLinearColor Color = FLinearColor::White;
	switch (InType)
	{
	case GLC_DISPLAY:
		Log += TEXT("Display: ");
		break;
	case GLC_WARNING:
		Log += TEXT("Warning: ");
		Color = FLinearColor::Yellow;
		break;
	case GLC_ERROR:
		Log += TEXT("Error: ");
		Color = FLinearColor::Red;
		break;
	default:
		break;
	}

	Log += InMessage;
	FGLCOutputPendingInfo NewInfo;
	NewInfo.Info = Log;
	NewInfo.Color = Color;

	OutputInfo.PengdingInfo.Enqueue(NewInfo);
}

void FGLCOutputLog::Create()
{
	if (!MyOutputLog)
	{
		MyOutputLog = new FGLCOutputLog();
	}
}

void FGLCOutputLog::DestroyLog()
{
	if (MyOutputLog)
	{
		delete MyOutputLog;
		MyOutputLog = NULL;
	}
}

void FGLCOutputLog::Tick()
{
	if(OutputInfo.PengdingInfo.IsEmpty()) return;

	if(!bIsLogWindowShow)
	{
		OutputInfo.OutputWindow =
			SNew(SWindow)
			.Title(FText::FromString(TEXT("GLCFileHelperOutputLog")))
			.ClientSize(FVector2D(1100, 500))
			[
				SNew(SScrollBox)
				.Orientation(EOrientation::Orient_Horizontal)
				.WheelScrollMultiplier(3)

				+ SScrollBox::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				[
					SAssignNew(OutputInfo.ScrollBox, SScrollBox)
					.Orientation(EOrientation::Orient_Vertical)
					.WheelScrollMultiplier(3)
				]
			];
		FOnWindowClosed CloseEven;
		CloseEven.BindLambda([&](const TSharedRef<SWindow>& InWindow) {bIsLogWindowShow = false; });
		OutputInfo.OutputWindow->SetOnWindowClosed(CloseEven);
		FSlateApplication::Get().AddWindow(OutputInfo.OutputWindow.ToSharedRef());

		bIsLogWindowShow = true;
	}

	FGLCOutputPendingInfo NewInfo;
	if(OutputInfo.PengdingInfo.Dequeue(NewInfo))
	{
		if (OutputInfo.ScrollBox)
		{
			OutputInfo.ScrollBox->AddSlot()
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				.VAlign(EVerticalAlignment::VAlign_Top)
				[
					SNew(SHorizontalBox)

					+ SHorizontalBox::Slot()
					.Padding(4.f)
					.FillWidth(1.f)
					[
						SNew(STextBlock)
						.Text(FText::FromString(NewInfo.Info))
						.ColorAndOpacity(NewInfo.Color)
						.AutoWrapText(true)
					]
				];
		}
	}
}
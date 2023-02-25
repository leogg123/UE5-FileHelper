#pragma once
#include "CoreMinimal.h"
#include "HAL/Runnable.h"


struct GLCFILEHELPER_API FGLCOutputPendingInfo
{
	FString Info;
	FLinearColor Color;
};

struct GLCFILEHELPER_API FGLCOutputInfo
{
	TQueue<FGLCOutputPendingInfo> PengdingInfo;
	TSharedPtr<SScrollBox> ScrollBox;
	TSharedPtr<SWindow>	   OutputWindow;
};

struct GLCFILEHELPER_API FGLCOutputLog
{
	enum EMessageType
	{
		GLC_DISPLAY			= 0,
		GLC_WARNING			= 1,
		GLC_ERROR			= 2
	};
protected:
	FGLCOutputLog();
public:
	static void AddNewMessage(const FString& InMessage,EMessageType InType = EMessageType::GLC_DISPLAY);
	static void Create();
	static void DestroyLog();

	void Tick();

protected:
	bool bRun;
	bool bWantExit;
};
static FGLCOutputLog* MyOutputLog;
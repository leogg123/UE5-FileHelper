// Copyright Epic Games, Inc. All Rights Reserved.


#include "GLCFileHelper.h"

#include "RequiredProgramMainCPPInclude.h"
#include "Framework\Application\SlateApplication.h"
#include "StandaloneRenderer.h"
#include "GLCFileHelper\Core\Methods\GLCStartupMethods.h"
#include <Styling/UMGCoreStyle.h>
#include <GLCFileHelper/Core/Methods/GLCCommonMethods.h>


IMPLEMENT_APPLICATION(GLCFileHelper, "GLCFileHelper");


int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	GEngineLoop.PreInit(GetCommandLineW());
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());
	FSlateApplication::InitHighDPI(true);
	FSlateApplication::InitializeCoreStyle();

	GLCStartupMethods::InitMySlate();

	while (!IsEngineExitRequested())
	{
		BeginExitIfRequested();
		FSlateApplication::Get().Tick();
		FSlateApplication::Get().PumpMessages();
		//FPlatformProcess::Sleep(0.01f);
	}

	FSlateApplication::Shutdown();
	FEngineLoop::AppPreExit();
	FEngineLoop::AppExit();
	return 0;
}

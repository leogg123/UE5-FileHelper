#include "GLCCommonMethods.h"

#include "GLCFileHelper\Core\GLCSaveObject.h"
#include <HAL/PlatformFileManager.h>



namespace GLCCommonMethods
{

	UGLCSaveObject* GetGLCSaveObject()
	{
		if (UGLCSaveObject* InObject = GetMutableDefault<UGLCSaveObject>())
		{
			InObject->LoadConfig();
			return InObject;
		}
		return nullptr;
	}

	FString GetEnginePath()
	{
		if (UGLCSaveObject* InObject = GetGLCSaveObject())
		{
			return InObject->EnginePath;
		}
		return FString();
	}

	void SetEnginePath(const FString& InEnginePath)
	{
		if (UGLCSaveObject* InObject = GetGLCSaveObject())
		{
			InObject->EnginePath = InEnginePath;
			InObject->SaveConfig();
		}
	}

	FString GetLastGenerateProgramPath()
	{
		if (UGLCSaveObject* InObject = GetGLCSaveObject())
		{
			return InObject->LastGenerateProgramPath;
		}
		return FString();
	}

	void SetGenerateProgramPath(const FString& InPath)
	{
		if (UGLCSaveObject* InObject = GetGLCSaveObject())
		{
			InObject->LastGenerateProgramPath = InPath;
			InObject->SaveConfig();
		}
	}

	void ModifyFileCoding(const FString& InSearchPath, FFileHelper::EEncodingOptions CodingType)
	{
		TArray<FString> FoundFiles;
		IFileManager::Get().FindFilesRecursive(FoundFiles,*InSearchPath,TEXT("*"),true,false);
		if (FoundFiles.Num())
		{
			for (FString& InFileName : FoundFiles)
			{
				TArray<FString> FileData;
				FFileHelper::LoadFileToStringArray(FileData,*InFileName);
				if (FileData.Num())
				{
					FFileHelper::SaveStringArrayToFile(FileData,*InFileName,
						CodingType);
				}
			}
		}
	}

	

	void GenerateNewProgram(const FString& InNewProgramName, bool bIsConsoleApp /*= true*/, 
		const FString& InTargetPath /*= GetLastGenerateProgramPath()*/)
	{
		if (CheckPath(InTargetPath))
		{
			const FString EngineProgramSource = GetEnginePath() / TEXT("Engine") / TEXT("Source")
				/ TEXT("Programs");
			const FString BlankProgramPath = GetEnginePath() / TEXT("Engine") / TEXT("Source")
				/ TEXT("Programs") / TEXT("BlankProgram");
			const FString TargetDiretory = InTargetPath / InNewProgramName;

			if (IFileManager::Get().DirectoryExists(*TargetDiretory))
			{
				OpenMessageDialogByString(FString::Printf(TEXT("[%s] 程序已经存在 !"), *InNewProgramName));
				FPlatformProcess::ExploreFolder(*InTargetPath);
				return;
			}
			FGLCOutputLog OutputLog;

			if (bIsConsoleApp)
			{
				if (IFileManager::Get().DirectoryExists(*BlankProgramPath))
				{
					if (FPlatformFileManager::Get().GetPlatformFile().CopyDirectoryTree(*TargetDiretory,
						*BlankProgramPath, true))
					{
						OutputLog.AddNewMessage(TEXT("文件夹复制成功"));

						TArray<FString> FileNameStrings;
						IFileManager::Get().FindFilesRecursive(FileNameStrings, *TargetDiretory, TEXT("*"),
							true, false);
						OutputLog.AddNewMessage(FString::Printf(TEXT("找到文件数量 = %d"), FileNameStrings.Num()));
						if (FileNameStrings.Num())
						{
							for (FString& InFileName : FileNameStrings)
							{
								if(InFileName.Contains(TEXT("ico")))continue;
								if (InFileName.Contains(TEXT("png")))continue;

								TArray<FString> FileDatas;
								if (FFileHelper::LoadFileToStringArray(FileDatas, *InFileName))
								{
									for (FString& InDatas : FileDatas)
									{
										InDatas.ReplaceInline(TEXT("BlankProgram"),*InNewProgramName);
									}
									if (!IFileManager::Get().Delete(*InFileName, true, true))
									{
										OutputLog.AddNewMessage(FString::Printf(TEXT("[%s] 文件删除失败！"), *InFileName)
											, FGLCOutputLog::ERROR);
									}
									InFileName.ReplaceInline(TEXT("BlankProgram"),*InNewProgramName);
									if (FFileHelper::SaveStringArrayToFile(FileDatas, *InFileName, 
										FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
									{
										OutputLog.AddNewMessage(FString::Printf(TEXT("[%s] 文件保存成功！"), *InFileName)
											, FGLCOutputLog::DISPLAY);
									}
									else
									{
										OutputLog.AddNewMessage(FString::Printf(TEXT("[%s] 文件保存失败！"),*InFileName)
											,FGLCOutputLog::ERROR);
									}
								}
							}
						}
					}

				}
				else
				{
					OpenMessageDialogByString(FString::Printf(TEXT("[%s] 文件夹不存在"),*BlankProgramPath));
				}
			}
			else
			{
				
			}
			OutputLog.AddNewMessage(TEXT("完成"));
			FPlatformProcess::ExploreFolder(*InTargetPath);
		}		
	}

	bool CheckPath(const FString& InPath)
	{
		if (!IFileManager::Get().DirectoryExists(*InPath))
		{
			OpenMessageDialogByString(TEXT("请现在设置里设置引擎的目录"));
			return false;
		}
		if (!IFileManager::Get().DirectoryExists(*GetEnginePath()))
		{
			OpenMessageDialogByString(TEXT("目标文件夹不存在"));
			return false;
		}
		return true;
	}

	void OpenMessageDialogByString(const FString& InMessage)
	{
		FText Title = FText::FromString(TEXT("GLCFileHelper"));
		FMessageDialog::Open(EAppMsgType::Ok,
			FText::FromString(InMessage),&Title);
	}

}

FGLCOutputLog::FGLCOutputLog()
{
	TSharedPtr<SWindow> LogWindow =
		SNew(SWindow)
		.Title(FText::FromString(TEXT("GLCFileHelperOutputLog")))
		.ClientSize(FVector2D(1100, 500))
		[
			SNew(SVerticalBox)

			+SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SNew(SScrollBox)
				.Orientation(EOrientation::Orient_Horizontal)

				+ SScrollBox::Slot()
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				.VAlign(EVerticalAlignment::VAlign_Fill)
				[
					SAssignNew(ScrollBox, SScrollBox)
					.Orientation(EOrientation::Orient_Vertical)
				]
			]
			
		];
	FSlateApplication::Get().AddWindow(LogWindow.ToSharedRef());
	FPlatformProcess::Sleep(0.05f);
}

void FGLCOutputLog::AddNewMessage(const FString& InMessage, EMessageType InType /*= EMessageType::DISPLAY*/)
{
	FString Log = TEXT("GLCFileHelper: ");
	FLinearColor Color = FLinearColor::White;
	switch (InType)
	{
	case FGLCOutputLog::DISPLAY:
		Log += TEXT("Display: ");
		break;
	case FGLCOutputLog::WARNING:
		Log += TEXT("Warning: ");
		Color = FLinearColor::Yellow;
		break;
	case FGLCOutputLog::ERROR:
		Log += TEXT("Error: ");
		Color = FLinearColor::Red;
		break;
	default:
		break;
	}

	Log += InMessage;
	if (ScrollBox)
	{
		ScrollBox->AddSlot()
		.HAlign(EHorizontalAlignment::HAlign_Fill)
		.VAlign(EVerticalAlignment::VAlign_Fill)
		.Padding(4.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Log))
			.ColorAndOpacity(Color)
		];
	}
	FPlatformProcess::Sleep(0.05f);
}

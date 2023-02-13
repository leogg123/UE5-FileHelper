#include "GLCCommonMethods.h"

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

	bool GetSourceDirAndProgramNameByFileName(const FString& InFileName, FString& OutSourceDir,
		FString& OutProgramName)
	{
		FString NewTargetPath = InFileName;
		FPaths::NormalizeDirectoryName(NewTargetPath);

		TArray<FString> PathStrings;
		NewTargetPath.ParseIntoArray(PathStrings, TEXT("/"));

		int32 Index = 10;
		bool bFind = false;
		while (Index != 0 && bFind == false)
		{
			FString SearchDiretory;
			for (FString& InPath : PathStrings)
			{
				SearchDiretory += InPath += TEXT("/");
			}
			SearchDiretory.RemoveFromEnd(TEXT("/"));

			TArray<FString> FileNames;
			IFileManager::Get().FindFilesRecursive(FileNames, *SearchDiretory, TEXT("*")
				, true, false);
			if (FileNames.Num())
			{
				for (FString& TempFileName : FileNames)
				{
					if (TempFileName.Contains(TEXT("Build.cs")))
					{
						FPaths::NormalizeFilename(TempFileName);
						OutSourceDir = FPaths::GetPath(TempFileName);
						
						TArray<FString> PathParseStrings;
						OutSourceDir.ParseIntoArray(PathParseStrings,TEXT("/"));

						OutProgramName = PathParseStrings.Last();
						bFind = true;
						break;
					}
				}
			}

			PathStrings.Pop();
			--Index;
		}
		if(bFind) return true;

		return false;
	}

	bool GetFileIncludeByClassName(const FString& InClassName, const FString& InProgramName,
		const FString& InSourceDir, FString& OutInclude)
	{
		if(!IFileManager::Get().DirectoryExists(*InSourceDir) || InClassName.IsEmpty()) return false;
		OutInclude.Empty();

		TArray<FString> FileNames;
		IFileManager::Get().FindFilesRecursive(FileNames,*InSourceDir,TEXT("*"), true, false);
		if (FileNames.Num())
		{
			for (FString& InFileName : FileNames)
			{
				if(!InFileName.Contains(TEXT(".h"))) continue;

				TArray<FString> FileDatas;
				if (FFileHelper::LoadFileToStringArray(FileDatas, *InFileName))
				{
					for (FString& Data : FileDatas)
					{
						if (Data.Contains(InClassName))
						{
							FPaths::NormalizeFilename(InFileName);
							TArray<FString> FileNameArr;
							InFileName.ParseIntoArray(FileNameArr,TEXT("/"));

							bool bFind = false;
							for (FString& InSingleName : FileNameArr)
							{
								if (bFind)
								{
									OutInclude += InSingleName + TEXT("/");
								}
								else
								{
									if (InSingleName.Contains(InProgramName))
									{
										OutInclude += FString::Printf(TEXT("#include \"%s/"),*InSingleName);
										bFind = true;
									}
								}
							}
							OutInclude.RemoveFromEnd(TEXT("/"));
							OutInclude += TEXT("\"");

							return true;
						}
					}
				}
			}
		}
		return false;
	}

	void GenerateCompoundWidget(const FString& InTargetPath, const FString& InNewSlateName,
		const FString& OptionalParent)
	{
		if(InNewSlateName.IsEmpty()) OpenMessageDialogByString(TEXT("SlateName 不能为空"));

		if(CheckPath(InTargetPath))
		{
			const FString Temp_hFile = FPaths::ProjectSavedDir() / TEXT("MyTempSlate__.h");
			const FString Temp_cppFile = FPaths::ProjectSavedDir() / TEXT("MyTempSlate__.cpp");

			const FString Target_hFile = InTargetPath / InNewSlateName + TEXT(".h");
			const FString Target_cppFile = InTargetPath / InNewSlateName + TEXT(".cpp");

			FGLCOutputLog OutputLog;
			if (IFileManager::Get().Copy(*Target_hFile, *Temp_hFile) == ECopyResult::COPY_OK)
			{
				OutputLog.AddNewMessage(FString::Printf(TEXT("[%s] 文件复制到 [%s]"),*Temp_hFile,*InTargetPath));
				if (IFileManager::Get().Copy(*Target_cppFile, *Temp_cppFile) == ECopyResult::COPY_OK)
				{
					OutputLog.AddNewMessage(FString::Printf(TEXT("[%s] 文件复制到 [%s]"), *Temp_cppFile, *InTargetPath));
					
					auto ModifyFile = [&](bool bIscpp,TFunction<void(FString& InString)>fun = nullptr)
					{
						FString FileName = bIscpp ? Target_cppFile : Target_hFile;
						TArray<FString> Datas;
						if (FFileHelper::LoadFileToStringArray(Datas, *FileName))
						{
							for (FString& InData : Datas)
							{
								if (fun)
								{
									fun(InData);
								}
								InData.ReplaceInline(TEXT("MyTempSlate__"), *InNewSlateName);
							}
							IFileManager::Get().Delete(*FileName, true, true);
							if (FFileHelper::SaveStringArrayToFile(Datas, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
							{
								OutputLog.AddNewMessage(FString::Printf(TEXT("[%s] 文件修改成功"), *FileName));
							}
						}
					};
					

					//找到程序的Source文件夹
					FString SourceDir;
					FString ProgramName;
					FString IncludeString;

					bool bFind = false;
					if (!OptionalParent.IsEmpty())
					{
						bFind = GetSourceDirAndProgramNameByFileName(InTargetPath, SourceDir, ProgramName);
						bFind = GetFileIncludeByClassName(OptionalParent, ProgramName, SourceDir, IncludeString);
						
						if (!bFind)
						{
							OpenMessageDialogByString(TEXT("确保项目文件夹里存在build.cs文件"));
						}
					}

					//处理复制的.h文件
					ModifyFile(false,[&](FString& InData)
					{
						if (bFind)
						{
							if (InData.Contains(TEXT("Widgets/SCompoundWidget.h")))
							{
								InData = IncludeString;
							}
							else if (InData.Contains(TEXT("public SCompoundWidget")))
							{
								InData.ReplaceInline(TEXT("SCompoundWidget"),*OptionalParent);
							}
						}
					});

					//处理复制的.cpp文件
					ModifyFile(true);
					OutputLog.AddNewMessage(TEXT("完成"));
					FPlatformProcess::ExploreFolder(*InTargetPath);
				}
			}
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
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Top)
		.Padding(4.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Log))
			.ColorAndOpacity(Color)
		];
	}
}

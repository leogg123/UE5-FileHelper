#include "GLCCommonMethods.h"

#include <HAL/PlatformFileManager.h>

#include "WindowsAPI.h"
#include "GLCFileHelper\Core\Type\GLCOutPutLog.h"
#include "HAL/RunnableThread.h"

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
		if(!CheckEnginePathAndPath(InSearchPath)) return;
		
		TArray<FString> FoundFiles;
		IFileManager::Get().FindFilesRecursive(FoundFiles,*InSearchPath,TEXT("*"),true,false);

		FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("共找到文件数量 %d 个"),FoundFiles.Num()));
		if (FoundFiles.Num())
		{
			for (FString& InFileName : FoundFiles)
			{
				TArray<FString> FileData;
				FFileHelper::LoadFileToStringArray(FileData,*InFileName);
				if (FileData.Num())
				{
					if(!IFileManager::Get().Delete(*InFileName,true,true))
					{
						FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件删除失败"),*InFileName)
							,FGLCOutputLog::GLC_ERROR);
					}
					if(FFileHelper::SaveStringArrayToFile(FileData,*InFileName,
						CodingType))
					{
						FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件保存成功"),*InFileName));
					}
					else
					{
						FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件保存失败"),*InFileName)
							,FGLCOutputLog::GLC_ERROR);
					}
				}
			}
		}
	}

	

	void GenerateNewProgram(const FString& InNewProgramName, bool bIsConsoleApp /*= true*/, 
		const FString& InTargetPath /*= GetLastGenerateProgramPath()*/)
	{
		if (CheckEnginePathAndPath(InTargetPath))
		{
			const FString EngineProgramSource = GetEnginePath() / TEXT("Engine") / TEXT("Source")
				/ TEXT("Programs");
			FString CopiedProgramPath = GetEnginePath() / TEXT("Engine") / TEXT("Source")
				/ TEXT("Programs") / TEXT("BlankProgram");
			FString SearchStr = TEXT("BlankProgram");
			if(!bIsConsoleApp)
			{
				CopiedProgramPath = FPaths::ProjectSavedDir() / TEXT("MyTempProgram__");
				SearchStr = TEXT("MyTempProgram__");
			}
			const FString TargetDirectory = InTargetPath / InNewProgramName;
			
			if (IFileManager::Get().DirectoryExists(*TargetDirectory))
			{
				OpenMessageDialogByString(FString::Printf(TEXT("[%s] 程序已经存在 !"), *InNewProgramName));
				FPlatformProcess::ExploreFolder(*InTargetPath);
				return;
			}
			
			if (IFileManager::Get().DirectoryExists(*CopiedProgramPath))
			{
				if (FPlatformFileManager::Get().GetPlatformFile().CopyDirectoryTree(*TargetDirectory,
					*CopiedProgramPath, true))
				{
					FGLCOutputLog::AddNewMessage(TEXT("文件夹复制成功"));

					TArray<FString> FileNameStrings;
					IFileManager::Get().FindFilesRecursive(FileNameStrings, *TargetDirectory, TEXT("*"),
						true, false);
					FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("找到文件数量 = %d"), FileNameStrings.Num()));
					if (FileNameStrings.Num())
					{
						for (FString& InFileName : FileNameStrings)
						{
							if(InFileName.Contains(TEXT("ico")))continue;
							if (InFileName.Contains(TEXT("png")))continue;

							TArray<FString> FileData;
							if (FFileHelper::LoadFileToStringArray(FileData, *InFileName))
							{
								for (FString& InData : FileData)
								{
									InData.ReplaceInline(*SearchStr,*InNewProgramName);
								}
								if (!IFileManager::Get().Delete(*InFileName, true, true))
								{
									FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件删除失败！"), *InFileName)
										, FGLCOutputLog::GLC_ERROR);
								}
								InFileName.ReplaceInline(*SearchStr,*InNewProgramName);
								if (FFileHelper::SaveStringArrayToFile(FileData, *InFileName, 
									FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
								{
									FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件保存成功！"), *InFileName)
										, FGLCOutputLog::GLC_DISPLAY);
								}
								else
								{
									FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件保存失败！"),*InFileName)
										,FGLCOutputLog::GLC_ERROR);
								}
							}
						}
					}
				}
				else
				{
					OpenMessageDialogByString(FString::Printf(TEXT("[%s] 文件夹不存在"),*CopiedProgramPath));
				}
			}
			FGLCOutputLog::AddNewMessage(TEXT("完成"));
			FPlatformProcess::ExploreFolder(*InTargetPath);
		}		
	}

	bool FindFileSpecInfo(const FString& InFileName,FGLCSearchInfo& OutInfo)
	{
		FString NewTargetPath = InFileName;
		FPaths::NormalizeDirectoryName(NewTargetPath);

		TArray<FString> PathStrings;
		NewTargetPath.ParseIntoArray(PathStrings, TEXT("/"));

		int32 Index = 10;
		bool bFind = false;
		while (Index != 0 && bFind == false)
		{
			FString SearchDirectory;
			for (FString& InPath : PathStrings)
			{
				SearchDirectory += InPath += TEXT("/");
			}
			SearchDirectory.RemoveFromEnd(TEXT("/"));

			TArray<FString> FileNames;
			IFileManager::Get().FindFilesRecursive(FileNames, *SearchDirectory, TEXT("*")
				, true, false);
			if (FileNames.Num())
			{
				for (FString& TempFileName : FileNames)
				{
					if (TempFileName.Contains(TEXT("Build.cs")))
					{
						OutInfo.Build_cs_Path = TempFileName;
						
						FPaths::NormalizeFilename(TempFileName);
						OutInfo.SourceDir_Complete = FPaths::GetPath(TempFileName);
						
						TArray<FString> PathParseStrings;
						OutInfo.SourceDir_Complete.ParseIntoArray(PathParseStrings,TEXT("/"));

						OutInfo.ModuleName = PathParseStrings.Last();
						
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

				TArray<FString> FileData;
				if (FFileHelper::LoadFileToStringArray(FileData, *InFileName))
				{
					for (FString& Data : FileData)
					{
						if (Data.Contains(InClassName))
						{
							int32 ClassIndex = Data.Find(InClassName);
							int32 Index = Data.Find(TEXT(":"));
							if(ClassIndex > Index) continue;
							
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

		if(CheckEnginePathAndPath(InTargetPath))
		{
			const FString Temp_hFile = FPaths::ProjectSavedDir() / TEXT("MyTempSlate__.h");
			const FString Temp_cppFile = FPaths::ProjectSavedDir() / TEXT("MyTempSlate__.cpp");

			const FString Target_hFile = InTargetPath / InNewSlateName + TEXT(".h");
			const FString Target_cppFile = InTargetPath / InNewSlateName + TEXT(".cpp");

			if (IFileManager::Get().Copy(*Target_hFile, *Temp_hFile) == ECopyResult::COPY_OK)
			{
				FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件复制到 [%s]"),*Temp_hFile,*InTargetPath));
				if (IFileManager::Get().Copy(*Target_cppFile, *Temp_cppFile) == ECopyResult::COPY_OK)
				{
					FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件复制到 [%s]"), *Temp_cppFile, *InTargetPath));
					
					auto ModifyFile = [&](bool bIscpp,TFunction<void(FString& InString)>fun = nullptr)
					{
						FString FileName = bIscpp ? Target_cppFile : Target_hFile;
						TArray<FString> Data;
						if (FFileHelper::LoadFileToStringArray(Data, *FileName))
						{
							for (FString& InData : Data)
							{
								if (fun)
								{
									fun(InData);
								}
								InData.ReplaceInline(TEXT("MyTempSlate__"), *InNewSlateName);
							}
							IFileManager::Get().Delete(*FileName, true, true);
							if (FFileHelper::SaveStringArrayToFile(Data, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
							{
								FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件修改成功"), *FileName));
							}
						}
					};
					

					//找到程序的Source文件夹
					FString IncludeString;
					FGLCSearchInfo SearchInfo;

					bool bFind = false;
					if (!OptionalParent.IsEmpty())
					{
						FindFileSpecInfo(InTargetPath,SearchInfo);
						bFind = GetFileIncludeByClassName(OptionalParent, SearchInfo.ModuleName, SearchInfo.SourceDir_Complete, IncludeString);
						
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
					FGLCOutputLog::AddNewMessage(TEXT("完成"));
					FPlatformProcess::ExploreFolder(*InTargetPath);
				}
			}
		}
	}

	void ModifyCharactersIteration(const FString& InPath, const FString& InSearch, 
		const FString& InReplace,const FString& InOptionalCondition)
	{
		if(CheckEnginePathAndPath(InPath))
		{
			int32 Count = 0;
			
			TArray<FString> FileNames;
			IFileManager::Get().FindFilesRecursive(FileNames,*InPath,
				TEXT("*"),true,false);
			FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("找到文件 %d 个"),FileNames.Num()));
			if(FileNames.Num())
			{
				for(FString& TempFileName : FileNames)
				{
					TArray<FString> FileData;
					int32 LastCount = Count;
					if(FFileHelper::LoadFileToStringArray(FileData,*TempFileName))
					{
						for(FString& InData : FileData)
						{
							if(!InOptionalCondition.IsEmpty())
							{
								if(InData.Contains(InOptionalCondition))
								{
									if(InData.ReplaceInline(*InSearch,*InReplace)) ++Count;
								}
							}
							else
							{
								if(InData.ReplaceInline(*InSearch,*InReplace)) ++Count;
							}
							
						}
						IFileManager::Get().Delete(*TempFileName,true,true);

						if(!InOptionalCondition.IsEmpty())
						{
							if(TempFileName.Contains(InOptionalCondition))
							{
								if(TempFileName.ReplaceInline(*InSearch,*InReplace)) ++Count;
							}
						}
						else
						{
							if(TempFileName.ReplaceInline(*InSearch,*InReplace)) ++Count;
						}
						
						FFileHelper::SaveStringArrayToFile(FileData,*TempFileName,
							FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);

						if(Count != LastCount)
						{
							FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件被修改"),*TempFileName));
							FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("当前修改的总行数为 %d"),Count));
						}
					}
				}

				FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("当前修改的总行数为 %d"),Count));
				FGLCOutputLog::AddNewMessage(TEXT("完成 !"));
			}
		}
	}

	void PackageProgram(const FString& InProgramName, const FString& TargetPath)
	{
		if(CheckEnginePathAndPath(TargetPath) && !InProgramName.IsEmpty())
		{
			const FString EngineWin64BinaryDir = GetEnginePath() / TEXT("Engine") / TEXT("Binaries")
				/ TEXT("Win64");
			const FString EngineContentOfSlate = GetEnginePath() / TEXT("Engine")
				/ TEXT("Content") / TEXT("Slate");
			const FString ProgramSave = GetEnginePath() / TEXT("Engine") / TEXT("Programs")
				/ InProgramName;
			const FString Shader = GetEnginePath() / TEXT("Engine") / TEXT("Shaders");

			
			const FString NewTargetPath = TargetPath / InProgramName;
			const FString TargetWin64BinaryDir = NewTargetPath / TEXT("Engine") / TEXT("Binaries")
				/ TEXT("Win64");
			const FString TargetContentOfSlate = NewTargetPath / TEXT("Engine")
				/ TEXT("Content") / TEXT("Slate");
			const FString TargetSave = NewTargetPath / TEXT("Engine") / TEXT("Programs")
				/ InProgramName;
			const FString TargetShader = NewTargetPath / TEXT("Engine") / TEXT("Shaders");

			if (IFileManager::Get().DirectoryExists(*NewTargetPath))
			{
				IFileManager::Get().DeleteDirectory(*NewTargetPath,true,true);
			}
			
			if(CheckPath(*EngineWin64BinaryDir) && CheckPath(EngineContentOfSlate)
				&& CheckPath(ProgramSave))
			{

				auto CopyFiles = [&](const FString& FromDir,const FString& ToDir,bool bCopyAll)
				{
					if(!CreateDirectory(ToDir)) return;

					if(bCopyAll)
					{
						if(FPlatformFileManager::Get().GetPlatformFile().CopyDirectoryTree(*ToDir,
							*FromDir,true))
						{
							FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件夹打包成功"),*FromDir));
						}
						else
						{
							FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件夹存在打包失败的文件"),*FromDir),
								FGLCOutputLog::GLC_WARNING);
						}
						return;
					}
					
					TArray<FString> FileNames;
					IFileManager::Get().FindFilesRecursive(FileNames,*FromDir,
						TEXT("*"),true,false);
					
					for(FString& InFileName : FileNames)
					{
						if(!InFileName.Contains(InProgramName)) continue;

						//当前在引擎搜索到的文件名字
						FPaths::NormalizeFilename(InFileName);
						TArray<FString> PathStrs;
						InFileName.ParseIntoArray(PathStrs,TEXT("/"));
						
						FString NewDir = ToDir;
						FPaths::NormalizeFilename(NewDir);

						//目标的文件名字
						TArray<FString> TargetFileNames;
						NewDir.ParseIntoArray(TargetFileNames,TEXT("/"));

						//保持相对的路径是一致的
						bool bFind = false;
						for(FString& InStr : PathStrs)
						{
							if(bFind)
							{
								NewDir += InStr + TEXT("/");
							}
							else
							{
								if(InStr.Equals(TargetFileNames[TargetFileNames.Num() - 1]))
								{
									bFind = true;
									NewDir += TEXT("/");
								}
							}
						}
						NewDir.RemoveFromEnd(TEXT("/"));
						
						const FString NewFileName = FPaths::GetPath(NewDir) / FPaths::GetCleanFilename(InFileName);
						if(IFileManager::Get().Copy(*NewFileName,*InFileName,true,true) == ECopyResult::COPY_OK)
						{
							FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件打包成功"),*InFileName));
						}
						else
						{
							FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 文件打包失败"),*InFileName),
								FGLCOutputLog::GLC_WARNING);
						}
					}
				};

				//打包Binary
				CopyFiles(EngineWin64BinaryDir,TargetWin64BinaryDir,false);

				//打包Content的Slate文件夹
				CopyFiles(EngineContentOfSlate,TargetContentOfSlate,true);

				//打包程序的保存目录
				CopyFiles(ProgramSave,TargetSave,true);

				//打包Shader目录
				CopyFiles(Shader,TargetShader,true);

				TArray<FString> FileNames;
				IFileManager::Get().FindFilesRecursive(FileNames,*TargetWin64BinaryDir,
					TEXT("*"),true,false);
				for(FString& InFileName : FileNames)
				{
					if(InFileName.Contains(TEXT("exe")))
					{
						const FString ShortcutFileName = NewTargetPath / InProgramName + TEXT(".lnk");
						if(GLCWindowAPI::CreateProgramShortcut(InFileName,
						ShortcutFileName))
						{
							FGLCOutputLog::AddNewMessage(TEXT("快捷方式创建成功"));
						}
						else
						{
							FGLCOutputLog::AddNewMessage(TEXT("快捷方式创建失败"),FGLCOutputLog::GLC_WARNING);
						}
						break;
					}
				}
				
				FGLCOutputLog::AddNewMessage(TEXT("完成！"));
				FPlatformProcess::ExploreFolder(*NewTargetPath);
			}
		}
	}

	void AddCopyRight(const FString& InSearchPath, FString& InCopyRight)
	{
		if(CheckPath(InSearchPath))
		{
			if(!InCopyRight.Contains(TEXT("//")))
			{
				InCopyRight.InsertAt(0,TEXT("//"));
			}
			
			TArray<FString> FileNames;
			IFileManager::Get().FindFilesRecursive(FileNames,
				*InSearchPath,TEXT("*"),true,false);

			for(FString& InFileName : FileNames)
			{
				TArray<FString> FileData;
				if(FFileHelper::LoadFileToStringArray(FileData,*InFileName))
				{
					TArray<FString> CopiedFileData = FileData;
					for(int32 i = 0;i < 5;++i)
					{
						if(CopiedFileData.IsValidIndex(i) && CopiedFileData[i].Contains(TEXT("//")))
						{
							FileData.RemoveSingle(CopiedFileData[i]);
							FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("移除了原有声明 [%s] 在 [%s]"),*CopiedFileData[i],*InFileName));
						}
					}
					FileData.Insert(InCopyRight,0);
					if(FFileHelper::SaveStringArrayToFile(FileData,*InFileName))
					{
						FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("在 [%s] 添加新声明"),*InFileName));
					}
					else
					{
						FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("在 [%s] 添加新声明失败"),*InFileName),
							FGLCOutputLog::GLC_WARNING);
					}
					
				}
			}
			FGLCOutputLog::AddNewMessage(TEXT("完成！"));
			FPlatformProcess::ExploreFolder(*InSearchPath);
		}
	}

	void FixInclude(const FString& InSearchDir)
	{
		int32 Count = 0;
		if(CheckEnginePathAndPath(InSearchDir))
		{
			FGLCOutputLog::AddNewMessage(TEXT("处理中..."));
			TArray<FString> FileNames;
			IFileManager::Get().FindFilesRecursive(FileNames,*InSearchDir,TEXT("*"),
				true,false);
			FGLCOutputLog::AddNewMessage(
				FString::Printf(TEXT("搜索到文件共 %d 个"),FileNames.Num()));

			FString CurrentModule;
			for(FString& InFileName : FileNames)
			{
				FGLCSearchInfo SearchInfo;
				FindFileSpecInfo(InFileName,SearchInfo);
				//加载文件内容
				TArray<FString> FileData;
				if(FFileHelper::LoadFileToStringArray(FileData,
					*InFileName))
				{
					int32 LineCount = 0;
					for(FString& Data : FileData)
					{
						if(++LineCount == 200)break;

						//测试
						if(Data.Contains(TEXT("我的测试")))
						{
							FString ab;
						}
						
						if(Data.Contains(TEXT("#include"))&&
							!Data.Contains(TEXT("generated.h")))
						{
							FString CopyData = Data;
							CopyData.ReplaceInline(TEXT("#include"),TEXT(""));
							CopyData.ReplaceInline(TEXT("\""),TEXT(""));
							CopyData.ReplaceInline(TEXT("<"),TEXT(""));
							CopyData.ReplaceInline(TEXT(">"),TEXT(""));
							CopyData.RemoveSpacesInline();

							
							if(IFileManager::Get().FileExists(*(SearchInfo.SourceDir_Complete / TEXT("Public") / CopyData))
								|| IFileManager::Get().FileExists(*(SearchInfo.SourceDir_Complete / TEXT("Private") / CopyData)))
							{
								continue;
							}

							FString ClearFileName = FPaths::GetCleanFilename(CopyData);
							FString NewInclude;

							//获取include 路径
							for(FString& NewFileName : FileNames)
							{
								if(FPaths::GetCleanFilename(NewFileName) == ClearFileName)
								{
									TArray<FString> ParseStr;
									FPaths::NormalizeFilename(NewFileName);
									NewFileName.ParseIntoArray(ParseStr,TEXT("/"));

									bool bFind = false;
									for(FString& InStr : ParseStr)
									{
										if(!bFind)
										{
											if(InStr.Contains(TEXT("Public")) ||
											InStr.Contains(TEXT("Private")))
											{
												bFind = true;
											}
										}
										else
										{
											NewInclude += InStr + TEXT("/");
										}
									}
									NewInclude.RemoveFromEnd(TEXT("/"));
									break;
								}
							}

							const FString TempData = Data;
							if(!NewInclude.IsEmpty())
							{
								Data = FString::Printf(TEXT("#include \"%s\""),*NewInclude);
								++Count;
								
								FGLCOutputLog::AddNewMessage(
									FString::Printf(TEXT("[%s] 文件中的 [%s] 被替换成 [%s]"),
										*InFileName,*TempData,*Data));
							}
							/*else
							{
								FGLCOutputLog::AddNewMessage(
									FString::Printf(TEXT("[%s] 文件中的 [%s] 替换失败！"),
										*InFileName,*TempData),FGLCOutputLog::GLC_ERROR);
							}*/
						}
					}
					FFileHelper::SaveStringArrayToFile(FileData,*InFileName);
				}
			}
		}
		FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("%d 个文件被处理"),Count));
		FGLCOutputLog::AddNewMessage(TEXT("完成！"));
	}

	void DeleteProgram(const FString& InProgramName)
	{
		if(CheckEnginePath())
		{
			FString BinaryPath = GetEnginePath() / TEXT("Engine") / TEXT("Binaries");
			FString ProgramPath = GetEnginePath() / TEXT("Engine") / TEXT("Programs");
			FString ProgramSourcePath = GetEnginePath() / TEXT("Engine") / TEXT("Source")
				/ TEXT("Programs");

			TArray<FString> FileNames;
			IFileManager::Get().FindFilesRecursive(FileNames,*BinaryPath,TEXT("*"),
				true,true,false);
			IFileManager::Get().FindFilesRecursive(FileNames,*ProgramPath,TEXT("*"),
				true,true,false);
			IFileManager::Get().FindFilesRecursive(FileNames,*ProgramSourcePath,TEXT("*"),
			true,true,false);

			static TArray<FString> DeleteFileNames;
			for(FString& InFileName : FileNames)
			{
				if(InFileName.Contains(InProgramName))
				{
					DeleteFileNames.Add(InFileName);
					FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("找到文件 [%s] ")
						,*InFileName));
				}
			}
			FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("共找到文件 %d 个")
						,DeleteFileNames.Num()));

			TSharedPtr<SWindow> NewWindow =
				SNew(SWindow)
				.ClientSize(FVector2D(350,120))
				.Title(FText::FromString(TEXT("确认删除文件吗")))
				.SizingRule(ESizingRule::FixedSize)
				.SupportsMinimize(false)
				.SupportsMaximize(false)
				.UseOSWindowBorder(false)
				.IsTopmostWindow(true)
				[
					SNew(SBorder)
					[
						SNew(SVerticalBox)

						+SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(EHorizontalAlignment::HAlign_Center)
						.VAlign(EVerticalAlignment::VAlign_Center)
						.Padding(5.f)
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("请在log窗口里查看查找到的文件名字")))
						]

						+SVerticalBox::Slot()
						.AutoHeight()
						.HAlign(EHorizontalAlignment::HAlign_Fill)
						.VAlign(EVerticalAlignment::VAlign_Bottom)
						.Padding(5.f)
						[
							SNew(SHorizontalBox)

							+SHorizontalBox::Slot()
							.AutoWidth()
							.HAlign(EHorizontalAlignment::HAlign_Center)
							.VAlign(EVerticalAlignment::VAlign_Center)
							.Padding(FMargin(95,35,0,0))
							[
								SNew(SButton)
								.Text(FText::FromString(TEXT("确认")))
								.OnReleased_Lambda(
									[&]()
									{
										FSlateApplication::Get().GetActiveTopLevelWindow()->RequestDestroyWindow();
										FGLCOutputLog::AddNewMessage(TEXT("开始删除文件....."));
										for(FString& MyFileName : DeleteFileNames)
										{
											bool bDelete = false;
											if(IFileManager::Get().Delete(*MyFileName,true,true))
											{
												bDelete = true;
											}
											if(IFileManager::Get().DeleteDirectory(*MyFileName,true,true))
											{
												bDelete = true;
											}
											if(bDelete)
											{
												FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 删除成功"),*MyFileName));
											}
											else
											{
												FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("[%s] 删除失败"),*MyFileName)
													,FGLCOutputLog::GLC_ERROR);
											}
										}
										FGLCOutputLog::AddNewMessage(TEXT("删除程序完成！"));
										DeleteFileNames.Empty();
									})
							]
						]
					]

					/*+SOverlay::Slot()
					.HAlign(EHorizontalAlignment::HAlign_Fill)
					.VAlign(EVerticalAlignment::VAlign_Fill)
					[
						
					]*/
				];
			FSlateApplication::Get().AddWindow(NewWindow.ToSharedRef());
		}
	}

	bool CheckPath(const FString& InPath)
	{
		if (!IFileManager::Get().DirectoryExists(*InPath))
		{
			OpenMessageDialogByString(FString::Printf(TEXT("[%s] 路径不存在"),*InPath));
			return false;
		}
		return true;
	}

	bool CreateDirectory(const FString& InPath)
	{
		bool Ret = FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*InPath);
		if(!Ret)
		{
			OpenMessageDialogByString(FString::Printf(TEXT("[%s] 文件夹创建失败"),*InPath));
		}
		return Ret;
	}

	bool CheckEnginePath()
	{
		if (!IFileManager::Get().DirectoryExists(*GetEnginePath()))
		{
			OpenMessageDialogByString(TEXT("请在设置里设置引擎的目录"));
			return false;
		}
		return true;
	}

	bool CheckEnginePathAndPath(const FString& InPath)
	{
		if (!CheckPath(InPath)) return false;
		if (!CheckEnginePath()) return false;
		return true;
	}

	void OpenMessageDialogByString(const FString& InMessage)
	{
		FText Title = FText::FromString(TEXT("GLCFileHelper"));
		FMessageDialog::Open(EAppMsgType::Ok,
			FText::FromString(InMessage),&Title);
	}

}

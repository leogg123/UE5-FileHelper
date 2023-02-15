#include "GLCTempMethods.h"
#include "GLCCommonMethods.h"


namespace GLCTempMethods
{
	void ModifyNotesIteration(const FString& InPath)
	{
		FGLCOutputLog OutputLog;
		int32 Count = 0;

		TArray<FString> FileNames;
		IFileManager::Get().FindFilesRecursive(FileNames, *InPath,
			TEXT("*"), true, false);
		OutputLog.AddNewMessage(FString::Printf(TEXT("找到文件 %d 个"), FileNames.Num()));
		if (FileNames.Num())
		{
			for (FString& TempFileName : FileNames)
			{
				TArray<FString> FileData;
				int32 LastCount = Count;
				if (FFileHelper::LoadFileToStringArray(FileData, *TempFileName))
				{
					TArray<FString> TempFileData = FileData;
					for (FString& InData : TempFileData)
					{
						if (InData.Contains(TEXT("//")))
						{
							FString NewData = InData;
							NewData.RemoveSpacesInline();
							if (NewData.Contains(TEXT("		")) || NewData.Contains(TEXT("1")))
							{
								if (FileData.RemoveSingle(InData))
								{
									++Count;
								}
								if (Count != LastCount)
								{
									OutputLog.AddNewMessage(FString::Printf(TEXT("当前修改的总行数为 %d"),Count));
								}
							}
						}
					}
					IFileManager::Get().Delete(*TempFileName, true, true);
					FFileHelper::SaveStringArrayToFile(FileData,*TempFileName
						,FFileHelper::EEncodingOptions::ForceUTF8);
				}
			}

			OutputLog.AddNewMessage(FString::Printf(TEXT("当前修改的总行数为 %d"), Count));
			OutputLog.AddNewMessage(TEXT("完成 !"));
		}
	}
}
#include "GLCTempMethods.h"
#include "GLCCommonMethods.h"
#include "GLCFileHelper\Core\Type\GLCOutPutLog.h"


namespace GLCTempMethods
{
	void ModifyNotesIteration(const FString& InPath)
	{
		int32 Count = 0;

		TArray<FString> FileNames;
		IFileManager::Get().FindFilesRecursive(FileNames, *InPath,
			TEXT("*"), true, false);
		FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("找到文件 %d 个"), FileNames.Num()));
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
									FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("当前修改的总行数为 %d"),Count));
								}
							}
						}
					}
					IFileManager::Get().Delete(*TempFileName, true, true);
					FFileHelper::SaveStringArrayToFile(FileData,*TempFileName
						,FFileHelper::EEncodingOptions::ForceUTF8);
				}
			}

			FGLCOutputLog::AddNewMessage(FString::Printf(TEXT("当前修改的总行数为 %d"), Count));
			FGLCOutputLog::AddNewMessage(TEXT("完成 !"));
		}
	}
}
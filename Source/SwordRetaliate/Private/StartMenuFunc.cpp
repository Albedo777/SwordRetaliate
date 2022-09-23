// Fill out your copyright notice in the Description page of Project Settings.
#include "StartMenuFunc.h"


bool UStartMenuFunc::SaveToFile(FString Dir, FString Name, FString Text, bool Overwrite)
{
	IPlatformFile& F = FPlatformFileManager::Get().GetPlatformFile();
	if (!F.DirectoryExists(*Dir))
	{
		F.CreateDirectoryTree(*Dir);
		if (!F.DirectoryExists(*Dir))
		{
			return false;
		}
	}


	Dir += "\\";
	Dir += Name;


	if (!Overwrite)
	{
		if (F.FileExists(*Dir))
		{
			return false;
		}
	}

	return FFileHelper::SaveStringToFile(Text, *Dir);
}
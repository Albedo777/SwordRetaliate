// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HAL/IPlatformFileCachedWrapper.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "StartMenuFunc.generated.h"


/**
 * 
 */
UCLASS()
class SWORDRETALIATE_API UStartMenuFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "LoginMenu")
	static bool SaveToFile(FString Dir, FString Name, FString Text, bool Overwrite = false);
};

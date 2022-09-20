#pragma once

#include "CoreMinimal.h"
#include "SwordRetaliateCharacter.h"
#include "SwordRetaliateUtils.generated.h"

UCLASS()
class SWORDRETALIATE_API USwordRetaliateUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static ASwordRetaliateCharacter* GetSwordRetaliateCharacter(const UObject* WorldContextObject);
};

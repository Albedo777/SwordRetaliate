#pragma once

#include "CoreMinimal.h"
#include "SwordRetaliateCharacter.h"
#include "SkillSystem/SkillBase.h"
#include "SwordRetaliateUtils.generated.h"

UCLASS()
class SWORDRETALIATE_API USwordRetaliateUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static ASwordRetaliateCharacter* GetSwordRetaliateCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static USkillBase* GetSkillConfig(const UObject* WorldContextObject, const int32 SkillId);
};

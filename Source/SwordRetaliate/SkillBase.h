#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SkillBase.generated.h"

class ASwordRetaliateCharacter;

UCLASS(Blueprintable)
class SWORDRETALIATE_API USkillBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillDuration = 0.f;

	virtual void OnInitialize();
	
	virtual void OnActiveSkill(ASwordRetaliateCharacter* Character);

	virtual void OnDeActiveSkill(ASwordRetaliateCharacter* Character);

	virtual bool CanCastSkill();

	UFUNCTION(BlueprintNativeEvent)
	void BP_OnActiveSkill(ASwordRetaliateCharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
	void BP_OnDeActiveSkill(ASwordRetaliateCharacter* Character);
	
	FTimerHandle TimerHandleSkill;

protected:
	bool bIsCasting = false;
};

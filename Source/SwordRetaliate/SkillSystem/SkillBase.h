#pragma once

#include "CoreMinimal.h"
#include "EffectActor.h"
#include "SwordRetaliate/SwordRetaliateCharacter.h"
#include "UObject/Object.h"
#include "SkillBase.generated.h"

class ASwordRetaliateCharacter;

UCLASS(Blueprintable)
class SWORDRETALIATE_API USkillBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEffectActor> EffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EFlipAnimationType AnimationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillCoolDownTime;
	
	virtual void OnInitialize();
	
	virtual void OnActiveSkill(ASwordRetaliateCharacter* Character);

	virtual void OnDeActiveSkill(ASwordRetaliateCharacter* Character);

	virtual bool CanCastSkill();

	UFUNCTION(BlueprintNativeEvent)
	void BP_OnActiveSkill(ASwordRetaliateCharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
	void BP_OnDeActiveSkill(ASwordRetaliateCharacter* Character);

private:
	bool bIsInCoolDown = false;
	
	FTimerHandle TimerHandleSkill;
};

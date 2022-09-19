#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "DurationSkill.generated.h"

UCLASS()
class SWORDRETALIATE_API UDurationSkill : public USkillBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SkillDuration = 0.f;
	
	virtual void OnInitialize() override;
	
	virtual void OnActiveSkill(ASwordRetaliateCharacter* Character) override;

	virtual void OnDeActiveSkill(ASwordRetaliateCharacter* Character) override;

	virtual bool CanCastSkill() override;
	
	bool bIsCasting = false;

private:
	UPROPERTY(Transient)
	AEffectActor* EffectActor;
};
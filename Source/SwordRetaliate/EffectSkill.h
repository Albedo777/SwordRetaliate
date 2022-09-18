#pragma once

#include "CoreMinimal.h"
#include "EffectActor.h"
#include "SkillBase.h"
#include "EffectSkill.generated.h"

/**
 * Shield Skill
 */
UCLASS()
class SWORDRETALIATE_API UEffectSkill : public USkillBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEffectActor> EffectClass;

	virtual void OnInitialize() override;
	
	virtual void OnActiveSkill(ASwordRetaliateCharacter* Character) override;

	virtual void OnDeActiveSkill(ASwordRetaliateCharacter* Character) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEffectActor* EffectActor;
};

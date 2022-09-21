#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "InstantSkill.generated.h"

UCLASS()
class SWORDRETALIATE_API UInstantSkill : public USkillBase
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillNum = 0;
	
	virtual void OnInitialize() override;
	
	virtual void OnActiveSkill(ASwordRetaliateCharacter* Character) override;

	virtual void OnDeActiveSkill(ASwordRetaliateCharacter* Character) override;

	virtual bool CanCastSkill() override;
};

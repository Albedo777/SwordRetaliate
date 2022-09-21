#include "DurationSkill.h"

#include "SwordRetaliate/SwordRetaliateCharacter.h"

void UDurationSkill::OnInitialize()
{
	Super::OnInitialize();

	if (EffectClass != nullptr)
	{
		EffectActor = Cast<AEffectActor>(GetWorld()->SpawnActor(EffectClass));
	}
}

void UDurationSkill::OnActiveSkill(ASwordRetaliateCharacter* Character)
{
	Super::OnActiveSkill(Character);

	bIsCasting = true;
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandleSkill, FTimerDelegate::CreateLambda([this, Character]
	{
		OnDeActiveSkill(Character);
	}), SkillDuration, false);
	
	EffectActor->BP_OnActiveEffect(Character);
}

void UDurationSkill::OnDeActiveSkill(ASwordRetaliateCharacter* Character)
{
	Super::OnDeActiveSkill(Character);

	bIsCasting = false;
	
	EffectActor->BP_OnDeActiveEffect(Character);
}

bool UDurationSkill::CanCastSkill()
{
	return !bIsCasting;
}


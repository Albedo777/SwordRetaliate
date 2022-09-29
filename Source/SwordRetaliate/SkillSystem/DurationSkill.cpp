#include "DurationSkill.h"

#include "SwordRetaliate/SwordRetaliateCharacter.h"
#include "SwordRetaliate/SwordRetaliateUtils.h"

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

	if (!bIsCasting)
	{
		EffectActor->BP_OnActiveEffect(Character);
	}

	bIsCasting = true;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandleDurationSkill);
	GetWorld()->GetTimerManager().SetTimer(TimerHandleDurationSkill, this, &UDurationSkill::DeActiveSkill, SkillDuration, false);
}

void UDurationSkill::OnDeActiveSkill(ASwordRetaliateCharacter* Character)
{
	Super::OnDeActiveSkill(Character);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandleDurationSkill);

	bIsCasting = false;
	EffectActor->BP_OnDeActiveEffect(Character);
}

bool UDurationSkill::CanCastSkill()
{
	return Super::CanCastSkill();
}

void UDurationSkill::DeActiveSkill()
{
	if (ASwordRetaliateCharacter* Character = USwordRetaliateUtils::GetSwordRetaliateCharacter(this))
	{
		OnDeActiveSkill(Character);
	}
}


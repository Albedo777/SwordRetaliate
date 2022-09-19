#include "SkillBase.h"

#include "SwordRetaliateCharacter.h"

void USkillBase::OnInitialize()
{
	
}

void USkillBase::OnActiveSkill(ASwordRetaliateCharacter* Character)
{
	SkillNum--;
	bIsCasting = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleSkill, FTimerDelegate::CreateLambda([this, Character]
	{
		OnDeActiveSkill(Character);
	}), SkillDuration, false);

	BP_OnActiveSkill(Character);
}

void USkillBase::OnDeActiveSkill(ASwordRetaliateCharacter* Character)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandleSkill);
	bIsCasting = false;
	BP_OnDeActiveSkill(Character);
}

bool USkillBase::CanCastSkill()
{
	return SkillNum > 0 && !bIsCasting;
}

void USkillBase::BP_OnDeActiveSkill_Implementation(ASwordRetaliateCharacter* Character)
{
	
}

void USkillBase::BP_OnActiveSkill_Implementation(ASwordRetaliateCharacter* Character)
{
	
}

#include "SkillBase.h"

void USkillBase::OnInitialize()
{
	
}

void USkillBase::OnActiveSkill(ASwordRetaliateCharacter* Character)
{
	Character->PlayFlipAnimation(AnimationType);
	
	BP_OnActiveSkill(Character);
}

void USkillBase::OnDeActiveSkill(ASwordRetaliateCharacter* Character)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandleSkill);
	Character->PlayFlipAnimation(EFlipAnimationType::Idle);
	
	BP_OnDeActiveSkill(Character);
}

bool USkillBase::CanCastSkill()
{
	return false;
}

void USkillBase::BP_OnDeActiveSkill_Implementation(ASwordRetaliateCharacter* Character)
{
	
}

void USkillBase::BP_OnActiveSkill_Implementation(ASwordRetaliateCharacter* Character)
{
	
}

#include "SkillBase.h"

void USkillBase::OnInitialize()
{
	
}

void USkillBase::OnActiveSkill(ASwordRetaliateCharacter* Character)
{
	Character->PlayFlipAnimation(AnimationType);
	BP_OnActiveSkill(Character);

	bIsInCoolDown = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandleSkill, FTimerDelegate::CreateLambda([this]
	{
		bIsInCoolDown = false;
	}), SkillCoolDownTime, false);
}

void USkillBase::OnDeActiveSkill(ASwordRetaliateCharacter* Character)
{
	Character->PlayFlipAnimation(EFlipAnimationType::Idle);
	
	BP_OnDeActiveSkill(Character);
}

bool USkillBase::CanCastSkill()
{
	return !bIsInCoolDown;
}

void USkillBase::BP_OnDeActiveSkill_Implementation(ASwordRetaliateCharacter* Character)
{
	
}

void USkillBase::BP_OnActiveSkill_Implementation(ASwordRetaliateCharacter* Character)
{
	
}

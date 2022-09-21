#include "InstantSkill.h"

void UInstantSkill::OnInitialize()
{
	Super::OnInitialize();
}

void UInstantSkill::OnActiveSkill(ASwordRetaliateCharacter* Character)
{
	Super::OnActiveSkill(Character);
	SkillNum--;

	AEffectActor* InstActor = Cast<AEffectActor>(GetWorld()->SpawnActor(EffectClass));
	InstActor->BP_OnActiveEffect(Character);
}

void UInstantSkill::OnDeActiveSkill(ASwordRetaliateCharacter* Character)
{
	Super::OnDeActiveSkill(Character);
}

bool UInstantSkill::CanCastSkill()
{
	return SkillNum > 0;
}
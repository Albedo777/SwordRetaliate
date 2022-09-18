#include "EffectSkill.h"

#include "SwordRetaliateCharacter.h"

void UEffectSkill::OnInitialize()
{
	Super::OnInitialize();

	EffectActor = Cast<AEffectActor>(GetWorld()->SpawnActor(EffectClass));
}

void UEffectSkill::OnActiveSkill(ASwordRetaliateCharacter* Character)
{
	Super::OnActiveSkill(Character);
	
	EffectActor->BP_OnActiveEffect(Character);
}

void UEffectSkill::OnDeActiveSkill(ASwordRetaliateCharacter* Character)
{
	Super::OnDeActiveSkill(Character);

	EffectActor->BP_OnDeActiveEffect(Character);
}



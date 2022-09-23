#include "SwordRetaliateUtils.h"

#include "Kismet/GameplayStatics.h"
#include "SkillSystem/SkillComponent.h"

ASwordRetaliateCharacter* USwordRetaliateUtils::GetSwordRetaliateCharacter(const UObject* WorldContextObject)
{
	return Cast<ASwordRetaliateCharacter>(UGameplayStatics::GetPlayerPawn(WorldContextObject, 0));
}

USkillBase* USwordRetaliateUtils::GetSkillConfig(const UObject* WorldContextObject, const int32 SkillId)
{
	const ASwordRetaliateCharacter* Character = GetSwordRetaliateCharacter(WorldContextObject);
	for (USkillBase* Skill : Character->SkillComponent->Skills)
	{
		if (Skill->SkillId == SkillId)
		{
			return Skill;
		}
	}
	return nullptr;
}
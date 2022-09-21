#include "SkillComponent.h"

#include "SwordRetaliate/SwordRetaliateCharacter.h"


USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<USkillBase> SkillConfig : SkillConfigs)
	{
		USkillBase* CopySkill = Cast<USkillBase>(StaticDuplicateObject(SkillConfig.GetDefaultObject(), this));
		if (CopySkill)
		{
			CopySkill->OnInitialize();
			Skills.Add(CopySkill);
		}
	}
}

void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void USkillComponent::CastSkill(int32 InSkillId)
{
	ASwordRetaliateCharacter* Character = Cast<ASwordRetaliateCharacter>(GetOwner());
	if (Character == nullptr)
	{
		return;
	}

	USkillBase* CastSkill = nullptr;
	for (USkillBase* Skill : Skills)
	{
		if (Skill->SkillId == InSkillId)
		{
			CastSkill = Skill;
			break;
		}
	}

	if (CastSkill && CastSkill->CanCastSkill())
	{
		CastSkill->OnActiveSkill(Character);
	}
}


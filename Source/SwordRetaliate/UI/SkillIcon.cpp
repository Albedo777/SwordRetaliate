#include "SkillIcon.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "SwordRetaliate/SwordRetaliateUtils.h"
#include "SwordRetaliate/SkillSystem/SkillComponent.h"

void USkillIcon::NativeConstruct()
{
	Super::NativeConstruct();
	
	BindSkill = USwordRetaliateUtils::GetSkillConfig(this, SkillId);
	SkillButton->OnClicked.AddUniqueDynamic(this, &USkillIcon::OnCastSkill);
	Material = CoolDownImage->GetDynamicMaterial();
}

void USkillIcon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (bIsInCoolDown)
	{
		AccumulatedTime += InDeltaTime;
		
		if (Material && BindSkill)
		{
			const float Step = AccumulatedTime / BindSkill->SkillCoolDownTime;
			Material->SetScalarParameterValue(TEXT("Step"), Step);
			if (Step >= 1.f)
			{
				bIsInCoolDown = false;
				AccumulatedTime = 0.f;
				SkillButton->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}

	if (BindSkill == nullptr)
	{
		BindSkill = USwordRetaliateUtils::GetSkillConfig(this, SkillId);
	}
}

void USkillIcon::NativeDestruct()
{
	SkillButton->OnClicked.RemoveAll(this);
	
	Super::NativeDestruct();
}

void USkillIcon::OnCastSkill()
{
	const ASwordRetaliateCharacter* LocalPawn = USwordRetaliateUtils::GetSwordRetaliateCharacter(this);
	if (LocalPawn->SkillComponent->CastSkill(SkillId))
	{
		AccumulatedTime = 0.f;
		bIsInCoolDown = true;
		SkillButton->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		bIsInCoolDown = false;
	}
}

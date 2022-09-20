#include "UIController.h"

#include "Components/Button.h"
#include "SwordRetaliate/SwordRetaliateUtils.h"
#include "SwordRetaliate/SkillSystem/SkillComponent.h"

void UUIController::NativeConstruct()
{
	Super::NativeConstruct();

	FirstSkillButton->OnClicked.AddUniqueDynamic(this, &UUIController::CastFirstSkill);
	SecondSkillButton->OnClicked.AddUniqueDynamic(this, &UUIController::CastSecondSkill);
	JumpButton->OnClicked.AddUniqueDynamic(this, &UUIController::OnClickJump);
}

void UUIController::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUIController::NativeDestruct()
{
	FirstSkillButton->OnClicked.RemoveAll(this);
	SecondSkillButton->OnClicked.RemoveAll(this);
	JumpButton->OnClicked.RemoveAll(this);
	
	Super::NativeDestruct();
}

void UUIController::CastFirstSkill()
{
	const ASwordRetaliateCharacter* LocalPawn = USwordRetaliateUtils::GetSwordRetaliateCharacter(this);
	LocalPawn->SkillComponent->CastSkill(FirstSkillId);
}

void UUIController::CastSecondSkill()
{
	const ASwordRetaliateCharacter* LocalPawn = USwordRetaliateUtils::GetSwordRetaliateCharacter(this);
	LocalPawn->SkillComponent->CastSkill(SecondSkillId);
}

void UUIController::OnClickJump()
{
	ASwordRetaliateCharacter* LocalPawn = USwordRetaliateUtils::GetSwordRetaliateCharacter(this);
	LocalPawn->Jump();
}

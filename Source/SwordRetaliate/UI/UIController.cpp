#include "UIController.h"

#include "Components/Button.h"
#include "SwordRetaliate/SwordRetaliateUtils.h"
#include "SwordRetaliate/SkillSystem/SkillComponent.h"

void UUIController::NativeConstruct()
{
	Super::NativeConstruct();
	
	JumpButton->OnClicked.AddUniqueDynamic(this, &UUIController::OnClickJump);
}

void UUIController::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUIController::NativeDestruct()
{
	JumpButton->OnClicked.RemoveAll(this);
	
	Super::NativeDestruct();
}

void UUIController::OnClickJump()
{
	ASwordRetaliateCharacter* LocalPawn = USwordRetaliateUtils::GetSwordRetaliateCharacter(this);
	LocalPawn->Jump();
}

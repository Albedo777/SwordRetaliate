#include "HeadUI.h"

#include "SwordRetaliate/SwordRetaliateUtils.h"

void UHeadUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHeadUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (LocalPawn == nullptr)
	{
		LocalPawn = USwordRetaliateUtils::GetSwordRetaliateCharacter(this);
	}
	else
	{
		const float Percent = LocalPawn->Health / LocalPawn->MaxHealth;
		BloodProgressBar->SetPercent(Percent);
	}
}

void UHeadUI::NativeDestruct()
{
	Super::NativeDestruct();
}

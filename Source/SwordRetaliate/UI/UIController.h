#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIController.generated.h"

class UButton;

UCLASS()
class SWORDRETALIATE_API UUIController : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* JumpButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* FirstSkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FirstSkillId = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SecondSkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SecondSkillId = 2;
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeDestruct() override;

	UFUNCTION()
	void CastFirstSkill();

	UFUNCTION()
	void CastSecondSkill();

	UFUNCTION()
	void OnClickJump();
};

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
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnClickJump();
};

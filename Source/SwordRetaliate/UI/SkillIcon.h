#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwordRetaliate/SkillSystem/SkillBase.h"
#include "SkillIcon.generated.h"

class UImage;
class UButton;

UCLASS()
class SWORDRETALIATE_API USkillIcon : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* SkillButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CoolDownImage;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnCastSkill();
	
private:
	UPROPERTY(Transient)
	USkillBase* BindSkill;

	UPROPERTY(Transient)
	UMaterialInstanceDynamic* Material;
		
	float AccumulatedTime = 0.f;

	float bIsInCoolDown = false;
};

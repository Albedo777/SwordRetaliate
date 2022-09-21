#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SWORDRETALIATE_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USkillComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void CastSkill(int32 InSkillId);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<USkillBase>> SkillConfigs;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<USkillBase*> Skills;

protected:
	virtual void BeginPlay() override;
};

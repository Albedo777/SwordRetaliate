#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

UCLASS(BlueprintType)
class SWORDRETALIATE_API AEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AEffectActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void BP_OnActiveEffect(ACharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
	void BP_OnDeActiveEffect(ACharacter* Character);

protected:
	virtual void BeginPlay() override;
};

#pragma once

#include "CoreMinimal.h"
#include "EffectActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireBallEffectActor.generated.h"

UCLASS()
class SWORDRETALIATE_API AFireBallEffectActor : public AEffectActor
{
	GENERATED_BODY()

public:
	AFireBallEffectActor();

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* EmitterTemplate;
	
	UFUNCTION(BlueprintCallable)
	void AimTarget(FVector TargetPosition);
	
	UFUNCTION(BlueprintCallable)
	void OnHitTarget(FVector HitPosition);
	
protected:
	virtual void BeginPlay() override;
};

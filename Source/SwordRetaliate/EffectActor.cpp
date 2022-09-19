#include "EffectActor.h"

AEffectActor::AEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEffectActor::BP_OnActiveEffect_Implementation(ACharacter* Character)
{
	
}

void AEffectActor::BP_OnDeActiveEffect_Implementation(ACharacter* Character)
{
	
}
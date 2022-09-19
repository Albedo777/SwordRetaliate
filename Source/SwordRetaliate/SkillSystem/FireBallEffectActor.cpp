#include "FireBallEffectActor.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AFireBallEffectActor::AFireBallEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
}

void AFireBallEffectActor::AimTarget(const FVector TargetPosition)
{
	const ACharacter* LocalCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	const FVector2D LocalPos = FVector2D(LocalCharacter->GetActorLocation().X, LocalCharacter->GetActorLocation().Z);
	const FVector2D OtherPos = FVector2D(TargetPosition.X, TargetPosition.Z);
	FVector2D Dir = LocalPos - OtherPos;
	Dir.Normalize();
	const FVector2D FrontDir = FVector2D(1, 0);
	const float Degree = FMath::Acos(FrontDir.X * Dir.X + FrontDir.Y * Dir.Y);
	SetActorRotation(FRotator(Degree, 0, 0));
}

void AFireBallEffectActor::OnHitTarget(FVector HitPosition)
{
	ParticleSystemComponent->Deactivate();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this, HitPosition]
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, EmitterTemplate, HitPosition);
		Destroy();
	}), 0.5, false);
}

void AFireBallEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFireBallEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


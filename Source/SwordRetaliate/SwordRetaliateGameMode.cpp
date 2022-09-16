#include "SwordRetaliateGameMode.h"
#include "SwordRetaliateCharacter.h"
#include "Kismet/GameplayStatics.h"

ASwordRetaliateGameMode::ASwordRetaliateGameMode()
{
	DefaultPawnClass = ASwordRetaliateCharacter::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
}

void ASwordRetaliateGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(this, BackgroundTag, BackgroundSpriteActors);
}

void ASwordRetaliateGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (AActor* BackgroundSpriteActor : BackgroundSpriteActors)
	{
		const FVector CurrentLocation = BackgroundSpriteActor->GetActorLocation();
		if (CurrentLocation.X < LeftBound)
		{
			BackgroundSpriteActor->SetActorLocation(FVector(RightBound, CurrentLocation.Y, CurrentLocation.Z));
		}
		BackgroundSpriteActor->AddActorLocalOffset(FVector(LevelMoveSpeed * DeltaSeconds, 0.f, 0.f));
	}
}

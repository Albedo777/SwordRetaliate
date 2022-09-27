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
	
}

void ASwordRetaliateGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

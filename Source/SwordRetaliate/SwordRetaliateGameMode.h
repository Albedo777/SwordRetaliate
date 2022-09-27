#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SwordRetaliateGameMode.generated.h"

UCLASS(minimalapi)
class ASwordRetaliateGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASwordRetaliateGameMode();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
};

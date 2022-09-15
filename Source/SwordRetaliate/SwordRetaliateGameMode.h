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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BackgroundTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LeftBound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RightBound;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(Transient)
	TArray<AActor*> BackgroundSpriteActors;
};

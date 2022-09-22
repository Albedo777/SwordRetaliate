#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "Components/ActorComponent.h"
#include "PaperAnimationComponent.generated.h"

UENUM(BlueprintType)
enum class EFlipAnimationType : uint8
{
	Idle = 0,
	Run,
	Jump,
	Fall,
	Attack,
	AirTrans,
	Walk,
	Dash,
	Hit,
	Die,
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SWORDRETALIATE_API UPaperAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPaperAnimationComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	TMap<EFlipAnimationType, UPaperFlipbook*> FlipAnimationMap;
	
	void PlayFlipAnimation(EFlipAnimationType AnimationType);

	EFlipAnimationType GetCharacterCurrentAction() const;
	
	void SetIsRunning(bool bInIsRunning)
	{
		bIsRunning = bInIsRunning;
	}
	
	UFUNCTION()
	void OnJumpApexReached();

	UFUNCTION()
	void OnFlipbookPlaybackCompleted();
	
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	void HandleAnimation();
	
	float AnimationTimer;

	UPROPERTY(Transient)
	class APaperCharacter* PaperCharacter;

	bool bIsRunning = false;
};

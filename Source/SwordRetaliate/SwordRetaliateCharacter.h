#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SwordRetaliateCharacter.generated.h"

UENUM(BlueprintType)
enum class EFlipAnimationType : uint8
{
	Idle = 0,
	Run,
	Jump,
	Attack,
	Dash,
};

class UPaperFlipbook;
class UTextRenderComponent;

UCLASS(Config = Game, Blueprintable)
class ASwordRetaliateCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	ASwordRetaliateCharacter();
	
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkillComponent* SkillComponent;
	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void PlayFlipAnimation(EFlipAnimationType AnimationType);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	TMap<EFlipAnimationType, UPaperFlipbook*> FlipAnimationMap;
	
	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();
	
	/** Called for side to side input */
	void MoveRight(float Value);

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};

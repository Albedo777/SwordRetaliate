#pragma once

#include "CoreMinimal.h"
#include "PaperAnimationComponent.h"
#include "PaperCharacter.h"
#include "SwordRetaliateCharacter.generated.h"

class UPaperFlipbook;
class UTextRenderComponent;

UCLASS(Config = Game, Blueprintable)
class  ASwordRetaliateCharacter : public APaperCharacter
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperAnimationComponent* AnimationComponent;
	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void PlayFlipAnimation(EFlipAnimationType AnimationType);

	UFUNCTION(BlueprintCallable)
	void SetIsRunning(bool bIsRunning);
	
	UFUNCTION(BlueprintCallable)
	EFlipAnimationType GetCharacterCurrentAction() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsCharacterAttackAction() const;

	UFUNCTION(BlueprintCallable)
	void OnCharacterHit(float Damage);

	UFUNCTION(BlueprintCallable)
	void OnCharacterDie();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed = 1200.f;
	
protected:
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

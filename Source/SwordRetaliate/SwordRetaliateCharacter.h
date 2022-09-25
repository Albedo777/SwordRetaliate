#pragma once

#include "CoreMinimal.h"
#include "PaperAnimationComponent.h"
#include "PaperCharacter.h"
#include "Components/WidgetComponent.h"
#include "SwordRetaliateCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterTakeDamage);

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
	void Attack();

	UFUNCTION(BlueprintCallable)
	void Dash();
	
	UFUNCTION(BlueprintCallable)
	EFlipAnimationType GetCharacterCurrentAction() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsCharacterAttackAction() const;

	UFUNCTION(BlueprintCallable)
	bool IsCharacterDash() const;
	
	UFUNCTION(BlueprintCallable)
	void OnCharacterHit(float Damage);

	UFUNCTION(BlueprintCallable)
	void OnCharacterDie();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed = 1200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraVerticalOffset = 360.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraHorizontalOffset = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* Curve;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraRecoverSpeed = 4.f;
	
	FCharacterTakeDamage OnCharacterTakeDamage;
	
protected:
	virtual void BeginPlay() override;
	
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

private:
	float DashTimer = 0.f;
};

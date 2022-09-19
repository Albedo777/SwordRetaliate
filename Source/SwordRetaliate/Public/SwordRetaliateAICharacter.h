// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
//#include "PaperFlipbook.h"
#include "SwordRetaliateAICharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType, meta = (Bitflags)
enum class EAICharacterStatus : uint16
{				
	Run	= 0				UMETA(DisplayName = "��"),
	SlowRun				UMETA(DisplayName = "����"),
	FastRun				UMETA(DisplayName = "˲��"),
	StopRun				UMETA(DisplayName = "ѣ��"),
	BeHit				UMETA(DisplayName = "�ܻ�"),
	Jump				UMETA(DisplayName = "��Ծ"),
	Dead				UMETA(DisplayName = "����"),
	Skill				UMETA(DisplayName = "�ͷż���"),
	Hit					UMETA(DisplayName = "ײ"),
};

UCLASS()
class SWORDRETALIATE_API ASwordRetaliateAICharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//	class UPaperFlipbook* FastRunAnimation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//	class UPaperFlipbook* SlowRunAnimation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//	class UPaperFlipbook* JumpAnimation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//	class UPaperFlipbook* HitAnimation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	//	class UPaperFlipbook* VertigoAnimation;


private: 

	UP
	TEnumAsByte<EAICharacterStatus> AIStatus;

protected:
//
	virtual void Tick(float DeltaSeconds) override;
//
	void UpdateAnimation();
//
	void MoveRight(float Value);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* SkillAnimation;

public:

	ASwordRetaliateAICharacter();
	
	UFUNCTION(BlueprintCallable)
	const TEnumAsByte<EAICharacterStatus> GetAIStatus();

	UFUNCTION(BlueprintCallable)
	bool SetAIStatus(TEnumAsByte<EAICharacterStatus> NewAIStatus);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
};

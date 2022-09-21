// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
//#include "PaperFlipbook.h"
#include "SwordRetaliateAICharacter.generated.h"

/**
 * 
 */

#define TOFLAG(Enum) (1 << static_cast<uint8>(Enum))

UENUM(BlueprintType, meta = (Bitflags))
enum class EAICharacterStatus : uint8
{
	Run = 0				UMETA(DisplayName = "跑"),
	SlowRun				UMETA(DisplayName = "慢跑"),
	FastRun				UMETA(DisplayName = "瞬移"),
	StopRun				UMETA(DisplayName = "眩晕"),
	BeHit				UMETA(DisplayName = "受击"),
	Jump				UMETA(DisplayName = "跳跃"),
	Dead				UMETA(DisplayName = "死亡"),
	Skill				UMETA(DisplayName = "释放技能"),
	Hit					UMETA(DisplayName = "撞"),
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


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EAICharacterStatus"))
		int32 AIStatus;

protected:
//
	virtual void Tick(float DeltaSeconds) override;
//
	void UpdateAnimation();
//
	void MoveRight();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* RunAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UPaperFlipbook* SkillAnimation;



public:

	ASwordRetaliateAICharacter();
	
	UFUNCTION(BlueprintCallable)
		bool AIStatusHasTag(EAICharacterStatus AITag);

	UFUNCTION(BlueprintCallable)
		bool AIStatusAddTag(EAICharacterStatus AITag);

	UFUNCTION(BlueprintCallable)
		bool AIStatusRemoveTag(EAICharacterStatus AITag);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Skill)
		class USkillComponent* SkillComponent;

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
};

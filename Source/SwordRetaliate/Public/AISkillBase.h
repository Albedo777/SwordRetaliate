// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AISkillComponent.h"
//#include "AISkillBase.h"
//#include "SwordRetaliateAICharacter.h"
#include "AISkillBase.generated.h"

//UENUM(BlueprintType)
//enum class EAISkill : uint8
//{
//	Hit = 0			UMETA(DisplayName = "×²»÷"),
//	Fire			UMETA(DisplayName = "»ðÇò"),
//	Bellow			UMETA(DisplayName = "Å­ºð"),
//	Claw			UMETA(DisplayName = "×¦»÷"),
//	Plunge			UMETA(DisplayName = "ÃÍÆË"),
//};

class ASwordRetaliateAICharacter;

UCLASS()
class SWORDRETALIATE_API AAISkillBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAISkill SkillID;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: 
	UFUNCTION(BlueprintNativeEvent)
		void EnableSkill(ASwordRetaliateAICharacter* Character);

	UFUNCTION(BlueprintNativeEvent)
		void DisableSkill(ASwordRetaliateAICharacter* Character);

};

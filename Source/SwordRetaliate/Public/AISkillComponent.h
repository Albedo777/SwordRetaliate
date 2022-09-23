// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "AISkillBase.h"
#include "AISkillComponent.generated.h"

UENUM(BlueprintType)
enum class EAISkill : uint8
{
	Hit = 0			UMETA(DisplayName = "撞击"),
	Fire			UMETA(DisplayName = "火球"),
	Bellow			UMETA(DisplayName = "怒吼"),
	Claw			UMETA(DisplayName = "爪击"),
	Plunge			UMETA(DisplayName = "猛扑"),
};

class AAISkillBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDRETALIATE_API UAISkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAISkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<EAISkill, TSubclassOf<AAISkillBase>> Skills;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		TSubclassOf<AAISkillBase> FindSkillBySkillID(EAISkill AISkillID);
		
};

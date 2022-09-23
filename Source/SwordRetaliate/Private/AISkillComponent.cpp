// Fill out your copyright notice in the Description page of Project Settings.


#include "AISkillComponent.h"

// Sets default values for this component's properties
UAISkillComponent::UAISkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAISkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAISkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSubclassOf<AAISkillBase> UAISkillComponent::FindSkillBySkillID(EAISkill AISkillID)
{
	TSubclassOf<AAISkillBase> SkillClass = *(Skills.Find(AISkillID));
	return SkillClass;
}


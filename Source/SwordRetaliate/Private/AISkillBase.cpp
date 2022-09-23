// Fill out your copyright notice in the Description page of Project Settings.

#include "AISkillBase.h"
#include "SwordRetaliateAICharacter.h"

// Sets default values
AAISkillBase::AAISkillBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAISkillBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAISkillBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAISkillBase::EnableSkill_Implementation(ASwordRetaliateAICharacter* Character)
{

}

void AAISkillBase::DisableSkill_Implementation(ASwordRetaliateAICharacter* Character)
{

}


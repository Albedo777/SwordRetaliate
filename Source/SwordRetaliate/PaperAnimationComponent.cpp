﻿#include "PaperAnimationComponent.h"

#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UPaperAnimationComponent::UPaperAnimationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UPaperAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	PaperCharacter = Cast<APaperCharacter>(GetOwner());

	PaperCharacter->OnReachedJumpApex.AddUniqueDynamic(this, &UPaperAnimationComponent::OnJumpApexReached);
	PaperCharacter->GetSprite()->OnFinishedPlaying.AddUniqueDynamic(this, &UPaperAnimationComponent::OnFlipbookPlaybackCompleted);
}

void UPaperAnimationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	PaperCharacter->OnReachedJumpApex.RemoveAll(this);
	PaperCharacter->GetSprite()->OnFinishedPlaying.RemoveAll(this);
	
	Super::EndPlay(EndPlayReason);
}

void UPaperAnimationComponent::HandleAnimation()
{
	const UCharacterMovementComponent* MovementComponent = PaperCharacter->GetCharacterMovement();
	if (MovementComponent->IsWalking())
	{
		if (GetCharacterCurrentAction() == EFlipAnimationType::Attack ||
			GetCharacterCurrentAction() == EFlipAnimationType::Dash )
		{
			PaperCharacter->GetSprite()->SetLooping(false);
		}
		else
		{
			PaperCharacter->GetSprite()->SetLooping(true);
			const FVector PlayerVelocity = PaperCharacter->GetVelocity();
			const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();
			PlayFlipAnimation(PlayerSpeedSqr > 0.0f ? (bIsRunning ? EFlipAnimationType::Run : EFlipAnimationType::Walk) : EFlipAnimationType::Idle);
			PaperCharacter->GetSprite()->SetLooping(true);
		}
	}
	else if (MovementComponent->IsFalling())
	{
		PaperCharacter->GetSprite()->SetLooping(false);
	}
}

void UPaperAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HandleAnimation();
}

void UPaperAnimationComponent::PlayFlipAnimation(EFlipAnimationType AnimationType)
{
	if (FlipAnimationMap.Contains(AnimationType))
	{
		UPaperFlipbook* DesiredAnimation = FlipAnimationMap[AnimationType];
		
		if (PaperCharacter->GetSprite()->GetFlipbook() != DesiredAnimation)
		{
			PaperCharacter->GetSprite()->SetFlipbook(DesiredAnimation);
			PaperCharacter->GetSprite()->PlayFromStart();
		}
	}
}

EFlipAnimationType UPaperAnimationComponent::GetCharacterCurrentAction() const
{
	const UPaperFlipbook* CurrentAnimation = PaperCharacter->GetSprite()->GetFlipbook();
	TArray<EFlipAnimationType> OutKeys;
	FlipAnimationMap.GetKeys(OutKeys);

	for (const EFlipAnimationType Type : OutKeys)
	{
		if (FlipAnimationMap[Type] == CurrentAnimation)
		{
			return Type;
		}
	}
	return EFlipAnimationType::Idle;
}

void UPaperAnimationComponent::OnJumpApexReached()
{
	PlayFlipAnimation(EFlipAnimationType::AirTrans);
}

void UPaperAnimationComponent::OnFlipbookPlaybackCompleted()
{
	if (GetCharacterCurrentAction() == EFlipAnimationType::AirTrans)
	{
		PlayFlipAnimation(EFlipAnimationType::Fall);
	}
	if (GetCharacterCurrentAction() == EFlipAnimationType::Attack)
	{
		PlayFlipAnimation(EFlipAnimationType::Idle);
	}
	if (GetCharacterCurrentAction() == EFlipAnimationType::Dash)
	{
		PlayFlipAnimation(EFlipAnimationType::Idle);
	}
}


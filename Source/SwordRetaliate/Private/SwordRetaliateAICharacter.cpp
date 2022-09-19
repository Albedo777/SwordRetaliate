// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordRetaliateAICharacter.h"
#include "PaperFlipbookComponent.h"
//#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
//#include "Components/InputComponent.h"
//#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
//#include "Camera/CameraComponent.h"

ASwordRetaliateAICharacter::ASwordRetaliateAICharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	//// Create a camera boom attached to the root (capsule)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 500.0f;
	//CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	//CameraBoom->SetUsingAbsoluteRotation(true);
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	//// Create an orthographic camera (no perspective) and attach it to the boom
	//SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	//SideViewCameraComponent->OrthoWidth = 2048.0f;
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	//CameraBoom->SetUsingAbsoluteRotation(true);
	//SideViewCameraComponent->bUsePawnControlRotation = false;
	//SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
	// 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	// 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
	// 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	// 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(false);
	bReplicates = false;

	// TODO: Here

	AIStatus = EAICharacterStatus::Run;
}

bool ASwordRetaliateAICharacter::SetAIStatus(TEnumAsByte<EAICharacterStatus> NewAIStatus)
{
	return false;
}

const TEnumAsByte<EAICharacterStatus> ASwordRetaliateAICharacter::GetAIStatus()
{
	return AIStatus;
}

void ASwordRetaliateAICharacter::UpdateAnimation()
{
	// Are we moving or skilling?
	UPaperFlipbook* DesiredAnimation = RunAnimation;

	// TODO: change Animation every tick
	GetSprite()->SetFlipbook(DesiredAnimation);

}

void ASwordRetaliateAICharacter::MoveRight(float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ASwordRetaliateAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateAnimation();

	MoveRight(1.0);
}


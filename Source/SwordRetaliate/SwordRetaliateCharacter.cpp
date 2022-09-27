#include "SwordRetaliateCharacter.h"

#include "PaperAnimationComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "SkillSystem/SkillComponent.h"

ASwordRetaliateCharacter::ASwordRetaliateCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	
	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 1600;
	SideViewCameraComponent->SetupAttachment(RootComponent, USpringArmComponent::SocketName);
	SideViewCameraComponent->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->SetUsingAbsoluteLocation(true);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	SideViewCameraComponent->SetWorldLocation(FVector(0.f, 1000.f,  CameraHorizontalOffset));
	SideViewCameraComponent->SetWorldRotation(FRotator(0.f, 0.f, -90.f));
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 6.0f;
	GetCharacterMovement()->AirControl = 1.f;
	GetCharacterMovement()->JumpZVelocity = 2000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->MaxFlySpeed = RunSpeed;
	JumpMaxCount = 2;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	// Skill system
	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));

	// Animation system
	AnimationComponent = CreateDefaultSubobject<UPaperAnimationComponent>(TEXT("AnimationComponent"));
}

void ASwordRetaliateCharacter::PlayFlipAnimation(EFlipAnimationType AnimationType)
{
	AnimationComponent->PlayFlipAnimation(AnimationType);
}

void ASwordRetaliateCharacter::SetIsRunning(bool bIsRunning)
{
	AnimationComponent->SetIsRunning(bIsRunning);
	
	if (bIsRunning)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed * DashRate;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed * DashRate;
	}
}

void ASwordRetaliateCharacter::Attack()
{
	if (!IsCharacterAttackAction())
	{
		PlayFlipAnimation(EFlipAnimationType::Attack);
	}
}

void ASwordRetaliateCharacter::Dash()
{
	if (!IsCharacterDash())
	{
		PlayFlipAnimation(EFlipAnimationType::Dash);
	}
}

EFlipAnimationType ASwordRetaliateCharacter::GetCharacterCurrentAction() const
{
	return AnimationComponent->GetCharacterCurrentAction();
}

bool ASwordRetaliateCharacter::IsCharacterAttackAction() const
{
	return GetCharacterCurrentAction() == EFlipAnimationType::Attack;
}

bool ASwordRetaliateCharacter::IsCharacterDash() const
{
	return GetCharacterCurrentAction() == EFlipAnimationType::Dash;
}

void ASwordRetaliateCharacter::OnCharacterHit(float Damage)
{
	PlayFlipAnimation(EFlipAnimationType::Hit);
	Health -= Damage;

	if (OnCharacterTakeDamage.IsBound())
	{
		OnCharacterTakeDamage.Broadcast();
	}
	
	if (Health <= 0.f)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]()
		{
			OnCharacterDie();
		}), 0.5f, false);
	}
}

void ASwordRetaliateCharacter::OnCharacterDie()
{
	
}

void ASwordRetaliateCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (IsCharacterDash())
	{
		DashTimer += DeltaSeconds;
		DashRate = Curve->GetFloatValue(DashTimer);
	}
	else
	{
		DashTimer = 0.f;
		DashRate = 1.f;
	}

	// Move camera
	float MoveOffset;
	const float Offset = SideViewCameraComponent->GetComponentLocation().X - GetActorLocation().X ;
	UE_LOG(LogTemp, Log, TEXT("Offset %f"), SideViewCameraComponent->GetComponentLocation().X - GetActorLocation().X)
	const float MoveSpeed = FMath::Min(FMath::Abs(FMath::Abs(Offset) - CameraHorizontalOffset), CameraRecoverSpeed);
	if (FMath::IsNearlyZero(Offset))
	{
		MoveOffset = 0.f;
	}
	else if (Offset <= CameraHorizontalOffset)
	{
		MoveOffset = MoveSpeed;
	}
	else
	{
		MoveOffset = -MoveSpeed;
	}
	SideViewCameraComponent->AddWorldOffset(FVector(RunSpeed * DeltaSeconds + MoveOffset, 0.f, 0.f));
	
	UpdateCharacter();
}

void ASwordRetaliateCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASwordRetaliateCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ASwordRetaliateCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ASwordRetaliateCharacter::TouchStopped);
}

void ASwordRetaliateCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void ASwordRetaliateCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Jump on any touch
	Jump();
}

void ASwordRetaliateCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// Cease jumping once touch stopped
	StopJumping();
}

void ASwordRetaliateCharacter::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	// Current frame
	UPaperFlipbook* CurrentFlipbook = GetSprite()->GetFlipbook();
	FSpriteFrameData CurrentData(CurrentFlipbook, GetSprite()->GetPlaybackPosition());

	auto SetAfterImageSprite = [this](int Index, UPaperFlipbookComponent* AfterImageSprite)
	{
		if (IsCharacterDash())
		{
			if (FrameDataList.IsValidIndex(Index) && AfterImageSprite)
			{
				AfterImageSprite->SetVisibility(true);
				AfterImageSprite->SetFlipbook(FrameDataList[Index].CachePaperFlipbook);
				AfterImageSprite->Play();
				AfterImageSprite->SetPlaybackPosition(FrameDataList[Index].PlaybackTime, true);
				AfterImageSprite->SetLooping(false);
			}
		}
		else
		{
			AfterImageSprite->SetVisibility(false, false);
		}
	};
	// Set 1 frame
	SetAfterImageSprite(1, AfterImage1Sprite);
	// Set 2 frame
	SetAfterImageSprite(0, AfterImage2Sprite);
	// The frame which needs to be drop
	FrameDataList.Add(CurrentData);
	if (FrameDataList.Num() > 2)
	{
		FSpriteFrameData DropData = FrameDataList[0];
		FrameDataList.RemoveAt(0);
	}
}

void ASwordRetaliateCharacter::BeginPlay()
{
	Super::BeginPlay();

	const FVector CameraLocation = SideViewCameraComponent->GetComponentLocation();
	SideViewCameraComponent->SetWorldLocation(FVector(GetActorLocation().X + CameraHorizontalOffset, CameraLocation.Y, CameraVerticalOffset));

	for (UActorComponent* Component : GetComponents())
	{
		if (Component->GetName().Contains("AfterImage1"))
		{
			AfterImage1Sprite = Cast<UPaperFlipbookComponent>(Component);
		}
		else if (Component->GetName().Contains("AfterImage2"))
		{
			AfterImage2Sprite = Cast<UPaperFlipbookComponent>(Component);
		}
	}
}

void ASwordRetaliateCharacter::UpdateCharacter()
{
	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

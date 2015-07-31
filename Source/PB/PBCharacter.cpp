// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "PB.h"
#include "Movement/MovementState.h"
#include "Movement/Walking.h"
#include "Movement/Idle.h"
#include "PBCharacter.h"

APBCharacter::APBCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->RelativeRotation = FRotator(0.f,180.f,0.f);

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
    
    JumpMaxHoldTime = 10.0f;
    jumpCounter = 0;
    jumpCountTop = 3;
    dashTiming = 0;
    eCurrentState = APBCharacter::eMovementState::idle;
    currentState  = new Idle(this);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void APBCharacter::Jump()
{
    if(jumpCounter < jumpCountTop)
    {
        jumpCounter++;
        
        bPressedJump = true;
        JumpKeyHoldTime = 0.0f;
        JumpMaxHoldTime = 0.01f;
    }
    
}
void APBCharacter::Tick(float deltaTime)
{
    if(currentState)
    {
        currentState->Tick(deltaTime);
    }
    
    if(isDashing && dashTiming < 0.2f)
    {
        GetCharacterMovement()->MaxWalkSpeed = 100000.0f;
        GetCharacterMovement()->AddImpulse(GetActorForwardVector() * 10 * 100000);
        dashTiming+=deltaTime;
        UE_LOG(LogTemp, Warning, TEXT("Your message"), dashTiming);
        isDashing = false;
    }
    else
    {
        isDashing = false;
     //   dashTiming = 0.0f;
    }
}


void APBCharacter::StopJumping()
{
    bPressedJump = false;
    JumpKeyHoldTime = 0.0f;
}
void APBCharacter::Landed(const FHitResult &Hit)
{
    jumpCounter = 0;
    OnLanded(Hit);
}


bool APBCharacter::CanJumpInternal_Implementation() const
{
    const bool bCanHoldToJumpHigher = (GetJumpMaxHoldTime() > 0.0f) && IsJumpProvidingForce();
    return !bIsCrouched && CharacterMovement && (CharacterMovement->IsMovingOnGround() || jumpCounter < jumpCountTop || bCanHoldToJumpHigher) && CharacterMovement->IsJumpAllowed() && !CharacterMovement->bWantsToCrouch;
}

void APBCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &APBCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &APBCharacter::StopJumping);
	InputComponent->BindAxis("MoveRight", this, &APBCharacter::MoveRight);
    InputComponent->BindAction("Dash", IE_Pressed,this, &APBCharacter::Dash);
    InputComponent->BindAction("Dash", IE_Released, this, &APBCharacter::StopDashing);
	InputComponent->BindTouch(IE_Pressed, this, &APBCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &APBCharacter::TouchStopped);
}

void APBCharacter::Dash()
{
    isDashing = true;
}
void APBCharacter::StopDashing()
{
    dashTiming = 0.0f;
    isDashing = false;
}
void APBCharacter::MoveRight(float Value)
{
    if(Value == 0 && eCurrentState == walking)
    {
        Idle* newState = new Idle(this);
        delete currentState;
        currentState = newState;
        eCurrentState = idle;
    }
    else if(eCurrentState == idle && Value != 0)
    {
        Walking* newState = new Walking(this);
        newState->SetDirection(Value);
        delete currentState;
        currentState = newState;
        eCurrentState = walking;
    }
    else if(eCurrentState == walking && Value != 0)
    {
        static_cast<Walking*>(currentState)->SetDirection(Value);
    }
}

void APBCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void APBCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}


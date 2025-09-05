// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Controller/PlayerCharacterController.h"
#include "Character/Player/PlayerCharacter.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* const SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultContext)
		{
			SubSystem->AddMappingContext(DefaultContext, 0);
		}
	}
	OwnerCharacter = Cast<APlayerCharacter>(GetPawn());
}

void APlayerCharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* const EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &APlayerCharacterController::StartAim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &APlayerCharacterController::EndAim);
		EnhancedInputComponent->BindAction(BasicAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::BasicAttack);
	}
}

void APlayerCharacterController::Move(const FInputActionInstance& Action)
{
	const FVector2D InputDirection = Action.GetValue().Get<FVector2D>();

	const FRotator YawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	const FVector ForwadDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	GetPawn()->AddMovementInput(ForwadDirection, InputDirection.Y);
	GetPawn()->AddMovementInput(RightDirection, InputDirection.X);
}

void APlayerCharacterController::Look(const FInputActionInstance& Action)
{
	const FVector2D LookDirection = Action.GetValue().Get<FVector2D>();
	AddYawInput(LookDirection.X * LookingRotationValue * GetWorld()->GetDeltaSeconds());
	AddPitchInput(LookDirection.Y * -LookingRotationValue * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacterController::StartAim(const FInputActionInstance& Action)
{
	if (OwnerCharacter)
	{
		bIsAim = true;
		OwnerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		GetWorld()->GetTimerManager().ClearTimer(AimTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AimTimerHandle, this, &APlayerCharacterController::UpdateAimState, TimerInterupt, true);
	}
}

void APlayerCharacterController::UpdateAimState()
{
	if (bIsAim)
	{
		ZoomFactor += TimerInterupt / 0.2f;
	}
	else
	{
		ZoomFactor -= TimerInterupt / 0.2f;
	}

	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
	OwnerCharacter->GetFollowCamera()->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	OwnerCharacter->GetCameraBoom()->TargetArmLength = FMath::Lerp<float>(200.0f, 100.0f, ZoomFactor);

	if (ZoomFactor >= 1.0f || ZoomFactor <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(AimTimerHandle);
	}
}

void APlayerCharacterController::EndAim(const FInputActionInstance& Action)
{
	if (OwnerCharacter)
	{
		bIsAim = false;
		OwnerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		GetWorld()->GetTimerManager().ClearTimer(AimTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AimTimerHandle, this, &APlayerCharacterController::UpdateAimState, 0.01f, true);
	}
}

void APlayerCharacterController::BasicAttack()
{

}

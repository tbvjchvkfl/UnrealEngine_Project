// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Anim/PlayerCharacterAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"
#include "Controller/PlayerCharacterController.h"

// Engine
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterTrajectoryComponent.h"
#include "PoseSearch/PoseSearchTrajectoryLibrary.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	CurrentState = EPlayerState::IDLE;
}

void UPlayerCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	OwnerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	OwnerCharacterMovement = OwnerCharacter->GetCharacterMovement();
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// State value Setting
	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	}
	if (!OwnerController)
	{
		OwnerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	}
	if (!OwnerCharacterMovement && OwnerCharacter)
	{
		OwnerCharacterMovement = OwnerCharacter->GetCharacterMovement();
	}
	if (OwnerCharacter && OwnerController && OwnerCharacterMovement)
	{
		bIsAim = OwnerController->bIsAim;
		bIsSwitchMovementState = OwnerController->bIsSwitchMovementState;
		bIsInAir = OwnerCharacter->GetCharacterMovement()->IsFalling();
		bIsAcceleration = OwnerCharacterMovement->GetCurrentAcceleration().Size() > 0.0f;
		//bIsAcceleration = (OwnerCharacterMovement->GetCurrentAcceleration().Size() / OwnerCharacterMovement->GetMaxAcceleration()) > 0.0f;
		CurrentVelocity = OwnerCharacterMovement->Velocity;
		Speed = CurrentVelocity.Size2D();

		SetCurrentState();
	}
}

void UPlayerCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	// IK, AimOffset
	if (OwnerCharacter)
	{
		FPoseSearchTrajectoryData TrajectoryData;
		TrajectoryData.RotateTowardsMovementSpeed = 0.0f;
		TrajectoryData.MaxControllerYawRate = 0.0f;
		UPoseSearchTrajectoryLibrary::PoseSearchGenerateTrajectory(this, TrajectoryData, DeltaSeconds, CurrentTrajectory, DesiredYawLastUpdate, CurrentTrajectory, -1.0f, 30, 0.1f, 15);
	}
}

void UPlayerCharacterAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();

	// Final Result, 본 위치 보정 및 최종 확인 
}

void UPlayerCharacterAnimInstance::SetCurrentState()
{
	EPlayerState ReturnState = EPlayerState::IDLE;
	if (bIsAcceleration)
	{
		if (bIsSwitchMovementState)
		{
			ReturnState = EPlayerState::RUN;
		}
		else
		{
			ReturnState = EPlayerState::WALK;
		}
	}
	CurrentState = ReturnState;
}
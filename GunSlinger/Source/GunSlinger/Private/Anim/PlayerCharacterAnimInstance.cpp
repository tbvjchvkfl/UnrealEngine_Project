// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Anim/PlayerCharacterAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"
#include "Controller/PlayerCharacterController.h"

// Engine
#include "CharacterTrajectoryComponent.h"
#include "PoseSearch/PoseSearchTrajectoryLibrary.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	OwnerController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
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
	if (OwnerCharacter && OwnerController)
	{
		bIsAim = OwnerController->bIsAim;
		Acceleration = OwnerCharacter->GetVelocity().Size();
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

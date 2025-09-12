// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Anim/PlayerCharacterAnimInstance.h"
#include "Character/Player/PlayerCharacter.h"
#include "Controller/PlayerCharacterController.h"

// Engine
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PoseSearch/PoseSearchTrajectoryLibrary.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"


UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
	CurrentState = EPlayerState::IDLE;
	StateDataBaseTagsArray.Empty();

	// Init Foot Placement Setting
	InitializeFootPlacement();
}

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
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

		bIsStartMovement = (TrajectoryFutureVelocity.Size() >= CurrentVelocity.Size() + 100.0f) && !StateDataBaseTagsArray.Contains("Run Pivot");
		bIsPivot = FMath::Abs(UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::MakeRotFromX(TrajectoryFutureVelocity), UKismetMathLibrary::MakeRotFromX(CurrentVelocity)).Yaw) > 30.0f;
		LastNonZeroVelocity = Speed > 5.0f ? CurrentVelocity : LastNonZeroVelocity;

		SetCurrentState();
	}
}

void UPlayerCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	// IK, AimOffset
	if (OwnerCharacter)
	{
		// 모션 매칭을 위한 궤적 계산 및 생성
		FPoseSearchTrajectoryData TrajectoryData;
		TrajectoryData.RotateTowardsMovementSpeed = 0.0f;
		TrajectoryData.MaxControllerYawRate = 0.0f;
		UPoseSearchTrajectoryLibrary::PoseSearchGenerateTrajectory(this, TrajectoryData, DeltaSeconds, CurrentTrajectory, DesiredYawLastUpdate, CurrentTrajectory, -1.0f, 30, 0.1f, 15);

		// RunStart에서 RunLoop로 넘어가기 위한 전환 조건
		UPoseSearchTrajectoryLibrary::GetTrajectoryVelocity(CurrentTrajectory, 0.4f, 0.5f, TrajectoryFutureVelocity, false);
	}
}

void UPlayerCharacterAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();

	// Final Result, 본 위치 보정 및 최종 확인 
}

void UPlayerCharacterAnimInstance::InitializeFootPlacement()
{
	PlantSettingsMoving.SpeedThreshold = 60.0f;
	PlantSettingsMoving.UnplantRadius = 20.0f;
	PlantSettingsMoving.UnplantAngle = 60.0f;
	PlantSettingsMoving.ReplantRadiusRatio = 0.2f;

	PlantSettingsStop.SpeedThreshold = 20.0f;
	PlantSettingsStop.UnplantRadius = 40.0f;
	PlantSettingsStop.UnplantAngle = 60.0f;
	PlantSettingsStop.ReplantRadiusRatio = 0.75f;

	InterpolationSettingsMoving.UnplantLinearStiffness = 10.0f;
}

FFootPlacementPlantSettings UPlayerCharacterAnimInstance::GetPlantSetting() const
{
	if(CurrentState == EPlayerState::IDLE)
	{
		return PlantSettingsStop;
	}
	return PlantSettingsMoving;
}

FFootPlacementInterpolationSettings UPlayerCharacterAnimInstance::GetInterpolationSetting() const
{
	if (CurrentState == EPlayerState::IDLE)
	{
		return InterpolationSettingsStop;
	}
	return InterpolationSettingsMoving;
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"
#include "PlayerCharacterAnimInstance.generated.h"

struct FPoseSearchQueryTrajectory;
class APlayerCharacter;
class APlayerCharacterController;
class UCharacterMovementComponent;

UENUM()
enum class EPlayerState : uint8
{
	IDLE UMETA(Displayname = "Idle"),
	WALK UMETA(Displayname = "Walk"),
	RUN UMETA(Displayname = "Run"),
};

UCLASS()
class GUNSLINGER_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	

	//==============================================================
	//=                          Function                          =
	//==============================================================
	EPlayerState GetCurrentState() const { return CurrentState; }

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | EssentialData", meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | EssentialData", meta = (AllowPrivateAccess = "true"))
	APlayerCharacterController* OwnerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | EssentialData", meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* OwnerCharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	EPlayerState CurrentState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	bool bIsAim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	bool bIsSwitchMovementState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	bool bIsAcceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	bool bIsStartMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	bool bIsPivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	FVector CurrentVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | Tajectory", meta = (AllowPrivateAccess = "true"))
	float DesiredYawLastUpdate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | Tajectory", meta = (AllowPrivateAccess = "true"))
	FVector TrajectoryFutureVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | Tajectory", meta = (AllowPrivateAccess = "true"))
	FPoseSearchQueryTrajectory CurrentTrajectory;
	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;

	void SetCurrentState();
};

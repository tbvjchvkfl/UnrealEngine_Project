// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h"
#include "PlayerCharacterAnimInstance.generated.h"

struct FPoseSearchQueryTrajectory;
class APlayerCharacter;
class APlayerCharacterController;

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

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | EssentialData", meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | EssentialData", meta = (AllowPrivateAccess = "true"))
	APlayerCharacterController* OwnerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	bool bIsAim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | State", meta = (AllowPrivateAccess = "true"))
	float Acceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Property | Tajectory", meta = (AllowPrivateAccess = "true"))
	float DesiredYawLastUpdate;

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
};

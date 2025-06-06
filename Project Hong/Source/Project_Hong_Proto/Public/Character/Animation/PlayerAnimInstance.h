// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


UCLASS()
class PROJECT_HONG_PROTO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================



private:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};

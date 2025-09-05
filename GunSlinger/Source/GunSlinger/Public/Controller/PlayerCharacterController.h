// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

struct FInputActionInstance;
struct FinputActionValue;
class UInputMappingContext;
class UInputAction;
class APlayerCharacter;

UCLASS()
class GUNSLINGER_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(VisibleAnywhere, Category = "Property | State")
	bool bIsAim = false;

	UPROPERTY(EditAnywhere, Category = "Property | Value")
	float LookingRotationValue = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Property | Essential Data")
	APlayerCharacter* OwnerCharacter;

	UPROPERTY()
	FTimerHandle AimTimerHandle;
	//==============================================================
	//=                          Function                          =
	//==============================================================
	APlayerCharacterController();

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Property | ETC", meta = (AllowPrivateAccess = "true"))
	float ZoomFactor = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Property | ETC", meta = (AllowPrivateAccess = "true"))
	float TimerInterupt = 0.01f;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* BasicAttackAction;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent()override;

	void Move(const FInputActionInstance& Action);
	void Look(const FInputActionInstance& Action);
	void StartAim(const FInputActionInstance& Action);
	void UpdateAimState();
	void EndAim(const FInputActionInstance& Action);
	void BasicAttack();
};

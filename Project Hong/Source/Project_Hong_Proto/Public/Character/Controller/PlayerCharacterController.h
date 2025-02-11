// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HONG_PROTO_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================
	APlayerCharacterController();

private:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECT_HONG_PROTO_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================
	APlayerCharacter();

protected:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

private:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================

};

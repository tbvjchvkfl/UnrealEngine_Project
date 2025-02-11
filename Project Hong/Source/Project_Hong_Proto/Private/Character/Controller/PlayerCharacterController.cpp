// Fill out your copyright notice in the Description page of Project Settings.


// GameFramwork
#include "Character/Controller/PlayerCharacterController.h"


// Engine

APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

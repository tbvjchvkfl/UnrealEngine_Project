// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PHHUD.generated.h"




UCLASS()
class PROJECT_HONG_PROTO_API APHHUD : public AHUD
{
	GENERATED_BODY()
public:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================
	APHHUD();

private:
	//=========================================================
	//=                   - Variables -                       =
	//=========================================================



	//=========================================================
	//=                   - Functionary -                     =
	//=========================================================
	virtual void BeginPlay()override;
};

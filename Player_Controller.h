// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player_Controller.generated.h"


UCLASS()
class GALAGAARCADE_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()

protected:

protected:
	void BeginPlay();

	void Tick(float DeltaTime);

public:

};
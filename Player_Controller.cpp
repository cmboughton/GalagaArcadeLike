// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Controller.h"
#include "Engine/EngineTypes.h"


void APlayer_Controller::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

}
void APlayer_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

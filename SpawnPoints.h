// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoints.generated.h"

UCLASS()
class GALAGAARCADE_API ASpawnPoints : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoints();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	FTransform CurrentTransform;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	const FTransform						GetCurrentTransform()						const { return CurrentTransform; }
};

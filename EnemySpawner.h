// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class GALAGAARCADE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TArray<struct FWaveSpawnerConditions> EnemySpawnerConditions;

	UPROPERTY()
	int WaveTracker = 0;

	UPROPERTY()
	bool DelayTimer = false;

	UPROPERTY()
	class AGalagaArcadeCharacter* PlayerCharacter = nullptr;

	TArray<AActor*> FoundActors;

	UFUNCTION()
	void StartSpawning(int EnemySpawnerIndex);

	UFUNCTION()
	void SpawnEnemy(TSubclassOf<class AEnemyCharacter> EnemyCharacter, FTransform SpawnTransform);

	UFUNCTION()
	FVector GetRandomPointNearOrigin(const FVector& Origin, float MinDistance, float MaxDistance);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	int CurrentWave = 0;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "..\..\Source\GalagaArcade\ProjectileBullets.h"
#include "..\..\Source\GalagaArcade\SpawnPoints.h"
#include "Structs.generated.h"

USTRUCT(BlueprintType)
struct FShipLayout
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMesh* ShipMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int NumberOfGuns = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseDamage = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseFireRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseBulletSpeed = 2000.f;
};

USTRUCT(BlueprintType)
struct FBulletTypes
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString BulletName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	BulletType StructBulletType = BulletType::NormalBullet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AProjectileBullets>Bullet = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int AmmoAmount = 0;
};

USTRUCT(BlueprintType)
struct FBuffStats
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	Buffs EnumBuffs = Buffs::Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BuffValue = 0;
};

USTRUCT(BlueprintType)
struct FBuffBaseStruct
{
	GENERATED_BODY()

	UPROPERTY()
	class UBuffUIWidget* BuffWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<struct FBuffStats> Stats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Duration = 10.f;
};

USTRUCT(BlueprintType)
struct FWaveSpawner
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere)
	//float WaveSpawnerDelay = 0.f;

	//UPROPERTY(EditAnywhere)
	//bool SpawnWhenAllDead = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyCharacter> EnemyCharacter = nullptr;

	UPROPERTY(EditAnywhere)
	int SpawnAmount = 1;

	UPROPERTY(EditAnywhere)
	SpawningType SpawningLocation = SpawningType::RandomSpawnPoint;

	UPROPERTY(EditAnywhere)
	TArray <class ASpawnPoints*> SpawnPoints;

};

USTRUCT(BlueprintType)
struct FCheckTotalEnemies
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	LessThanorGreaterThanType EnemyCountCheck = LessThanorGreaterThanType::LessThanOrEqual;

	UPROPERTY(EditAnywhere)
	int TotalEnemyAmount = 0;
};

USTRUCT(BlueprintType)
struct FWaveSpawnerConditions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float SpawnDelay = 0.f;

	UPROPERTY(EditAnywhere)
	struct FCheckTotalEnemies EnemyCountChecker;

	UPROPERTY(EditAnywhere)
	TArray<struct FWaveSpawner> WaveSpawner;

};
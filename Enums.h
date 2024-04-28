// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class BulletType : uint8
{
	NormalBullet				UMETA(DisplayName = "NormalBullet"),
	ExplosiveBullet				UMETA(DisplayName = "ExplosiveBullet"),
	BouncingBettyBullet			UMETA(DisplayName = "BouncingBettyBullet"),
	SplittingBullet				UMETA(DisplayName = "SplittingBullet"),
	HommingBullet				UMETA(DisplayName = "HommingBullet"),
};

UENUM(BlueprintType)
enum class WeaponSlot : uint8
{
	WeaponSlot1					UMETA(DisplayName = "WeaponSlot1"),
	WeaponSlot2					UMETA(DisplayName = "WeaponSlot2"),
	WeaponSlot3					UMETA(DisplayName = "WeaponSlot3"),
};

UENUM(BlueprintType)
enum class Buffs : uint8
{
	Health						UMETA(DisplayName = "Health"),
	Damage						UMETA(DisplayName = "Damage"),
	FireRate					UMETA(DisplayName = "FireRate"),
};

UENUM(BlueprintType)
enum class SpawningType : uint8
{
	//SingleSpawnPoint			UMETA(DisplayName = "SingleSpawnPoint"),
	RandomSpawnPoint			UMETA(DisplayName = "RandomSpawnPoint"),
	RandomLocationSpawn			UMETA(DisplayName = "RandomLocationSpawn"),
};

UENUM(BlueprintType)
enum class EnemyType : uint8
{
	Normal						UMETA(DisplayName = "Normal"),
	Elite						UMETA(DisplayName = "Elite"),
	MiniBoss					UMETA(DisplayName = "Mini-Boss"),
	Boss						UMETA(DisplayName = "Boss"),
};

UENUM(BlueprintType)
enum class LessThanorGreaterThanType : uint8
{
	LessThanOrEqual				UMETA(DisplayName = "Less Than or Equal"),
	GreaterThanorEqual			UMETA(DisplayName = "Greater Than or Equal"),
};
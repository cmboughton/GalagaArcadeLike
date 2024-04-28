// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GalagaArcadeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"
#include "EnemyCharacter.h"
#include "Logging/StructuredLog.h"
#include "ProjectileBullets.generated.h"

UCLASS()
class GALAGAARCADE_API AProjectileBullets : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileBullets();

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UProjectileMovementComponent* MovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

	UFUNCTION()
	virtual void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void TimerElapsed();

	UFUNCTION()
	virtual TArray<FHitResult> SphereTrace(FVector ActorLocation, float ExplosionSize);

	UFUNCTION()
	virtual FHitResult LineTrace(FVector StartLocation, FVector EndLocation);

public:
	// Called every frame
	virtual void Tick(float DeltaTime);

protected:

	UPROPERTY(BlueprintReadOnly)
	class AGalagaArcadeCharacter* PlayerCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float TimeTillDestroy = 5.f;

	UPROPERTY(BlueprintReadOnly)
	float BulletSpeed;

	UPROPERTY(BlueprintReadOnly)
	float ExplsionRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsHommingMissile = false;

	UPROPERTY()
	class APlayer_Controller* PlayerController = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BulletDamageModifier = 1.f;
};
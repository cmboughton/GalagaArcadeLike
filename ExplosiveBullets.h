// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBullets.h"
#include "ExplosiveBullets.generated.h"

UCLASS()
class GALAGAARCADE_API AExplosiveBullets : public AProjectileBullets
{
	GENERATED_BODY()

protected:
	
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	//UFUNCTION()
	//TArray<FHitResult> SphereTrace(FVector ActorLocation, float ExplosionSize);

	void TimerElapsed() override;

	void ApplyDamage(TArray<struct FHitResult> AllActorsHit, float AddDamageModifier);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ExplosionRadius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DamageModifier = 1.f;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplosiveBullets.h"
#include "ExplosiveBettyBullets.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API AExplosiveBettyBullets : public AExplosiveBullets
{
	GENERATED_BODY()

protected:

	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	UPROPERTY()
	int BettyBounces = 4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BounceRadius = 300.f;

};

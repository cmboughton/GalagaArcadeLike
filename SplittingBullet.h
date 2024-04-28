// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBullets.h"
#include "SplittingBullet.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API ASplittingBullet : public AProjectileBullets
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SplitBullet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int BulletSplitAmount = 1;

	UPROPERTY(BlueprintReadOnly)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SplitDistance = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AProjectileBullets>BasicBullet = NULL;

	UPROPERTY()
	bool CanSplit = true;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GalagaArcadeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BuffBase.generated.h"

UCLASS()
class GALAGAARCADE_API ABuffBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuffBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* OverlappingSphere;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* BuffMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	struct FBuffBaseStruct BuffValues;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadOnly)
	class AGalagaArcadeCharacter* PlayerCharacter;

public:	

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GALAGAARCADE_API AEnemyCharacter : public AActor
{
	GENERATED_BODY()

#pragma region Components
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Capsule Component")
	class UCapsuleComponent* EnemyCapsule;

	UPROPERTY(EditDefaultsOnly, Category = "Skeletal Mesh")
	class USkeletalMeshComponent* EnemySkeletalMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Arrow Component")
	class UArrowComponent* Arrow;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Component")
	class UWidgetComponent* HealthBarWidget;

#pragma endregion

public:	
	// Sets default values for this actor's properties
	AEnemyCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	float DealDamage(float Health, float DamageValue);

	UFUNCTION()
	void Death();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 100.f;
	
	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EnemyType EnemyDifficulty = EnemyType::Normal;

	UPROPERTY(BlueprintReadOnly)
	class UEnemyHealthWidget* EnemyHealthWidget = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

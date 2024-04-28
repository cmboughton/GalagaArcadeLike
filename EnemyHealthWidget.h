// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API UEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Health;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor MiniBossPBColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor BossPBColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	UPROPERTY()
	float CurrentHealthNormalized = 1.f;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:

	UFUNCTION()
	void SetUpHealthBar(const EnemyType EnemyTypeEnum);

	UFUNCTION()
	void UpdateHealthBar(const float CurrentHealth, const float MaxHealth);

};

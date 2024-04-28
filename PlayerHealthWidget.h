// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API UPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_CurrentHealth;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MaxHealth;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_PlayerHealth;

public:

	void UpdateHealth(const float CurrentHealth, const float MaxHealth);
};

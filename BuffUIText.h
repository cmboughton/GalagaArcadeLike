// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Structs.h"
#include "BuffUIText.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API UBuffUIText : public UUserWidget
{
	GENERATED_BODY()

protected:

	//virtual void NativeConstruct();

	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BuffNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BuffValueText;

public:

	UFUNCTION()
	void UpdateText(Buffs EnumBuffs, float BuffValue);
};

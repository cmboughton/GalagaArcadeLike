// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs.h"
#include "GalagaArcadeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BuffUIText.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "BuffUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API UBuffUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	struct FBuffBaseStruct BuffValues;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* BuffTextVB;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DurationText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class TSubclassOf<UBuffUIText> BuffTextBP;

	UPROPERTY()
	FTimerHandle BuffTimer;

	UPROPERTY()
	bool TimerActive = false;

	UPROPERTY()
	float Timer = 0.f;

	UPROPERTY()
	class AGalagaArcadeCharacter* PlayerCharacter = Cast<AGalagaArcadeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//void TimeElapsed();

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UFUNCTION()
	float ClampFloatToDecimal(float Value, float DecimalPlaces);

public:

	UFUNCTION()
	void StartTimer(FBuffBaseStruct Buff);
};

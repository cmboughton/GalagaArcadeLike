// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BulletTypeWidget.h"
#include "BuffUIWidget.h"
#include "PlayerHealthWidget.h"
#include "MainUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* WeaponSlotHB;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* BuffsHB;

	virtual void NativeConstruct();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class AGalagaArcadeCharacter* PlayerCharacter = NULL;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	const TSubclassOf<UUserWidget> BulletTypeWidget;

	class TArray<class UBulletTypeWidget*> BulletWidgetArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<struct FBuffBaseStruct> BuffStats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UBuffUIWidget> BuffUI = nullptr;

	UPROPERTY()
	class UBuffUIWidget* BPBuffWidget = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UPlayerHealthWidget* WB_PlayerHealth;

public:

	UFUNCTION()
	void AddBuff(FBuffBaseStruct Buff);

	UFUNCTION()
	void RemoveBuff(UBuffUIWidget* BuffWidget);

	class UPlayerHealthWidget*						GetWB_PlayerHealth()			const { return WB_PlayerHealth; }
};



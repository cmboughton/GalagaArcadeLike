// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GalagaArcadeCharacter.h"
#include "Components/TextBlock.h"
#include "Enums.h"
#include "BulletTypeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GALAGAARCADE_API UBulletTypeWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BulletName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AmmoText;
	
	UPROPERTY(meta = (BindWidget))
	class UBorder* BulletImage;

	UPROPERTY(BlueprintReadOnly)
	class AGalagaArcadeCharacter* PlayerCharacter;
	
protected:

	virtual void NativeConstruct();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	WeaponSlot WeaponSlotEnum = WeaponSlot::WeaponSlot1;

	//UFUNCTION(BlueprintCallable)
	//void UpdateAmmo();
};

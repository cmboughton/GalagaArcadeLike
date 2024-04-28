// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthWidget.h"
#include "GalagaArcadeCharacter.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UPlayerHealthWidget::UpdateHealth(const float CurrentHealth, const float MaxHealth)
{
	if (Text_MaxHealth != nullptr && Text_CurrentHealth != nullptr && PB_PlayerHealth != nullptr)
	{
		Text_MaxHealth->SetText(FText::FromString(FString::SanitizeFloat(MaxHealth)));
		Text_CurrentHealth->SetText(FText::FromString(FString::SanitizeFloat(CurrentHealth)));
		PB_PlayerHealth->SetPercent(UKismetMathLibrary::NormalizeToRange(CurrentHealth, 0.f, MaxHealth));
		//UE_LOGFMT(LogTemp, Warning, "Health UI set up");
	}
}

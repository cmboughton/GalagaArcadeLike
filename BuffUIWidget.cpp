// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffUIWidget.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetTextLibrary.h"

void UBuffUIWidget::StartTimer(FBuffBaseStruct Buff)
{
	BuffValues = Buff;
	if (BuffValues.Duration > 0)
	{
		UWorld* World = GetWorld();
		if (World != NULL)
		{
			//World->GetTimerManager().SetTimer(BuffTimer, this, &UBuffUIWidget::TimeElapsed, BuffValues.Duration, false);
			TimerActive = true;
			for (int i = 0; i < BuffValues.Stats.Num(); i++)
			{
				if (BuffTextBP != NULL)
				{
					UBuffUIText* BuffText = CreateWidget<UBuffUIText>(GetWorld(), BuffTextBP);
					if (BuffText != NULL && BuffTextVB != NULL)
					{
						BuffTextVB->AddChild(BuffText);
						if (BuffValues.Stats.IsValidIndex(i))
						{
							BuffText->UpdateText(BuffValues.Stats[i].EnumBuffs, BuffValues.Stats[i].BuffValue);
						}
					}
				}
			}
		}
	}
}
void UBuffUIWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (TimerActive)
	{
		Timer += InDeltaTime;
		float RemainingTimer = BuffValues.Duration - Timer;
		FText TimerConv = UKismetTextLibrary::Conv_DoubleToText(RemainingTimer, HalfToEven, false, true, 1, 1000, 2, 2);
		DurationText->SetText(TimerConv);
		if (Timer >= BuffValues.Duration && PlayerCharacter->WidgetInstance != NULL)
		{
			PlayerCharacter->WidgetInstance->RemoveBuff(this);
			RemoveFromParent();
		}
	}
}
float UBuffUIWidget::ClampFloatToDecimal(float Value, float DecimalPlaces)
{
	float Multiplier = FMath::Pow(10, DecimalPlaces);
	float RoundedValue = FMath::RoundToFloat(Value * Multiplier) / Multiplier;
	return RoundedValue;
}
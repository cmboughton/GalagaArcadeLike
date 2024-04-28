// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffUIText.h"

void UBuffUIText::UpdateText(Buffs EnumBuffs, float BuffValue)
{
	switch (EnumBuffs)
	{
	case Buffs::Health:
		BuffNameText->SetText(FText::FromString("Health"));
		BuffValueText->SetText(FText::FromString(FString::SanitizeFloat(BuffValue)));
		break;
	case Buffs::Damage:
		BuffNameText->SetText(FText::FromString("Damage"));
		BuffValueText->SetText(FText::FromString(FString::SanitizeFloat(BuffValue)));
		break;
	case Buffs::FireRate:
		BuffNameText->SetText(FText::FromString("Fire Rate"));
		FString Str = "%";
		BuffValueText->SetText(FText::FromString(*FString::SanitizeFloat((BuffValue * 100)).Append(Str)));
		break;
	}
	
}

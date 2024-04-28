// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIWidget.h"
#include "GalagaArcadeCharacter.h"
#include "Components/HorizontalBox.h"
#include "Logging/StructuredLog.h"

void UMainUIWidget::NativeConstruct()
{
	PlayerCharacter = Cast<AGalagaArcadeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter != NULL && WeaponSlotHB != NULL)
	{
		BulletWidgetArray.Empty();
		for (int i = 1; i <= PlayerCharacter->GetBulletsAvaliable(); i++)
		{
			UBulletTypeWidget* WidgetInstance = CreateWidget<UBulletTypeWidget>(GetWorld(), BulletTypeWidget);
			if (WidgetInstance != NULL)
			{
				//UE_LOGFMT(LogTemp, Warning, "WidgetInstanceTrue");
				switch (i)
				{
				case 1:
					WidgetInstance->WeaponSlotEnum = WeaponSlot::WeaponSlot1;
					WeaponSlotHB->AddChild(WidgetInstance);
					BulletWidgetArray.Add(WidgetInstance);
					//UE_LOGFMT(LogTemp, Warning, "Slot1");
					break;
				case 2:
					WidgetInstance->WeaponSlotEnum = WeaponSlot::WeaponSlot2;
					WeaponSlotHB->AddChild(WidgetInstance);
					BulletWidgetArray.Add(WidgetInstance);
					//UE_LOGFMT(LogTemp, Warning, "Slot2");
					break;
				case 3:
					WidgetInstance->WeaponSlotEnum = WeaponSlot::WeaponSlot3;
					WeaponSlotHB->AddChild(WidgetInstance);
					BulletWidgetArray.Add(WidgetInstance);
					//UE_LOGFMT(LogTemp, Warning, "Slot3");
					break;
				}
			}
		}
	}
}

void UMainUIWidget::AddBuff(FBuffBaseStruct Buff)
{
	//UE_LOGFMT(LogTemp, Warning, "Buffs: {0}", Buff.Duration);
	if (BuffUI != NULL && BuffsHB != NULL && PlayerCharacter != NULL)
	{
		if (GetWorld())
		{
			BPBuffWidget = CreateWidget<UBuffUIWidget>(GetWorld(), BuffUI);
			if (BPBuffWidget != NULL)
			{
				FBuffBaseStruct BuffStructSetUp;
				BuffStructSetUp = Buff;
				BuffStructSetUp.BuffWidget = BPBuffWidget;
				BuffsHB->AddChild(BPBuffWidget);
				BPBuffWidget->StartTimer(BuffStructSetUp);
				BuffStats.Add(BuffStructSetUp);
				if (PlayerCharacter != NULL)
				{
					PlayerCharacter->UpdateBuffs(BuffStats);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("PlayerCharacter NULL"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to create BPBuffWidget"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Null pointer detected: BuffUI, BuffsHB, or PlayerCharacter"));
	}
}

void UMainUIWidget::RemoveBuff(UBuffUIWidget* BuffWidget)
{
	if (!BuffStats.IsEmpty())
	{
		for (int i = 0; i < BuffStats.Num(); i++)
		{
			if (BuffStats.IsValidIndex(i))
			{
				if (BuffStats[i].BuffWidget == BuffWidget)
				{
					BuffStats.RemoveAt(i);
				}
			}
		}
		PlayerCharacter->UpdateBuffs(BuffStats);
	}
}
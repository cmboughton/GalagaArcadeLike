// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTypeWidget.h"
#include "Logging/StructuredLog.h"
#include "Kismet/GameplayStatics.h"


void UBulletTypeWidget::NativeConstruct()
{
	PlayerCharacter = Cast<AGalagaArcadeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter != NULL)
	{
		TArray<struct FBulletTypes> BulletTypes = PlayerCharacter->GetStructBulletTypes();
		switch (WeaponSlotEnum)
		{
		case WeaponSlot::WeaponSlot1:
			BulletName->SetText(FText::FromString(BulletTypes[PlayerCharacter->GetWeaponSelection1()].BulletName));
			break;
		
		case WeaponSlot::WeaponSlot2:
			BulletName->SetText(FText::FromString(BulletTypes[PlayerCharacter->GetWeaponSelection2()].BulletName));
			break;
		
		case WeaponSlot::WeaponSlot3:
			BulletName->SetText(FText::FromString(BulletTypes[PlayerCharacter->GetWeaponSelection3()].BulletName));
			break;
		}
		//UE_LOGFMT(LogTemp, Warning, "Weapon Slot 1: {0}", BulletName->GetName());
	}
}

//void UBulletTypeWidget::UpdateAmmo()
//{
//	if(PlayerCharacter != NULL)
//	{
//		UE_LOGFMT(LogTemp, Warning, "Weapon Slot 1");
//		TArray<struct FBulletTypes> BulletNames = PlayerCharacter->GetStructBulletTypes();
//		int AmmoText1 = BulletNames[PlayerCharacter->GetWeaponSelection1()].AmmoAmount;
//		int AmmoText2 = BulletNames[PlayerCharacter->GetWeaponSelection2()].AmmoAmount;
//		int AmmoText3 = BulletNames[PlayerCharacter->GetWeaponSelection3()].AmmoAmount;
//		BulletType BulletTypeStruct = BulletType::NormalBullet;
//		switch (WeaponSlotEnum)
//		{
//		case WeaponSlot::WeaponSlot1:
//			if (BulletNames[PlayerCharacter->GetWeaponSelection1()].StructBulletType == BulletTypeStruct)
//			{
//				AmmoText->SetText(FText::FromString("Infinite"));
//			}
//			else
//			{
//				AmmoText->SetText(FText::FromString(FString::FromInt(AmmoText1)));
//			}
//			break;
//
//		case WeaponSlot::WeaponSlot2:
//			if (BulletNames[PlayerCharacter->GetWeaponSelection2()].StructBulletType == BulletTypeStruct)
//			{
//				AmmoText->SetText(FText::FromString("Infinite"));
//			}
//			else
//			{
//				AmmoText->SetText(FText::FromString(FString::FromInt(AmmoText2)));
//			}
//			break;
//
//		case WeaponSlot::WeaponSlot3:
//			if (BulletNames[PlayerCharacter->GetWeaponSelection3()].StructBulletType == BulletTypeStruct)
//			{
//				AmmoText->SetText(FText::FromString("Infinite"));
//			}
//			else
//			{
//				AmmoText->SetText(FText::FromString(FString::FromInt(AmmoText3)));
//			}
//			break;
//		}
//	}
//}

// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthWidget.h"
#include "Enums.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UEnemyHealthWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (PB_Health != nullptr)
	{
		if (PB_Health->GetPercent() > CurrentHealthNormalized)
		{
			PB_Health->SetPercent(PB_Health->GetPercent() - InDeltaTime);
		}
	}
}

void UEnemyHealthWidget::SetUpHealthBar(const EnemyType EnemyTypeEnum)
{
	if (PB_Health != nullptr)
	{
		PB_Health->SetPercent(1.f);
		switch (EnemyTypeEnum)
		{
		case EnemyType::Normal:
			break;
		case EnemyType::Elite:
			break;
		case EnemyType::MiniBoss:
			PB_Health->SetFillColorAndOpacity(MiniBossPBColor);
			break;
		case EnemyType::Boss:
			PB_Health->SetFillColorAndOpacity(BossPBColor);
			break;
		}
	}
}

void UEnemyHealthWidget::UpdateHealthBar(const float CurrentHealth, const float MaxHealth)
{
	CurrentHealthNormalized = UKismetMathLibrary::NormalizeToRange(CurrentHealth, 0.f, MaxHealth);
}
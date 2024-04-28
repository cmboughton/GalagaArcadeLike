// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"

#include "EnemyHealthWidget.h"

#include "Logging/StructuredLog.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("EnemyCapsule"));
	SetRootComponent(EnemyCapsule);
	
	EnemySkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemySkeletalMesh"));
	EnemySkeletalMesh->SetupAttachment(RootComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
}


// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	if (HealthBarWidget != nullptr)
	{
		EnemyHealthWidget = Cast<UEnemyHealthWidget>(HealthBarWidget->GetUserWidgetObject());

		FVector2D MiniBossDrawSize	= FVector2D(100.f, 8.f);
		FVector2D BossDrawSize		= FVector2D(150.f, 12.f);

		if (EnemyHealthWidget != nullptr)
		{
			switch (EnemyDifficulty)
			{
			case EnemyType::Normal:
				HealthBarWidget->SetVisibility(false);
				break;
			case EnemyType::Elite:
				HealthBarWidget->SetVisibility(false);
				break;
			case EnemyType::MiniBoss:
				HealthBarWidget->SetVisibility(true);
				HealthBarWidget->SetDrawSize(MiniBossDrawSize);
				EnemyHealthWidget->SetUpHealthBar(EnemyType::MiniBoss);
				break;
			case EnemyType::Boss:
				HealthBarWidget->SetVisibility(true);
				HealthBarWidget->SetDrawSize(BossDrawSize);
				EnemyHealthWidget->SetUpHealthBar(EnemyType::Boss);
				break;
			}
		}
	}
}


// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//float DamageCaused = TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//DamageCaused = FMath::Min(Health, DamageCaused);

	CurrentHealth = DealDamage(CurrentHealth, DamageAmount);
	if (EnemyHealthWidget != nullptr)
	{
		EnemyHealthWidget->UpdateHealthBar(CurrentHealth, MaxHealth);
	}
	//UE_LOGFMT(LogTemp, Warning, "Remaing Health: {0}", CurrentHealth);
	if (CurrentHealth <= 0)
	{
		Death();
	}
	return CurrentHealth;
}

float AEnemyCharacter::DealDamage(float Health, float DamageValue)
{
	float HealthOut = Health - DamageValue;
	return HealthOut;
}

void AEnemyCharacter::Death()
{
	this->Destroy();
}

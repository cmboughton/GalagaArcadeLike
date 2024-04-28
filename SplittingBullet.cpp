// Fill out your copyright notice in the Description page of Project Settings.


#include "SplittingBullet.h"

void ASplittingBullet::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = this->GetActorLocation();
}
void ASplittingBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FVector::Distance(this->GetActorLocation(), StartLocation) >= SplitDistance && CanSplit)
	{
		CanSplit = false;
		SplitBullet();
	}
}
void ASplittingBullet::SplitBullet()
{
	//UE_LOG(LogTemp, Warning, TEXT("BulletSplit"));
	bool FlipFlopTracker = false;
	FVector SplitLocation = this->GetActorLocation();
	FRotator SplitRotation = this->GetActorRotation();
	FVector SpawnScale = FVector(1.f, 1.f, 1.f);

	for (int i = 0; i < BulletSplitAmount; i++)
	{
		class AProjectileBullets* SpawnedBullet = NULL;
		if (FlipFlopTracker)
		{
			FVector SpawnLocation = FVector (SplitLocation.X, SplitLocation.Y, SplitLocation.Z);
			FRotator SpawnRotation = FRotator(SplitRotation.Pitch, SplitRotation.Yaw - (i * (BulletSplitAmount / 2)), SplitRotation.Roll);
			FTransform SpawnTransform(SpawnRotation, SpawnLocation, SpawnScale);
			SpawnedBullet = GetWorld()->SpawnActor<AProjectileBullets>(BasicBullet, SpawnTransform);
			if (SpawnedBullet)
			{
				SpawnedBullet->BulletDamageModifier = 2.f / BulletSplitAmount;
			}
			//UE_LOGFMT(LogTemp, Warning, "SpawnTrue");
		}
		else
		{
			FVector SpawnLocation = FVector(SplitLocation.X, SplitLocation.Y, SplitLocation.Z);
			FRotator SpawnRotation = FRotator(SplitRotation.Pitch, SplitRotation.Yaw + (i * (BulletSplitAmount / 2)), SplitRotation.Roll);
			FTransform SpawnTransform(SpawnRotation, SpawnLocation, SpawnScale);
			SpawnedBullet = GetWorld()->SpawnActor<AProjectileBullets>(BasicBullet, SpawnTransform);
			if (SpawnedBullet)
			{
				SpawnedBullet->BulletDamageModifier = 2.f / BulletSplitAmount;
			}
			//UE_LOGFMT(LogTemp, Warning, "SpawnFalse");
		}
		FlipFlopTracker = !FlipFlopTracker;
	}
	this->Destroy();
}
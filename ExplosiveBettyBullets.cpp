// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBettyBullets.h"

void AExplosiveBettyBullets::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	for (int i = 0; i <= BettyBounces - 1; i++)
	{
		FVector CurrentLocation = this->GetActorLocation();
		double RandomX = FMath::RandRange(CurrentLocation.X - BounceRadius, CurrentLocation.X + BounceRadius);
		double RandomY = FMath::RandRange(CurrentLocation.Y - BounceRadius, CurrentLocation.Y + BounceRadius);
		FVector RandomLocation = FVector(RandomX, RandomY, CurrentLocation.Z);
		TArray<FHitResult> CurrentActorsHit = SphereTrace(RandomLocation, ExplosionRadius);
		ApplyDamage(CurrentActorsHit, DamageModifier);
	}
	Super::HitMesh(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

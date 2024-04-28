// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveBullets.h"

void AExplosiveBullets::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOGFMT(LogTemp, Warning, "HitMesh Triggered");
	TArray<struct FHitResult> CurrentActorsHit = SphereTrace(this->GetActorLocation(), ExplosionRadius);
	ApplyDamage(CurrentActorsHit, DamageModifier);
	this->Destroy();
}
void AExplosiveBullets::ApplyDamage(TArray<struct FHitResult> ActorsHit, float AddDamageModifier)
{
	if (!ActorsHit.IsEmpty())
	{
		UE_LOGFMT(LogTemp, Warning, "Total Number of Actors Hit {0}", ActorsHit.Num());
		for (int i = 0; i <= ActorsHit.Num(); i++)
		{
			if (ActorsHit.IsValidIndex(i))
			{
				if (Cast<AEnemyCharacter>(ActorsHit[i].GetActor()))
				{
					if (PlayerCharacter != NULL)
					{
						FVector ActorLocation = ActorsHit[i].GetActor()->GetActorLocation();
						FPointDamageEvent DamageEvent(PlayerCharacter->GetDamage() * AddDamageModifier, ActorsHit[i], ActorLocation, nullptr);
						ActorsHit[i].GetActor()->TakeDamage((PlayerCharacter->GetDamage() * AddDamageModifier), DamageEvent, GetInstigatorController(), this);
						//UE_LOGFMT(LogTemp, Warning, "Enemy Hit: {0} Damage Done: {1} At: {2}", ActorsHit[i].GetActor()->GetName(), PlayerCharacter->GetDamage() * AddDamageModifier, ActorLocation.ToString());
					}
				}
			}
			UE_LOGFMT(LogTemp, Warning, "Actors Hit {0}", i);
		}
	}

}
//TArray<FHitResult> AProjectileBullets::SphereTrace(FVector ActorLocation, float ExplosionSize)
//{
//	TArray<AActor*> ActorsToIgnore;
//	ActorsToIgnore.Init(this, 1);
//	TArray<FHitResult> AllActorsHit;
//	UKismetSystemLibrary::SphereTraceMulti(		GetWorld(),
//												ActorLocation,
//												ActorLocation,
//												ExplosionSize, 
//												ETraceTypeQuery::TraceTypeQuery1,
//												false,
//												ActorsToIgnore,
//												EDrawDebugTrace::Persistent,
//												AllActorsHit,
//												true,
//												FLinearColor::Red,
//												FLinearColor::Green,
//												5.f);
//	
//	return TArray<FHitResult>(AllActorsHit);
//}
void AExplosiveBullets::TimerElapsed()
{
	UE_LOG(LogTemp, Warning, TEXT("Time!"));
	Super::TimerElapsed();
}


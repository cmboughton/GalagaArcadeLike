// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBullets.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Player_Controller.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileBullets::AProjectileBullets()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BulletMesh"));
	SetRootComponent(BulletMesh);
	BulletMesh->CastShadow = false;
	//const FCollisionResponseContainer CollisionChannels(uint8 WorldStatic<3>);
	//BulletMesh->SetCollisionResponseToChannels(ECollisionChannel::ECC_Pawn, ECR_Block,);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject< UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->ProjectileGravityScale = 0.f;
	
}

// Called when the game starts or when spawned
void AProjectileBullets::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AProjectileBullets::TimerElapsed, TimeTillDestroy, false);

	PlayerCharacter = Cast<AGalagaArcadeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerController = Cast<APlayer_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PlayerCharacter != nullptr)
	{
		BulletSpeed = PlayerCharacter->GetBulletSpeed();
	}

	if (IsHommingMissile)
	{
		if (PlayerCharacter != nullptr && PlayerController != nullptr)
		{
			FVector TraceEndLocation = (PlayerCharacter->GetMouseDirection() * 5000.f) + PlayerCharacter->GetMouseLocation();
			const FVector MouseLocation = LineTrace(PlayerCharacter->GetMouseLocation(), TraceEndLocation).ImpactPoint;
			TArray<struct FHitResult> CurrentActorsHit = SphereTrace(MouseLocation, 500.f);
			//UE_LOGFMT(LogTemp, Warning, "PlayerLocation - X: {0} Y: {1} Z: {2}", PlayerCharacter->GetActorLocation().X, PlayerCharacter->GetActorLocation().Y, PlayerCharacter->GetActorLocation().Z);
			//UE_LOGFMT(LogTemp, Warning, "MouseLocation - X: {0} Y: {1} Z: {2}", MouseLocation.X, MouseLocation.Y, MouseLocation.Z);
			if (!CurrentActorsHit.IsEmpty())
			{
				int ClosestActor = 0;
				for (int i = 0; i < CurrentActorsHit.Num(); i++)
				{
					if (CurrentActorsHit.IsValidIndex(i))
					{
						if (CurrentActorsHit[i].GetActor() != nullptr && Cast<AEnemyCharacter>(CurrentActorsHit[i].GetActor()))
						{
							if (FVector::Distance(CurrentActorsHit[i].GetActor()->GetActorLocation(), MouseLocation) <= FVector::Distance(CurrentActorsHit[ClosestActor].GetActor()->GetActorLocation(), MouseLocation))
							{
								ClosestActor = i;
							}
							//UE_LOGFMT(LogTemp, Warning, "Enemy Hit: {0}", CurrentActorsHit[i].GetActor()->GetName());
						}
					}
				}
				if (Cast<AEnemyCharacter>(CurrentActorsHit[ClosestActor].GetActor()))
				{
					MovementComponent->bIsHomingProjectile = true;
					MovementComponent->HomingAccelerationMagnitude = (BulletSpeed * 1.5f);
					MovementComponent->bRotationFollowsVelocity = true;
					MovementComponent->HomingTargetComponent = CurrentActorsHit[ClosestActor].GetActor()->GetRootComponent();
					//UE_LOGFMT(LogTemp, Warning, "HomingTarget: {0}", CurrentActorsHit[ClosestActor].GetActor()->GetName());
				}
			}
		}
	}

	BulletMesh->OnComponentHit.AddDynamic(this, &AProjectileBullets::HitMesh);
}

// Called every frame
void AProjectileBullets::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProjectileBullets::TimerElapsed()
{
	this->Destroy();
}
void AProjectileBullets::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& ActorHit)
{
	if (Cast<AEnemyCharacter>(ActorHit.GetActor()))
	{
		if (PlayerCharacter != NULL)
		{
			AActor* EnemyHit = ActorHit.GetActor();
			FVector ActorLocation = ActorHit.GetActor()->GetActorLocation();
			FPointDamageEvent DamageEvent((PlayerCharacter->GetDamage() * BulletDamageModifier), ActorHit, ActorLocation, nullptr);
			EnemyHit->TakeDamage((PlayerCharacter->GetDamage() * BulletDamageModifier), DamageEvent, GetInstigatorController(), this);
		}
	}
	this->Destroy();
}
TArray<FHitResult> AProjectileBullets::SphereTrace(FVector ActorLocation, float ExplosionSize)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Init(this, 1);
	TArray<FHitResult> AllActorsHit;
	UKismetSystemLibrary::SphereTraceMulti(	GetWorld(),
											ActorLocation,
											ActorLocation,
											ExplosionSize,
											ETraceTypeQuery::TraceTypeQuery1,
											false,
											ActorsToIgnore,
											EDrawDebugTrace::None,
											AllActorsHit,
											true,
											FLinearColor::Red,
											FLinearColor::Green,
											5.f);
	return TArray<FHitResult>(AllActorsHit);
}
FHitResult AProjectileBullets::LineTrace(FVector StartLocation, FVector EndLocation)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Init(this, 1);
	FHitResult ActorHit;
	UKismetSystemLibrary::LineTraceSingle(	GetWorld(),
											StartLocation,
											EndLocation,
											ETraceTypeQuery::TraceTypeQuery1,
											false,
											ActorsToIgnore,
											EDrawDebugTrace::None,
											ActorHit,
											true,
											FLinearColor::Red,
											FLinearColor::Green,
											5.f);

	return ActorHit;
}

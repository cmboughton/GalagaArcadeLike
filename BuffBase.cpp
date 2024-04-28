// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffBase.h"
#include "Logging/StructuredLog.h"

// Sets default values
ABuffBase::ABuffBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlappingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlappingSphere"));
	OverlappingSphere->InitSphereRadius(100.f);
	OverlappingSphere->OnComponentBeginOverlap.AddDynamic(this, &ABuffBase::OnSphereOverlap);
	SetRootComponent(OverlappingSphere);
	OverlappingSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlappingSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	BuffMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuffMesh"));
	BuffMesh->SetupAttachment(OverlappingSphere);
	FVector BuffMeshScale = FVector(.2f, .2f, .2f);
	BuffMesh->SetRelativeScale3D(BuffMeshScale);
	BuffMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

// Called when the game starts or when spawned
void ABuffBase::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AGalagaArcadeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ABuffBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AGalagaArcadeCharacter>(OtherActor))
	{
		if (PlayerCharacter != nullptr && PlayerCharacter->WidgetInstance != nullptr)
		{
			PlayerCharacter->WidgetInstance->AddBuff(BuffValues);
			this->Destroy();
		}

	}
}
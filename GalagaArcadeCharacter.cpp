// Copyright Epic Games, Inc. All Rights Reserved.

#include "GalagaArcadeCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player_Controller.h"
#include "Logging/StructuredLog.h"
#include "UObject/Class.h"
#include "Blueprint/UserWidget.h"

//////////////////////////////////////////////////////////////////////////
// AGalagaArcadeCharacter

AGalagaArcadeCharacter::AGalagaArcadeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->TargetArmLength = 1500;
	CameraBoom->bEnableCameraLag = false;
	CameraBoom->CameraLagMaxDistance = 2000.f;
	CameraBoom->CameraLagSpeed = 1.5f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void AGalagaArcadeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	Player_Controller = Cast<APlayer_Controller>(GetController());

	//Adding Main UI Widget to viewport
	if (IsValid(MainWidgetUI))
	{
		WidgetInstance = CreateWidget<UMainUIWidget>(GetWorld(), MainWidgetUI);
		if (WidgetInstance != nullptr)
		{
			WidgetInstance->AddToViewport();
		}
	}

	SetUpShipLayout();
}

void AGalagaArcadeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Player_Controller != nullptr)
	{

		//FVector mouseLocation, mouseDirection;
		Player_Controller->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		FRotator currentCharacterRotation = this->GetActorRotation();
		FRotator targetRotation = mouseDirection.Rotation();

		FRotator newRotation = FRotator(currentCharacterRotation.Pitch, targetRotation.Yaw, currentCharacterRotation.Roll);
		this->SetActorRotation(newRotation);

	}

	if (FireRateTimer > 0)
	{
		FireRateTimer -= DeltaTime;
		//UE_LOGFMT(LogTemp, Warning, "FireRateTimer: {0}", FireRateTimer);
	}
}
void AGalagaArcadeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGalagaArcadeCharacter::Move);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGalagaArcadeCharacter::Shoot);

		//WeaponSwapping
		EnhancedInputComponent->BindAction(WeaponSlot1Action, ETriggerEvent::Started, this, &AGalagaArcadeCharacter::WeaponSlot1);
		EnhancedInputComponent->BindAction(WeaponSlot2Action, ETriggerEvent::Started, this, &AGalagaArcadeCharacter::WeaponSlot2);
		EnhancedInputComponent->BindAction(WeaponSlot3Action, ETriggerEvent::Started, this, &AGalagaArcadeCharacter::WeaponSlot3);
	}
}
void AGalagaArcadeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
void AGalagaArcadeCharacter::Shoot()
{
	//if (!GetWorldTimerManager().IsTimerActive(FireRateTimer))
	//{
	//	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AGalagaArcadeCharacter::TimerElapsed, FireRate, false);
	//	TimerFinished();
	//}

	if (FireRateTimer <= 0)
	{
		//UE_LOGFMT(LogTemp, Warning, "Shoot");
		FireRateTimer = FireRate;
		FTransform VFXSpawn = FTransform(this->GetActorRotation(), this->GetActorLocation(), FVector(1.f, 1.f, 1.f));
		for (int i = 1; i <= NumberOfGuns; i++)
		{
			FString Str = "WeaponSocket";
			FName WeaponSocket = FName(*Str.Append(FString::FromInt(i)));
			FVector WeaponSocketLocation = GetMesh()->GetSocketLocation(WeaponSocket);
			if (GetMesh()->DoesSocketExist(WeaponSocket))
			{
				if (StructBulletTypes[BulletTypeSwitcher].AmmoAmount > 0 && StructBulletTypes[BulletTypeSwitcher].StructBulletType != BulletTypeVar)
				{
					FTransform SpawnLocation(GetActorRotation(), WeaponSocketLocation, GetActorScale());
					GetWorld()->SpawnActor<AActor>(StructBulletTypes[BulletTypeSwitcher].Bullet, SpawnLocation);
					StructBulletTypes[BulletTypeSwitcher].AmmoAmount = StructBulletTypes[BulletTypeSwitcher].AmmoAmount - 1;
					//UE_LOGFMT(LogTemp, Warning, "Ammo Remaining: {0}", StructBulletTypes[BulletTypeSwitcher].AmmoAmount);
					VFXSpawn = FTransform(this->GetActorRotation(), GetMesh()->GetSocketLocation(WeaponSocket), FVector(1.f, 1.f, 1.f));
					ShootEvent(VFXSpawn, WeaponSocket);
				}
				else if (StructBulletTypes[BulletTypeSwitcher].StructBulletType == BulletTypeVar)
				{
					FTransform SpawnLocation(GetActorRotation(), WeaponSocketLocation, GetActorScale());
					GetWorld()->SpawnActor<AActor>(StructBulletTypes[BulletTypeSwitcher].Bullet, SpawnLocation);
					VFXSpawn = FTransform(this->GetActorRotation(), GetMesh()->GetSocketLocation(WeaponSocket), FVector(1.f, 1.f, 1.f));
					ShootEvent(VFXSpawn, WeaponSocket);
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}
void AGalagaArcadeCharacter::SetUpShipLayout()
{
	GetMesh()->SetSkeletalMeshAsset(StructShipLayout[CurrentShipLayout].ShipMesh);
	NumberOfGuns = StructShipLayout[CurrentShipLayout].NumberOfGuns;
	BulletSpeed = StructShipLayout[CurrentShipLayout].BaseBulletSpeed;
	UpdateStats();
	CurrentHealth = MaxHealth;
	if (WidgetInstance != nullptr && WidgetInstance->GetWB_PlayerHealth() != nullptr)
	{
		WidgetInstance->GetWB_PlayerHealth()->UpdateHealth(CurrentHealth, MaxHealth);
		//UE_LOGFMT(LogTemp, Warning, "Health set up");
	}
	else
	{
		UE_LOGFMT(LogTemp, Warning, "WidgetInstance is NULL");
	}
}
void AGalagaArcadeCharacter::UpdateStats()
{
	MaxHealth = StructShipLayout[CurrentShipLayout].BaseHealth + BuffHealthModifier;
	CurrentHealth += BuffHealthModifier;
	Damage = StructShipLayout[CurrentShipLayout].BaseDamage + BuffDamageModifer;
	FireRate = FMath::Clamp(StructShipLayout[CurrentShipLayout].BaseFireRate - (StructShipLayout[CurrentShipLayout].BaseFireRate * BuffFireRateModifer), 0.01f, 10000.f);
	//UE_LOGFMT(LogTemp, Warning, "Health: {0}", Health);
	//UE_LOGFMT(LogTemp, Warning, "Damage: {0}", Damage);
	//UE_LOGFMT(LogTemp, Warning, "FireRate: {0}", FireRate);
}
void AGalagaArcadeCharacter::UpdateBuffs(TArray<struct FBuffBaseStruct> Buff)
{
	BuffHealthModifier = 0;
	BuffDamageModifer = 0;
	BuffFireRateModifer = 0;
	for (int i = 0; i < Buff.Num(); i++)
	{
		if (Buff.IsValidIndex(i))
		{
			for (int j = 0; j < Buff[i].Stats.Num(); j++)
			{
				if (Buff[i].Stats.IsValidIndex(j))
				{
					switch (Buff[i].Stats[j].EnumBuffs)
					{
					case Buffs::Health:
						BuffHealthModifier = BuffHealthModifier + Buff[i].Stats[j].BuffValue;
						break;
					case Buffs::Damage :
						BuffDamageModifer = BuffDamageModifer + Buff[i].Stats[j].BuffValue;
						break;
					case Buffs::FireRate:
						BuffFireRateModifer = BuffFireRateModifer + Buff[i].Stats[j].BuffValue;
						break;
					}
				}
			}
		}
	}
	//UE_LOGFMT(LogTemp, Warning, "BuffHealthModifer: {0}",	BuffHealthModifier);
	//UE_LOGFMT(LogTemp, Warning, "BuffDamageModifer: {0}",	BuffDamageModifer);
	//UE_LOGFMT(LogTemp, Warning, "BuffFireRateModifer: {0}", BuffFireRateModifer);
	UpdateStats();
}
void AGalagaArcadeCharacter::WeaponSlot1()
{
	/*FString BulletTypeName;
	UEnum::GetValueAsString(BulletTypeVar, BulletTypeName);
	UE_LOGFMT(LogTemp, Warning, "Weapon Slot 1: {0}", BulletTypeName);*/
	if (BulletsAvaliable >= 1)
	{
		BulletTypeSwitcher = WeaponSelection1;
	}
}
void AGalagaArcadeCharacter::WeaponSlot2()
{
	if (BulletsAvaliable >= 2)
	{
		BulletTypeSwitcher = WeaponSelection2;
	}
}
void AGalagaArcadeCharacter::WeaponSlot3()
{
	if (BulletsAvaliable >= 3)
	{
		BulletTypeSwitcher = WeaponSelection3;
	}
}
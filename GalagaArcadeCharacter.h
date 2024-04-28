// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Structs.h"
#include "Enums.h"
#include "..\..\Source\GalagaArcade\ProjectileBullets.h"
#include "..\..\Source\GalagaArcade\MainUIWidget.h"
#include "GalagaArcadeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS(config=Game)
class AGalagaArcadeCharacter : public ACharacter
{
	GENERATED_BODY()

	/* Camera boom positioning the camera behind the character*/ 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/* Follow camera*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	//Shoot
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	//Weapon Swapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponSlot1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponSlot2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WeaponSlot3Action;

public:
	AGalagaArcadeCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Shoot();


	UFUNCTION()
	void WeaponSlot1();
	
	UFUNCTION()
	void WeaponSlot2();

	UFUNCTION()
	void WeaponSlot3();

	UFUNCTION()
	void SetUpShipLayout();

	UFUNCTION()
	void UpdateStats();

#pragma region BlueprintImplementableEvents

	UFUNCTION(BlueprintImplementableEvent)
	void ShootEvent(FTransform VFXSpawnTransform, FName SocketName);

#pragma endregion

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	void Tick(float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	UPROPERTY()
	class APlayer_Controller* Player_Controller;

	UPROPERTY()
	FVector mouseLocation = FVector(0.f, 0.f, 0.f);

	UPROPERTY()
	FVector mouseDirection = FVector(0.f, 0.f, 0.f);

	UPROPERTY()
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerStats)
	const TSubclassOf<class AProjectileBullets>Bullet;
	
	UPROPERTY(BlueprintReadOnly, Category = PlayerStats)
	float FireRate = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = PlayerStats)
	int NumberOfGuns = 1;

	UPROPERTY(BlueprintReadOnly, Category = PlayerStats)
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadOnly, Category = PlayerStats)
	float CurrentHealth = 100.f;

	UPROPERTY(BlueprintReadOnly, Category = PlayerStats)
	float Damage = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = PlayerStats)
	float BulletSpeed = 0.f;

	UPROPERTY()
	float BuffHealthModifier = 0.f;

	UPROPERTY()
	float BuffDamageModifer = 0.f;

	UPROPERTY()
	float BuffFireRateModifer = 0.f;

	UPROPERTY()
	float FireRateTimer = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerStats)
	TArray<struct FShipLayout> StructShipLayout;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerStats)
	TArray<struct FBulletTypes> StructBulletTypes;

	UPROPERTY()
	BulletType BulletTypeVar = BulletType::NormalBullet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<UUserWidget> MainWidgetUI = nullptr;

	UPROPERTY()
	int CurrentShipLayout = 0;

	UPROPERTY()
	int BulletTypeSwitcher = 0;

	UPROPERTY(BlueprintReadOnly, Category = Tracker)
	int WeaponSelection1 = 0;

	UPROPERTY(BlueprintReadOnly, Category = Tracker)
	int WeaponSelection2 = 1;

	UPROPERTY(BlueprintReadOnly, Category = Tracker)
	int WeaponSelection3 = 4;

	UPROPERTY(BlueprintReadOnly, Category = Tracker)
	int BulletsAvaliable = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	struct FBuffBaseStruct BuffStats;

public:

	void UpdateBuffs(TArray<struct FBuffBaseStruct> Buff);

	UPROPERTY()
	class UMainUIWidget* WidgetInstance;

	const float							GetDamage()						const { return Damage; }
	const float							GetBulletSpeed()				const { return BulletSpeed; }
	const TArray<struct FBulletTypes>	GetStructBulletTypes()			const { return StructBulletTypes; }
	const int							GetBulletTypeSwitcher()			const { return BulletTypeSwitcher; }
	const int							GetWeaponSelection1()			const { return WeaponSelection1; }
	const int							GetWeaponSelection2()			const { return WeaponSelection2; }
	const int							GetWeaponSelection3()			const { return WeaponSelection3; }
	const int							GetBulletsAvaliable()			const { return BulletsAvaliable; }
	const FVector						GetMouseLocation()				const { return mouseLocation; }
	const FVector						GetMouseDirection()				const { return mouseDirection; }
	const float							GetMaxHealth()					const { return MaxHealth; }
	const float							GetCurrentHealth()				const { return CurrentHealth; }
};


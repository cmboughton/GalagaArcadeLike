// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Structs.h"
#include "Logging/StructuredLog.h"
#include "SpawnPoints.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCharacter = Cast<AGalagaArcadeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	++CurrentWave;
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Enemy Spawning Condition Checks
	if (EnemySpawnerConditions.IsValidIndex(CurrentWave - 1) && WaveTracker < CurrentWave)
	{
		if (EnemySpawnerConditions[CurrentWave - 1].EnemyCountChecker.TotalEnemyAmount > 0)
		{
			if (EnemySpawnerConditions[CurrentWave - 1].SpawnDelay <= 0)
			{
				FoundActors.Empty();
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCharacter::StaticClass(), FoundActors);

				switch (EnemySpawnerConditions[CurrentWave - 1].EnemyCountChecker.EnemyCountCheck)
				{
				case LessThanorGreaterThanType::LessThanOrEqual:
					if (FoundActors.Num() <= EnemySpawnerConditions[CurrentWave - 1].EnemyCountChecker.TotalEnemyAmount)
					{
						StartSpawning(CurrentWave - 1);
						++WaveTracker;
					}
					break;

				case LessThanorGreaterThanType::GreaterThanorEqual:
					if (FoundActors.Num() >= EnemySpawnerConditions[CurrentWave - 1].EnemyCountChecker.TotalEnemyAmount)
					{
						StartSpawning(CurrentWave - 1);
						++WaveTracker;
					}
					break;
				}
			}
			else
			{
				EnemySpawnerConditions[CurrentWave - 1].SpawnDelay -= DeltaTime;
				//UE_LOGFMT(LogTemp, Warning, "Timer Remaining {0}", EnemySpawnerConditions[CurrentWave - 1].SpawnDelay);
			}
		}
		else
		{
			if (EnemySpawnerConditions[CurrentWave - 1].SpawnDelay <= 0)
			{
				StartSpawning(CurrentWave - 1);
				++WaveTracker;
				UE_LOGFMT(LogTemp, Warning, "WaveSpawned: {0}", CurrentWave - 1);
			}
			else
			{
				EnemySpawnerConditions[CurrentWave - 1].SpawnDelay -= DeltaTime;
				//UE_LOGFMT(LogTemp, Warning, "Timer Remaining {0}", EnemySpawnerConditions[CurrentWave - 1].SpawnDelay);
			}
		}	
	}
}

//Start the Spawning of Enemies within the FStruct EnemySpawnerConditions 
void AEnemySpawner::StartSpawning(int EnemySpawnerIndex)
{
	if (EnemySpawnerConditions.IsValidIndex(EnemySpawnerIndex))
	{
		for (int i = 0; i < EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner.Num(); i++)
		{
			if (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner.IsValidIndex(i))
			{
				for (int j = 0; j < EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnAmount; j++)
				{
					if (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].EnemyCharacter != nullptr)
					{
						// Create a Random Point in the Spawn Array for the Random Array Spawn
						int RandomPoint = FMath::RandRange(0, (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints.Num() - 1));

						// Create Random Location for the Random Spawner
						FVector RandomSpawnLocation = GetRandomPointNearOrigin(PlayerCharacter->GetActorLocation(), 1500.f, 2000.f);
						FTransform RandomSpawnTransform = FTransform(FRotator(0.f, 0.f, 0.f), FVector(RandomSpawnLocation), FVector(1.f, 1.f, 1.f));

						//Switch Based on the Selection of the Spawning Location Determined by the Enemy Spawner Array in the Blueprint
						switch (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawningLocation)
						{
						//// Spawn an Enemy at the First index in the Spawn Points Array
						//case SpawningType::SingleSpawnPoint:

						//	// Check if the Spawn Point is Valid
						//	if (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints.IsValidIndex(0))
						//	{
						//		FTransform SpawnPointTransform = FTransform (FRotator (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints[0]->GetActorRotation()), FVector (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints[0]->GetActorLocation().X, EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints[0]->GetActorLocation().Y, PlayerCharacter->GetActorLocation().Z), FVector (1.f, 1.f, 1.f));
						//		SpawnEnemy(EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].EnemyCharacter, SpawnPointTransform);
						//		//UE_LOGFMT(LogTemp, Warning, "EnemySpawned at SpawnPoint[0]");
						//		break;
						//	}
						//	else
						//	{
						//		//Randomly Spawn the Enemy if the Spawn Point is InValid.
						//		SpawnEnemy(EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].EnemyCharacter, RandomSpawnTransform);
						//		UE_LOGFMT(LogTemp, Warning, "EnemySpawner[{0}].SpawnPoints[0] is InValid. Enemy Spawned at a RandomLocation Instead.", EnemySpawnerIndex);
						//		break;
						//	}

						//Spawn an Enemy at a Random Point in the Spawn Points Array
						case SpawningType::RandomSpawnPoint:


							// Check if the Spawn Point is Valid
							if (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints.IsValidIndex(RandomPoint))
							{
								FTransform SpawnPointTransform = FTransform (FRotator (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints[RandomPoint]->GetActorRotation()), FVector (EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints[RandomPoint]->GetActorLocation().X, EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].SpawnPoints[RandomPoint]->GetActorLocation().Y, PlayerCharacter->GetActorLocation().Z), FVector (1.f, 1.f, 1.f));
								SpawnEnemy(EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].EnemyCharacter, SpawnPointTransform);
								//UE_LOGFMT(LogTemp, Warning, "EnemySpawned at SpawnPoint[{0}]", RandomPoint);
								break;
							}
							else
							{
								//Randomly Spawn the Enemy if the Spawn Point is InValid.
								SpawnEnemy(EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].EnemyCharacter, RandomSpawnTransform);
								UE_LOGFMT(LogTemp, Warning, "EnemySpawner[{0}].SpawnPoints[{1}] is InValid. Enemy Spawned at a RandomLocaiton Instead", EnemySpawnerIndex, RandomPoint);
								break;
							}

						// Randomly Spawn an Enemy outside of the Players Vision
						case SpawningType::RandomLocationSpawn:

							SpawnEnemy(EnemySpawnerConditions[EnemySpawnerIndex].WaveSpawner[i].EnemyCharacter, RandomSpawnTransform);
							break;
						}
					}
				}
			}
		}
		++CurrentWave;
	}
}

//Spawn Enemy at given Transform
void AEnemySpawner::SpawnEnemy(TSubclassOf<class AEnemyCharacter> EnemyCharacter, FTransform SpawnTransform)
{
	GetWorld()->SpawnActor<AActor>(EnemyCharacter, SpawnTransform);
}

// Function to get a random FVector within a certain distance range from an origin point
FVector AEnemySpawner::GetRandomPointNearOrigin(const FVector& Origin, float MinDistance, float MaxDistance)
{
	// Create a random stream for generating random values
	FRandomStream RandStream(FMath::Rand());

	// Generate a random direction vector with a random magnitude
	FVector RandomDirection = RandStream.VRand().GetSafeNormal() * RandStream.FRandRange(MinDistance, MaxDistance);

	FVector RandomPoint = FVector (Origin.X + RandomDirection.X, Origin.Y + RandomDirection.Y, Origin.Z);

	while (FVector::DistSquared(Origin, RandomPoint) < MinDistance * MinDistance)
	{
		RandomDirection = RandStream.VRand().GetSafeNormal() * RandStream.FRandRange(MinDistance, MaxDistance);
		RandomPoint = FVector(Origin.X + RandomDirection.X, Origin.Y + RandomDirection.Y, Origin.Z);
	}

	//UE_LOGFMT(LogTemp, Warning, "Random EnemySpawned at {0}", RandomPoint.Z);
	return RandomPoint;
}
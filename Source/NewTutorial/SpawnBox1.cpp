// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBox1.h"

// Sets default values
ASpawnBox1::ASpawnBox1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;*/
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnBox1::BeginPlay()
{
	Super::BeginPlay();

	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}
	
}

void ASpawnBox1::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Remove all timers associated with this objects instance
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

bool ASpawnBox1::SpawnActor()
{
	bool SpawnedActor = false;
	if (ActorClassToBeSpawned)
	{
		// Calculate the extends of the box
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		// Compute a random position within the box bounds
		FVector SpawnLocation = BoxBounds.Origin;
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();

		// Spawn the actor
		SpawnedActor = GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation) != nullptr;
	}

	return SpawnedActor;
}

void ASpawnBox1::EnableActorSpawning(bool Enable)
{
	ShouldSpawn = Enable;

	// Check witch timer action should be done
	if (Enable)
	{
		ScheduleActorSpawn();
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void ASpawnBox1::ScheduleActorSpawn()
{
	// 1. Compute time offset to spawn
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());

	// 2. Schedule spawning
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnBox1::SpawnActorScheduled, DeltaToNextSpawn, false);
}

void ASpawnBox1::SpawnActorScheduled()
{
	/*SpawnActor();
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}*/
	if (SpawnActor())
	{
		if (ShouldSpawn)
		{
			ScheduleActorSpawn();
		}
	}
	else {

	}
}





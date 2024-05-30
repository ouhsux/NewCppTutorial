// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

#include "SpawnBox1.generated.h"

UCLASS()
class NEWTUTORIAL_API ASpawnBox1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnBox1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool SpawnActor();
	//void ScheduleActorSpawn();

	UFUNCTION(BlueprintCallable)
	void EnableActorSpawning(bool Enable);
private:
	UFUNCTION()
	void SpawnActorScheduled();

	// Will schedule an actor spawn 
	void ScheduleActorSpawn();

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;
	// Average time between spawns (without random)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 5.f;

	// Random +/- offset of the spawn time
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 1.f;

private:

	UPROPERTY(EditAnywhere)
	bool ShouldSpawn = true;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* SpawnBox;

	FTimerHandle SpawnTimerHandle;
};

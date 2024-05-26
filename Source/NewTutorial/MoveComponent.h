// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEWTUTORIAL_API UMoveComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	friend class FMoveComponentVisualizer;
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;
	UPROPERTY(EditAnywhere)
	float speed = 1.0f;

	FVector StartRelativeLocation;
	FVector MoveOffsetNorm;
	float MaxDis;
	int MoveDirection = 1;
	float CurDis;
		
};

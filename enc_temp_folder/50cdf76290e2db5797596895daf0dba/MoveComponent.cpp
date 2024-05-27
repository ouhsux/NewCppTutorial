// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMoveComponent::EnableMovement(bool ShouldMove)
{
	// Assign value and set correct tick enable state
	MoveEnable = ShouldMove;
	SetComponentTickEnabled(MoveEnable);
}

void UMoveComponent::ResetMovement()
{	
	CurDis = 0.0f;
	SetRelativeLocation(StartRelativeLocation);
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	StartRelativeLocation = this->GetRelativeLocation();
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();
	MaxDis = MoveOffset.Length();

	SetComponentTickEnabled(MoveEnable); 
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//if (MoveEnable)
	//{
	//	
	//}
	//CurDis += speed * DeltaTime * MoveDirection;
	//if (CurDis >= MaxDis || CurDis <= 0.0f)
	//	MoveDirection *= -1;

	if (MoveEnable)
	{
		CurDis += DeltaTime * speed * MoveDirection;
		if (CurDis >= MaxDis|| CurDis <= 0.0f)
		{
			// Invert direction
			MoveDirection *= -1;

			// Fire event
			OnEndpointReached.Broadcast(CurDis >= MaxDis);

			// Clamp distance
			CurDis= FMath::Clamp(CurDis, 0.0f, MaxDis);
		}
	}
	SetRelativeLocation(CurDis * MoveOffsetNorm + StartRelativeLocation);
}


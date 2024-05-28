// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCollectableActor.h"

// Sets default values
AMyCollectableActor::AMyCollectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	// Create collision box
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
}

// Called when the game starts or when spawned
void AMyCollectableActor::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);

	SetActorTickEnabled(false);
}
void AMyCollectableActor::OnComponentBeginlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Islaunched && OtherActor->IsA(TriggerClass))
	{
		OnJumpTrigger.Broadcast(OtherActor, Component);
	}
	/*if (OtherActor->IsA())
	{
		Jump(5.0f);
	}*/
}
void AMyCollectableActor::Jump(float velocity)
{
	if (!Islaunched)
	{
		StaticMesh->AddImpulse({ .0f,.0f,velocity * 500.f });

		SetActorTickEnabled(true);
		Islaunched = true;
	}
}
// Called every frame
void AMyCollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Islaunched)
	{
		// Decrement lifetime
		Livetime -= DeltaTime;

		// Check actor destruction
		if (Livetime <= 0.f)
		{
			Destroy();
		}
	}

}


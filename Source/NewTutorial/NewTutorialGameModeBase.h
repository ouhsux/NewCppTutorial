// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "XPCharacter.h"
#include "GameFramework/DefaultPawn.h"

#include "NewTutorialGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class NEWTUTORIAL_API ANewTutorialGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	void InitGameState() override;
private:
	UPROPERTY(EditAnywhere,NoClear)
	TSubclassOf<AXPCharacter> CustomXPPawnClass = AXPCharacter::StaticClass();
};

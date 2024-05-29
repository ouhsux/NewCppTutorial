// Fill out your copyright notice in the Description page of Project Settings.


#include "NewTutorialGameModeBase.h"



void ANewTutorialGameModeBase::InitGameState()
{
    //if (DefaultPawnClass == ADefaultPawn::StaticClass() || !DefaultPawnClass)
    //{
    //    // Update to custom implementation
    //    DefaultPawnClass = CustomXPCharacterClass;
    //} 
    Super::InitGameState();
    if (DefaultPawnClass == ADefaultPawn::StaticClass() )
    {
        // Update to custom implementation
        DefaultPawnClass = CustomXPPawnClass;
    }
}

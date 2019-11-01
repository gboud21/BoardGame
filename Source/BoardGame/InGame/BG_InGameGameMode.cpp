// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_InGameGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "InGame/Player/BG_InGamePlayerController.h"

ABG_InGameGameMode::ABG_InGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Player/Character/BP_ShooterCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerControllerClass = ABG_InGamePlayerController::StaticClass();

}

void ABG_InGameGameMode::InitGame()
{

}

AActor * ABG_InGameGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	return nullptr;
}


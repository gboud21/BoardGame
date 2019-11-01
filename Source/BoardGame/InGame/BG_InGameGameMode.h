// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BG_InGameGameMode.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class BOARDGAME_API ABG_InGameGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:
	int x;


protected:
	float MinRespawnDelay = 1.0f;

	float TimeBetweenObjectives = 500.f;

	int ObjectiveWinsToWin = 3;
	int MaxObjectives = 5;

	
private:
	//Initialize the Match
	virtual void InitGame();

	//Select the best spawn point for a player
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BG_LobbyGameMode.h"
#include "BG_LobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API ABG_LobbyGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ABG_LobbyGameState();

	FString GetSessionName();
	void SetSessionName(FString sessionName);
	
	UFUNCTION()
		virtual void OnRep_UpdateGameSettings();

	UPROPERTY(Replicated)
	FString SessionName;

	//UPROPERTY(Replicated)
	UPROPERTY(ReplicatedUsing = OnRep_UpdateGameSettings)
	FBG_GameSettings GameSettings;

private:
	
	
};

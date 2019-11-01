// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "EngineUtils.h"
#include "BoardGameInstance.h"
//#include "BG_LobbyPlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "BG_LobbyGameMode.generated.h"

/**
 * 
 */

class BG_LobbyPlayerController;

USTRUCT()
struct FBG_GameSettings {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString SessionName;

	UPROPERTY()
	FString MaxTurns;

	UPROPERTY()
	FString GameSpeed;

	UPROPERTY()
	FString MapName;

	UPROPERTY()
	FString TurnSpeed;

	UPROPERTY()
	FString ResourceLevel;

	UPROPERTY()
	FString AlienHostility;
};

USTRUCT()
struct FBG_PlayerInfo {
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool bPlayerReadyState;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	FString SelectedFaction;
};

UCLASS()
class BOARDGAME_API ABG_LobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ABG_LobbyGameMode();

	/******************************************************************************************************
	Network Functions
	******************************************************************************************************/
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* ExitingPlayer) override;

	void KickPlayer(int32 PlayerIndex);
	
	/******************************************************************************************************
	Init Functions
	******************************************************************************************************/

	/******************************************************************************************************
	Public Update Functions
	******************************************************************************************************/
	void LGM_PlayerRequestUpdate();
	void LGM_PlayerRequestUpdate(FString faction);

	void UpdatePlayerList();
	void UpdatePlayerList(class ABG_LobbyPlayerController* pController, FString faction);

	void LGM_UpdateSessionName(FText sessionName);
	void LGM_UpdateSetting(FString widgetName, FString setting);

	void LGM_UpdateGameSettings();
	/******************************************************************************************************
	Lobby Chat Functions
	******************************************************************************************************/
	void DistributeChat(FString chatText);

private:
	/******************************************************************************************************
	Init Functions
	******************************************************************************************************/		
	void InitGameSettings();

	void InitPlayerStarts();
	/******************************************************************************************************
	Init Variables
	******************************************************************************************************/
	//UBoardGameInstance* MyGameInstance;

	//TMap<int32, ABG_LobbyPlayerController*> AllPlayerControllers;

	TArray<class ABG_LobbyPlayerController*> PcArray;

	TArray<struct FBG_PlayerInfo> PlayerInfoArray;

	TArray<APlayerStart*> AllPlayerStarts;
	
	TArray<FString> Factions = { "Space Marines",
								"Stormtroopers",
								"Rebel Scum",
								"Chaos",
								"Sneks",
								"TB12" };

	int32 MaxNumberOfPlayers = 6;

	FBG_GameSettings GameSettings_t;
};

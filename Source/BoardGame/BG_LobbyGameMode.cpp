// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyGameMode.h"
#include "BG_LobbyPawn.h"
#include "BG_LobbyPlayerController.h"
#include "UI/BG_LobbyMenu.h"
#include "math.h"
#include "Lobby/BG_LobbyPlayerState.h"
#include "Lobby/BG_LobbyGameState.h"
#include "Runtime/Engine/Public/TimerManager.h"


#define Log(x) UE_LOG(LogTemp,Warning,TEXT(x))



ABG_LobbyGameMode::ABG_LobbyGameMode() :Super() {
	PlayerStateClass = ABG_LobbyPlayerState::StaticClass();
	GameStateClass = ABG_LobbyGameState::StaticClass();
	bReplicates = true;

	GameSettings_t.AlienHostility = "Normal";
	GameSettings_t.GameSpeed = "Normal";
	GameSettings_t.MapName = "Classic";
	GameSettings_t.MaxTurns = "7";
	GameSettings_t.ResourceLevel = "Normal";
	GameSettings_t.SessionName = "Custom Match";
	GameSettings_t.TurnSpeed = "Normal";
}

/******************************************************************************************************
Public Network Functions
******************************************************************************************************/
void ABG_LobbyGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	Log("LGM 1: Post Login");
	ABG_LobbyPlayerController* JoiningPlayer = Cast<ABG_LobbyPlayerController>(NewPlayer);
	JoiningPlayer->LPC_SetBG_LobbyPlayerState(Cast<ABG_LobbyPlayerState>(JoiningPlayer->PlayerState));

	if (JoiningPlayer) {
		Log("LGM 2: Added Player");
		PcArray.Add(JoiningPlayer);

		//create array to see what player indexes are available
		TArray<bool> playerIndexAvailable;
		for (int j = 0; j < 7; j++) {
			playerIndexAvailable.Add(true);
		}

		//set the player index to false if a player already is at that index
		for (int playerIndex = 0; playerIndex < PcArray.Num(); playerIndex++) {
			if (PcArray[playerIndex]) {
				ABG_LobbyPlayerState* pState = Cast<ABG_LobbyPlayerState>(PcArray[playerIndex]->PlayerState);
				if (pState) {
					playerIndexAvailable[pState->PlayerNumber] = false;
					Log("LGM 10: Post Login pstate passed");
				}
				else {
					Log("LGM 10: Post Login pstate failed");
				}
			}
		}

		//assign the player to the first available index
		for (int32 playerIndex = 0; playerIndex < playerIndexAvailable.Num(); playerIndex++) {
			if (playerIndexAvailable[playerIndex]) {
				ABG_LobbyPlayerState* pState = Cast<ABG_LobbyPlayerState>(JoiningPlayer->PlayerState);
				if (pState) {
					pState->PlayerNumber = playerIndex;
					Log("LGM 11:  pstate passed");
					break;
				}
				else {
					Log("LGM 11: No pstate yet");
				}
			}
		}

	}
	else {
		Log("LGM 2: Joining Player Failed");
	}

	//InitPlayerStarts();
}

void ABG_LobbyGameMode::Logout(AController * ExitingPlayer)
{
	Super::Logout(ExitingPlayer);
	ABG_LobbyPlayerController* pc = Cast<ABG_LobbyPlayerController>(ExitingPlayer);
	if (pc) {
		PcArray.Remove(pc);
		UpdatePlayerList();
	}
}

void ABG_LobbyGameMode::KickPlayer(int32 PlayerIndex)
{
	for (int32 pIndex = 0; pIndex < PcArray.Num(); pIndex++) {
		ABG_LobbyPlayerState* pState = Cast<ABG_LobbyPlayerState>(PcArray[pIndex]->PlayerState);
		if (pState && pState->PlayerNumber == PlayerIndex) {
			//boot player
			PcArray[PlayerIndex]->LPC_Client_KickPlayer();
			break;
		}
	}
}

/******************************************************************************************************
Public Update Functions
******************************************************************************************************/
void ABG_LobbyGameMode::LGM_PlayerRequestUpdate()
{
	UpdatePlayerList();
}

void ABG_LobbyGameMode::LGM_PlayerRequestUpdate(FString faction)
{

	UpdatePlayerList();
}

void ABG_LobbyGameMode::UpdatePlayerList()
{
	Log("LGM 3: Update Player List");
	PlayerInfoArray.Empty();

	//get all the lobby player info vars

	for (ABG_LobbyPlayerController* pc : PcArray) {
		FBG_PlayerInfo tempPlayerInfo;

		ABG_LobbyPlayerState* pState = Cast<ABG_LobbyPlayerState>(pc->PlayerState);

		if (pState) {
			tempPlayerInfo.bPlayerReadyState = pState->bIsReady;
			tempPlayerInfo.SelectedFaction = pState->GetSelectedFaction();
		}
		else {
			tempPlayerInfo.bPlayerReadyState = false;
			tempPlayerInfo.SelectedFaction = "Random";
		}

		tempPlayerInfo.PlayerName = pc->PlayerState->PlayerName;
		UE_LOG(LogTemp, Warning, TEXT("Player Name: %s"), *(tempPlayerInfo.PlayerName));
		PlayerInfoArray.Add(tempPlayerInfo);
	}

	for (ABG_LobbyPlayerController* pc : PcArray) {
		pc->LPC_Client_UpdatePlayerList(PlayerInfoArray);
	}
}

void ABG_LobbyGameMode::UpdatePlayerList(class ABG_LobbyPlayerController* pController, FString faction)
{
	Log("LGM 4: Update Player List Faction Overload");
	PlayerInfoArray.Empty();

	//get all the lobby player info vars

	if (NULL != pController) {
		Log("LGM 6: Update Player List Faction Overload pController Not Null");
	}
	else {
		Log("LGM 6: Update Player List Faction Overload pController  Null");

	}
	for (class ABG_LobbyPlayerController* pc : PcArray) {
		FBG_PlayerInfo tempPlayerInfo;

		ABG_LobbyPlayerState* pState = Cast<ABG_LobbyPlayerState>(pc->PlayerState);

		if (pState) {
			tempPlayerInfo.bPlayerReadyState = pState->bIsReady;
			if (pc == pController) {
				Log("LGM 5: UpdatePlayerList pc found");
				pState->SetSelectedFaction(faction);
			}
			tempPlayerInfo.SelectedFaction = pState->GetSelectedFaction();
		}
		else {
			tempPlayerInfo.bPlayerReadyState = false;
			tempPlayerInfo.SelectedFaction = "Random";
		}

		tempPlayerInfo.PlayerName = pc->PlayerState->PlayerName;
		PlayerInfoArray.Add(tempPlayerInfo);
	}

	for (ABG_LobbyPlayerController* pc : PcArray) {
		pc->LPC_Client_UpdatePlayerList(PlayerInfoArray);
	}
}

void ABG_LobbyGameMode::LGM_UpdateSessionName(FText sessionName)
{
	Log("LGM: Update Session Name Begin");
	GameSettings_t.SessionName = sessionName.ToString();
	ABG_LobbyGameState* gState = Cast<ABG_LobbyGameState>(GetWorld()->GetGameState());
	if (gState) {
		gState->GameSettings.SessionName = sessionName.ToString();
		gState->SessionName = sessionName.ToString();
	}
	else {
		Log("LGM: Update Session Name - Game State is Null");
	}

	LGM_UpdateGameSettings();
}

void ABG_LobbyGameMode::LGM_UpdateSetting(FString widgetName, FString setting)
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Name: %s"), *widgetName);
	if ("MaxTurnsSetting" == widgetName) {
		GameSettings_t.MaxTurns = setting;
	}
	else if ("MapSetting" == widgetName) {
		GameSettings_t.MapName = setting;
	}
	else if ("TurnSpeedSetting" == widgetName) {
		GameSettings_t.TurnSpeed = setting;
	}
	else if ("UnitResourcesSettings" == widgetName) {
		GameSettings_t.ResourceLevel = setting;
	}
	else {
		Log("LGM: Update Setting unknown widget error");
		return;
	}

	ABG_LobbyGameState* gState = Cast<ABG_LobbyGameState>(GetWorld()->GetGameState());
	if (gState) {
		gState->GameSettings = GameSettings_t;
		//FTimerHandle UpdateGameStateTimeHandler;
		//GetWorldTimerManager().SetTimer(UpdateGameStateTimeHandler, this, &ABG_LobbyGameMode::LGM_UpdateGameSettings, 0.1f, false);
		//LGM_UpdateGameSettings();
	}
}

void ABG_LobbyGameMode::LGM_UpdateGameSettings()
{
	Log("LGM 3: Update Game Settings");

	for (ABG_LobbyPlayerController* pc : PcArray) {
		pc->LPC_Client_UpdateLobbySettings();
	}

	UBoardGameInstance* gameInstance = Cast<UBoardGameInstance>(GetGameInstance());
	ABG_LobbyGameState* gState = Cast<ABG_LobbyGameState>(GetWorld()->GetGameState());
	if (gameInstance && gState) {
		gameInstance->UpdateSessionSettings(gState->GameSettings.SessionName, MaxNumberOfPlayers);
	}
}

/******************************************************************************************************
Lobby Chat Functions
******************************************************************************************************/
void ABG_LobbyGameMode::DistributeChat(FString chatText)
{
	for (class ABG_LobbyPlayerController* pc : PcArray) {
		pc->LPC_Client_ReceiveChat(chatText);
	}
}

/******************************************************************************************************
Private Init Functions
******************************************************************************************************/
void ABG_LobbyGameMode::InitGameSettings()
{
	GameSettings_t.SessionName = "New Board Game";
	GameSettings_t.MaxTurns = "7";
	GameSettings_t.MapName = "Classic";
	GameSettings_t.TurnSpeed = "Normal";
	GameSettings_t.ResourceLevel = "Normal";
}

void ABG_LobbyGameMode::InitPlayerStarts()
{
	for (TActorIterator<APlayerStart> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AllPlayerStarts.Add(*ActorItr);
	}
}

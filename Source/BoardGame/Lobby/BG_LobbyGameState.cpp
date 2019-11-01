// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyGameState.h"
#include "UnrealNetwork.h"
#include "BG_LobbyPlayerController.h"

ABG_LobbyGameState::ABG_LobbyGameState():Super() {
	SessionName = "CustomSession";
	GameSettings.SessionName = "CustomSession";
	GameSettings.AlienHostility = "Normal";
	GameSettings.GameSpeed = "Normal";
	GameSettings.MapName = "TestWorld";
	GameSettings.MaxTurns = "7";
	GameSettings.ResourceLevel = "Normal";
	GameSettings.TurnSpeed = "Normal";
}

FString ABG_LobbyGameState::GetSessionName()
{
	return SessionName;
}

void ABG_LobbyGameState::SetSessionName(FString sessionName)
{
	SessionName = sessionName;
}

void ABG_LobbyGameState::OnRep_UpdateGameSettings()
{
	ABG_LobbyPlayerController* pc = Cast<ABG_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc) {
		pc->LPC_Client_UpdateLobbySettings();
	}
}

void ABG_LobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABG_LobbyGameState, SessionName);
	DOREPLIFETIME(ABG_LobbyGameState, GameSettings);
}

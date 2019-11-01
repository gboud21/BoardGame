// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyPlayerState.h"
#include "BoardGameInstance.h"
#include "UnrealNetwork.h"

#define Log(x) UE_LOG(LogTemp,Warning,TEXT(x))


ABG_LobbyPlayerState::ABG_LobbyPlayerState() : Super(){
	bIsReady = false;
	SelectedFaction = "Random";
	PlayerName;
	//ChangePlayerName();
}

void ABG_LobbyPlayerState::BeginPlay()
{
	Super::BeginPlay();

	//change player name to the name in the game isntance if it is on lan
	ChangePlayerName();

	//UpdatePlayer("Random");
}

void ABG_LobbyPlayerState::ChangePlayerName()
{

	if(Role == ROLE_Authority){
		
		UBoardGameInstance* MyGameInstance = Cast<UBoardGameInstance>(GetWorld()->GetGameInstance());

		if(MyGameInstance){
			FString ActualPlayerName = MyGameInstance->GetPlayerName();

			/*if(ActualPlayerName != ""){
				//set player name here
				SetPlayerName("Player");
			}*/

			if (PlayerName == "" && MyGameInstance->GetPlayerName() == "") {
				SetPlayerName("No One");
			}
		}
	}else{
		Server_ChangePlayerName();
	}
}

void ABG_LobbyPlayerState::Server_ChangePlayerName_Implementation()
{
	ChangePlayerName();
}

void ABG_LobbyPlayerState::UpdatePlayer(FString faction)
{
		if(Role == ROLE_Authority){
		
		UBoardGameInstance* MyGameInstance = Cast<UBoardGameInstance>(GetWorld()->GetGameInstance());

		if(MyGameInstance){
			FString ActualPlayerName = MyGameInstance->GetPlayerName();

			if(ActualPlayerName != ""){
				//set player name here
				//eventually change this to use player profile name
				SetPlayerName("Player");
			}
		}

		SetSelectedFaction(faction);
	}else{
		Server_UpdatePlayer(faction);
	}
}

void ABG_LobbyPlayerState::Server_UpdatePlayer_Implementation(const FString& faction)
{
	UpdatePlayer(faction);
}

void ABG_LobbyPlayerState::SetSelectedFaction(FString faction)
{
	SelectedFaction = faction;
}

FString ABG_LobbyPlayerState::GetSelectedFaction()
{
	return SelectedFaction;
}

void ABG_LobbyPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABG_LobbyPlayerState, bIsReady);
	DOREPLIFETIME(ABG_LobbyPlayerState, SelectedFaction);
	DOREPLIFETIME(ABG_LobbyPlayerState, PlayerNumber);
}
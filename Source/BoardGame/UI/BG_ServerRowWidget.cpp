// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_ServerRowWidget.h"
#include "BoardGameInstance.h"


void UBG_ServerRowWidget::InitializeServerRowWidget(FString sessionName, int32 sessionOpenPlayerCount, int32 sessionMaxPlayerCount, int32 sessionPing, int32 sessionIndex)
{
	SessionName = sessionName;
	SessionOpenPlayerCount = sessionOpenPlayerCount;
	SessionMaxPlayerCount = sessionMaxPlayerCount;
	SessionPing = sessionPing;
	SessionIndex = sessionIndex;
}


void UBG_ServerRowWidget::SetupServerRowWidget(UTextBlock * serverNameTextBlock, UTextBlock * playerCountTextBlock, UTextBlock * pingTextBlock)
{
	int32 currentPlayers = SessionMaxPlayerCount - SessionOpenPlayerCount;
	FString playerCount = FString::FromInt(currentPlayers).Append("/").Append(FString::FromInt(SessionMaxPlayerCount));
	
	serverNameTextBlock->SetText(FText::FromString(SessionName));
	playerCountTextBlock->SetText(FText::FromString(playerCount));
	pingTextBlock->SetText(FText::FromString(FString::FromInt(SessionPing)));
}

void UBG_ServerRowWidget::JoinGameOnClick()
{
	UBoardGameInstance* myGameInstance = Cast<UBoardGameInstance>(GetWorld()->GetGameInstance());
	if (myGameInstance) {
		UE_LOG(LogTemp, Warning, TEXT("Server Row On CLick: Game Instance is valid. Join Session."));
		myGameInstance->JoinGame(SessionIndex);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Server Row On CLick: Game Instance is not valid"));
	}
}
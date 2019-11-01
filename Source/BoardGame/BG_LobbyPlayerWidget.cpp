// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyPlayerWidget.h"
#include "BG_LobbyPlayerController.h"
#include "PanelWidget.h"


void UBG_LobbyPlayerWidget::LPW_InitializePlayerWidget(UTextBlock* playerNameText, UWidgetSwitcher* widgetSwitcher, UComboBoxString* comboBox, UTextBlock* factionTextBlock, UOverlay* factionTextOverlay, UButton* kickButton)
{
	PlayerNameTextWidget = playerNameText;
	SelectedFactionComboBoxWidget = comboBox;
	//SelectedFaction = "Random";
	FactionTextBlock = factionTextBlock;
	FactionWidgetSwitcher = widgetSwitcher;
	FactionTextOverlay = factionTextOverlay;
	KickButton = kickButton;
}

void UBG_LobbyPlayerWidget::LPW_UpdatePlayerWidget(const FString& playerName, const FString& faction)
{
	UE_LOG(LogTemp, Warning, TEXT("LPW_UpdateLobbyPlayerWidget"));

	//FText TextVariable = FText::AsCultureInvariant(playerName);
	PlayerNameTextWidget->SetText(FText::FromString(playerName));
	SelectedFactionComboBoxWidget->SetSelectedOption(faction);
	//TextVariable = FText::AsCultureInvariant(faction);
	FactionTextBlock->SetText(FText::FromString(faction));
}

void UBG_LobbyPlayerWidget::SetPlayerName(FString playerName) { PlayerName = playerName; }

void UBG_LobbyPlayerWidget::SetSelectedFaction(FString selectedFaction) { SelectedFaction = selectedFaction; }

void UBG_LobbyPlayerWidget::SetbIsPlayer(bool isPlayer)
{
	if (FactionWidgetSwitcher) {
		UE_LOG(LogTemp, Warning, TEXT("Faction widget enabled"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Faction widget not available"));
	}
	bIsPlayer = isPlayer;
	if (bIsPlayer) {
		FactionWidgetSwitcher->SetActiveWidget(SelectedFactionComboBoxWidget);
		if (FactionTextBlock) {
			UE_LOG(LogTemp, Warning, TEXT("LPW 1: setbisplayer true"));
		}
	}
	else {
		FactionWidgetSwitcher->SetActiveWidget(FactionTextOverlay);
		if (FactionTextBlock) {
			UE_LOG(LogTemp, Warning, TEXT("LPW 1: setbisplayer false"));
		}

	}
}

void UBG_LobbyPlayerWidget::LPW_UpdateFactionOnSelection(FString faction) {
	ABG_LobbyPlayerController* localPlayerController = Cast<ABG_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (faction == SelectedFaction) {
		return;
	}
	else if (faction == "Random") {
		//Update the faction to random
		SelectedFaction = faction;
		localPlayerController->UpdateFaction(localPlayerController, SelectedFaction);
	}
	else if(CheckFactionNotSelected(faction)){
		SelectedFaction = faction;
		localPlayerController->UpdateFaction(localPlayerController, SelectedFaction);
	}
}

void UBG_LobbyPlayerWidget::KickPlayer()
{
	int32 myIndex = GetParent()->GetChildIndex(this);
	ABG_LobbyPlayerController* pc = Cast<ABG_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (pc && pc->Role == ROLE_Authority) {
		ABG_LobbyGameMode* gm = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());
		if (gm) {
			gm->KickPlayer(myIndex);
		}
	}
}

bool UBG_LobbyPlayerWidget::CheckFactionNotSelected(FString faction)
{
	bool status = true;
	UPanelWidget* parentWidget = GetParent();
	for (int childIndex = 0; childIndex < parentWidget->GetChildrenCount(); childIndex++) {
		UBG_LobbyPlayerWidget* childLobbyPlayerWidget = Cast<UBG_LobbyPlayerWidget>(parentWidget->GetChildAt(childIndex));
		if (NULL != childLobbyPlayerWidget && faction == childLobbyPlayerWidget->SelectedFaction) {
			status = false;
			break;
		}
	}
	return status;
}

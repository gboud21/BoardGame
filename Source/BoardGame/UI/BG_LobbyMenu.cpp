// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyMenu.h"
#include "BG_LobbyPlayerWidget.h"
#include "BG_LobbyPlayerController.h"
#include "BG_LobbyGameMode.h"
#include "UI/BG_LobbyGameSettingsWidget.h"

void UBG_LobbyMenu::InitializeLobbyPlayerWindow(UButton* matchNameButton, UTextBlock* sessionText, UGridPanel* playerWindow, UGridPanel* settingsWindow, UBG_ChatWindow* chatWindow)
{
	ChangeMatchNameButton = matchNameButton;
	SessionNameTextBlock = sessionText;
	LobbyPlayerWindow = playerWindow;
	LobbyGameSettingsWindow = settingsWindow;
	ChatWindow = chatWindow;
}

void UBG_LobbyMenu::InitPlayerWidgetComboBox(int32 myPlayerIndex)
{
	for (int playerWidgetIndex = 0; playerWidgetIndex < LobbyPlayerWindow->GetChildrenCount(); playerWidgetIndex++) {
		UBG_LobbyPlayerWidget* tempWidget = Cast<UBG_LobbyPlayerWidget>(LobbyPlayerWindow->GetChildAt(playerWidgetIndex));
		if (tempWidget) {
			UE_LOG(LogTemp, Warning, TEXT("LM: InitPlayerWidgetComboBox widget available"));
			if (playerWidgetIndex == myPlayerIndex) {
					tempWidget->SetbIsPlayer(true);
			}
			else {
				tempWidget->SetbIsPlayer(false);
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("LM: InitPlayerWidgetComboBox widget unavailable"));
		}
	}
}

void UBG_LobbyMenu::InitDisableChangeMatchNameButton()
{
	ChangeMatchNameButton->SetVisibility(ESlateVisibility::Hidden);
	//ABG_LobbyPlayerController* myController = Cast<ABG_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());

}

void UBG_LobbyMenu::InitDisableGameSettingsSelection()
{
	for (int gsIndex = 0; gsIndex < LobbyGameSettingsWindow->GetChildrenCount(); gsIndex++) {
		UBG_LobbyGameSettingsWidget* gsWidget = Cast<UBG_LobbyGameSettingsWidget>(LobbyGameSettingsWindow->GetChildAt(gsIndex));
		if (gsWidget) {
			gsWidget->DisableSettingSelection();
		}
	}
}

void UBG_LobbyMenu::CommitUpdateSessionName(FText sessionName)
{
	ABG_LobbyPlayerController* myController = Cast<ABG_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (myController && myController->Role == ROLE_Authority) {
		ABG_LobbyGameMode* myGM = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());
		if (myGM) {
			myGM->LGM_UpdateSessionName(sessionName);
		}
	}
}

void UBG_LobbyMenu::UpdateSessionName(FText sessionName)
{
	if (SessionNameTextBlock) {
		SessionNameTextBlock->SetText(sessionName);
	}
}

void UBG_LobbyMenu::UpdateAlienHostility(FText setting)
{
}

void UBG_LobbyMenu::UpdateGameSpeed(FText setting)
{
}

void UBG_LobbyMenu::UpdateMap(FText setting)
{
	if (LobbyGameSettingsWindow) {
		UBG_LobbyGameSettingsWidget* gsWidget = Cast<UBG_LobbyGameSettingsWidget>(LobbyGameSettingsWindow->GetChildAt(EGameSettingsWidgets::MapSettings));
		if (gsWidget) {
			gsWidget->SetSettingWidget(setting.ToString());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("LM: Update Map - MAp Name Setting Widget is NULL"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LM: Update Map - Game Setting Window is NULL"));
	}
}

void UBG_LobbyMenu::UpdateMaxTurns(FText setting)
{
	UE_LOG(LogTemp, Warning, TEXT("Updating Setting 1"));
	if (LobbyGameSettingsWindow) {
		if (LobbyGameSettingsWindow) {
			UE_LOG(LogTemp, Warning, TEXT("Updating Setting 2"));
			UBG_LobbyGameSettingsWidget* gsWidget = Cast<UBG_LobbyGameSettingsWidget>(LobbyGameSettingsWindow->GetChildAt(EGameSettingsWidgets::MaxTurns));
			if (gsWidget) {
				UE_LOG(LogTemp, Warning, TEXT("Updating Setting 3"));
				gsWidget->SetSettingWidget(setting.ToString());
			}
		}
	}
}

void UBG_LobbyMenu::UpdateResourceLevel(FText setting)
{
	if (LobbyGameSettingsWindow) {
		UBG_LobbyGameSettingsWidget* gsWidget = Cast<UBG_LobbyGameSettingsWidget>(LobbyGameSettingsWindow->GetChildAt(EGameSettingsWidgets::UnitResources));
		if (gsWidget) {
			gsWidget->SetSettingWidget(setting.ToString());
		}
	}
}

void UBG_LobbyMenu::UpdateTurnSpeed(FText setting)
{
	if (LobbyGameSettingsWindow) {
		UBG_LobbyGameSettingsWidget* gsWidget = Cast<UBG_LobbyGameSettingsWidget>(LobbyGameSettingsWindow->GetChildAt(EGameSettingsWidgets::TurnSpeed));
		if (gsWidget) {
			gsWidget->SetSettingWidget(setting.ToString());
		}
	}
}

UButton * UBG_LobbyMenu::GetChangeMatchNameButton()
{
	return ChangeMatchNameButton;
}

UTextBlock* UBG_LobbyMenu::GetSessionNameTextBlock()
{
	return SessionNameTextBlock;
}

UGridPanel* UBG_LobbyMenu::GetLobbyPlayerWindow()
{
	return LobbyPlayerWindow;
}

UGridPanel * UBG_LobbyMenu::GetLobbyGameSettingsWindow()
{
	return LobbyGameSettingsWindow;
}

UBG_ChatWindow* UBG_LobbyMenu::GetChatWindow()
{
	return ChatWindow;
}

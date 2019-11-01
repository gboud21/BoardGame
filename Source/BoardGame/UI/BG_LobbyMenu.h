// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "GridPanel.h"
#include "UI/BG_ChatWindow.h"
#include "BG_LobbyMenu.generated.h"


/**
 * 
 */
UCLASS()
class BOARDGAME_API UBG_LobbyMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	/******************************************************************************************************
	Public Init Functions
	******************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void InitializeLobbyPlayerWindow(UButton* matchNameButton, UTextBlock* sessionText, UGridPanel* playerWindow, UGridPanel* settingsWindow, UBG_ChatWindow* chatWindow);

	void InitPlayerWidgetComboBox(int32 myPlayerIndex);

	void InitDisableChangeMatchNameButton();

	void InitDisableGameSettingsSelection();

	/******************************************************************************************************
	Public Update Functions
	******************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void CommitUpdateSessionName(FText sessionName);

	void UpdateSessionName(FText sessionName);
	void UpdateAlienHostility(FText setting);
	void UpdateGameSpeed(FText setting);
	void UpdateMap(FText setting);
	void UpdateMaxTurns(FText setting);
	void UpdateResourceLevel(FText setting);
	void UpdateTurnSpeed(FText setting);
	

	UButton* GetChangeMatchNameButton();

	UTextBlock* GetSessionNameTextBlock();
	
	UGridPanel* GetLobbyPlayerWindow();
	
	UGridPanel* GetLobbyGameSettingsWindow();

	UBG_ChatWindow* GetChatWindow();

private:
	UButton* ChangeMatchNameButton;
	UTextBlock* SessionNameTextBlock;
	UGridPanel* LobbyPlayerWindow;
	UGridPanel* LobbyGameSettingsWindow;
	UBG_ChatWindow* ChatWindow;
	
	enum EGameSettingsWidgets {
		MaxTurns = 0,
		MapSettings = 1,
		TurnSpeed = 2,
		UnitResources = 3
	};
	
	
};

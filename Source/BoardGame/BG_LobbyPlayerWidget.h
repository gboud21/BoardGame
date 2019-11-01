// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComboBoxString.h"
#include "TextBlock.h"
#include "WidgetSwitcher.h"
#include "Overlay.h"
#include "Button.h"
#include "BG_LobbyPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API UBG_LobbyPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void LPW_InitializePlayerWidget(UTextBlock* playerNameText, UWidgetSwitcher* widgetSwitcher, UComboBoxString* comboBox, UTextBlock* factionTextBlock, UOverlay* factionTextOverlay, UButton* kickButton);

	void LPW_UpdatePlayerWidget(const FString& playerName, const FString& faction);

	void SetPlayerName(FString playerName);
	void SetSelectedFaction(FString selectedFaction);
	void SetbIsPlayer(bool isPlayer);

	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void LPW_UpdateFactionOnSelection(FString faction);

	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void KickPlayer();

private:
	bool CheckFactionNotSelected(FString faction);
	
	UPROPERTY(meta = (AllowPrivateAccess = "true"), BlueprintReadOnly, Category = "LobbyUI")
		FString PlayerName;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), BlueprintReadOnly, Category = "LobbyUI")
		FString SelectedFaction;

	UTextBlock* PlayerNameTextWidget;
	UWidgetSwitcher* FactionWidgetSwitcher;
	UComboBoxString* SelectedFactionComboBoxWidget;
	UTextBlock* FactionTextBlock;
	UOverlay* FactionTextOverlay;
	UButton* KickButton;

	bool bIsPlayer;
};

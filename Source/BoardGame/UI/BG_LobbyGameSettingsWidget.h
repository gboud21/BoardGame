// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ComboBoxString.h"
#include "TextBlock.h"
#include "WidgetSwitcher.h"
#include "Overlay.h"
#include "BG_LobbyGameSettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API UBG_LobbyGameSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void LGSW_InitializeLobbySettingsWidget(UWidgetSwitcher* widgetSwitcher, UComboBoxString* comboBox, UTextBlock* settingTextBlock, UOverlay* settingTextOverlay);
	
	void SetSettingWidget(FString setting);
	
	void DisableSettingSelection();

	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void LGSW_UpdateSettingOnSelection(FString setting);

private:
	UWidgetSwitcher* SettingWidgetSwitcher;
	UComboBoxString* SelectedSettingComboBoxWidget;
	UTextBlock* SettingTextBlock;
	UOverlay* SettingTextOverlay;
	
};

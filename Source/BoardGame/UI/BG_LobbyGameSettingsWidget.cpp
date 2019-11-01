// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyGameSettingsWidget.h"
#include "BG_LobbyPlayerController.h"
#include "BG_LobbyGameMode.h"


void UBG_LobbyGameSettingsWidget::LGSW_InitializeLobbySettingsWidget(UWidgetSwitcher* widgetSwitcher, UComboBoxString* comboBox, UTextBlock* settingTextBlock, UOverlay* settingTextOverlay)
{	
	SettingWidgetSwitcher = widgetSwitcher;
	SelectedSettingComboBoxWidget = comboBox;
	SettingTextBlock = settingTextBlock;
	SettingTextOverlay = settingTextOverlay;
}

void UBG_LobbyGameSettingsWidget::SetSettingWidget(FString setting){
	if(SettingTextBlock){
		SettingTextBlock->SetText(FText::FromString(setting));
	}
	if(SelectedSettingComboBoxWidget){
		SelectedSettingComboBoxWidget->SetSelectedOption(setting);
	}
}

void UBG_LobbyGameSettingsWidget::DisableSettingSelection(){
	if(SettingWidgetSwitcher){
		SettingWidgetSwitcher->SetActiveWidget(SettingTextOverlay);
	}
}

void UBG_LobbyGameSettingsWidget::LGSW_UpdateSettingOnSelection(FString setting){
	//call gm and update the setting
	ABG_LobbyPlayerController* myController = Cast<ABG_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (myController && myController->Role == ROLE_Authority) {
		ABG_LobbyGameMode* myGM = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());
		if (myGM) {
			myGM->LGM_UpdateSetting(GetName(), setting);
		}
	}
}
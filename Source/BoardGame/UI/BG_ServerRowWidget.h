// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "OnlineSessionInterface.h"
#include "BG_ServerRowWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API UBG_ServerRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void InitializeServerRowWidget(FString sessionName, int32 sessionOpenPlayerCount, int32 sessionMaxPlayerCount, int32 sessionPing, int32 sessionIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Widget")
	void SetupServerRowWidgetEvent();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SetupServerRowWidget(UTextBlock* serverNameTextBlock, UTextBlock* playerCountTextBlock, UTextBlock* pingTextBlock);

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void JoinGameOnClick();


private:
	
	FString SessionName;
	int32 SessionOpenPlayerCount;
	int32 SessionMaxPlayerCount;
	int32 SessionPing;
	int32 SessionIndex;
	
	FOnlineSession* FoundSession;
};

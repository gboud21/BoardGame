// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollBox.h"
#include "OnlineSessionInterface.h"
#include "BG_ServerListWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API UBG_ServerListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//UBG_ServerListWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> wServerRowWidget;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void InitializeServerListWidget(UScrollBox* serverRowScrollBox);
	
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void ClearServerRowScrollBox();

	void AddServerRow(FString sessionName, int32 sessionOpenPlayerCount, int32 sessionMaxPlayerCount, int32 sessionPing, int32 sessionIndex);


private:
	UScrollBox* ServerRowScrollBox;
	
};

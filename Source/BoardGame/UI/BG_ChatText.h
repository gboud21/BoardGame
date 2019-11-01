// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "BG_ChatText.generated.h"


/**
 * 
 */
UCLASS()
class BOARDGAME_API UBG_ChatText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "ChatWindow")
	void InitializeChatText();

	UTextBlock* GetTextBlock();

private:
	UTextBlock* TextBlock;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EditableTextBox.h"
#include "ScrollBox.h"
#include "BG_ChatWindow.generated.h"


/**
 * 
 */
UCLASS()
class BOARDGAME_API UBG_ChatWindow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "ChatWindowUI")
	void InitializeChatWindow(UEditableTextBox* textBox, UScrollBox* scrollBox);
	
	UEditableTextBox* GetChatTextBox();
	UScrollBox* GetChatScrollBox();



private:
	UEditableTextBox* ChatTextBox;

	UScrollBox* ChatScrollBox;
	
	
};

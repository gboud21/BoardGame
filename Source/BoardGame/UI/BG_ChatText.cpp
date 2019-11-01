// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_ChatText.h"



void UBG_ChatText::InitializeChatText() {
	if (UTextBlock* textBlock = Cast<UTextBlock>(GetRootWidget())) {
		TextBlock = textBlock;
		UE_LOG(LogTemp, Warning, TEXT("PAssed cast text block"));

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast text block"));
	}
}

UTextBlock* UBG_ChatText::GetTextBlock() {
	return TextBlock;
}

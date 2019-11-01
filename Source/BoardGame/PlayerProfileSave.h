// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerProfileSave.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API UPlayerProfileSave : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Player Profile")
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "Player Profile")
		UTexture2D* PlayerImageIcon;

	UPROPERTY(VisibleAnywhere, Category = "Player Profile")
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Player Profile")
		uint32 UserIndex;

	UPlayerProfileSave();
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "InGameLevel.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API AInGameLevel : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	void ReceiveBeginPlay(); 

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
	TSubclassOf<class AActor> bp_BaseTileHex;
	TArray<TArray<AActor *>> tileArray;
};

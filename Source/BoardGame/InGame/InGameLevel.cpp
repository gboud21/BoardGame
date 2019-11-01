// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameLevel.h"
#include "Engine/World.h"


void AInGameLevel::ReceiveBeginPlay() {
	Super::ReceiveBeginPlay();

	if (bp_BaseTileHex) {
		FActorSpawnParameters SpawnParams;

		int mapX = 50;
		int mapY = 50;
		//tileArray.Init(TArray<AActor*>.Init())
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyPawn.h"


// Sets default values
ABG_LobbyPawn::ABG_LobbyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABG_LobbyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABG_LobbyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABG_LobbyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


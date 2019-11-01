// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_Camera.h"


// Sets default values
ABG_Camera::ABG_Camera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABG_Camera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABG_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABG_Camera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


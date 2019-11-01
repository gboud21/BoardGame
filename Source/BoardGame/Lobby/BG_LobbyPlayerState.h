// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BG_LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BOARDGAME_API ABG_LobbyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	ABG_LobbyPlayerState();

	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	bool bIsReady;

	/******************************************************************************************************
	Update Player State Functions
	******************************************************************************************************/
	void ChangePlayerName();

	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_ChangePlayerName();
	void Server_ChangePlayerName_Implementation();
	FORCEINLINE bool Server_ChangePlayerName_Validate() { return true; }

	void UpdatePlayer(FString faction);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdatePlayer(const FString& faction);
	void Server_UpdatePlayer_Implementation(const FString& faction);
	FORCEINLINE bool Server_UpdatePlayer_Validate(const FString& faction) { return true; }

	void SetSelectedFaction(FString faction);
	FString GetSelectedFaction();

	UPROPERTY(Replicated)
	FString SelectedFaction;

	UPROPERTY(Replicated)
	int32 PlayerNumber;
private:



	
	
};

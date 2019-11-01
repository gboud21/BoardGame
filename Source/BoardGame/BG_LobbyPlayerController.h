// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BG_LobbyGameMode.h"
#include "UI/BG_LobbyMenu.h"
#include "BG_LobbyPlayerController.generated.h"

USTRUCT()
struct FPlayerProfile {
	GENERATED_BODY()

	UPROPERTY()
	FString PlayerName;
	UPROPERTY()
	UTexture2D* PlayerIcon;
};

UCLASS()
class BOARDGAME_API ABG_LobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/******************************************************************************************************
	Constructor
	******************************************************************************************************/
	ABG_LobbyPlayerController(const FObjectInitializer& ObjectInitializer);

	/******************************************************************************************************
	Lobby Widgets
	******************************************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyUI")
		TSubclassOf<class UBG_LobbyMenu> wLobbyMenu;

	UPROPERTY(BlueprintReadOnly, Category = "LobbyUI")
	UBG_LobbyMenu* MyLobbyMenu;

	/******************************************************************************************************
	Init Functions
	******************************************************************************************************/
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	void LPC_RequestServerPlayerListUpdate();

	UFUNCTION(Server, Reliable, WithValidation)
	void LPC_Server_RequestServerPlayerListUpdate();
	void LPC_Server_RequestServerPlayerListUpdate_Implementation();
	FORCEINLINE bool LPC_Server_RequestServerPlayerListUpdate_Validate() { return true; }

	void LPC_RequestServerPlayerListUpdate(FString faction);

	UFUNCTION(Server, Reliable, WithValidation)
	void LPC_Server_RequestServerPlayerListUpdate_Faction(const FString& faction);
	void LPC_Server_RequestServerPlayerListUpdate_Faction_Implementation(const FString& faction);
	FORCEINLINE bool LPC_Server_RequestServerPlayerListUpdate_Faction_Validate(const FString& faction) { return true; }
	
	UFUNCTION(Client,Reliable)
	void LPC_Client_InitProfile();
	void LPC_Client_InitProfile_Implementation();

	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void LPC_HostClientLobbySetup();

	/******************************************************************************************************
	Public Network Functions
	******************************************************************************************************/
	class ABG_LobbyPlayerState* LPC_GetBG_LobbyPlayerState();
	void LPC_SetBG_LobbyPlayerState(class ABG_LobbyPlayerState* ps);

	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void LPC_KickPlayer(int32 playerIndex);

	UFUNCTION(Client, Reliable)
	void LPC_Client_KickPlayer();
	void LPC_Client_KickPlayer_Implementation();

	void LPC_LeaveGame();
	/******************************************************************************************************
	Public Update Functions
	******************************************************************************************************/
	void LPC_UpdateSessionName(FText sessionName);
	UFUNCTION(Client, Reliable)
	void LPC_Client_UpdateLobbySettings();
	void LPC_Client_UpdateLobbySettings_Implementation();

	
	UFUNCTION(Client, Reliable)
	void LPC_Client_UpdatePlayerList(const TArray<FBG_PlayerInfo>& PlayerInfoArray);
	void LPC_Client_UpdatePlayerList_Implementation(const TArray<FBG_PlayerInfo>& PlayerInfoArray);

	/******************************************************************************************************
	Public Chat Functions
	******************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "LobbyUI")
	void LPC_BP_SendChat(FString chatText);

	UFUNCTION(Server, Reliable, WithValidation)
	void LPC_Server_SendChat(const FString& chatText);
	void LPC_Server_SendChat_Implementation(const FString& chatText);
	FORCEINLINE bool LPC_Server_SendChat_Validate(const FString& chatText) { return true; }

	UFUNCTION(Client, Reliable)
	void LPC_Client_ReceiveChat(const FString& chatText);
	void LPC_Client_ReceiveChat_Implementation(const FString& chatText);

	/******************************************************************************************************
	Player Settings Functions
	******************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "LobbyPlayerController")
	void UpdateFaction(ABG_LobbyPlayerController* pc, FString faction);

	UFUNCTION(Server, Reliable, WithValidation)
	void LPC_Server_UpdateFaction(ABG_LobbyPlayerController* pc, const FString& faction);
	void LPC_Server_UpdateFaction_Implementation(ABG_LobbyPlayerController* pc, const FString& faction);
	FORCEINLINE bool LPC_Server_UpdateFaction_Validate(ABG_LobbyPlayerController* pc, const FString& faction) { return true; }

	UFUNCTION(BlueprintCallable, Category = "LobbyPlayerController")
	FString GetSelectedFaction();

	//UFUNCTION(BlueprintCallable, Category = "LobbyPlayerController")
	//void SetSelectedFaction(FString faction);
	/******************************************************************************************************
	Player Settings Variables
	******************************************************************************************************/


	UPROPERTY(Replicated)
	FPlayerProfile MyPlayerProfile;


	UPROPERTY(Replicated)
	FString SelectedFaction;

private:

	void LPC_InitPlayer();
	void LPC_SetupLobbyMenu();

	UFUNCTION(Client, Reliable)
	void CheckProfileSave();
	void CheckProfileSave_Implementation();

	/******************************************************************************************************
	Private Chat Functions
	******************************************************************************************************/
	void LPC_SendChat(FString chatText);

protected:
	class ABG_LobbyPlayerState* BG_LobbyPlayerState;
	
};

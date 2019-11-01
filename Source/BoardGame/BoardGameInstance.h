// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerProfileSave.h"
#include "Kismet/GameplayStatics.h"
#include "ScrollBox.h"
#include "TextBlock.h"
#include "Button.h"
#include "Image.h"
#include "UI/BG_ServerListWidget.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
#include "BoardGameInstance.generated.h"

UENUM(BlueprintType)
enum class EStatusMessageState :uint8 
{
	SMS_Complete	UMETA(DisplayName = "Complete"),
	SMS_Searching	UMETA(DisplayName = "Searching"),
	SMS_NoMatches	UMETA(DisplayName = "No Matches Found"),
	SMS_Error		UMETA(DisplayName = "Error")
};

/**
 * 
 */
UCLASS()
class BOARDGAME_API UBoardGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:
	/******************************************************************************************************
	Constructor
	******************************************************************************************************/
	UBoardGameInstance(const FObjectInitializer& ObjectInitializer);

	/******************************************************************************************************
	Virtual Functions
	******************************************************************************************************/
	virtual void Init();

	/******************************************************************************************************
	UMG Widgets
	******************************************************************************************************/
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> wProfileImage;

	UUserWidget* MyProfileImage;
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> wPlayerProfileIcon;

	UUserWidget* MyPlayerProfileIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UTextBlock* MyPlayerNameText;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UImage* MyProfileImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> wPlayerProfileMenu;

	UUserWidget* MyPlayerProfileMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> wMainMenu;

	UUserWidget* MyMainMenu;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> wMultiplayerMenu;

	UUserWidget* MyMultiplayerMenu;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> wOptionsMenu;

	UUserWidget* MyOptionsMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> wTutorialMenu;

	UUserWidget* MyTutorialMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	//TSubclassOf<UBG_ServerListWidget> wServerList;
	TSubclassOf<class UUserWidget> wServerList;

	UBG_ServerListWidget* MyServerList;

	/************************************************************************************************************
	UI Functions
	*************************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayPlayerProfileIcon();
	
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayPlayerProfileMenu();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayMultiplayerMenu();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayOptionsMenu();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayTutorialMenu();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayServerList(bool isLAN);	

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void UpdatePlayerProfileMenuWidget(FString Name, UTexture2D* Texture);

	/************************************************************************************************************
	Player Profile Variables
	*************************************************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Player Profile")
	TArray<UTexture2D*> PlayerProfileImageArray;

	/************************************************************************************************************
	Player Profile Functions
	*************************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Player Profile")
		bool CheckProfileSave();

	UFUNCTION(BlueprintCallable, Category = "Player Profile")
		void SavePlayerProfile();

	UFUNCTION(BlueprintCallable, Category = "Player Profile")
		void LoadPlayerProfile();

	UFUNCTION(BlueprintCallable, Category = "Player Profile")
		FString GetPlayerName();

	UFUNCTION(BlueprintCallable, Category = "Player Profile")
		UTexture2D* GetPlayerProfileImage();

	/************************************************************************************************************
	Network Functions
	*************************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Networking")
		bool InitRefresh(UScrollBox* ServerList, UTextBlock* StatusMessage, UButton* RefreshButton);

	UFUNCTION(BlueprintCallable, Category = "Networking")
		void WrapUpRefresh(EStatusMessageState SMS);

	UFUNCTION(BlueprintCallable, Category = "Networking")
		bool GetIsLAN();

	/************************************************************************************************************
	Match Session Functions
	*************************************************************************************************************/
	UFUNCTION(BlueprintCallable, Category = "Match Session")
		void HostSession();

	UFUNCTION(BlueprintCallable, Category = "Match Session")
		void DestroyGame();

	UFUNCTION(BlueprintCallable, Category = "Match Session")
		void FindSession(UButton* refreshButton);

	void JoinGame(int32 sessionIndex);

	void UpdateSessionSettings(FString serverName, int32 playerCount);

	UFUNCTION(BlueprintCallable, Category = "Match Session")
		void InitializeMatchSession();

	UFUNCTION(BlueprintCallable, Category = "Match Session")
		int32 GetMaxPlayers();

	UFUNCTION(BlueprintCallable, Category = "Match Session")
		void DecrementMaxPlayers();

	UFUNCTION(BlueprintCallable, Category = "MatchSession")
		void IncrementMaxPlayers();

	UFUNCTION(BlueprintCallable, Category = "Match Session")
		FString GetMatchName();

	UPROPERTY(EditAnywhere)
		TAssetPtr<UWorld> LobbyLevel;


private:

	/************************************************************************************************************
	Private Network Functions
	*************************************************************************************************************/
	void CreateSession();

	void OnCreateSessionComplete(FName SessionName, bool Success);

	void OnDestroySessionComplete(FName SessionName, bool Success);

	void OnFindSessionComplete(bool Success);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	
	/************************************************************************************************************
	Widget Variables
	*************************************************************************************************************/
	UTextBlock* MyStatusMessage;
	UButton* RefreshButton;
	
	/************************************************************************************************************
	Network Variables
	*************************************************************************************************************/
	bool bIsLAN;
	bool bIsHosting = false;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	/************************************************************************************************************
	Widget Functions
	*************************************************************************************************************/
	void ChangeStatusMessage(EStatusMessageState SMS);

	/************************************************************************************************************
	Player Profile Variables
	*************************************************************************************************************/
	FString PlayerName;
	FString PlayerIcon_NoIcon = "Texture2D'/Game/Artwork/Player_Icons/PlayerIcon_NoIcon.PlayerIcon_NoIcon'";
	UTexture2D* PlayerProfileImage;

	/************************************************************************************************************
	Match Session Variables
	*************************************************************************************************************/
	int32 MaxPlayers;
	FString MatchName;
	const FName ServerNameKey = "ServerNameKey";

};

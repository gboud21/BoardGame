// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_LobbyPlayerController.h"
//#include "BG_LobbyGameMode.h"
#include "PlayerProfileSave.h"
#include "BG_LobbyPlayerWidget.h"
#include "UnrealNetwork.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Lobby/BG_LobbyPlayerState.h"
#include "UI/BG_ChatText.h"
#include "Online.h"
#include "Engine.h"
#include "UnrealNetwork.h"
#include "Lobby/BG_LobbyGameState.h"


#define Log(x) UE_LOG(LogTemp,Warning,TEXT(x))

/******************************************************************************************************
Public Constructor
******************************************************************************************************/
ABG_LobbyPlayerController::ABG_LobbyPlayerController(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer){
	bReplicates = true;
}

/******************************************************************************************************
Public Replication
******************************************************************************************************/
void ABG_LobbyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABG_LobbyPlayerController, SelectedFaction);
	DOREPLIFETIME(ABG_LobbyPlayerController, MyPlayerProfile);
}

/******************************************************************************************************
Public Init Functions
******************************************************************************************************/
void ABG_LobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	Log("2: Begin Play, Player Controller");

	FTimerHandle RequestServerPlayerListUpdateHandle;

	ABG_LobbyPlayerController* myController = Cast<ABG_LobbyPlayerController>(GetWorld()->GetFirstPlayerController());

	if (myController == this) {
		LPC_SetupLobbyMenu();
		//GetWorldTimerManager().SetTimer(RequestServerPlayerListUpdateHandle, this, &ABG_LobbyPlayerController::LPC_InitPlayer, 0.01f, false);

		SetActorTickEnabled(true);

		if (Role == ROLE_Authority) {
			//Get session info
			FString x = "Ok qoq";
			FName myName = FName(*x);
			IOnlineSubsystem* const OnlineSub = IOnlineSubsystem::Get();
			if (OnlineSub) {
				Log("Online sub not null");
				IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
				if (Session.IsValid()) {
					Log("Session valid");
					TSharedPtr<class FOnlineSessionSettings> SessionSettings;
					SessionSettings = MakeShareable(new FOnlineSessionSettings());
					SessionSettings->NumPublicConnections = 8;
					Session->UpdateSession(myName, *SessionSettings, true);

				}
				else {
					Log("No seesion");
				}
			}
			else {
				Log("No online sub");
			}
			
		}
	}
}

void ABG_LobbyPlayerController::Tick(float DeltaTime)
{
	if (this->PlayerState) {
		LPC_InitPlayer();
	}
}

void ABG_LobbyPlayerController::LPC_RequestServerPlayerListUpdate()
{
	if (Role == ROLE_Authority) {
		ABG_LobbyGameMode* myGameMode = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());

		if (myGameMode) {
			myGameMode->LGM_PlayerRequestUpdate();
		}
	}
	else {
		LPC_Server_RequestServerPlayerListUpdate();
	}
}

void ABG_LobbyPlayerController::LPC_Server_RequestServerPlayerListUpdate_Implementation()
{
	LPC_RequestServerPlayerListUpdate();
}

void ABG_LobbyPlayerController::LPC_RequestServerPlayerListUpdate(FString faction)
{
	if (Role == ROLE_Authority) {
		ABG_LobbyGameMode* myGameMode = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());

		if (myGameMode) {
			myGameMode->LGM_PlayerRequestUpdate();
		}
	}
	else {
		LPC_Server_RequestServerPlayerListUpdate_Faction_Implementation(faction);
	}
}

void ABG_LobbyPlayerController::LPC_Server_RequestServerPlayerListUpdate_Faction_Implementation(const FString& faction)
{
	LPC_RequestServerPlayerListUpdate();
}

void ABG_LobbyPlayerController::LPC_Client_InitProfile_Implementation()
{
	if (Role == ROLE_Authority) {
		Log("Server: LPC InitProfile Start");
	}
	else {
		Log("Client: LPC InitProfile Start");

	}
	CheckProfileSave();
	FString tempName = MyPlayerProfile.PlayerName;
	if (Role == ROLE_Authority) {
		UE_LOG(LogTemp, Warning, TEXT("Server: Player Profile Name: %s"), *tempName);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Client: Player Profile Name: %s"), *tempName);
	}

//	SelectedFaction = "Random";
	//LPC_Server_CallUpdate();
}

void ABG_LobbyPlayerController::LPC_HostClientLobbySetup()
{
	//If Not RoleAuthority then hide ChangeMatchNameButton, Swap the Game Settings from comboboxes to text blocks, hide the launch game button
	if (Role < ROLE_Authority) {
		MyLobbyMenu->InitDisableChangeMatchNameButton();
		//Swap Widget for each game settings
		MyLobbyMenu->InitDisableGameSettingsSelection();
	}

	//for all players change the comboboxes to text blocks for all players that are not your own
	ABG_LobbyPlayerState* pState = Cast<ABG_LobbyPlayerState>(PlayerState);
	if (pState) {
		MyLobbyMenu->InitPlayerWidgetComboBox((pState->PlayerNumber)-1);
	}else{
		Log("LPC 10: HostClientLobbySetup pstate fail");
	}
}

ABG_LobbyPlayerState * ABG_LobbyPlayerController::LPC_GetBG_LobbyPlayerState()
{
	if (BG_LobbyPlayerState) {
		return BG_LobbyPlayerState;
	}
	else {
		BG_LobbyPlayerState = Cast<ABG_LobbyPlayerState>(PlayerState);
		return BG_LobbyPlayerState;
	}
}

void ABG_LobbyPlayerController::LPC_SetBG_LobbyPlayerState(ABG_LobbyPlayerState * ps)
{
	if (ps && Role == ROLE_Authority) {
		BG_LobbyPlayerState = ps;
		PlayerState = ps;
	}
}

void ABG_LobbyPlayerController::LPC_KickPlayer(int32 playerIndex)
{
	if (Role == ROLE_Authority) {
		ABG_LobbyGameMode* gm = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());
		if (gm) {
			//Figure out what index the player is.
			//gm->KickPlayer(1);
		}
	}
}

/******************************************************************************************************
Public Update Functions
******************************************************************************************************/
void ABG_LobbyPlayerController::LPC_Client_UpdateLobbySettings_Implementation()
{
	Log("LPC: Client Update Lobby Settings Start");
	
	//Update Widgets here based off of game state
	ABG_LobbyGameState* gState = Cast<ABG_LobbyGameState>(GetWorld()->GetGameState());
	if (gState) {
		Log("LPC: Client Update Lobby Settings gstate is not null");
		if (Role == ROLE_Authority) {
			UE_LOG(LogTemp, Warning, TEXT("LPC: Client Update Lobby Settings max turns = %s"), *(gState->GameSettings.MaxTurns));
			UE_LOG(LogTemp, Warning, TEXT("LPC: Client Update Lobby Settings session name = %s"), *(gState->SessionName));
			UE_LOG(LogTemp, Warning, TEXT("LPC: Client Update Lobby Settings gssn = %s"), *(gState->GameSettings.SessionName));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("LPC: not host Client Update Lobby Settings max turns = %s"), *(gState->GameSettings.MaxTurns));
			UE_LOG(LogTemp, Warning, TEXT("LPC:not host  Client Update Lobby Settings session name = %s"), *(gState->SessionName));
			UE_LOG(LogTemp, Warning, TEXT("LPC:not host  Client Update Lobby Settings gssn = %s"), *(gState->GameSettings.SessionName));
		}
		MyLobbyMenu->UpdateSessionName(FText::FromString(gState->GameSettings.SessionName));
		MyLobbyMenu->UpdateAlienHostility(FText::FromString(gState->GameSettings.AlienHostility));
		MyLobbyMenu->UpdateGameSpeed(FText::FromString(gState->GameSettings.GameSpeed));
		MyLobbyMenu->UpdateMap(FText::FromString(gState->GameSettings.MapName));
		MyLobbyMenu->UpdateMaxTurns(FText::FromString(gState->GameSettings.MaxTurns));
		MyLobbyMenu->UpdateResourceLevel(FText::FromString(gState->GameSettings.ResourceLevel));
		MyLobbyMenu->UpdateTurnSpeed(FText::FromString(gState->GameSettings.TurnSpeed));
	}
	else {
		Log("LPC: Client Update Lobby Settings gstate is null");
	}
}


void ABG_LobbyPlayerController::LPC_Client_UpdatePlayerList_Implementation(const TArray<FBG_PlayerInfo>& PlayerInfoArray)
{
	Log("LPC 3: Update Player List");
	//for (int j = 0; j < PlayerInfoArray.Num(); j++) {
	for (int j = 0; j < 6; j++) {
		UBG_LobbyPlayerWidget* playerWidget = Cast<UBG_LobbyPlayerWidget>(MyLobbyMenu->GetLobbyPlayerWindow()->GetChildAt(j));
		if (j < PlayerInfoArray.Num()) {
			playerWidget->LPW_UpdatePlayerWidget(PlayerInfoArray[j].PlayerName, PlayerInfoArray[j].SelectedFaction);
		}
		else {
			playerWidget->LPW_UpdatePlayerWidget("", "");
		}
	}
}

void ABG_LobbyPlayerController::LPC_Client_KickPlayer_Implementation()
{
	UBoardGameInstance* gameInstance = Cast<UBoardGameInstance>(GetGameInstance());
	if (gameInstance) {
		Log("LPC_Client_kick_Player: Client Kicked");
		gameInstance->DestroyGame();
	}
	else {
		Log("LPC_Client_kick_Player: Failed to kick player");
	}
}

void ABG_LobbyPlayerController::LPC_LeaveGame()
{
}

void ABG_LobbyPlayerController::LPC_UpdateSessionName(FText sessionName)
{

}



/******************************************************************************************************
Chat Functions
******************************************************************************************************/
void ABG_LobbyPlayerController::LPC_BP_SendChat(FString chatText)
{
	FString fullMessage = Cast<ABG_LobbyPlayerState>(PlayerState)->PlayerName;
	fullMessage.Append(": " + chatText);
	LPC_SendChat(fullMessage);
}

void ABG_LobbyPlayerController::LPC_Server_SendChat_Implementation(const FString & chatText)
{
	LPC_SendChat(chatText);
}

void ABG_LobbyPlayerController::LPC_Client_ReceiveChat_Implementation(const FString & chatText)
{
	//update chat window here
	//UTextBlock* chatTextWidget = ConstructObject<UTextBlock>(UTextBlock::StaticClass(), this);
	UTextBlock* chatTextWidget = NewObject<UTextBlock>(UTextBlock::StaticClass());

	if (chatTextWidget) {
		chatTextWidget->SetText(FText::FromString(chatText));
		MyLobbyMenu->GetChatWindow()->GetChatScrollBox()->AddChild(chatTextWidget);
	}
}


/******************************************************************************************************
Player Settings Functions
******************************************************************************************************/
void ABG_LobbyPlayerController::UpdateFaction(ABG_LobbyPlayerController* pc, FString faction)
{ 

	if (Role == ROLE_Authority) {
		if (pc) {
			ABG_LobbyPlayerState* pState = Cast<ABG_LobbyPlayerState>(pc->PlayerState);
			Log("LPC 6: Update Faction pc Passed");

			if (pc->PlayerState) {
				Log("LPC 7: Player State is not null");
			}
			else {
				Log("LPC 8: Player State is null");
			}
			ABG_LobbyGameMode* gm = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());
			//gm->UpdatePlayerList(pc, faction);
			if (pState) {
				Log("LPC 9: Lobby Player State is not null");
				pState->SelectedFaction = faction;
				LPC_RequestServerPlayerListUpdate();
			}
			else {
				Log("LPC 9: Lobby Player State is null");
			}
		}
		else {
			Log("LPC 6: Update Faction pc Failed");
		}
	}
	else {
		LPC_Server_UpdateFaction(this, faction);
	}
}

void ABG_LobbyPlayerController::LPC_Server_UpdateFaction_Implementation(ABG_LobbyPlayerController* pc, const FString & faction)
{
	UpdateFaction(pc, faction);
}

FString ABG_LobbyPlayerController::GetSelectedFaction()
{ 
	FString faction = (Cast<ABG_LobbyPlayerState>(PlayerState))->GetSelectedFaction();
	return faction;
}

//void ABG_LobbyPlayerController::SetSelectedFaction(FString faction) { SelectedFaction = faction; }

/******************************************************************************************************
Private Init Functions
******************************************************************************************************/

void ABG_LobbyPlayerController::LPC_InitPlayer()
{
	LPC_HostClientLobbySetup();
	LPC_RequestServerPlayerListUpdate();
	LPC_Client_UpdateLobbySettings();
	SetActorTickEnabled(false);
}


void ABG_LobbyPlayerController::LPC_SetupLobbyMenu()
{
	if (wLobbyMenu)
	{
		MyLobbyMenu = CreateWidget<UBG_LobbyMenu>(this, wLobbyMenu);

		if (MyLobbyMenu)
		{
			MyLobbyMenu->AddToViewport();
		}

		//Show the Cursor.
		APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
		myPlayerController->bShowMouseCursor = true;
	}
}

void ABG_LobbyPlayerController::CheckProfileSave_Implementation()
{
	UPlayerProfileSave* LoadGameInstance = Cast<UPlayerProfileSave>(UGameplayStatics::CreateSaveGameObject(UPlayerProfileSave::StaticClass()));
	LoadGameInstance = Cast<UPlayerProfileSave>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (NULL == LoadGameInstance) {
		MyPlayerProfile.PlayerName = "No one";
	}
	else {
		MyPlayerProfile.PlayerName = LoadGameInstance->PlayerName;
		MyPlayerProfile.PlayerIcon = LoadGameInstance->PlayerImageIcon;
	}
}

void ABG_LobbyPlayerController::LPC_SendChat( FString chatText)
{
	//get passed chatText from UMG Widget
	//if it is the server than distribute chat to all players via the game mode
	//if it is not the server then call Send Chat on the server
	if (Role == ROLE_Authority) {
		ABG_LobbyGameMode* gm = Cast<ABG_LobbyGameMode>(GetWorld()->GetAuthGameMode());
		if (gm) {
			gm->DistributeChat(chatText);
		}
	}
	else {
		LPC_Server_SendChat(chatText);
	}
}


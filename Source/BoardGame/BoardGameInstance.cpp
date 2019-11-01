// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardGameInstance.h"
#include "OnlineSessionSettings.h"

#define LOCTEXT_NAMESPACE "Text Namespace"

const static FName SESSION_NAME = TEXT("My Session Game");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName");

UBoardGameInstance::UBoardGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}

void UBoardGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Board Game Instance Init"));
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (nullptr != Subsystem) {
		UE_LOG(LogTemp, Warning, TEXT("Board Game Instance Subsystem not null"));
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Board Game Instance Found session interface"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UBoardGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UBoardGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UBoardGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UBoardGameInstance::OnJoinSessionComplete);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Board Game Instance no Found session interface"));

		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Board Game Instance Subsystem null"));

	}
}

void UBoardGameInstance::DisplayPlayerProfileIcon()
{
	if (wPlayerProfileIcon)
	{
		MyPlayerProfileIcon = CreateWidget<UUserWidget>(this, wPlayerProfileIcon);

		if (MyPlayerProfileIcon)
		{
			MyPlayerProfileIcon->AddToViewport();
		}
	}
}

void UBoardGameInstance::DisplayPlayerProfileMenu()
{
	if (wPlayerProfileMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyPlayerProfileMenu = CreateWidget<UUserWidget>(this, wPlayerProfileMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyPlayerProfileMenu)
		{
			//let add it to the view port
			MyPlayerProfileMenu->AddToViewport();
		}

		//Show the Cursor.
		APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
		myPlayerController->bShowMouseCursor = true;
	}
}

/************************************************************************************************************
Public UI Functions
*************************************************************************************************************/
void UBoardGameInstance::DisplayMainMenu(void)
{
	if (wMainMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyMainMenu = CreateWidget<UUserWidget>(this, wMainMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyMainMenu)
		{
			//let add it to the view port
			MyMainMenu->AddToViewport();
		}

		//Show the Cursor.
		APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
		myPlayerController->bShowMouseCursor = true;
	}
}

void UBoardGameInstance::DisplayMultiplayerMenu(void)
{
	if (wMultiplayerMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyMultiplayerMenu = CreateWidget<UUserWidget>(this, wMultiplayerMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyMultiplayerMenu)
		{
			//let add it to the view port
			MyMultiplayerMenu->AddToViewport();
		}

		//Show the Cursor.
		APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
		myPlayerController->bShowMouseCursor = true;
	}
}

void UBoardGameInstance::DisplayOptionsMenu(void)
{
	if (wOptionsMenu) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		MyOptionsMenu = CreateWidget<UUserWidget>(this, wOptionsMenu);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (MyOptionsMenu)
		{
			//let add it to the view port
			MyOptionsMenu->AddToViewport();
		}

		//Show the Cursor.
		APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
		myPlayerController->bShowMouseCursor = true;
	}
}

void UBoardGameInstance::DisplayTutorialMenu(void)
{
}

void UBoardGameInstance::DisplayServerList(bool isLAN)
{
	UE_LOG(LogTemp, Warning, TEXT("Display Server List "));

	
	bIsLAN = isLAN;
	if (wServerList) // Check if the Asset is assigned in the blueprint.
	{
		// Create the widget and store it.
		//MyServerList = NewObject<UBG_ServerListWidget>(UBG_ServerListWidget::StaticClass());
		UUserWidget* serverList = CreateWidget<UUserWidget>(this, wServerList);

		// now you can use the widget directly since you have a referance for it.
		// Extra check to  make sure the pointer holds the widget.
		if (serverList)
		{
			UE_LOG(LogTemp, Warning, TEXT("Add Server List to viewport "));
			//let add it to the view port
			serverList->AddToViewport();
			//MyServerList->GetParent();
			MyServerList = Cast<UBG_ServerListWidget>(serverList);
		}
		else {
		}
		APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();
			UE_LOG(LogTemp, Warning, TEXT("Server List not valid2 "));

		//Show the Cursor.
		myPlayerController->bShowMouseCursor = true;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Server List not valid 1 "));
	}
}

void UBoardGameInstance::UpdatePlayerProfileMenuWidget(FString Name, UTexture2D* Texture)
{
	PlayerName = Name;
	PlayerProfileImage = Texture;
	//Add line to set Player Profile Name Text Widget
	//FText PlayerNameText = FText::AsCultureInvariant(PlayerName);
	MyPlayerNameText->SetText(FText::AsCultureInvariant(PlayerName));
	MyProfileImage->SetBrushFromTexture(PlayerProfileImage, false);
	SavePlayerProfile();
}

bool UBoardGameInstance::CheckProfileSave()
{
	UPlayerProfileSave* LoadGameInstance = Cast<UPlayerProfileSave>(UGameplayStatics::CreateSaveGameObject(UPlayerProfileSave::StaticClass()));
	LoadGameInstance = Cast<UPlayerProfileSave>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (NULL == LoadGameInstance) {
		UpdatePlayerProfileMenuWidget("No One", PlayerProfileImageArray[0]);
		return false;
	}
	else {
		UpdatePlayerProfileMenuWidget(LoadGameInstance->PlayerName, LoadGameInstance->PlayerImageIcon);
		return true;
	}
	return true;
}

void UBoardGameInstance::SavePlayerProfile()
{
	UPlayerProfileSave* SaveProfileInstance = Cast<UPlayerProfileSave>(UGameplayStatics::CreateSaveGameObject(UPlayerProfileSave::StaticClass()));
	SaveProfileInstance->PlayerName = PlayerName;
	SaveProfileInstance->PlayerImageIcon = PlayerProfileImage;
	UGameplayStatics::SaveGameToSlot(SaveProfileInstance, SaveProfileInstance->SaveSlotName, SaveProfileInstance->UserIndex);
}

void UBoardGameInstance::LoadPlayerProfile()
{

}

FString UBoardGameInstance::GetPlayerName(){ return PlayerName; }

UTexture2D* UBoardGameInstance::GetPlayerProfileImage(){ return PlayerProfileImage; }



/************************************************************************************************************
Public Network Functions
*************************************************************************************************************/

bool UBoardGameInstance::InitRefresh(UScrollBox* ServerList, UTextBlock* StatusMessage, UButton* RefreshButton)
{
	MyStatusMessage = StatusMessage;

	ChangeStatusMessage(EStatusMessageState::SMS_Searching);
	RefreshButton->SetIsEnabled(false);

	ServerList->ClearChildren();
	
	return bIsLAN;
}

void UBoardGameInstance::WrapUpRefresh(EStatusMessageState SMS)
{
	ChangeStatusMessage(SMS);

	if (RefreshButton) {
		RefreshButton->SetIsEnabled(true);
	}
}

bool UBoardGameInstance::GetIsLAN() { return bIsLAN; }

void UBoardGameInstance::HostSession()
{
	if (SessionInterface.IsValid()) {
		bIsHosting = true;
		FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (nullptr != ExistingSession) {
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else {
			CreateSession();
		}
	}
}

void UBoardGameInstance::DestroyGame()
{
	if (SessionInterface.IsValid()) {
		SessionInterface->DestroySession(SESSION_NAME);
	}

}

void UBoardGameInstance::FindSession(UButton* refreshButton)
{
	RefreshButton = refreshButton;
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("Game Instance Starting Find Session"));
		SessionSearch->bIsLanQuery = bIsLAN;
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		
	}
}

void UBoardGameInstance::JoinGame(int32 sessionIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Board Game Instance Join Session: Session Number = %d"), sessionIndex);
	if (!SessionInterface.IsValid() || !SessionSearch.IsValid()) {
		return;
	}
	if (MyServerList) {
		MyServerList->RemoveFromViewport();
	}

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[sessionIndex]);
}

void UBoardGameInstance::UpdateSessionSettings(FString serverName, int32 playerCount)
{
	FOnlineSessionSettings* SessionSettings = SessionInterface->GetSessionSettings(SESSION_NAME);
	SessionSettings->NumPublicConnections = playerCount;
	
	SessionSettings->Set(SERVER_NAME_SETTINGS_KEY, serverName);
	SessionInterface->UpdateSession(SESSION_NAME, *SessionSettings);
}

void UBoardGameInstance::InitializeMatchSession()
{
	MaxPlayers = 6;
	MatchName = "New BoardGame Session";
}

int32 UBoardGameInstance::GetMaxPlayers(){ return MaxPlayers; }

void UBoardGameInstance::DecrementMaxPlayers(){ MaxPlayers--; }

void UBoardGameInstance::IncrementMaxPlayers() { MaxPlayers++; }

FString UBoardGameInstance::GetMatchName(){ return MatchName; }

/************************************************************************************************************
Private Network Functions
*************************************************************************************************************/
void UBoardGameInstance::CreateSession()
{
	bIsHosting = false;
	if (SessionInterface.IsValid()) {
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = false;
		SessionSettings.NumPublicConnections = 6;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		FString tempSessionName = "Board Game Session";
		SessionSettings.Settings.Add(SERVER_NAME_SETTINGS_KEY, tempSessionName);
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UBoardGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session"));
	}
	
	//Destroy Multiplayer Server list

	UEngine* Engine = GetEngine();

	if (!ensure(nullptr != Engine)) {
		return;
	}

	//Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));
	UE_LOG(LogTemp, Warning, TEXT("Hosting"));

	UWorld* World = GetWorld();

	if (!ensure(nullptr != World)) {
		return;
	}
	
	//World->ServerTravel("/Game/Maps/LobbyMap?listen");
	World->ServerTravel(LobbyLevel.GetLongPackageName().Append("?listen"));
}

void UBoardGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success) {
		if (bIsHosting) {
			CreateSession();
		}
		else {
			//Possibly Load Main Menu
			UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
		}
	}
}

void UBoardGameInstance::OnFindSessionComplete(bool Success)
{
	if (!SessionSearch.IsValid() && MyStatusMessage) {
		WrapUpRefresh(EStatusMessageState::SMS_Error);
	}
	else if (SessionSearch->SearchResults.Num() == 0 && MyStatusMessage) {
		WrapUpRefresh(EStatusMessageState::SMS_NoMatches);
	}
	else {
		if (Success && SessionSearch.IsValid()) {
			UE_LOG(LogTemp, Warning, TEXT("Game Instance Find Session Complete"));
			UE_LOG(LogTemp, Warning, TEXT("Number of Sesssions %d"), (SessionSearch->SearchResults.Num()));
			//for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults) {
			for (int sessionIndex = 0; sessionIndex < SessionSearch->SearchResults.Num(); sessionIndex++) {
				//UE_LOG(LogTemp, Warning, TEXT("Found Session Named %s"), *(SearchResult.GetSessionIdStr()));
				const FOnlineSessionSearchResult& SearchResult = SessionSearch->SearchResults[sessionIndex];
				FString sessionName;
				bool bHasName = SearchResult.Session.SessionSettings.Get<FString>(SERVER_NAME_SETTINGS_KEY, sessionName);
				int32 sessionOpenPlayerCount = SearchResult.Session.NumOpenPublicConnections;
				int32 sessionMaxPlayerCount = SearchResult.Session.SessionSettings.NumPublicConnections;
				int32 ping = SearchResult.PingInMs;
				UE_LOG(LogTemp, Warning, TEXT("Game Instance Find Session Complete: Add Server Row"));
				if (MyServerList) {
					if (bHasName) {
						MyServerList->AddServerRow(sessionName, sessionOpenPlayerCount, sessionMaxPlayerCount, ping, sessionIndex);
					}
					else {
						MyServerList->AddServerRow("Unknown Session Name", sessionOpenPlayerCount, sessionMaxPlayerCount, ping, sessionIndex);
					}
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("Game Instance Find Session Complete : My Server List Invalid"));
				}
			}
			if (MyStatusMessage) {
				WrapUpRefresh(EStatusMessageState::SMS_Complete);
			}
		}
	}
}

void UBoardGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) {
		return;
	}
	
	FString address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, address)) {
		UE_LOG(LogTemp, Warning, TEXT("On Join Session Complete: Could not get connect string"));
	}

	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *address));

	APlayerController* pc = GetFirstLocalPlayerController();
	if (!ensure(nullptr != pc)) {
		return;
	}

	pc->ClientTravel(address, ETravelType::TRAVEL_Absolute);
	
}

/************************************************************************************************************
Private Network Functions
*************************************************************************************************************/
void UBoardGameInstance::ChangeStatusMessage(EStatusMessageState SMS)
{
	FText StatusMessageText;
	switch (SMS) {
	case EStatusMessageState::SMS_Complete:
		UE_LOG(LogTemp, Warning, TEXT("Search Complete."));
		if (MyStatusMessage) {
			MyStatusMessage->SetVisibility(ESlateVisibility::Collapsed);
		}
		break;
	case EStatusMessageState::SMS_Searching:
		UE_LOG(LogTemp, Warning, TEXT("Searching"));
		if (MyStatusMessage) {
			MyStatusMessage->SetVisibility(ESlateVisibility::Visible);
			StatusMessageText = FText::FromString("Searching...");
			MyStatusMessage->SetText(StatusMessageText);
		}
		break;
	case EStatusMessageState::SMS_NoMatches:
		UE_LOG(LogTemp, Warning, TEXT("No Matches"));
		if (MyStatusMessage) {
			MyStatusMessage->SetVisibility(ESlateVisibility::Visible);
			StatusMessageText = FText::FromString("No Matches Found.");
			MyStatusMessage->SetText(StatusMessageText);
		}
		break;
	case EStatusMessageState::SMS_Error:
		UE_LOG(LogTemp, Warning, TEXT("Error"));
		if (MyStatusMessage) {
			MyStatusMessage->SetVisibility(ESlateVisibility::Visible);
			StatusMessageText = FText::FromString("There was an error while searching. Check Network Connection");
			MyStatusMessage->SetText(StatusMessageText);
		}
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Default"));
		if (MyStatusMessage) {
			MyStatusMessage->SetVisibility(ESlateVisibility::Visible);
			StatusMessageText = FText::FromString("There was an error while searching. Check Network Connection");
			MyStatusMessage->SetText(StatusMessageText);
		}
		break;
	}
}

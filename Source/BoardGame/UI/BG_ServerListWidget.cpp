// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_ServerListWidget.h"
#include "UI/BG_ServerRowWidget.h"

/*UBG_ServerListWidget::UBG_ServerListWidget(const FObjectInitializer& ObjectInitializer):
{
}*/

void UBG_ServerListWidget::InitializeServerListWidget(UScrollBox* serverRowScrollBox)
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize Server List Widget"));
	ServerRowScrollBox = serverRowScrollBox;
}

void UBG_ServerListWidget::ClearServerRowScrollBox()
{
	if (ServerRowScrollBox) {
		ServerRowScrollBox->ClearChildren();
	}
}

void UBG_ServerListWidget::AddServerRow(FString sessionName, int32 sessionOpenPlayerCount, int32 sessionMaxPlayerCount, int32 sessionPing, int32 sessionIndex)
{
	if (wServerRowWidget) {
		UE_LOG(LogTemp, Warning, TEXT("Server List Widget: Creating Server Row User Widget"));
		UUserWidget* serverRowUserWidget = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), wServerRowWidget);
		//UBG_ServerRowWidget* serverRowWidget = NewObject<UBG_ServerRowWidget>(UBG_ServerRowWidget::StaticClass());
		if (serverRowUserWidget) {
			UE_LOG(LogTemp, Warning, TEXT("Server List Widget: Add Server Row"));
			ServerRowScrollBox->AddChild(serverRowUserWidget);
			
			UBG_ServerRowWidget* serverRowWidget = Cast<UBG_ServerRowWidget>(serverRowUserWidget);
			serverRowWidget->InitializeServerRowWidget(sessionName, sessionOpenPlayerCount, sessionMaxPlayerCount, sessionPing, sessionIndex);
			serverRowWidget->SetupServerRowWidgetEvent();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Server List Widget: Server Row User Widget Not Valid"));

		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Server List Widget: Server Row Widget Subclass Not Valid"));

	}
}



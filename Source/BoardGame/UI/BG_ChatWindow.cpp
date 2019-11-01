// Fill out your copyright notice in the Description page of Project Settings.

#include "BG_ChatWindow.h"



void UBG_ChatWindow::InitializeChatWindow(UEditableTextBox* textBox, UScrollBox* scrollBox){
	ChatTextBox = textBox;
	ChatScrollBox = scrollBox;
}


UEditableTextBox* UBG_ChatWindow::GetChatTextBox(){
	return ChatTextBox;
}


UScrollBox* UBG_ChatWindow::GetChatScrollBox(){
	return ChatScrollBox;
}

// Fill out your copyright notice in the Description page of Project Settings.
/*
MapManager
Description: This class controls the In Game Map. It is created by the Game Mode when the level is first loaded. 
Eventually, the map manager will generate the terrain based off of a seed. For now we just want the tiles to be 
dynamically spawned based off of the number of players in the game.


*/
#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BOARDGAME_API MapManager
{
public:
	/*
	MapManager

	Description:	Map Manager Constructor. Initializes all member variables.
	
	Inputs:			int32 NumPlayers - The number of players in the game.

	Outputs:		None
	*/
	MapManager(int32 NumPlayers);

	/*
	~MapManager

	Description:	Map Manager Destructor. Deletes all allocated variables.

	Inputs:			None

	Outputs:		None
	
	*/
	~MapManager();

private:

};

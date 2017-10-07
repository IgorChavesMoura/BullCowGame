#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"


FBullCowGame BCGame;


int main(){
	BCGame = FBullCowGame::CreateGame();
	
	BCGame.RunGame();

	FBullCowGame::DestroyGame(BCGame);
	return EXIT_SUCCESS;
}




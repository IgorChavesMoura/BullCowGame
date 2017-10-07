#include "stdafx.h"
#include "FBullCowGame.h"


FBullCowGame::FBullCowGame() {
	Reset();
}



int32 FBullCowGame::GetMaxTries() const {
	
	TMap <int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} }; //Variable initialization syntatic sugar
	
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}


void FBullCowGame::Reset(){

	const FString HIDDEN_WORD = "planet";

	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bWon = false;
	
	return;
}
bool FBullCowGame::IsGameWon() const {
	
	return bWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess){
	
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram; 
	}
	
	if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}

	if (Guess.length() !=  GetHiddenWordLength() ) {
		return EGuessStatus::Wrong_Length;
	}

	return EGuessStatus::OK;

}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){


	MyCurrentTry++;

	FBullCowCount BCCount;

	int32 HiddenWordLength = GetHiddenWordLength();

	for (int32 i = 0; i < HiddenWordLength; i++) {
		for (int32 j = 0; j < HiddenWordLength; j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) {
					BCCount.Bulls++;
				} else {
					BCCount.Cows++;
				}
			}
		}
	}
	if (BCCount.Bulls == GetHiddenWordLength()) {
		bWon = true;
	}


	return BCCount;
}

int32 FBullCowGame::GetHiddenWordLength() const{
	return MyHiddenWord.length();
}

void FBullCowGame::PlayGame(){
}

bool FBullCowGame::AskToPlayAgain(){
	return false;
}

void FBullCowGame::PrintIntro(){
}

bool FBullCowGame::IsIsogram(FString Guess) const {
	
	//Treat 0 and 1 letter word as isograms
	if (Guess.length() <= 1) {
		return true;
	}
	
	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess) { //auto means the compiler will decide which type the variable will be 
		Letter = tolower(Letter);

		if (!!LetterSeen[Letter]) {
			return false;
		}
		LetterSeen[Letter] = true;
	}

	
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const {
	
	TMap <char, bool> Letters;

	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	
	return true;
}

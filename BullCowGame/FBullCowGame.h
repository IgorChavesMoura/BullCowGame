#pragma once

#include <string>

#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus { //Strongly defined enum, smaller scope
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame {
public:

	FBullCowGame();
	int32 GetMaxTries() const ;
	int32 GetCurrentTry() const ;
	int32 GetHiddenWordLength() const;
	
	void Reset();
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString);
	FBullCowCount SubmitValidGuess(FString);



	void PlayGame();
	bool AskToPlayAgain();
	void PrintIntro();


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bWon;

	bool IsIsogram(FString) const ;
	bool IsLowercase(FString) const ;
	
};
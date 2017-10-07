#pragma once

#include <string>

#define TMap std::map

//Unreal cross platform API

using FText = std::string;
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



	

	//Unreal code pattern, all variables and functions names are capitalized

	void PrintIntro(); //Signature of the function
	FText GetGuess();
	void PrintGuess(FText);
	void PlayGame();
	bool AskToPlayAgain();
	void PrintGameSummary();
	void RunGame();
	static FBullCowGame CreateGame();
	static void DestroyGame(FBullCowGame);



private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bWon;

	bool IsIsogram(FString) const ;
	bool IsLowercase(FString) const ;
	
};
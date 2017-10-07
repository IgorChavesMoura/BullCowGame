#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"

//Unreal cross platform API

using FText = std::string;
using int32 = int; 

//Unreal code pattern, all variables and functions names are capitalized

void PrintIntro(); //Signature of the function
FText GetGuess();
void PrintGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;


int main(){

	

	bool bCanPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bCanPlayAgain = AskToPlayAgain();

	} while (bCanPlayAgain);

	return EXIT_SUCCESS;
}



void PrintIntro() { 

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of ?" << "\n";

	return;
}


FText GetGuess() {


	


	FText Guess = " ";
	EGuessStatus Status;
	
	do {
		int CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " - Turns left: "<< (BCGame.GetMaxTries() - BCGame.GetCurrentTry()) << std::endl;
		
		std::cout << "Enter your guess: ";

		//Get the whole line until the line break (\n)
		getline(std::cin, Guess);
		
		Status = BCGame.CheckGuessValidity(Guess);


		switch (Status) {
			case EGuessStatus::Wrong_Length:

				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word" << std::endl;

				break;

			case EGuessStatus::Not_Lowercase:

				std::cout << "Please enter all lowercase letters" << std::endl;

				break;

			case EGuessStatus::Not_Isogram:

				std::cout << "Please enter a word without repeating letters" << std::endl;

				break;

			


		}
		

	} while (Status != EGuessStatus::OK);
	
	return Guess;

}
void PrintGuess(FText Guess) {
	
	std::cout << "Your guess was: " << Guess << "\n";
}
void PlayGame() { 	

	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= BCGame.GetMaxTries())) {

		FText Guess = GetGuess(); 
		

		PrintGuess(Guess);

		FBullCowCount BCCount = BCGame.SubmitValidGuess(Guess);
		 
		std::cout << "Bulls: " << BCCount.Bulls << std::endl;
		std::cout << "Cows: " << BCCount.Cows << std::endl;

		std::cout << std::endl;
		
	}
	
	PrintGameSummary();

	return;

}
bool AskToPlayAgain() {
	
	std::cout << "Do you want to play again with the same hidden word ? (y/n) ";
	std::string Response = " ";
	getline(std::cin, Response);

	std::cout << std::endl;
		
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE! YOU WIN" << std::endl;
	}
	else {
		std::cout << "Better luck next time." << std::endl;
	}
}
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

bool FBullCowGame::IsIsogram(FString Guess) const {
	
	//Treat 0 and 1 letter word as isograms
	if (Guess.length() <= 1) {
		return true;
	}
	
	TMap<char, bool> LetterSeen = *(new TMap<char, bool>());;

	for (auto Letter : Guess) { //auto means the compiler will decide which type the variable will be 
		Letter = tolower(Letter);

		if (!!LetterSeen[Letter]) {
			delete &LetterSeen;
			return false;
		}
		LetterSeen[Letter] = true;
	}

	delete &LetterSeen;
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const {
	
	TMap <char, bool> Letters = *(new TMap<char,bool>());

	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			delete &Letters;
			return false;
		}
	}
	delete &Letters;
	return true;
}
void FBullCowGame::PrintIntro() {

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << GetHiddenWordLength() << " letter isogram I'm thinking of ?" << "\n";

	return;
}


FText FBullCowGame::GetGuess() {





	FText Guess = " ";
	EGuessStatus Status;

	do {
		int CurrentTry = GetCurrentTry();

		std::cout << "Try " << CurrentTry << " - Turns left: " << (GetMaxTries() - GetCurrentTry()) << std::endl;

		std::cout << "Enter your guess: ";

		//Get the whole line until the line break (\n)
		getline(std::cin, Guess);

		Status = CheckGuessValidity(Guess);


		switch (Status) {
		case EGuessStatus::Wrong_Length:

			std::cout << "Please enter a " << GetHiddenWordLength() << " letter word" << std::endl;

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
void FBullCowGame::PrintGuess(FText Guess) {

	std::cout << "Your guess was: " << Guess << "\n";
}
void FBullCowGame::PlayGame() {

	Reset();

	int32 MaxTries = GetMaxTries();

	while (!IsGameWon() && (GetCurrentTry() <= GetMaxTries())) {

		FText Guess = GetGuess();


		PrintGuess(Guess);

		FBullCowCount BCCount = SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BCCount.Bulls << std::endl;
		std::cout << "Cows: " << BCCount.Cows << std::endl;

		std::cout << std::endl;

	}

	PrintGameSummary();

	return;

}
bool FBullCowGame::AskToPlayAgain() {

	std::cout << "Do you want to play again with the same hidden word ? (y/n) ";
	std::string Response = " ";
	getline(std::cin, Response);

	std::cout << std::endl;

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void FBullCowGame::PrintGameSummary() {
	if (IsGameWon()) {
		std::cout << "WELL DONE! YOU WIN" << std::endl;
	}
	else {
		std::cout << "Better luck next time." << std::endl;
	}
}

void FBullCowGame::RunGame(){
	bool bCanPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bCanPlayAgain = AskToPlayAgain();

	} while (bCanPlayAgain);
}

FBullCowGame FBullCowGame::CreateGame(){
	FBullCowGame* BCGame = new FBullCowGame();

	return *BCGame;


}

void FBullCowGame::DestroyGame(FBullCowGame BCGame){
	delete &BCGame;
}

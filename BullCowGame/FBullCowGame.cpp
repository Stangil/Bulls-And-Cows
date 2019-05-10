#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return  MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planets";

	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)const
{
	if (MyHiddenWord.length() != Guess.length())
	{
	return EGuessStatus::Wrong_Length;
	}
	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;//TODO write function
	}
	else if (false)// do we even need this check?
	{
		return EGuessStatus::Not_Lowercase;//TODO write function
	}
	
	else if (false)// if the guess contains incorrect characters ie numbers or symbols
	{
		return EGuessStatus::Invalid_Characters;//TODO write function may want to include in isogram test
	}
	else
	{
		return EGuessStatus::OK;
	}

}

//recieves a Valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	//loop through all letters in hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		//compares letters against the guess
		//If they match
		if (Guess[i] == MyHiddenWord[i])
		{
			//Increment bulls if in the same place
			BullCowCount.Bulls++;
		}
		else {
			
			for (int32 j = 0; j < WordLength; j++)
			{
				//If they match
				if (Guess[i] == MyHiddenWord[j])
				{
					//increment cows if not
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) { 
		bGameWon = true; 
	} else { 
		bGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

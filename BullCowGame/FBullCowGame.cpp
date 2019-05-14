#pragma once
#include "FBullCowGame.h"
#include <map>
//To make the game Unreal syntax friendly
#define TMap std::map


FBullCowGame::FBullCowGame(){ Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return  MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,6},{5,10},{6,15},{7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";//This MUST be and isogram (No repeating letters)

	MyHiddenWord = HIDDEN_WORD;
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
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
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

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

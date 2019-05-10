#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Invalid_Characters,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); //TODO Better return value
	FBullCowCount SubmitValidGuess(FString);

private:
	//See constructor for initilization
	int32 MyMaxTries;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;

};


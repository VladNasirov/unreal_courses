#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES=8;

	const FString HIDDEN_WORD = "ant";

	MyHiddenWord = HIDDEN_WORD;

	MyMaxTry = MAX_TRIES;

	MyCurrentTry = 1;

	bGameIsWon = false;

	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,5}, {6,5} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{

	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if(guess.length()!=GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

//recives a VALID guess, incriments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (MyHiddenWord[MHWChar] == guess[GChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	//compare leters against the hidden word
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString guess) const
{
	if (guess.length() <= 1)
	{
		return true;
	}
	else
	{
		TMap <char, bool> LetterSeen;
		for (auto Letter : guess) //for all letters of the guess
		{
			Letter = tolower(Letter);
			if (LetterSeen[Letter]) //letter already in the map
			{
				return false; 
			}
			else
			{
				LetterSeen[Letter] = true; //add the letter to the map
			}
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString guess) const
{
	for (auto Letter : guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

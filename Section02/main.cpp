/* This is the console executable, that makes use of the BullCow class
This acts as the view of the MVC pattern, and is responsible for all user interaction. For game logic see the FBullCowGame class.

*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;//user interaction text
using int32 = int;
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;

int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
}

void PrintIntro()
{
	std::cout << "\nWelcome to the BullCowGame" << std:: endl;
	std::cout << "Try to guess the " << BCGame.GetHiddenWordLength() << " letters isogram I`m thinking of." << std::endl;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries=BCGame.GetMaxTries();
	FText guess;
	//TODO change from FOR to WHILE loop once we are validating tries
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	{
			guess = GetValidGuess(); //TODO make loop checking valid
			//submit valid guess to the game
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
			//print number of bulls and cows
			std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows= " << BullCowCount.Cows << std::endl;
	}
	PrintGameSummary();
	return;
}

FText GetValidGuess()
{
	EGuessStatus status = EGuessStatus::Invalid;
	FText Guess;
	do
	{

		std::cout << "\nTry " << BCGame.GetCurrentTry()<<" of "<<BCGame.GetMaxTries()<< std::endl;
		std::cout << "Input your guess: ";
		std::getline(std::cin, Guess);
		status = BCGame.CheckGuessValidity(Guess);
		switch (status)
		{
		case(EGuessStatus::Not_Lowercase):
		{
			std::cout << "Please enter the word, using lowercase letters.\n\n";
			break;
		}
		case(EGuessStatus::Not_Isogram):
		{
			std::cout << "Please enter the word without repeating leters.\n\n";
			break;
		}
		case(EGuessStatus::Wrong_Length):
		{
			std::cout << "Please enter the " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		}
		default:
			break;
		}
	} while (status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	FText Response;
	std::cout << "\nDo you want to continue playing?" << std::endl;
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done! You Win!" << std::endl;
	}
	else
	{
		std::cout << "Better luck next time!" << std::endl;
	}
}
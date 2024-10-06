/*This is my first project. It's from Dr. Mohammed Abou-Hadhoud
* 
				Stone-Scissor-Paper Game.                      */


#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
using namespace std;


enum enGameChoice { Stone = 1, Paper, Scissor };

enum enWinner { Player = 1, Computer, Draw };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice ;
	enWinner Winner;
	string WinnerName = "";
};

struct stGameResults
{
	short GameRounds = 0;
	short PlayerWins = 0;
	short ComputerWins = 0;
	short DrawsTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

string Tabs(int Number)
{
	string Tabs = "";
	for (int i = 0; i < Number; i++)
	{
		Tabs += "\t";
	}

	return Tabs;
}

enGameChoice ReadPlayerChoice()
{
	short PlayerChoice = 1;
	do
	{
		cout << "\nYour Choice [1]Stone  [2]Paper  [3]Scissor:  ";
		cin >> PlayerChoice;
	} while (PlayerChoice < 1 || PlayerChoice > 3);
	return (enGameChoice) PlayerChoice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;
	case enGameChoice::Paper:
		if(RoundInfo.ComputerChoice == enGameChoice::Scissor)
			return enWinner::Computer;
	case enGameChoice::Scissor:
		if(RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;
	}

	return enWinner::Player;

}

string ChoiceName(enGameChoice Choice)
{
	string ArrChoiceName[3] = { "Stone", "Paper", "Scissor" };
	return ArrChoiceName[Choice - 1];
}

string GetWinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player", "Computer", "No One" };
	return ArrWinnerName[Winner - 1];
}

void SetScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	case enWinner::Player:
		system("color 2F");
		break;
	default:
		system("color 6F");
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player Choice  : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
	cout << "__________________________________\n" << endl;
	SetScreenColor(RoundInfo.Winner);
}

enWinner GetGameWinner(short PlayerWins, short ComputerWins)
{
	if (PlayerWins > ComputerWins)
		return enWinner::Player;
	else if (ComputerWins > PlayerWins)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(short GameRounds, short PlayerWins, short ComputerWins, short Draws)
{
	stGameResults GameResults;
	GameResults.ComputerWins = ComputerWins;
	GameResults.GameRounds = GameRounds;
	GameResults.PlayerWins = PlayerWins;
	GameResults.DrawsTimes = Draws;
	GameResults.GameWinner = GetGameWinner(PlayerWins, ComputerWins);
	GameResults.WinnerName = GetWinnerName(GameResults.GameWinner);

	return GameResults;
}

short ReadHowManyRounds()
{
	short Rounds = 0;
	do
	{
		cout << "Enter how many rounds 1 => 10 : ";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds > 10);
	return Rounds;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWins = 0, ComputerWins = 0, Draws = 0;

	for (int GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = GetWinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
			PlayerWins++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWins++;
		else
			Draws++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, PlayerWins, ComputerWins, Draws);
}

void PrintGameOverScreen() 
{
	cout << Tabs(2) << "__________________________________________________________\n\n";
	cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "__________________________________________________________\n\n";
}

void PrintGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "______________________[Game Results]______________________\n\n";
	cout << Tabs(2) << "Game Rounds       : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player won times  : " << GameResults.PlayerWins << endl;
	cout << Tabs(2) << "Computer won time : " << GameResults.ComputerWins << endl;
	cout << Tabs(2) << "Draw Times        : " << GameResults.DrawsTimes << endl;
	cout << Tabs(2) << "Final Winner      : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "___________________________________________________________\n";
	SetScreenColor(GameResults.GameWinner);
}

void RestScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		RestScreen();

		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		PrintGameOverScreen();
		PrintGameResults(GameResults);

		cout << endl << Tabs(2) << "Do want to play	again Y/N : ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
	//Seed the random number generator in C++, Called only once
	srand((unsigned)time(NULL));

	StartGame();


	return 0;
}
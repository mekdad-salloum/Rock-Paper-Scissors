#include <iostream>

using namespace std;

enum enWinner {Player = 1, Computer = 2, Draw = 3};

enum enChoice {Rock = 1, Paper = 2, Scissors = 3};

struct strGame
{
	short NumberOfRounds = 0;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
};

struct strRound
{
	short RoundNumber  = 0;
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner RoundWinner;
};

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
		case enWinner::Player:
		{
			system("color 2F");
			break;
		}

		case enWinner::Computer:
		{
			system("color 4F");
			cout << "\a";
			break;
		}

		case enWinner::Draw:
		{
			system("color 6F");
			break;
		}
	}
}

int GetRandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

string GetChoiceName(enChoice Choice)
{
	string Choices[3] = { "Rock", "Paper", "Scissors" };
	return Choices[Choice - 1];
}

string GetWinnerName(enWinner Winner)
{
	string Winners[3] = { "Player", "Computer", "Draw" };
	return Winners[Winner - 1];
}

short ReadNumberOfRounds()
{
	short Number;

	cout << "How Many Rounds 1 To 10?\n";
	cin >> Number;

	while (cin.fail() || Number < 1 || Number > 10)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Input, Enter A Number Between 1 And 10: ";
		cin >> Number;
	}

	return Number;
}

enChoice ReadPlayerChoice()
{
	short PlayerChoice;

	cout << "\nYour Choice: 1) Rock, 2) Paper, 3) Scissors?\n";
	cin >> PlayerChoice;

	while (cin.fail() || PlayerChoice < 1 || PlayerChoice > 3)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Invalid Input, Enter A Number Between 1 And 3: ";
		cin >> PlayerChoice;
	}

	return (enChoice)PlayerChoice;
}

enChoice GetComputerChoice()
{
	return (enChoice)GetRandomNumber(1, 3);
}

enWinner WhoWonTheRound(enChoice PlayerChoice, enChoice ComputerChoice)
{
	if (PlayerChoice == ComputerChoice)
		return enWinner::Draw;

	switch (PlayerChoice)
	{
		case enChoice::Rock:
		{
			if (ComputerChoice == enChoice::Scissors)
			{
				return enWinner::Player;
			}

			break;
		}

		case enChoice::Paper:
		{
			if (ComputerChoice == enChoice::Rock)
			{
				return enWinner::Player;
			}

			break;
		}

		case enChoice::Scissors:
		{
			if (ComputerChoice == enChoice::Paper)
			{
				return enWinner::Player;
			}

			break;
		}
	}
	
	return enWinner::Computer;
}

void PlayRound(strRound &Round)
{
	cout << "\nRound [" << Round.RoundNumber << "] Begins: ";
	Round.PlayerChoice = ReadPlayerChoice();
	Round.ComputerChoice = GetComputerChoice();
	Round.RoundWinner = WhoWonTheRound(Round.PlayerChoice, Round.ComputerChoice);
}

void PrintRoundResult(strRound Round)
{
	cout << "\n----------Round (" << Round.RoundNumber << ")----------------\n";
	cout << "\nPlayer Choice  : " << GetChoiceName(Round.PlayerChoice);
	cout << "\nComputer Choice: " << GetChoiceName(Round.ComputerChoice);
	cout << "\nRound Winner   : " << GetWinnerName(Round.RoundWinner);
	cout << "\n-----------------------------------\n\n";
	SetWinnerScreenColor(Round.RoundWinner);
}

enWinner WhoWonTheGame(short PlayerWonTimes, short ComputerWonTimes)
{
	if (PlayerWonTimes > ComputerWonTimes)
		return enWinner::Player;

	else if (PlayerWonTimes < ComputerWonTimes)
		return enWinner::Computer;

	else
		return enWinner::Draw;
}

strGame FillGameResult(short NumberOfRounds, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes)
{
	strGame Game;

	Game.NumberOfRounds = NumberOfRounds;
	Game.PlayerWonTimes = PlayerWonTimes;
	Game.ComputerWonTimes = ComputerWonTimes;
	Game.DrawTimes = DrawTimes;
	Game.GameWinner = WhoWonTheGame(PlayerWonTimes, ComputerWonTimes);

	return Game;
}

strGame PlayRounds(short NumberOfRounds)
{
	strRound Round;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

	for (short RoundNumber = 1; RoundNumber <= NumberOfRounds; RoundNumber++)
	{
		Round.RoundNumber = RoundNumber;
		PlayRound(Round);
		PrintRoundResult(Round);

		if (Round.RoundWinner == enWinner::Player)
			PlayerWonTimes++;

		else if (Round.RoundWinner == enWinner::Computer)
			ComputerWonTimes++;

		else
			DrawTimes++;
	}

	return FillGameResult(NumberOfRounds, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

string Tabs(short NumberOfTabs)
{
	string T;

	for (short i = 1; i <= NumberOfTabs; i++)
	{
		T += "\t";
	}
	return T;
}

void PrintGameOverScreeen()
{
	cout << Tabs(4) << "-----------------------------------------------------\n";
	cout << Tabs(6) << "*** G A	M E  O V E R ***\n";
	cout << Tabs(4) << "-----------------------------------------------------\n";

}

void PrintGameResult(strGame Game)
{
	cout << Tabs(4) << "---------------------(Game Result)-------------------\n";
	cout << Tabs(4) << "Game Rounds       : " << Game.NumberOfRounds << endl;
	cout << Tabs(4) << "Player Won Times  : " << Game.PlayerWonTimes << endl;
	cout << Tabs(4) << "Computer Won Times: " << Game.ComputerWonTimes << endl;
	cout << Tabs(4) << "Draw Times        : " << Game.DrawTimes << endl;
	cout << Tabs(4) << "Game Winner       : " << GetWinnerName(Game.GameWinner) << endl;
	cout << Tabs(4) << "-----------------------------------------------------\n";
	SetWinnerScreenColor(Game.GameWinner);
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		strGame Game = PlayRounds(ReadNumberOfRounds());
		PrintGameOverScreeen();
		PrintGameResult(Game);

		cout << Tabs(4) << "Do You Want To Play Again? (Y/N) ";
		cin >> PlayAgain;

	} while (toupper(PlayAgain) == 'Y');

}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
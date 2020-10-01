#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "Files.h"
#define  del cin.clear();cin.ignore(100000, '\n');
using namespace std;

bool checker = 1, p = 1, ops = 1;
float num_columns, sum = 0;
char table[20][26], check_table[20][26], Variable, index, YE;
int pieces_of_column[26];
string player1, player2, n_col;
char valid;
bool isMisere = 0, isValid = 1, Sound = true, finl = 1;
map<char, long long>mp;
int num_pieces, num_Rpieces, to = 0;

struct nim {
	string name[100];
	int score[100];
};

nim SO_player;

bool find(string pla) {
	for (int i = 0; i < to; i++) {
		if (pla == SO_player.name[i]) {
			return 1;
		}
	}
	return 0;
}

void pla1(string player_T) {
	for (int coi = 0; coi < to; coi++) {
		if (SO_player.name[coi] == player_T) {
			if (isMisere) {
				SO_player.score[coi] += 2;
				break;
			}
			else {
				SO_player.score[coi] += 3;
				break;
			}
		}
	}
}

void Sort() {
	for (int i = 0; i < to; i++) {
		for (int j = i + 1; j < to; j++) {
			if (SO_player.score[j] > SO_player.score[i]) {
				swap(SO_player.score[i], SO_player.score[j]);
				swap(SO_player.name[i], SO_player.name[j]);
			}
		}
	}
}



void File_Sc() {
	Sort();
	fstream file;
	file.open("ScoreBoard.txt", ios::out);
	for (int i = 0; i < to; i++) {
		if (i == to - 1) {
			file << SO_player.name[i] << "\t\t\t\t\t" << SO_player.score[i];
			break;
		}
		file << SO_player.name[i] << "\t\t\t\t\t" << SO_player.score[i] << "\n";
	}
	file.close();
}


void check_col() {
	checker = 1, p = 1, n_col.clear();
	do {
		if (!checker) {
			cout << "Ops! Invalid input .. Number of columns must be from 1 to 26 .Please re - enter the number of columns : " << endl;
			n_col.clear();
		}
		checker = 0;
		getline(cin, n_col);
		for (int i = 0; i < n_col.size(); i++) {
			if (n_col[i] < '1' || n_col[i] > '9') {
				p = 1;
				break;
			}
			p = 0;
		}
		if (!p) {
			num_columns = stoll(n_col);
			if (num_columns > 26 || num_columns <= 0) {
				p = 1;
			}
		}
	} while (p);
}

void check_pec() {
	p = 1, n_col.clear(), checker = 1;
	do {
		if (!checker) {
			cout << "Ops! Invalid input .. Number of columns must be from 1 to 20 .Please re - enter the number of pieces : " << endl;
			n_col.clear();
		}
		checker = 0;
		getline(cin, n_col);
		for (int i = 0; i < n_col.size(); i++) {
			if (n_col[i] < '1' || n_col[i]>'9') {
				p = 1;
				break;
			}
			p = 0;
		}
		if (!p) {
			num_pieces = stoll(n_col);
			if (num_pieces > 20 || num_pieces <= 0) {
				p = 1;
			}
		}
	} while (p);
}

void check_index() {
	p = 1, n_col.clear(), checker = 1;
	do {
		if (!checker) {
			cout << "Ops! Invalid input .. Enter new index" << endl;
			n_col.clear();
		}
		checker = 0;
		getline(cin, n_col);
		if (n_col.size() == 1) {
			for (int i = 0; i < n_col.size(); i++) {
				if (n_col[i] >= 'A' && n_col[i] <= 'Z' || n_col[i] >= 'a' && n_col[i] <= 'z') {
					p = 0;
				}
				else {
					p = 1;
					break;
				}
			}
		}
		if (!p) {
			if (n_col[0] >= 'A'&&n_col[0] <= 'Z' || n_col[0] >= 'a'&&n_col[0] <= 'z') {
				if (mp[n_col[0]] != 0) {
					index = n_col[0];
				}
				else {
					p = 1;
				}
			}
			else {
				p = 1;
			}
		}
	} while (p);
}

void check_npec(int column) {
	checker = 1, n_col.clear(), p = 1;
	do {
		if (!checker) {
			cout << "Ops! Invalid input ... Please re - enter the number of Circles : " << endl;
			n_col.clear();
		}
		checker = 0;
		getline(cin, n_col);
		for (int i = 0; i < n_col.size(); i++) {
			if (n_col[i] < '1' || n_col[i] > '9') {
				p = 1;
				break;
			}
			p = 0;
		}
		if (!p) {
			num_Rpieces = stoll(n_col);
			if (num_Rpieces > pieces_of_column[column] || num_Rpieces <= 0) {
				p = 1;
			}
		}
	} while (p);
}

void input_data()
{
	system("CLS");
	Choose_Version();
	isMisere = 0;
	char version;
	while (true) {
		version = _getch();
		if (version == '1' || version == '2')
			break;
	}
	cout << endl;
	if (version == '2') {
		isMisere = 1;
	}
	cout << "Player 1 name: ";
	do {
		getline(cin, player1);
	} while (player1.empty());
	if (!find(player1)) {
		SO_player.name[to++] = player1;
	}
	cout << "Player 2 name: ";
	do {
		getline(cin, player2);
		if (player1 == player2) {
			cout << "ERROR, Enter another name " << endl;
			player2.clear();
		}
	} while (player2.empty());
	if (!find(player2)) {
		SO_player.name[to++] = player2;
	}
	cout << "Number of columns: ";
	check_col();
	//num_columns = check_columns(num_columns);
}


void setting_table(int num_columns)
{
	sum = 0;
	char index = 'A';
	system("CLS"); {
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < num_columns; j++)
			{
				table[i][j] = '.';
				check_table[i][j] = '.';
				cout << table[i][j] << "   ";
			}
			cout << endl;
		}
		for (int i = 1; i <= num_columns; i++, index++)
		{
			cout << index << "   ";

		}
		cout << endl;
	}
	index = 'A';
	for (int j = 0; j < num_columns; j++)
	{
		cout << "Enter the number of pieces of column "
			<< index << ": ";
		check_pec();
		mp[index] = num_pieces;
		mp[tolower(index)] = num_pieces;
		//num_pieces = check_pieces(num_pieces);
		sum += num_pieces;
		system("CLS");
		{
			for (int i = 19, w = 0; w < num_pieces; w++, i--)
			{
				table[i][j] = 'O';
				pieces_of_column[j]++;
			}
			index++;
		}
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < num_columns; j++)
			{
				cout << table[i][j] << "   ";
			}
			cout << endl;
		}
		char indexx = 'A';
		for (int i = 1; i <= num_columns; i++, indexx++)
		{
			cout << indexx << "   ";
		}
		cout << endl;
	}
}


void play(int sum)
{
	int turn = 1, z = 0;
	bool PL1 = 1;
	while (true)
	{
		system("CLS");
		{
			system("CLS");
			{
				for (int i = 0; i<20; i++)
				{
					for (int j = 0; j<num_columns; j++)
					{
						cout << table[i][j] << "   ";
					}
					cout << endl;
				}
				char indexx = 'A';
				for (int i = 1; i <= num_columns; i++, indexx++)
				{
					cout << indexx << "   ";
				}
				cout << endl;
			}
			if (sum == 0)
			{
				system("cls");
				{
					if (isMisere) {
						if (turn == 1)
							PL1 = 0;
						else
							PL1 = 1;
					}
					if (PL1) {
						pla1(player1);
						cout << "\t\t" << player1 << " WINS!\n"
							<< "---------------------------------------------------------\n"
							<< "Press \"M\" for Main Menu , \"E\" to Exit: ";
						File_Sc();
						do {
							valid = _getch();
						} while (valid != 'M'&&valid != 'm'&&valid != 'e'&&valid != 'E');
						ops = 1;
						break;
					}
					else {
						pla1(player2);
						cout << "\t\t" << player2 << " WINS!\n"
							<< "---------------------------------------------------------\n"
							<< "Press \"M\" for Main Menu , \"E\" to Exit: ";
						File_Sc();
						do {
							valid = _getch();
						} while (valid != 'M'&&valid != 'm'&&valid != 'e'&&valid != 'E');
						ops = 1;
						break;
					}
				}
			}
			if (PL1) {
				cout << player1 << "'s turn:\n";
			}
			else {
				cout << player2 << "'s turn:\n";
			}
			cout << "Type the index of the column to remove from:";
			//cin >> index;
			check_index();
			//index = check_index(index, num_columns, pieces_of_column);
			int column = (toupper(index) - 'A');
			cout << "How many pieces do you want to remove:";
			//cin >> num_Rpieces;
			check_npec(column);
			//num_Rpieces = check_Rpieces(num_Rpieces, pieces_of_column[column]);
			mp[index] -= num_Rpieces;
			for (int i = 20 - pieces_of_column[column]; z < num_Rpieces; i++)
			{
				if (table[i][column] == '.')
				{
					continue;
				}
				else
				{
					table[i][column] = '.';
					z++;
				}
			}
			pieces_of_column[column] -= num_Rpieces;

			z = 0;
			sum -= num_Rpieces;
			if (sum == 0)
				continue;
			if (turn == 1) {
				turn = 2;
				PL1 = 0;
			}
			else {
				turn = 1;
				PL1 = 1;
			}
		}
	}
}

void Store() {
	ifstream file;
	file.open("ScoreBoard.txt");
	while (!file.eof()) {
		file >> SO_player.name[to] >> SO_player.score[to];
		if (SO_player.name[to] == "@@") {
			finl = 0;
			break;
		}
		to++;
	}
	file.close();
}

void Not_Solve() {
	fstream file;
	int con = 0;
	file.open("ScoreBoard.txt", ios::out);
	while (con != 6) {
		con++;
		if (con == 6) {
			file << "@@" << "\t\t\t\t\t--";
			break;
		}
		file << "@@" << "\t\t\t\t\t--" << endl;
	}
	file.close();
}

int main()
{
	system("cls"); {
		cout << "\t\t\t\t\t\t\tIf you want to store date ,Enter (1) and any other to clear data :- ";
		YE = _getch();
		if (YE == '1') {
			Store();
			if (finl) {
				File_Sc();
			}
		}
		else {
			Not_Solve();
		}
	}
	while (true) {
		isMisere = 0;
		if (ops) {
			system("cls"); {
				Nim_Game();
				if (Sound) {
				PlaySound(TEXT("Data\\Nim_Game.wav"), NULL, SND_SYNC);
				}
				menu();
				ops = 0;
			}
		}
		Variable = _getch();
		if (Variable == '1') {
			input_data();
			setting_table(num_columns);
			play(sum);
			if (valid == 'E' || valid == 'e') {
				break;
			}
		}
		else if (Variable == '2') {
			system("CLS"); {
				Instructions();
			}
			system("cls"); {
				Nim_Game();
				menu();
			}
		}
		else if (Variable == '3') {
			system("CLS"); {
				Credits();
			}
			system("cls"); {
				Nim_Game();
				menu();
			}
		}
		else if (Variable == '4') {
			system("CLS"); {
				cout << "\t\t\t\t\t\t\t\t\t\t" << "# Score Board #" << endl;
				Draw_Score();
			}
			system("cls"); {
				Nim_Game();
				menu();
			}
		}
		else if (Variable == '5') {
			Not_Solve();
			system("cls"); {
				cout << "\t\t\t\t\t\t\t\tdone!" << endl;
				cout << "\t\t\t\t\t\t\t\tpress any key to go back";
				SO_player.name->clear(), memset(SO_player.score, 0, sizeof(SO_player.score));
				to = 0;
				char is_back;
				is_back = _getch();
			}
			system("cls"); {
				Nim_Game();
				menu();
			}
		}
		else if (Variable == '6') {
			break;
		}
		Sound = false;
		Variable = 0;
	}
	system("CLS"); {
		End_Game();
		PlaySound(TEXT("Data\\End_Game.wav"), NULL, SND_SYNC);
	}
	return 0;
}

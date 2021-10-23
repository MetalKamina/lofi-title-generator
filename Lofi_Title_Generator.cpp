//Author: kamina
//Reason: literally none

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void menu(int &numNouns, int &numAdj, string nouns[], string adj[]);
void randTitle(int amt, int numNouns, int numAdj, string nouns[], string adj[]);
void importWords(fstream &stream, string nouns[], int &numNouns, string adj[], int &numAdj);

const int MAX_ARRAY = 100;

int main()
{
	fstream stream;
	string nouns[MAX_ARRAY];
	string adj[MAX_ARRAY];
	int numNouns = 0;
	int numAdj = 0;

	
	importWords(stream, nouns, numNouns, adj, numAdj);


	menu(numNouns, numAdj, nouns, adj);



	return 0;
}

void menu(int &numNouns, int &numAdj, string nouns[], string adj[]) {
	char choice = 'M';

	while (choice != 'E') {
		int maxNum;
		if (choice == 'M') {
			cout << endl << "Menu" << endl << "----" << endl << endl;
			cout << "Make a selection by pressing a key and then hitting enter." << endl << endl;
			cout << "Would you like a (R)andom lofi song title, main (M)enu, or to (E)xit?" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			choice = toupper(choice);
		}

		if (choice == 'R') {
			char again = 'Y';
			if (numNouns < numAdj) {
				maxNum = numNouns;
			}
			else {
				maxNum = numAdj;
			}
			while (again == 'Y') {
				cout << "Please enter the amount of song titles you want. Max is " << maxNum << ": ";
				int amt;
				cin >> amt;
				
				randTitle(amt, numNouns, numAdj, nouns, adj);
				maxNum -= amt;
				cout << "Go again? (Y/N) or reset words (R) : ";
				cin >> again;
				again = toupper(again);
				cout << endl;
				if (again == 'N') {
					choice = 'M';
				}
				else if (again == 'R') {
					fstream stream;
					maxNum = 0;
					numNouns = 0;
					numAdj = 0;
					importWords(stream, nouns, numNouns, adj, numAdj);
					cout << "List reset." << endl;
					choice = 'M';
				}
				else {
					cout << "Sorry, please try something else." << endl;
					choice = 'M';
				}
			}
		}





	}
	cout << "Exiting...";
}



void randTitle(int amt, int numNouns, int numAdj, string nouns[], string adj[]) {
	srand(time(NULL));
	for (int i = 0; i < amt; i++) {
		char goodTitle = 'N';
		while (goodTitle == 'N') {
			int rn = rand() % numNouns;
			int ra = rand() % numAdj;
			if (nouns[rn] != "" && adj[ra] != "") {
				cout << adj[ra] << " " << nouns[rn] << endl;
				adj[ra] = "";
				nouns[rn] = "";
				goodTitle = 'Y';
			}
		}
	}
	cout << endl;
}

void importWords(fstream &stream, string nouns[], int &numNouns, string adj[], int &numAdj) {
	stream.open("nouns.txt", ios::in);

	cout << "Inputting nouns..." << endl;
	getline(stream, nouns[numNouns]);
	while (!stream.eof()) {
		numNouns++;
		getline(stream, nouns[numNouns]);
	}
	stream.close();
	cout << "Nouns complete." << endl;

	stream.open("adj.txt", ios::in);

	cout << "Inputting adjectives..." << endl;

	getline(stream, adj[numAdj]);
	while (!stream.eof()) {
		numAdj++;
		getline(stream, adj[numAdj]);
	}
	stream.close();
	cout << "Adjectives complete." << endl;

}
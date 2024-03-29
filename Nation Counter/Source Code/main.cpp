//Copyright(c) 2024, Nikoloz Taturashvili
//All rights reserved.
//
//This source code is licensed under the BSD - style license found in the
//LICENSE file in the root directory of this source tree.

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

bool isCountryPresent(vector<string> vec, const string& target);
int getNumberOfLines();
bool deleteLineFromFile(const string&, int);
void nationSavedCounter(vector<string>& vec, unsigned int& count);
void nationSavedJustCounter(unsigned int& count);

int main() {

	vector<string> nations;
	unsigned int nationCount = 0;
	nationSavedCounter(nations, nationCount);

	string member;
	string country;


	cout << "Please input the name of the member alongside the country (nick georgia)" << endl;
	cout << "Type \"quit\" to quit the program" << endl;
	cout << "Type \"list\" to view nations list" << endl;
	cout << endl;
	cout << "Member\tCountry" << setw(65) << right << "Two word countries must be with \"_\" (new_zealand)" << endl;

	ofstream fout("data.txt", ios::app);
	while (true) {
		if (fout.is_open()) {
			cin >> member;
			if (member == "quit") {
				system("cls");
				cout << "Goodbye" << endl;
				break;
			}
			else if (member == "list") {
				system("cls");
				ifstream fin("data.txt");
				int listNum = 0;
				nationSavedJustCounter(nationCount);
				cout << "Members\t\t\tCountry" << setw(20) << right << "Nations: " << nationCount << endl;
				cout << "---------------------------------" << endl;
				while (fin >> member >> country) {
					listNum++;
					cout << listNum << ". " << setw(22) << left << member << setw(22) << left << country << endl;
				}
				cout << "---------------------------------" << endl;
				string tempInput;
				cout << "\nType \"exit\" to go back" << endl;
				cout << "Type \"nations\" to check available nations" << endl;
				cout << "Type \"remove\" to remove a member" << endl;
				do {
					cin >> tempInput;
					if (tempInput == "exit") {
						system("cls");
						cout << "Please input the name of the member alongside the country (nick Georgia)" << endl;
						cout << "Type \"quit\" to quit the program" << endl;
						cout << "Type \"list\" to view nations list" << endl;
						cout << endl;
						cout << "Member\tCountry" << setw(65) << right << "Two word countries must be with \"_\" (new_zealand)" << endl;
						break;
					}
					else if (tempInput == "remove") {
						cout << "What number do you want removed?" << endl;
						int desiredNumber;
						cin >> desiredNumber;
						deleteLineFromFile("data.txt", desiredNumber);
						nationSavedJustCounter(nationCount);

						system("cls");
						cout << "Members\t\t\tCountry" << setw(20) << right << "Nations: " << nationCount << endl;
						cout << "---------------------------------" << endl;
						listNum = 0;
						ifstream tempo("data.txt");
						while (tempo >> member >> country) {
							listNum++;
							cout << listNum << ". " << setw(22) << left << member << setw(22) << left << country << endl;
						}
						cout << "---------------------------------" << endl;
						cout << "\nType \"exit\" to go back" << endl;
						cout << "Type \"nations\" to check available nations" << endl;
						cout << "Type \"remove\" to remove a member" << endl;
						tempo.close();
					}
					else if (tempInput == "nations") {
						system("cls");
						sort(nations.begin(), nations.end());
						cout << "Nations" << setw(15) << right << "Total: " << nationCount << endl;
						cout << "-------------------------" << endl;
						vector<string> nationVec;
						for (string item : nations) {
							bool found = (count(nationVec.begin(), nationVec.end(), item) > 0);
							if (!found) {
								cout << item << endl;
							}
							nationVec.push_back(item);
						}
						cout << "-------------------------" << endl;

						cout << "(If you removed some members, this list will update after rerun)" << endl;
						cout << "\nType \"exit\" to go back" << endl;

					}
					else {
						system("cls");
						cout << "Invalid Input (type \"exit\" to go back)" << endl;
					}
				} while (true);
				continue;
			}
			cin >> country;
			fout << member << "\t\t" << country << endl;
			if (!(isCountryPresent(nations, country))) {
				nationCount++;
			}
			nations.push_back(country);
			system("cls");
			cout << "Keep going or type \"quit\"/\"list\"" << endl;
			cout << endl;
			cout << "Member\tCountry" << setw(65) << right << "Two word countries must be with \"_\" (new_zealand)" << endl;


		}
		else {
			cout << "Error - File could not be oppened" << endl;
			break;
		}
	}

	fout.close();
	return 0;
}

bool isCountryPresent(vector<string> vec, const string& target) {
	for (string item : vec) {
		if (item == target) {
			return true;
		}
	}
	return false;
}

int getNumberOfLines() {
	ifstream file("data.txt");

	if (!file.is_open()) {
		cout << "Error - Could not open the file" << endl;
	}

	int lineCount = 0;
	string line;
	while (getline(file, line)) {
		++lineCount;
	}

	file.close();
	return lineCount;
}

bool deleteLineFromFile(const string& filename, int lineToDelete) {
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cerr << "Unable to open the file: " << filename << endl;
		return false;
	}

	vector<string> lines;
	string line;
	while (getline(inFile, line)) {
		lines.push_back(line);
	}
	inFile.close();

	if (lineToDelete < 1 || lineToDelete > lines.size()) {
		return false;
	}

	lines.erase(lines.begin() + lineToDelete - 1); // -1 because line numbers start from 1

	ofstream outFile(filename);
	if (!outFile.is_open()) {
		cerr << "Unable to open the file for writing: " << filename << endl;
		return false;
	}

	for (const auto& l : lines) {
		outFile << l << endl;
	}
	outFile.close();

	return true;
}

void nationSavedCounter(vector<string>& vec, unsigned int& count) {
	ifstream fileSave("data.txt");
	if (fileSave.is_open()) {
		string discard;
		string counter;
		while (fileSave >> discard >> counter) {
			if (!(isCountryPresent(vec, counter))) {
				vec.push_back(counter);
				count++;
			}
		}
		fileSave.close();
	}
}

void nationSavedJustCounter(unsigned int& count) {
	ifstream filetemp("data.txt");
	if (filetemp.is_open()) {
		count = 0;
		vector<string> myVec;
		string discard;
		string counter;
		while (filetemp >> discard >> counter) {
			if (!(isCountryPresent(myVec, counter))) {
				myVec.push_back(counter);
				count++;
			}
		}
		filetemp.close();
	}
	else {
		cout << "Error - Couldn't open the file" << endl;
	}
}
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

const short vowelcount = 12;
const short consonantcount = 21;

const char* vowel[vowelcount] = { "а", "е", "ё", "и", "о", "у", "ъ", "ы", "ь", "э", "ю", "я" };
const char* consonant[consonantcount] = { "б", "в", "г", "д", "ж", "з", "й", "к", "л", "м", "н", "п", "р", "с", "т", "ф", "х", "ц", "ч", "ш", "щ" };

using namespace std;

bool isvowel(char check) {
	for (int i = 0; i < vowelcount; ++i) {
		if (check == *vowel[i]) {
			return true;
		}
	}
	return false;
}

bool isconsonant(char check) {
	for (int i = 0; i < consonantcount; ++i) {
		if (check == *consonant[i]) {
			return true;
		}
	}
	return false;
}

char capitalizer(char character) {
	if (character >= -64 && character <= -33)
		return character;
	if (character >= -32 && character <= -1)
		return character - 32;
	return *"";
}
char decapitalizer(char character) {
	if (character >= -64 && character <= -33)
		return character + 32;
	if (character >= -32 && character <= -1)
		return character;
	return *"";
}

bool isnum(char check) {
	if (check >= 48 && check <= 57) {
		return true;
	}
	return false;
}

void item0() {
	for (short i = -64; i < 123; ++i) {
		if (i == 0) {
			i = 48;
			cout << endl << endl << endl << endl;
			cout << (char)33 << "/" << 33 << "   " << (char)44 << "/" << 44 << "   " << (char)45 << "/" << 45 << "   " << (char)46 << "/" << 46 << "   " << (char)58 << "/" << 58 << "   " << (char)59 << "/" << 59 << "   " << (char)63 << "/" << 63 << "   ";
			cout << endl << endl;
		}

		if (i == 58) {
			cout << endl << endl << endl << endl;
			i = 65;
		}

		if (i == 91) {
			cout << endl << endl;
			i = 97;
		}

		if (i % 16 == 0) {
			cout << endl << endl;
		}
		cout << (char)i << "/" << i << "   ";
	}
	cout << endl << endl;
}

void item1() {
	cout << "Введите строку: ";
	char string[100];
	cin >> string;
	for (int i = 0; i < 100; ++i) {
		if (isconsonant(string[i]) == true) {
			string[i] = capitalizer(string[i]);
		}
	}
	cout << "Итог: " << string << endl << endl;
}

string readtext(ifstream& file) {
	if (file.is_open() == false) {
		return "";
	}
	string line;
	string returnvalue;
	while (getline(file, line)) {
		returnvalue += line;
		returnvalue += "\n";
	}
	return returnvalue;
}

void readinput(ifstream& file, int& N, char& char1, char& char2) {
	if (file.is_open() == false) {
		return;
	}
	string line;

	getline(file, line);
	N = stoi(line);

	if (getline(file, line))
	{
		char1 = decapitalizer(*line.c_str());
		if ((!isvowel(char1) && (!isconsonant(char1)))) {
			cerr << "[readinput] Неверные данные в input.txt, строка 2";
			exit(1);
		}
	}
	else {
		cerr << "[readinput] Недостаточно данных в input.txt";
		exit(1);
	}

	if (getline(file, line))
	{
		char2 = decapitalizer(*line.c_str());
		if ((!isvowel(char2) && (!isconsonant(char2)))) {
			cerr << "[readinput] Неверные данные в input.txt, строка 3";
			exit(1);
		}
	}
	else {
		cerr << "[readinput] Недостаточно данных в input.txt";
		exit(1);
	}
}

bool wordstartcondition(char wordstart) {
	if (isvowel(decapitalizer(wordstart)) || isconsonant(decapitalizer(wordstart)) || isnum(wordstart)) {
		return true;
	}
	return false;
}

bool wordpasser(char character) {
	if (isvowel(decapitalizer(character)) || isconsonant(decapitalizer(character)) || isnum(character) || character == 45) {
		return true;
	}
	return false;
}

bool wordreviewer(char character) {
	if (isvowel(decapitalizer(character)) || isconsonant(decapitalizer(character))) {
		return true;
	}
	return false;
}

string createword(string& textcontents, int l, int r, char char1, char char2) {
	string returnword = "";
	for (int rf = r; rf > l; --rf) {
		if (!wordreviewer(textcontents[rf]))
			continue;
		r = rf;
		break;
	}
	if (isnum(textcontents[r-1])) {
		return "";
	}
	bool char1flag = false;
	bool char2flag = false;
	for (int i = l; i <= r; ++i) {
		returnword += textcontents[i];
		
		if (decapitalizer(textcontents[i]) == char1) {
			char1flag = true;
			continue;
		}
		if (decapitalizer(textcontents[i]) == char2)
			char2flag = true;
	}
	if (char1flag == true && char2flag == true)
		return returnword;
	return "";
}

bool hasthisword(string*& wordarray, string& word, size_t current_size) {
	if (current_size == 0)
		return false;
	for (size_t i = 0; i < current_size; ++i) {
		if (wordarray[i].length() == word.length()) {
			bool match = true;
			for (size_t j = 0; j < word.length(); ++j) {
				if (decapitalizer(wordarray[i][j]) != decapitalizer(word[j])) {
					match = false;
					break;
				}
			}
			if (match == true) {
				return true;
			}
		}
	}
	return false;
}

size_t len(string& string) {
	size_t returnvalue = 0;
	for (size_t i = 0; i < string.length(); ++i) {
		if (string[i] == *"-")
			continue;
		++returnvalue;
	}
	return returnvalue;
}

void item2() {
	ifstream text("text.txt");
	ifstream input("input.txt");
	ofstream result("result.txt");

	string textcontents = readtext(text);
	text.close();
	
	int N = NULL;
	char char1 = NULL;
	char char2 = NULL;
	readinput(input, N, char1, char2);
	input.close();

	size_t textlength = textcontents.length();
	
	char wordstart;
	size_t wordarraycap = 0;

	for (int l = 0; l < textlength; ++l) {
		wordstart = textcontents[l];
		if (!wordstartcondition(wordstart)) {
			continue;
		}
		for (int r = l + 1; r < textlength; ++r) {
			if (wordpasser(textcontents[r])) {
				continue;
			}
			string word = createword(textcontents, l, r, char1, char2);
			l = r;
			if (word == "" || word == " ")
				break;
			++wordarraycap;
			break;
		}
	}
	if (wordarraycap == 0) {
		result << "Не найдены подходящие слова :(";
		return;
	}
	size_t wordarray_i = 0;
	string* wordarray = new string[wordarraycap];

	for (int l = 0; l < textlength; ++l) {
		bool flagstop = false;
		wordstart = textcontents[l];
		if (!wordstartcondition(wordstart)) {
			continue;
		}
		for (int r = l + 1; r < textlength; ++r) {
			if (wordpasser(textcontents[r])) {
				continue;
			}
			string word = createword(textcontents, l, r, char1, char2);
			l = r;
			if (word == "" || word == " " || hasthisword(wordarray, word, wordarray_i))
				break;
			wordarray[wordarray_i] = word;
			++wordarray_i;
			if (wordarray_i >= wordarraycap) {
				flagstop = true;
			}
			break;
		}
		if (flagstop == true) {
			break;
		}
	}

	for (size_t i = 0; i < wordarraycap; ++i) {
		for (size_t j = 0; j < wordarraycap; ++j) {
			if (len(wordarray[i]) < len(wordarray[j])) {
				string temp = wordarray[i];
				wordarray[i] = wordarray[j];
				wordarray[j] = temp;
			}
		}
	}

	result << "Топ " << N << " самых коротких слов с буквами " << char1 << " и " << char2 << ":";
	for (size_t i = 1; (i <= wordarray_i) && (i <= N); ++i) {
		result << " " << wordarray[i];
	}



	delete[] wordarray;
	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(CP_UTF8);
	item0();
	item1();
	item2();
}
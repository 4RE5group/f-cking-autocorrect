#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <winuser.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_CHAR_PER_WORD 128
#define EXIT_MAGIC_WORD "PLSEXITTHISShit!!!"

char currentWord[MAX_CHAR_PER_WORD];
int indexCharPos = 0;

void clearWord() {
	for(int i=0; i<MAX_CHAR_PER_WORD; i++) {
		currentWord[i] = '\0'; // null char
	}
	indexCharPos=0;
}

void magicKeyBoardSays(const std::string& input) {
	cout << "sending '" << input << "'" << endl;
    if (input.empty()) return;  // Ensure the string is not empty

    char ch = input[0];  // Get the first character
    SHORT vkey = VkKeyScanA(ch);  // Convert char to virtual key

    keybd_event(vkey, 0, 0, 0);       // Press key
    keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);  // Release key
}

void addLetterToWord(int character) {
	if(indexCharPos < MAX_CHAR_PER_WORD) { // add letter to word
		currentWord[indexCharPos] = char(character);
		indexCharPos++;
	} else {
		MessageBox(NULL, (LPCSTR)"Ayo stupid ass you missed a space or something???", (LPCSTR)"Dumb F*cking AutoCorrect", NULL);
		magicKeyBoardSays("    ");
		clearWord();
	} 
	
	// check magic word
	if(strncmp(currentWord, EXIT_MAGIC_WORD, strlen(EXIT_MAGIC_WORD)) == 0) {
		cout << "Yeah alright dude you won. Now f*ck off." << endl;
		exit(0);
	}
	
}

char getRandomCharacter() {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const size_t max_index = sizeof(charset) - 2;
    return charset[rand() % max_index];
}

bool isSpecialKeys(int S_Key) {
	switch (S_Key) {
	case VK_SPACE:
		return true;
	case VK_RETURN:
		return true;
	case '¾':
		return true;
	case VK_SHIFT:
		return true;
	case VK_BACK:
		return true;
	case VK_RBUTTON:
		return true;
	case VK_CAPITAL:
		return true;
	case VK_TAB:
		return true;
	case VK_UP:
		return true;
	case VK_DOWN:
		return true;
	case VK_LEFT:
		return true;
	case VK_RIGHT:
		return true;
	case VK_CONTROL:
		return true;
	case VK_MENU:
		return true;
	default: 
		return false;
	}
}

string getRandomWordWithPrefix(const string& filename, const string& prefix) {
    ifstream file(filename.c_str());
    if (!file) {
        cerr << "Shit, a f*cking error appened when opening this dead ass file: " << filename << endl;
        return "";
    }

    vector<string> words;
    string word;

    while (file >> word) {
    	std::transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.rfind(prefix, 0) == 0) { // Check if word starts with prefix
            words.push_back(word);
        }
    }

    file.close();

    if (words.empty()) {
        return " ";
    }

    srand(time(0));
    return words[rand() % words.size()];
}

int main()
{
	srand(time(0)); // init seed
	cout << "F*cking AutoCorrect a dumbass windows autocorrect" << endl;
	cout << "proudly made by 4re5 group - 2025" << endl;
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	char KEY = 'x';
	char uselessKey = '\0';
	cout << endl;
	cout << "Running... press CTRL+C or exit cross or maybe type '" << EXIT_MAGIC_WORD << "' on your keyboard to exit";
	while (true) {
		Sleep(10);
		for (int KEY = 8; KEY <= 190; KEY++)
		{
			if (GetAsyncKeyState(KEY) == -32767) {
				if (isSpecialKeys(KEY)) {
					if(KEY == VK_SPACE || KEY == VK_RETURN) { // reset word
						clearWord();
					} 
					if (KEY == VK_TAB) {
						cout << "tab '" << currentWord << "'" << endl;
						string randomWord = getRandomWordWithPrefix("dict.txt", currentWord);
						cout << "random word:" << randomWord << endl;
						magicKeyBoardSays(randomWord);
					}
				} else {  
					addLetterToWord(KEY);
					uselessKey = getRandomCharacter();
					if(uselessKey == 'a' || uselessKey == 'A' || uselessKey == '0') { // small probability
						uselessKey = getRandomCharacter();
						std::string str(1, uselessKey);
						magicKeyBoardSays(str);
					}
				}
			}
		}
	}

	return 0;
}

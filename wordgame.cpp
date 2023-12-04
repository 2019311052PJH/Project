#include "wordgame.h"

using namespace std;

WordGame::WordGame() {
    openai::start();
}

std::string WordGame::getUserWord() {
    std::string userWord;
    std::cin >> userWord;
    std::transform(userWord.begin(), userWord.end(), userWord.begin(), ::tolower);
    return userWord;
}

void WordGame::Gamesetting() {
    cout << "Game start! 'finishgame'to game finish" << endl;
    cout << "Input maxwrong(if you miss over maxwrong, you will lose) : ";
    cin >> maxwrong;
    cout << "Input maxattempt(if Ai miss over maxattempt in one turn, Ai will lose) : ";
    cin >> maxattempt;
}
bool Test::isWordValid(const std::string& wordToSearch, const std::set<std::string>& wordslist) {
    if (wordslist.find(wordToSearch) != wordslist.end()) {
        return true;
    }
    return false;
}

bool Test::isWordValid(const std::string& wordToSearch, const std::string& word) {
    char a = word.front();
    char b = wordToSearch.back();
    if (b != a) {
        return true;
    }
    return false;
}

bool Test::isWordValid(const std::string& str) {
    for (char c : str) {
        if (std::isspace(c)) {
            return true;
        }
    }
    return false;
}
bool Test::isWordReal(const std::string& wordToSearch) {
    std::ifstream inputFile("words_alpha.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Cannot open the file." << std::endl;
        return 0;
    }

    std::string word;
    bool found = false;

    while (inputFile >> word) {
        if (word.find(wordToSearch) != std::string::npos) {
            found = true;
            break;
        }
    }
    inputFile.close();
    return found;
}
std::string WordGame::generateAIWord() {
        openai::Json response = openai::completion().create({
            {"model", "text-davinci-003"},
            {"prompt", "A word that starts with '" + lastChar + "'"},
            {"max_tokens", 100},
            {"temperature", 1},
            {"top_p", 0.9},
            {"best_of", 1}
            });

        std::string aiWord = response["choices"][0]["text"].get<std::string>();
        std::transform(aiWord.begin(), aiWord.end(), aiWord.begin(), ::tolower);
        return aiWord;
        }

void WordGame::playGame() {
    bool endflag = 0;
    string userWord;
    Gamesetting();
    cout << "Start word: ";
    userWord = getUserWord();
    usedWords.insert(userWord);
    lastChar = userWord.back();
    int wrong =0;
    while (true) {
	    int attempt =0;
        while (true) {
            std::string aiWord = generateAIWord();
            aiWord.erase(0, 2);
            if (isWordValid(aiWord,usedWords)) {
                ++attempt;
		cout << "Ai generate used word. Try again...(Ai tried "<<attempt<<" times)" << endl;
                if (attempt == maxattempt) {
			endflag = 1;
		        cout << maxattempt <<" attempts over! You win!" << endl;
		       	break;
	       	}
		continue;
            }
            else if (isWordValid(aiWord)) {
                continue;
            }
            else {
                usedWords.insert(aiWord);
                aiWordans = aiWord;
                lastChar = aiWordans.back();
                break;
            }
        }
        if (endflag) { break; }
        std::cout << "AI's word: " << aiWordans << std::endl;

        while (true)
        {
            cout << "Your word: ";
            userWord = getUserWord();
	    lastChar = userWord.back();
            if (userWord == "finishgame") {
                cout << "Game finish!" << endl;
                endflag = 1;
                break;
            }
            if (isWordValid(aiWordans, userWord)) {
                ++wrong;
		auto frontChar = userWord.front();
		cout << "Word isn't match! Word must starts with " << frontChar << " Try again..." << endl;
		cout << "You " << wrong << " times miss " << endl;
                if(wrong == maxwrong){
                     cout << "You miss " << wrong << " times! Ai Win!! " << endl;
                     endflag =1;
                     break;
                }
                continue;
            }
            else if (isWordValid(userWord,usedWords)) {
		++wrong;
		cout << userWord << " is Already used! Try again... " << endl;
		cout << wrong << "times miss " << endl;
                if(wrong == maxwrong){
                     cout << "You miss " << wrong << " times! Ai Win!! " << endl;
                     endflag =1;
                     break;
                }
                continue;
            }
            else if (!isWordReal(userWord)) {
		++wrong;
        	std::cout << userWord << "is not a valid word, Try again..." << std::endl;
		cout << wrong << "times miss " << endl;
                if(wrong == maxwrong){
                     cout << "You miss " << wrong << " times! Ai Win!! " << endl;
                     endflag =1;
                     break;
                }
		continue;
            }
            else{
                usedWords.insert(userWord);
                lastChar = userWord.back();
		break;
            }
        }
        if (endflag) {
            break;
        }
    }
}




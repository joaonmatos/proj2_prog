//COMPILER DIRECTIVES
#include "puzzle.h"
using namespace std;

//CONSTRUCTOR
Puzzle::Puzzle(string filename, bool& control)
	: Board(filename, control)
{
	vector<map<string,char>::iterator> toRemove;

	for (map<string,char>::iterator it = addedChars.begin(); it != addedChars.end();)
	{
		if (it->second != '#')
			toRemove.push_back(it);
	}

	for (unsigned int i = 0; i < toRemove.size(); i++)
		addedChars.erase(toRemove.at(i));

	getHints();
}

//PUBLIC MEMBER FUNCTIONS

/**
 * New interface for the Board linkDic function
 */
void Puzzle::provideBackupDictionary(Dictionary* dictionary, bool replace) //DONE
{
	linkDic(dictionary, replace);
}

/**
 * Shows the puzzle
 */
void Puzzle::showPuzzle()
{
	show();
}

/**
 * Shows a synonym for each position
 */
void Puzzle::showSynonyms()
{
	//Prints horizontal synonyms
	setcolor(BLACK, WHITE_B);
	cout << "HORIZONTAL WORDS:";
	setcolor(DEFAULT_TEXT, DEFAULT_BG);
	cout << endl;
	for (map<string,string>::iterator it = words.begin(); it != words.end(); it++)
	{
		if (it->first.at(it->first.length() - 1) == 'H')
		{
			cout << it->first << ": " << hints.find(it->second)->second << endl;
		}
	}
	cout << endl;

	//Prints vertical synonyms
	setcolor(BLACK, WHITE_B);
	cout << "VERTICAL WORDS:";
	setcolor(DEFAULT_TEXT, DEFAULT_BG);
	cout << endl;
	for (map<string,string>::iterator it = words.begin(); it != words.end(); it++)
	{
		if (it->first.at(it->first.length() - 1) == 'V')
		{
			cout << it->first << ": " << hints.find(it->second)->second << endl;
		}
	}
	cout << endl;
}

/**
 * Tries to insert a word from the dictionary into the board, checking
 * for any ilegal overlap, inexistent words, repeated words, and lack of
 * space. Then updates the black space list.
 * <p>
 * Returns the following exit codes:
 * <p>
 *  0: success;
 * <p>
 * -1: inexistent word;
 * <p>
 * -2: ilegal overlap (different characters, black spaces);
 * <p>
 * -3: lack of space;
 * <p>
 * -4: repeated words;
 * <p>
 * -5: invalid position.
 *
 * @param	position	The position string to insert the word in
 * @param	word		The word to insert
 * @return				The exit code of the procedure
 */
int Puzzle::insGuess(string position, string word)

/**
 * Removes existing word from the board. Returns -1 if no word in position,
 * 0 if successful.
 *
 * @param	word	The position
 * @return			The exit code of the procedure
 */
int Puzzle::remGuess(string position)
{
	if (guessedWords.find(position) == guessedWords.end())
		return -1;
	else
		words.erase(words.find(position));

	refill();

	return 0;
}

/**
 * Returns a different synonym of the word in the given position, or the
 * same if there is only one
 *
 * @param	position	position of the word whose synonym is returned
 * @return					a different synonym or the same if unique
 */
string Puzzle::anotherHint(string position)
{
	string currentSynonym = hints.find(words.find(position)->second)->second;
	vector<string> moreHints = dictionary->getSynonyms(words.find(position)->second);

	if (moreHints.size() == 1)
		return currentSynonym;
	else
	{
		string another = currentSynonym;

		while (currentSynonym == another)
		{
			srand(time(NULL));
			another = moreHints.at(rand() % moreHints.size());
		}

		return another;
	}
}

/**
 * Returns whether the user's guesses are correct
 *
 * @return		Are the words input by the user the correct ones?
 */
bool Puzzle::correct()
{
	return words == guessedWords;
}

//PRIVATE MEMBER FUNCTIONS

/**
 * Populates the hint map
 */
void Puzzle::getHints()

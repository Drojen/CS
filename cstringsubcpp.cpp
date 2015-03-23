// CS318 - String Substitution using only C strings
// Jason Jendro

#include<cctype>
#include<fstream>
#include<iostream>

int getLength(char source[]) {
	int len = 0;
	while (source[len] != NULL) {
		len++;
	}
	return len;
}

void getWordandAdvance(char source[], char term[], int &start) { // gets the first complete word in the word pairs and advances the index to the start of the next word, changes index to -1 if end of list
	int termindex = 0;
	term[termindex] = NULL; // clear out the term
	while (isalnum(source[start]) || source[start] == '-' || source[start] == '.') {
		term[termindex] = source[start];
		termindex++;
		start++;
	}
	// out of loop, go ahead and find index of next word
	while (isspace(source[start]) && start) {
		start++;
	}
	if (source[start] == '$') {
		start = -1;
	}
	term[termindex] = NULL;
}

void getAppend(char source[], char append[], int start) { // gets the text to append
	int i = 0;
	append[0] = NULL;
	while (source[start]) {
		append[i] = source[start];
		i++;
		append[i] = NULL;
		start++;
	}
}

int findWord(char source[], char term[]) { // searches for word match, finds only first instance. If found, returns beginning index of word, if not, returns -1
	int sourcei = 0,
		savedi = 0;
	int len = getLength(term);
	bool matches = false;

	while (source[sourcei]) {
		if (source[sourcei] == term[0]) { // possible word match
			matches = true;
			savedi = sourcei;
			for (int i = 0; i < len; i++) {
				if (source[sourcei] != term[i]) {
					matches = false;
					break;
				}
				sourcei++;
			}
			if (matches) {
				return savedi;
			}
			else { // something didn't match
				sourcei++;
			}
		}
		else {
			sourcei++;
		}
	}
	// nothing found
	return -1;
}

void overwrite(char source[], char word[], int start) { // overwrites the word while overwriting, concat will fix the overwrite with append text
	for (int i = 0; i < getLength(word); i++) {
		source[start] = word[i];
		start++;
	}
}

void concat(char source[], char append[], int start) { // joins two strings at index start
	int i = 0;
	while (append[i]) {
		source[start] = append[i];
		start++;
		i++;
	}
	source[start] = NULL;
}

void slice(char source[], char wp[], char text[]) {		// this function slices the document in two, dividing it at the $
	char	*wpptr = source,							// tracking pointer for where we are in the word pairs
			*textptr = source,							// tracking pointer for where we are in the text
			*dollarptr = source;						// pointer to the $ that separates the two
	int i = 0;

	while (dollarptr) {
		if (source[i] == '$') {
			break;
		}
		i++;
		dollarptr++;
	}

	i = 0;
	textptr = dollarptr;
	textptr++;
	textptr++;

	while (wpptr) {						// write to word pairs
		if (wpptr == dollarptr) {
			wp[i] = *wpptr;
			break;
		}
		wp[i] = *wpptr;
		i++;
		wpptr++;
	}

	i = 0;

	while (textptr) {					// write to text
		if (!*textptr) {
			break;
		}
		text[i] = *textptr;
		i++;
		textptr++;
	}
}


int main() {
	std::ifstream inf;
	const int	DOC_SIZE = 700,
				WP_SIZE = 200,
				TEXT_SIZE = 700,
				TERM_SIZE = 30;

	char		document[DOC_SIZE] = " ",										// the whole text file
				wordpairs[WP_SIZE] = " ",										// just the word pairs
				text[TEXT_SIZE] = " ",											// just the text
				term[TERM_SIZE] = " ",											// term to match
				replacement[TERM_SIZE] = " ",									// word to overwrite the term with
				append[TEXT_SIZE] = " ";										// text to append after being overwritten

	int			matchindex = 0,
				wpindex = 0;

	inf.open("paragraphwordsub.txt");
	inf.get(document, DOC_SIZE, '|');											// get the whole document in so we can work with it.
	inf.close();

	slice(document, wordpairs, text);											// word pairs and text have been separated	

	std::cout << "String Substitution using C-strings...\n\n";
	std::cout << wordpairs << "\n\n";
	std::cout << "======================= BEFORE =======================\n\n";
	std::cout << text << "\n\n";

	while (wpindex > -1) {
		// get term and replacement
		getWordandAdvance(wordpairs, term, wpindex);
		getWordandAdvance(wordpairs, replacement, wpindex);
		// find, overwrite, concat routine
		matchindex = findWord(text, term);										// find first match
		while (matchindex > -1) {												// repeat for subsiquent matches
			getAppend(text, append, matchindex + getLength(term));
			overwrite(text, replacement, matchindex);
			concat(text, append, matchindex + getLength(replacement));
			matchindex = findWord(text, term);
		}
	}

	std::cout << "======================= AFTER ========================\n\n";
	std::cout << text << "\n\n";

	return 0;
}
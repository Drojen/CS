// CS318 - String Substitution using the C++ string class
// Jason Jendro

#include<string>
#include<sstream>
#include<fstream>
#include<iostream>

void getWordandAdvance(std::string source, std::string &term, int &start) { // gets the first complete word in the word pairs and advances the index to the start of the next word, changes index to -1 if end of list
	term.clear();
	while (isalnum(source[start]) || source[start] == '-' || source[start] == '.') {
		term.push_back(source[start]);
		start++;
	}
	// out of loop, go ahead and find index of next word
	while (isspace(source[start])) {
		start++;
	}
	if (source[start] == '$') {
		start = -1;
	}
}

int main() {
	std::ifstream inf;
	std::stringstream buffer;
	std::string document,
				text,
				wordpairs,
				term,
				replacement;

	int		wpindex = 0,
			tempindex = 0,
			matchindex = 0;

	inf.open("paragraphwordsub.txt");
	inf >> buffer.rdbuf();									// get the whole document in so we can work with it.
	inf.close();
	document = buffer.str();

	// setup strings...
	tempindex = document.find('$');
	wordpairs = document.substr(0, tempindex + 1);
	text = document.substr(tempindex + 2);

	std::cout << "String Substitution using the String Class...\n\n";
	std::cout << wordpairs << "\n\n";
	std::cout << "======================= BEFORE =======================\n\n";
	std::cout << text << "\n\n";

	while (wpindex > -1) {
		getWordandAdvance(wordpairs, term, wpindex);
		getWordandAdvance(wordpairs, replacement, wpindex);

		matchindex = text.find(term);
		while (matchindex > -1) {
			text.erase(matchindex, term.length());
			text.insert(matchindex, replacement);
			matchindex = text.find(term);
		}
	}

	std::cout << "======================= AFTER ========================\n\n";
	std::cout << text << "\n\n";

	return 0;
}
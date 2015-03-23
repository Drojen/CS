// CS 318 Postfix
// Jason Jendro

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

std::ifstream inFile;

class LineRec {
	public:
		std::string strLine;
		std::vector<int> ints;
		int answer;
		LineRec() : answer(0) {}
		bool isInt(char c) {
			char comp[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
			for (int i = 0; i < 10; i++) {
				if (c == comp[i]) {
					return true;
				}
			}
			return false;
		}
		int charToInt(char c) { // the method per lecture
			return c - '0';
		}
		void parse() { // parse ascii line and do math along the way
			int i = 0,
				temp = 0;
			char c = strLine[i];			
			while(c != '$') { // $ means end of line
				if (isInt(c)) { // if c is a number
					temp = (temp * 10) + charToInt(c); // convert and add

					if (strLine[i + 1] == ' ') { // look ahead to see if we need to record the number or not yet
						ints.push_back(temp);
						temp = 0; // reset temp for next number
					}
 				}
				// calculate if an operator is encountered, pops off last value of int vector as we go
				// handle only + - and * for this exersize
				if (c == '+') {
					ints[ints.size() - 2] += ints[ints.size() - 1];
					ints.pop_back();
				}
				if (c == '-') {
					ints[ints.size() - 2] -= ints[ints.size() - 1];
					ints.pop_back();
				}
				if (c == '*') {
					ints[ints.size() - 2] *= ints[ints.size() - 1];
					ints.pop_back();
				}
				// increment things
				i++;
				c = strLine[i];
			}			
			answer = ints[0];	// out of loop, ints[0] should equal the answer now
			strLine.pop_back(); // trim off the $ from the string
		};		
};

void processLines(std::vector<LineRec> &lines) { // read the lines in the file, make the record objects, parse them, push them to the vector of records
	inFile.open("posfix.txt");
	if (!inFile) { std::cerr << "Oops, file didn't open..."; }

	std::string current;

	while (std::getline(inFile, current)) {
		LineRec temp;
		temp.strLine = current + "$";	// $ signifies the end of the line, used in parsing, will be popped off
		temp.parse();					// parse as we go
		lines.push_back(temp);			// completed object is pushed to vector
	}
		
	inFile.close();
}

int main() {

	std::vector<LineRec> lines;
	processLines(lines);

	std::cout << "========================== Post Fix Calculations ==========================\n";

	for (int i = 0, len = lines.size(); i < len; i++) {
		std::cout << i + 1 << ". " << lines[i].strLine << " = " << lines[i].answer << std::endl;
	}

	return 0;
}
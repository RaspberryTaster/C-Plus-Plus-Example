// replace my comments with your own
// except: you can use my comment about one-word lookahead

// you may modify the code that I have supplied if you wish


using namespace std;

#include "ReadWords.h"
#include <cctype>
#include <cstdlib>
#include <iostream>

std::string removePunct(const string& word) {
    size_t start = 0;
    size_t end = word.size();

    auto isExemptPunctuation = [](char c) {
        return c == '-' || c == '\'';
    };

    while (start < end && std::ispunct(word[start]) && !isExemptPunctuation(word[start])) {
        ++start;
    }

    while (end > start && std::ispunct(word[end - 1]) && !isExemptPunctuation(word[end - 1])) {
        --end;
    }

    return word.substr(start, end - start);
}


ReadWords::ReadWords(const char *fname)
{   wordfile.open(fname);//open file
    if (!wordfile)
    {   cout << "Failed to open " << fname << endl;
        exit(1);
    }
    wordfile >> nextword;
    eoffound = false;
}

string ReadWords::getNextWord()
{ // should return next word in file, converted to lower case
  // empty string should be returned if next word contains no letters
  
  // uses a one-word lookahead to avoid any problems relating to when if end-of-file
  // is detected due to absence/presence of newline at end of file

  // incomplete

  string word = nextword;
  wordfile >> nextword;

  if (wordfile.eof())
     eoffound = true;

  word = removePunct(word);

  // also need to convert to lower case before returning
  string lowCase;
  bool containsLetter = false;
  for(char c : word)
  {
      if(isalpha(c))
      {
        containsLetter = true;
      }
      lowCase += tolower(c);
  }


  //need to check that word contains a letter and if not return an empty string;
  return containsLetter ? word : "";
}

bool ReadWords::isNextWord()
{ return !eoffound;
}

void ReadWords::close()
{ // you must write this
  wordfile.close();
}

//Attempt at Ex2 Challenge
/*
ostream& operator<<(ostream &out, ReadWords &rw) {
    while (rw.isNextWord()) {
        out << rw.getNextWord() << " ";
    }
    return out;
}
*/
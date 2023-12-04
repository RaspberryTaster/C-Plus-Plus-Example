#include <iostream>
#include "Custom Color Package/AnsiColors.h"
#include "ReadWords.cpp"
#include<fstream>
#include<string>
#include <unordered_map>
#include <vector>

using namespace std;


void generateBarGraph(const std::unordered_map<std::string, int>& wordCount) {
    int totalWords = 0;
    for (const auto& pair : wordCount) {
        totalWords += pair.second;
    }
    const int wordColumnWidth = 15; 
    auto color_a = make_tuple(255, 15, 60);
    auto color_b = make_tuple(0, 150, 30);
    std::cout << "\nWord Occurrence:" << std::endl;

    for (const auto& pair : wordCount) {
        if (totalWords > 0) {
            float percentage = static_cast<float>(pair.second) * 100 / totalWords;
            int barLength = static_cast<int>(percentage / 2); 

            std::string word = pair.first;
            word.resize(wordColumnWidth, ' '); 

            std::cout << word;
            AnsiColors::printWithGradient(std::string(barLength, '='), color_a, color_b);
            std::cout << " " << pair.second << " (" << static_cast<int>(percentage) << "%)" << std::endl;
        }
    }
}

int main(void)
{
    //int offset;
    //string line;
    string* fileA = new string();
    string fileB;
    ifstream SearchFile;
    string searchLine;
    //ifstream Myfile;
    vector<string> searchWords;
    unordered_map<string, int> wordCount;


    cout << "Please Insert the filename for the text you want to analyze: " <<endl;
    cin>>*fileA;

    cout << "Please Insert the filename for the word you will use to analyze: " <<endl;
    cin>>fileB;
    SearchFile.open(fileB);
    //Myfile.open("1787.txt");
    

    int count = 0;
    if(SearchFile.is_open())
    {
        while (getline(SearchFile,searchLine))
        {
            if(count >= 5)
            {
                break;
            }
            searchWords.push_back(searchLine);
            count++;
        }
        
        for (const auto& word : searchWords) {
            wordCount[word] = 0;
        }


    }
    else
    {
        cout << "File opening error" << endl;
        return 0;       
    }


    /*
    if(Myfile.is_open())
    {
        while(!Myfile.eof())
        {
            getline(Myfile,line);
            for (const auto& word : searchWords) {
                if((offset = line.find(word, 0)) != string::npos)
                {
                    wordCount[word]++;
                }
            }
        }

        Myfile.close();

        for (const auto& word : searchWords) {
            cout << word<< " was found " << wordCount[word] <<" times!" << endl;
        }
    }
    else
    {
        cout << "File opening error" << endl;
    }
    */
    ReadWords r = ReadWords(fileA->c_str());
    while(r.isNextWord())
    {
        string n = r.getNextWord();
        for (const auto& word : searchWords) {
            if(word == n)
            {
                wordCount[word]++;
            }
        }
    }
    r.close();

    //auto color1 = AnsiColors::getRgb(AnsiColors::RED);
    //auto color2 = AnsiColors::getRgb(AnsiColors::BLUE);
    //auto mixedColor = AnsiColors::getAnsiLerp(color1, color2, 0.5); 
    //cout << mixedColor << "Spooky colors!" <<AnsiColors::WHITE;
    //AnsiColors::printWithGradient("#########################", color1,color2);
    generateBarGraph(wordCount);
    return 0;
}




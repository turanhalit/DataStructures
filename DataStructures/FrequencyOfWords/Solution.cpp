/*
* @author :  152120171108 Halitcan Turan
* @author :  152120181008 Yasin Binler
* @brief  :  This program evaluates to frequency of words in a file
* @date   :  06/01/2021
*/

#include "WordFreq.h"
#include <vector>
#include<map>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;
struct OnlyWord : ctype<char>
{
    OnlyWord() : ctype<char>(get_table()) {}

    static ctype_base::mask const* get_table()
    {
        static vector<ctype_base::mask>
            rc(ctype<char>::table_size, ctype_base::space);

        fill(&rc['A'], &rc['z' + 1], ctype_base::alpha);
        return &rc[0];
    }
};

///-----------------------------------------------------------------
/// Process the given text file and return the most frequent "k" words
///
vector<WordFreq> GetMostFrequentKWords(string filename, int k) {
    vector<WordFreq> result;
    map<string, int> wordCount;
    ifstream input;
    input.imbue(locale(locale(), new OnlyWord())); //enable reading only letters!
    input.open(filename);
    string word;
    while (input >> word)
    {
        int index = 0;
        while (word[index])
        {
            int value = word[index];
            if (value > 64 && value < 91)
                word[index] += 32;

            index++;
        }
        ++wordCount[word];
    }
    int biggestfrequency = 0;
    for (map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
    {
        if (it->second > biggestfrequency && it->first.size() > 2)biggestfrequency = it->second;
    }
    int counter = 0;
    for (;;) {

        for (map<string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
        {
            if (it->second == biggestfrequency && it->first.size() > 2) {
                result.push_back(it->first);
                result[counter].freq = it->second;
                counter++;
                if (counter == k) break;
            }
        }
        biggestfrequency--;
        if (counter == k) break;
        if (biggestfrequency == 0)break;
    }
    return result;
} //end-GetMostFrequentKWords
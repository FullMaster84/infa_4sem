#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void GetArrayofSet(set<string> offer,string arr[]) {
    int i = 0;
    for (string word : offer) {
        arr[i] = word;
        i++;
    }
}

int main(int argc, char** argv)
{   
    int t = 0.29;
    vector<set<string>> text(1000);

    fstream file("C:\\Users\\Sparjaq\\Desktop\\text.txt");
    string line;
    int i_text = 0;
    int comparison_line = 1; // строка с которой сравниваются другие строки


    while (!file.eof()) // чтение с файла
    {
        getline(file,line);
        string word;
        stringstream ss(line);
        while (getline(ss,word,' ')) { //разбиение на слова
           text[i_text].insert(word);
        }
        i_text++;
    }

    string* second = new string[text[comparison_line].size()];
    GetArrayofSet(text[comparison_line], second);

    for (int i = 0; i < i_text; i++) { //вывод всех предложенний
        if (i != comparison_line) {
            const int size_text = text[i].size();

            vector<string> intersection(text[i].size());
            vector<string> union_(text[i].size()*999);
            string* first = new string[size_text];
            GetArrayofSet(text[i], first);

            auto it = set_intersection(first, first + text[i].size(),
                second, second + text[comparison_line].size(), intersection.begin());
            intersection.resize(it - intersection.begin());

            auto it1 = set_union(first, first + text[i].size(),
                second, second + text[comparison_line].size(), union_.begin());
           union_.resize(it1 - union_.begin());

           double result = (double)intersection.size() / union_.size();

           if (result >= t) {
               cout << "index:" << i << " t=" << result << endl;
           }
           
           delete[] first;
        }
    }

   delete[] second;

}
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include <sstream>
#include <map>

using namespace std;


string cleaning(string line)
{
    for(int i = 0; i <= line.length(); i++)
    {
        if(!isalnum(line[i]))
        {
            line[i] = ' ';
        }
        else
        {
            char c = (char)line[i];
            if (isupper(c))
            {
                line[i] = tolower(c);
            }
        }
    }
    return line;
}


map <string, int> separation(list <string> rows, float *cnt) { //на вход приходит список строк
    list <string> :: iterator it;  //создаём итератор
    map <string, int> words;  //создаём контейнер words
    for(it = rows.begin(); it != rows.end(); it++){
        stringstream line(*it); //
        string word;
        while(line >> word){
            if(words.find(word) == words.end()){
                words[word] = 1;
            }
            else{
                words[word]++;
            }
            (*cnt)++;
        }

    }
    return words;
}

void create(char* out_dir, multimap <int, string> MultiWords, float cnt){
    ofstream outfile;
    outfile.open(out_dir);
    multimap<int, string> :: iterator ite = MultiWords.end();
    while(ite != MultiWords.begin()){
        ite--;
        outfile << ite -> first << " " << (float)(ite -> first) / cnt << " " << ite -> second << endl;
    }
}


int main(int argc, char** argv) {
    ifstream file;
    file.open(argv[1]);  //считываем файл
    if (file.is_open())
    {
        cout << "The file is open" << endl;  //проверяем на открытие файла
        float cnt = 0; //создаем счетчик для процентов
        string line;  //создаем строку, по которой будет считываться файл
        list <string> rows;  //создаём список строк, в котором будет хваниться наш текст
        while (getline(file, line))
        {
            line = cleaning(line);  //очищаем текст от знаков препинания
            //cout << line << endl;
            rows.push_back(line);  //скидываем построчно текст в списоk
        }

        multimap <int, string> MultiWords;
        map<string, int> words = separation(rows, &cnt);
        for(auto & word : words){
            //cout << word.first << " " << word.second << endl;
            MultiWords.emplace(word.second, word.first);
        }
        create(argv[2], MultiWords, cnt);
    }
    else
    {
        cout << "Error" << endl;
    }
	return 0;
}
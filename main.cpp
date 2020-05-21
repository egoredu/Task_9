#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

void updateMap(map<string, vector<string>> &dict, string desc) {
    // функция, которая обновляет словарь по новому описанию
    string::iterator id = desc.begin();
    string engWord, translation;
    while ((id != desc.end()) && (*id != ' ')) { // выделяем английское слово
        engWord += (*id);
        ++id;
    }
    id += 3; // переступаем через тире
    while (id != desc.end()) {
        while ((id != desc.end()) && (*id != ',') && (*id != ' ')) {  // выделяем переводы
            translation += (*id);
            ++id;
        }
        if (!translation.empty()){
            dict[translation].push_back(engWord);
            //cout << translation << '\n';
            translation.clear();
        }
        if (id != desc.end() && (*id == ',')) id += 2; // дошли до конца

    }
}
int main() {
    // вводим количество описаний и сами описания в отдельных строках в формате примера apple - malum, pomum, popula
    int n; // количество английских слов-описаний
    string s, filename_in;
    map<string, vector<string>> dict;

    ifstream fin;
    cout << "Введите путь к входному файлу:\n";
    cin >> filename_in;
    fin.open(filename_in);

    fin >> n;
    getline(fin, s); // костыль, чтобы считать первую строку с числом в пустоту
    s.clear();
    // считываем строки и обновляем словарь
    for (int i = 0; i < n; ++i) {
        getline(fin, s);
        updateMap(dict, s);
    }

    map<string, vector<string>>::iterator it;
    vector<string>::iterator iv;
    // выводим количество элементов в словаре и его содержимое
    cout << dict.size() << '\n';
    for ( it = dict.begin(); it != dict.end(); it++ ) {
        cout << it->first << " - ";  // латинское слово
        vector<string> values = it->second;
        for (iv = values.begin(); iv != values.end(); iv++)
            if (iv != values.begin()) cout << ", " << *iv; // переводы
            else cout << *iv;
        cout << '\n';
    }
    return 0;
}

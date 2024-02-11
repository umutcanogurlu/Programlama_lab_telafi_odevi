#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

// kelimeleri ve bulunma sıklıklarını saklamak için bir yol haritası oluşturrduk
map<char, priority_queue<pair<int, string>, vector<pair<int, string>>, less<pair<int, string>>>> word_heaps;

// dosyadan okuma işlemini gerçekleştiriyoruz
void read_file(const string& file_path) {
    ifstream file(file_path); // dosyayı açma
    string line; // okunan satırı tutma
    regex word_regex("\\b\\w+\\b");
    map<string, int> word_freq; // kelimelerin metinde kaç kere geçtikleri

    // dosyayı satır satır okuyoruz
    while (getline(file, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower); // tüm harfleri küçük harfe dönüştürme

        auto words_begin = sregex_iterator(line.begin(), line.end(), word_regex);
        auto words_end = sregex_iterator();

        // satırdaki her kelimeyi işliyoruz
        for (sregex_iterator i = words_begin; i != words_end; ++i) {
            word_freq[(*i).str()]++; // Kelimenin frekansını bir arttırma
        }
    }

    // kelimeleri ilk harflerine göre ayırıp bulunma sıklıklarına göre heap'lerde saklıyoruz
    for (auto& pair : word_freq) {
        char first_letter = pair.first[0]; // kelimenin ilk harfi
        word_heaps[first_letter].push(make_pair(pair.second, pair.first)); // ilgili harfe sahip heap'e ekleme
    }
}

// kelimeleri sıralayıp ekrana yazdırıyoruz
void sort_and_print_words() {
    for (auto& heap_pair : word_heaps) {
        auto& heap = heap_pair.second;
        cout << "Words starting with '" << heap_pair.first << "':" << endl;
        while (!heap.empty()) {
            auto pair = heap.top();
            heap.pop();
            cout << pair.second << ": " << pair.first << endl;
        }
        cout << endl;
    }
}

// main fonksiyonu
int main() {
    // dosya yolunu kullanıcıdan alıyoruz
    string file_path;
    cout << "Please enter the file path: ";
    cin >> file_path;
    read_file(file_path); // dosyayı okuma
    sort_and_print_words(); // kelimeleri sıralayıp ve yazdırıyoruz
    return 0;
}
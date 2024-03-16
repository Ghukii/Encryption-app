#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Transpose_cypher{
private:
    int n;
    int key;

    string phrase;
    string result;

    vector<vector<char>> matrix;
    vector<int> key_vec;

    int find_n(){
        int k = 1;
        while (k * k < phrase.size()){
            k++;
        }
        return k;
    }

    void key_to_vec(){
        while(key != 0){
            key_vec.push_back(key % 10 - 1);
            key /= 10;
        }
        reverse(key_vec.begin(), key_vec.end());
    }

    void to_matrix(){

        int _size = phrase.size();

        if(_size < n * n){
            while(_size < n * n){
                phrase.append("x");
                _size++;
            }
        }

        size_t p_index = 0;
        vector<char> tmp;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                tmp.push_back((char)phrase[p_index]);
                p_index++;
            }
            matrix.push_back(tmp);
            tmp.clear();
        }

        tmp.clear();
    }

    void to_phrase(){
        for(size_t i = 0; i != matrix.size(); ++i){
            for(size_t j = 0; j != matrix.size(); ++j){
                result.push_back(matrix[i][j]);
            }
        }
    }

    void transpose(){
        for(size_t i = 0; i != matrix.size(); ++i){
            for(size_t j = i + 1; j != matrix.size(); ++j){
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    int find(int what){
        for(size_t i = 0; i != key_vec.size(); ++i){
            if(what == key_vec[i]){
                return i;
            }
        }
        return -1;
    }

    void encrypt(){

        vector<char> tmp;
        vector<vector<char>> m_tmp;

        for(size_t i = 0; i != key_vec.size(); ++i){
            for(size_t j = 0; j != matrix.size(); ++j){
                tmp.push_back(matrix[key_vec[i]][j]);
            }
            m_tmp.push_back(tmp);
            tmp.clear();
        }

        matrix = m_tmp;
        tmp.clear();
        m_tmp.clear();
    }

    void decrypt(){
        int ind;

        vector<char> tmp;
        vector<vector<char>> m_tmp;

        cout << "dec" << endl;
        for(size_t i = 0; i != key_vec.size(); ++i){
            ind = find(i);
            for(size_t j = 0; j != matrix.size(); ++j){
                tmp.push_back(matrix[ind][j]);
            }
            m_tmp.push_back(tmp);
            tmp.clear();
        }
        
        matrix = m_tmp;
        tmp.clear();
        m_tmp.clear();
    }

public:

    Transpose_cypher(string _phrase, int _key, string _parameter){
        this->phrase = _phrase;
        this->key = _key;
        this->n = this->find_n();

        this->key_to_vec();
        this->to_matrix();

        if(_parameter == "encrypt"){
            print_matrix();
            this->transpose();
            print_matrix();
            this->encrypt();
            print_matrix();
            this->to_phrase();
            cout << this->result << endl;
        }
        if(_parameter == "decrypt"){
            print_matrix();
            this->decrypt();
            print_matrix();
            this->transpose();
            print_matrix();
            this->to_phrase();
            cout << this->result << endl;
        }

    }

    void print_matrix(){
        for(int i = 0; i < this->n; i++){
            for(int j = 0; j<this->n; j++){
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main(){
    Transpose_cypher T("GhukiiWinnerOfTheWorld", 34152, "encrypt"); // repahs

    Transpose_cypher TD("uiOWxknfoxGiehlinTrxhWred", 34152, "decrypt"); // phrase
    
}



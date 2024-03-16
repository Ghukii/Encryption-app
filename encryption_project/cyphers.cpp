#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<pybind11/pybind11.h>

using namespace std;
namespace py = pybind11;

class Caesar{
private:

    int key = 1;
    string phrase;
    vector<char> phrase_encrypted;
    vector<char> phrase_decrypted;
    vector<int> ascii;

    void to_ascii(){
        for(size_t i = 0; i != phrase.size(); ++i){
            ascii.push_back((int) phrase[i]);
        }
    }

    void encrypt(){

        for(size_t i = 0; i != ascii.size(); ++i){

            if(ascii[i] >= 65 && ascii[i] <= 90){
                if(ascii[i] + key > 90) ascii[i] = ascii[i] + key - 26;
                else ascii[i] += key;
            } 
    
            if(ascii[i] >= 97 && ascii[i] <= 122){
                if(ascii[i] + key > 122) ascii[i] = ascii[i] + key - 26;
                else ascii[i] += key;
            }

            phrase_encrypted.push_back((char)ascii[i]);
        }
    }

    void decrypt(){
        for(size_t i = 0; i != ascii.size(); ++i){

            if(ascii[i] >= 65 && ascii[i] <= 90){
                if(ascii[i] - key < 65) ascii[i] = ascii[i] - key + 26;
                else ascii[i] -= key;
            } 
    
            if(ascii[i] >= 97 && ascii[i] <= 122){
                if(ascii[i] - key < 97) ascii[i] = ascii[i] - key + 26;
                else ascii[i] -= key;
            }
            
            phrase_decrypted.push_back((char)ascii[i]);
        }
    }

public:
    Caesar(string _phrase, int _key, string _mode){
        key = _key;
        phrase = _phrase;
        if (_mode == "encrypt"){
            to_ascii();
            encrypt();
        }
        if (_mode == "decrypt"){
            to_ascii();
            decrypt();
        }
    }

    void print_cyper(){
        for(size_t i = 0; i != this->phrase_encrypted.size(); ++i){
            cout<<this->phrase_encrypted[i];
        }
    }

    void print_cyper_decrypted(){
        for(size_t i = 0; i != this->phrase_decrypted.size(); ++i){
            cout<<this->phrase_decrypted[i];
        }
    }

    string get_cyper(){
        string cypher;

        for(size_t i = 0; i != this->phrase_encrypted.size(); ++i){
            cypher.push_back(this->phrase_encrypted[i]);
        }

        return cypher;
    }

    string get_phrase(){
        string phrase;

        for(size_t i = 0; i != this->phrase_decrypted.size(); ++i){
            phrase.push_back(this->phrase_decrypted[i]);
        }

        return phrase;
    }
};

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
                phrase.append("-");
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
            this->transpose();
            this->encrypt();
            this->to_phrase();
        }
        if(_parameter == "decrypt"){
            this->decrypt();
            this->transpose();
            this->to_phrase();
        }

    }

    string get_result(){
        return this->result;
    }
};


PYBIND11_MODULE(cyphers, m){
    m.doc() = "Encryption & decryption module";

    py::class_<Caesar>(m, "Caesar")
        .def(py::init<string, int, string>())
        .def("get_cypher", &Caesar::get_cyper)
        .def("get_phrase", &Caesar::get_phrase);

    py::class_<Transpose_cypher>(m, "Transpose_cypher")
        .def(py::init<string, int, string>())
        .def("get_result", &Transpose_cypher::get_result);
        
}

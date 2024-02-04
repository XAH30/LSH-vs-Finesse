#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <algorithm>
#include <set>
#include <cassert>
#include <chrono>
#include <thread>
#include <locale>
#include <utility>
#include <functional>

using namespace std;

/*
ПОДГРУЗКА ФУНКЦИОНАЛА РАБОТЫ С ДАННЫМИ
*/

// Класс для работы с результатом
#include "Classes/Results.cpp"

// Кастомное считывание из файла
#include "datasetReader.cpp"

// Функции вывода разных данных
#include "DataPrinters/allDataPrinter.cpp"
#include "DataPrinters/printVector.cpp"
#include "DataPrinters/oneHotMatrixPrinter.cpp"
#include "DataPrinters/bucketPrinter.cpp"
#include "DataPrinters\candidatesPrinter.cpp"

// Функция для получения вектора, состоящего из столбца или строки передаваемых данных 
#include "iFunctions/iloc.cpp"

// Функция для заполнения диапазона элементами, последовательно увеличивая их значения на заданное значение
#include "iFunctions/iota.cpp"

/*
ПОДГРУЗКА ФУНКЦИОНАЛА ДЛЯ АЛГОРИТМА LSH
*/

// Функции хэширования
#include "hashFunctions/minHash.cpp"
#include "hashFunctions/simHash.cpp"

// Остальные функции
#include "unfilteredFunctions/buildShingles.cpp"
#include "unfilteredFunctions/buildVocab.cpp"
#include "unfilteredFunctions/oneHotEncoder.cpp"
#include "unfilteredFunctions/getSignature.cpp"
#include "unfilteredFunctions/transpose.cpp"
#include "unfilteredFunctions/preparations.cpp"
#include "unfilteredFunctions/close.cpp"
#include "unfilteredFunctions/vec2set.cpp"
#include "unfilteredFunctions/set2vec.cpp"

// класс LSH
#include "Classes/LSH.cpp"

// Поиск кандидатов на схожесть
#include "unfilteredFunctions/candidatesFinder.cpp"

/*
ПОДГРУЗКА ФУНКЦИОНАЛА ДЛЯ АЛГОРИТМА FINESSE
*/

// Класс подчанка
#include "Classes\Subchunk.cpp"

// Класс чанка
#include "Classes\Chunk.cpp"

// Класс признаков
#include "Classes\Feature.cpp"

// Функция для перевода объекта данных в объект класса Chunk
#include "unfilteredFunctions\convert2Chunks.cpp"

// Функции для работы алгоритма Finesse
#include "unfilteredFunctions\splitIntoSubchunks.cpp"
#include "unfilteredFunctions\deltaCompression.cpp"
#include "unfilteredFunctions\isSimilar.cpp"

// Кольцевая функция хэширования
#include "hashFunctions\RabinFingerPrint.cpp"

// Алгоритм Finesse
#include "unfilteredFunctions\Finesse.cpp"



int main(){
    preparations();
    std::vector<std::vector<std::string>> data = readDataFromFile("../dataset/SICK_train.txt");

    std::vector<std::string> sentence_A = iloc(data, 1, 1); // начинается с sentence_A
    std::vector<std::string> sentences;
    std::set<std::string> setSentences;

    for(int i = 1; i < sentence_A.size(); i++) {
        sentences.push_back(sentence_A[i]);
    }

    setSentences = vec2set(sentences);
    sentences = set2vec(setSentences);

    int k = 8;

    std::vector<std::unordered_set<std::string>> shingles;
    for (const auto& sentence : sentences) {
        shingles.push_back(buildShingles(sentence, k));
    }

    std::unordered_map<std::string, int> vocab = buildVocab(shingles);

    std::vector<std::vector<double>> shingles_1hot;
    for (const auto& shingle_set : shingles) {
        shingles_1hot.push_back(oneHotEncoder(shingle_set, vocab));
    }

    int numShingles = shingles_1hot.size();
    int vocabSize = vocab.size();
    std::vector<std::vector<int>> shingles_1hot_matrix(vocabSize, std::vector<int>(numShingles, 0));
    for (int i = 0; i < numShingles; i++) {
        for (int j = 0; j < vocabSize; j++) {
            shingles_1hot_matrix[j][i] = shingles_1hot[i][j];
        }
    }

    auto startsimHash = chrono::steady_clock::now();
    std::vector<std::vector<int>> arr1 = simHash(vocab, 100);
    std::set<std::pair<int, int>> candidate_pairs1 = candidatesFinder(arr1, shingles_1hot_matrix);
    auto endsimHash = chrono::steady_clock::now();
    
    auto startminHash = chrono::steady_clock::now();
    std::vector<std::vector<int>> arr2 = minHash(vocab, 100);
    std::set<std::pair<int, int>> candidate_pairs2 = candidatesFinder(arr2, shingles_1hot_matrix);
    auto endminHash = chrono::steady_clock::now();

    int num_pairs1 = candidate_pairs1.size();
    int num_pairs2 = candidate_pairs2.size();

    vector<Chunk> chunks = convert2Chunks(sentences);
    
    size_t subchunkSize = 8;
    double similarityThreshold = 0.6; // Степень похожести в долях от 1
    auto startFinesse = chrono::steady_clock::now();
    set<pair<int, int>> candidate_pairs3 = Finesse(chunks, subchunkSize, similarityThreshold);
    auto endFinesse = chrono::steady_clock::now();

    int num_pairs3 = candidate_pairs3.size();

    cout << endl << "Number of candidate pairs (using simHash): " << num_pairs1 << endl;
    cout << "SimHash elapsed time in nanoseconds: "<< chrono::duration_cast<chrono::nanoseconds>(endsimHash - startsimHash).count() << " ns" << endl;

    cout << endl << "Number of candidate pairs (using minHash): " << num_pairs2 << endl;
    cout << "MinHash elapsed time in nanoseconds: "<< chrono::duration_cast<chrono::nanoseconds>(endminHash - startminHash).count() << " ns" << endl;

    cout << endl << "Number of candidate pairs (using Finesse): " << num_pairs3 << endl;
    cout << "Finesse elapsed time in nanoseconds: "<< chrono::duration_cast<chrono::nanoseconds>(endFinesse - startFinesse).count() << " ns" << endl << endl;

    Results SimHashResults(candidate_pairs1, "SimHash");
    Results MinHashResults(candidate_pairs2, "MinHash");
    Results FinesseResults(candidate_pairs3, "Finesse");

    SimHashResults.sample(7);
    MinHashResults.sample(8);
    FinesseResults.sample(9);

    close();
}
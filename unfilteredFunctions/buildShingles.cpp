std::unordered_set<std::string> buildShingles(const std::string& sentence, int k) {
    std::unordered_set<std::string> shingles;
    const int sentenceLength = sentence.length();
    const int lastStartIndex = sentenceLength - k + 1;

    shingles.reserve(lastStartIndex); // Предварительное выделение памяти для ускорения операций вставки

    for (int i = 0; i < lastStartIndex; i++) {
        shingles.emplace(sentence.substr(i, k)); // Использование emplace для эффективной вставки элементов
    }

    return shingles;
}
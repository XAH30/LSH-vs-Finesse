std::unordered_map<std::string, int> buildVocab(const std::vector<std::unordered_set<std::string>>& shingleSets) {
    std::unordered_set<std::string> fullSet;
    for (const auto& set_ : shingleSets) {
        fullSet.insert(set_.begin(), set_.end());
    }

    std::unordered_map<std::string, int> vocab;
    vocab.reserve(fullSet.size()); // Предварительное выделение памяти для ускорения операций вставки

    int index = 0;
    for (const auto& shingle : fullSet) {
        vocab.emplace(shingle, index); // Использование emplace для эффективной вставки элементов
        index++;
    }

    return vocab;
}
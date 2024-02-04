std::vector<std::vector<int>> simHash(const std::unordered_map<std::string, int>& vocab, int numBits) {
    int length = vocab.size();
    std::vector<std::vector<int>> hashCodes(numBits, std::vector<int>(length, 0));

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < numBits; i++) {
        std::vector<int> permutation(length);
        std::iota(permutation.begin(), permutation.end(), 0);
        std::shuffle(permutation.begin(), permutation.end(), g);

        int index = 0;
        for (const auto& item : vocab) {
            const std::string& token = item.first;
            int weight = item.second;

            std::hash<std::string> hasher;
            size_t hashed_value = hasher(token);

            int bit = (hashed_value & (1 << i)) ? 1 : -1;
            hashCodes[i][permutation[index]] = bit * weight;
            index++;
        }
    }

    return hashCodes;
}
std::vector<std::vector<int>> minHash(const std::unordered_map<std::string, int>& vocab, int numHashes) {
    int length = vocab.size();
    std::vector<std::vector<int>> arr(numHashes, std::vector<int>(length, 0));

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < numHashes; i++) {
        std::vector<int> permutation(length);
        std::iota(permutation.begin(), permutation.end(), 1);
        std::shuffle(permutation.begin(), permutation.end(), g);
        arr[i] = std::move(permutation);
    }

    return arr;
}

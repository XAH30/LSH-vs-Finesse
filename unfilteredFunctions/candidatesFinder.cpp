std::set<std::pair<int, int>> candidatesFinder(const std::vector<std::vector<int>> arr, std::vector<std::vector<int>> shingles_1hot_matrix){
    std::vector<std::vector<int>> signatures;

    shingles_1hot_matrix = transpose(shingles_1hot_matrix);

    for (const auto& vector : shingles_1hot_matrix) {
        signatures.push_back(getSignature(arr, vector));
    }

    // Объединение сигнатур в одномерный массив
    std::vector<std::vector<int>> mergedSignatures;
    for (const auto& row : signatures) {
        mergedSignatures.push_back(row);
    }
    
    int b = 20;
    LSH lsh(b);

    for (const auto& signature : signatures) {
        lsh.addHash(signature);
    }

    const std::vector<std::unordered_map<std::string, std::vector<int>>>& buckets = lsh.getBuckets();

    std::set<std::pair<int, int>> candidatePairs = lsh.check_candidates();
    return candidatePairs;
}


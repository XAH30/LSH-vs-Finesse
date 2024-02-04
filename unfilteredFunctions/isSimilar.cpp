bool isSimilar(const string& original, const string& candidate, double similarityThreshold) {
    size_t originalSize = original.size();
    size_t candidateSize = candidate.size();

    if (originalSize != candidateSize) {
        return false;
    }

    size_t numDifferent = 0;
    for (size_t i = 0; i < originalSize; i++) {
        if (original[i] != candidate[i]) {
            numDifferent++;
        }
    }

    double dissimilarity = static_cast<double>(numDifferent) / originalSize;
    return (dissimilarity <= (1.0 - similarityThreshold));
}
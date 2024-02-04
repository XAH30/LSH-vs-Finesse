vector<Subchunk> splitIntoSubchunks(const Chunk& chunk, size_t subchunkSize) {
    const string& chunkData = chunk.getData();
    size_t chunkSize = chunk.getSize();
    size_t numSubchunks = (chunkSize + subchunkSize - 1) / subchunkSize;  // Вычисляем количество подчастей заранее

    vector<Subchunk> subchunks;
    subchunks.reserve(numSubchunks);  // Резервируем память для всех подчастей заранее

    for (size_t i = 0; i < chunkSize; i += subchunkSize) {
        size_t currentSubchunkSize = min(subchunkSize, chunkSize - i);

        string subchunkData = chunkData.substr(i, currentSubchunkSize);
        Subchunk subchunk(subchunkData, currentSubchunkSize);
        subchunks.push_back(subchunk);
    }

    return subchunks;
}
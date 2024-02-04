std::string deltaCompression(const Chunk& baseChunk, const Subchunk& similarSubchunk) {
    const std::string& baseData = baseChunk.getData();
    const std::string& similarData = similarSubchunk.getData();

    size_t dataSize = similarSubchunk.getSize();

    std::string deltaCode;
    deltaCode.reserve(dataSize); // Предварительное выделение памяти для ускорения операций вставки

    for (size_t i = 0; i < dataSize; i++) {
        char deltaByte = similarData[i] - baseData[i];
        deltaCode.push_back(deltaByte);
    }

    return deltaCode;
}
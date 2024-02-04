std::vector<Chunk> convert2Chunks(const std::vector<std::string>& data) {
    std::vector<Chunk> chunks;
    chunks.reserve(data.size()); // Предварительное выделение памяти для ускорения операций вставки

    for (const std::string& str : data) {
        size_t strLength = str.length();
        chunks.emplace_back(str, strLength); // Использование emplace_back для эффективной вставки элементов
    }

    return chunks;
}
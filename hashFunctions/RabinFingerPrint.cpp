std::string RabinFingerPrint(const Subchunk& subchunk, size_t position) {
    const size_t hashSize = 8;
    const size_t prime = 4294967311;

    const std::string& subchunkData = subchunk.getData();
    size_t subchunkSize = subchunk.getSize();

    size_t hashValue = 0;
    for (size_t i = 0; i < subchunkSize; i++) {
        hashValue = (hashValue * prime + subchunkData[i]) % (1 << hashSize);
    }

    std::string hashString;
    hashString.reserve(hashSize);
    while (hashValue > 0) {
        hashString.push_back('0' + (hashValue % 10));
        hashValue /= 10;
    }
    while (hashString.length() < hashSize) {
        hashString.push_back('0');
    }

    hashString += std::to_string(position);

    return hashString;
}
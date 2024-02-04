class Chunk {
private:
    string data;
    size_t size;

public:
    Chunk(const string& chunkData, size_t chunkSize) : data(chunkData), size(chunkSize) {}

    const string& getData() const {
        return data;
    }

    size_t getSize() const {
        return size;
    }
};
class Subchunk {
private:
    string data;
    size_t size;

public:
    Subchunk(const string& subchunkData, size_t subchunkSize) : data(subchunkData), size(subchunkSize) {}

    const string& getData() const {
        return data;
    }

    size_t getSize() const {
        return size;
    }
};
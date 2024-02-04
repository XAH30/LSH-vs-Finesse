class Feature {
private:
    string hash;

public:
    Feature(const string& featureHash) : hash(featureHash) {}

    Feature() {}

    const string& getHash() const {
        return hash;
    }
};
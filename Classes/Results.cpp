class Results {
public:
    Results(const set<pair<int, int>>& results, const string& methodName)
        : results(results), methodName(methodName) {}

    Results() {}

    void head(int count = 5) const {
        cout << "Results from " << methodName << " (head " << count << "):" << endl;
        int printedCount = 0;
        for (const auto& result : results) {
            cout << "(" << result.first << ", " << result.second << ")" << endl;
            printedCount++;
            if (printedCount >= count) {
                break;
            }
        }
    }

    void tail(int count = 5) const {
        cout << "Results from " << methodName << " (tail " << count << "):" << endl;
        int resultCount = results.size();
        int printedCount = 0;
        for (auto it = results.rbegin(); it != results.rend(); ++it) {
            cout << "(" << it->first << ", " << it->second << ")" << endl;
            printedCount++;
            if (printedCount >= count || printedCount >= resultCount) {
                break;
            }
        }
    }

    void sample(int count = 5) const {
        cout << "Results from " << methodName << " (random sample " << count << "):" << endl;
        vector<pair<int, int>> resultVector(results.begin(), results.end());
        random_device rd;
        mt19937 g(rd());
        shuffle(resultVector.begin(), resultVector.end(), g);
        int printedCount = 0;
        for (const auto& result : resultVector) {
            cout << "(" << result.first << ", " << result.second << ")" << endl;
            printedCount++;
            if (printedCount >= count) {
                break;
            }
        }
    }

    string getName() const{
        return methodName;
    }
    
private:
    set<pair<int, int>> results;
    string methodName;
};
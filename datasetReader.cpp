// Функция для считывания данных из файла и записи в вектор векторов
std::vector<std::vector<std::string>> readDataFromFile(const std::string& filename) {
    std::vector<std::vector<std::string>> data;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("File could not be opened");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string token;
        while (getline(ss, token, '\t')) {
            row.push_back(token);
        }
        data.push_back(row);
    }

    return data;
}
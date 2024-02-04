// Функция принимает два параметра: shingles - множество шинглов, и vocab - словарь, содержащий соответствие между шинглами и их индексами.
// Создается пустой вектор vec длиной, равной размеру словаря vocab, и заполненный нулями.
// Затем происходит итерация по каждому шинглу shingle в множестве shingles.
// На каждой итерации проверяется, присутствует ли шингл shingle в словаре vocab с помощью метода count. Если шингл присутствует, 
// то получается его индекс idx с помощью метода at словаря vocab.
// Затем элемент с индексом idx в векторе vec устанавливается равным 1.0, чтобы представить шингл в формате "one-hot encoding".
// В конце функция возвращает вектор vec, который представляет шинглы в формате "one-hot encoding" с использованием словаря vocab.
std::vector<double> oneHotEncoder(const std::unordered_set<std::string>& shingles, const std::unordered_map<std::string, int>& vocab) {
    std::vector<double> vec(vocab.size(), 0.0);

    for (const auto& shingle : shingles) {
        if (vocab.count(shingle) > 0) {
            int idx = vocab.at(shingle);
            vec[idx] = 1.0;
        }
    }

    return vec;
}
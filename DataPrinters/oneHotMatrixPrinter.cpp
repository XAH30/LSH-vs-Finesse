// Вывод one-hot matrix в формате матрицы

// one-hot encoding представляет собой способ представления категориальных данных в виде 
// бинарных векторов. Основная идея заключается в том, что каждая уникальная категория или 
// класс данных представляется вектором фиксированной длины, где только один элемент равен 1, 
// а все остальные элементы равны 0

// Шинглы (shingles) - это последовательности элементов фиксированной длины
template<typename Type>
void printOneHotMatrix(std::vector<std::vector<Type>> shingles_1hot_matrix){
    std::cout << "[";
    for (int i = 0; i < shingles_1hot_matrix.size(); i++) {
        std::cout << "[";
        for (int j = 0; j < shingles_1hot_matrix[i].size(); j++) {
            std::cout << shingles_1hot_matrix[i][j];
            if (j != shingles_1hot_matrix[i].size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (i != shingles_1hot_matrix.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
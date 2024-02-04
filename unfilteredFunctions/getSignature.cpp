// функция getSignature выполняет создание сигнатуры для вектора vector на основе матрицы minhash. 
// Сигнатура представляет собой вектор, содержащий минимальные значения в каждой строке матрицы 
// minhash для соответствующих индексов из вектора vector.

// Аргументы функции:

// minhash: двумерный вектор, представляющий матрицу хэшей.
// vector: вектор, для которого необходимо создать сигнатуру.

// Алгоритм функции:

// Создается вектор idx, который будет содержать индексы элементов вектора vector, равных 1. 
// На каждой итерации цикла проходится по каждому элементу вектора vector, и если элемент равен 1, 
// то его индекс добавляется в вектор idx.
// Создается двумерный вектор shingles, который будет содержать значения из матрицы minhash только 
// для выбранных индексов из вектора idx. На каждой итерации цикла проходится по каждой строке матрицы minhash, 
// и для каждого индекса из вектора idx значение из соответствующей ячейки матрицы добавляется во внутренний вектор 
// shingle_row. Затем этот вектор shingle_row добавляется во внешний вектор shingles.
// Создается вектор signature, который будет содержать минимальные значения из каждой строки вектора shingles. 
// На каждой итерации цикла проходится по каждой строке вектора shingles, и с помощью функции std::min_element 
// находится минимальное значение в текущей строке. Затем это минимальное значение добавляется в вектор signature.
// В конце функция возвращает созданную сигнатуру вектора signature.
std::vector<int> getSignature(const std::vector<std::vector<int>>& minhash, const std::vector<int>& vector) {
    std::vector<int> idx;
    for (size_t i = 0; i < vector.size(); i++) {
        if (vector[i] == 1) {
            idx.push_back(i);
        }
    }

    std::vector<std::vector<int>> shingles;
    for (const auto& row : minhash) {
        std::vector<int> shingle_row;
        for (int index : idx) {
            shingle_row.push_back(row[index]);
        }
        shingles.push_back(shingle_row);
    }

    std::vector<int> signature;
    for (const auto& row : shingles) {
        int min_value = *std::min_element(row.begin(), row.end());
        signature.push_back(min_value);
    }

    return signature;
}
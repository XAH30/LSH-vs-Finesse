// Функция transpose выполняет транспонирование матрицы matrix. Транспонирование матрицы означает замену 
// строк матрицы на столбцы и столбцов на строки.

// Аргументы функции:

// matrix: двумерный вектор, представляющий исходную матрицу.

// Алгоритм функции:

// Проверяется, является ли матрица matrix пустой. Если это так, то возвращается пустой вектор (пустая матрица).
// Получается количество строк rows и количество столбцов cols матрицы matrix.
// Создается двумерный вектор result размером cols x rows, заполненный значениями типа Type.
// Для каждого элемента матрицы matrix с индексами (i, j) выполняется присваивание значения matrix[i][j] элементу result[j][i].
// В конце функция возвращает полученную транспонированную матрицу result.
template<typename Type>
std::vector<std::vector<Type>> transpose(const std::vector<std::vector<Type>>& matrix) {
    if (matrix.empty()) {
        return {};
    }

    std::size_t rows = matrix.size();
    std::size_t cols = matrix[0].size();

    std::vector<std::vector<Type>> result(cols, std::vector<Type>(rows));

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}
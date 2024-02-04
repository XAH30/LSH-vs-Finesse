// Вывод датасета

template<typename Type>
void printAllData(std::vector<std::vector<Type>> data) {
    for (const auto& row : data) {
        for (const Type& value : row) 
            std::cout << value << " ";
        std::cout << std::endl;
    }
}
// Вывод вектора в столбец
template<typename Type>
void printVector(vector<Type> data) {
    for (const Type& value : data) {
        cout << value << "\n";
    }
}
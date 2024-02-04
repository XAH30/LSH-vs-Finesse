// Функция printCandidates используется для печати пар кандидатов на основе входных данных candidate_pairs1, candidate_pairs2 и sentences.

// Аргументы функции:

// candidate_pairs1: множество пар кандидатов.
// candidate_pairs2: множество пар кандидатов.
// sentences: вектор строк, содержащих предложения.

// Алгоритм функции:

// Создается указатель checker на множество пар для добавления ппар, которые уже были выведены.
// Инициализируется переменная count со значением 0.
// Инициализируется флаг flag со значением true.
// Вложенным циклом перебираются пары из candidate_pairs2 и candidate_pairs1.
// Если пара {pair1.first, pair1.second} отсутствует в множестве checker, предложения sentences[pair1.first] и sentences[pair1.second] различны,
// а предложения sentences[pair2.first] и sentences[pair1.first], а также sentences[pair2.second] и sentences[pair1.second] совпадают,
// то выводится информация о паре кандидатов pair1 и увеличивается счетчик count. Затем пара {pair1.first, pair1.second} добавляется в множество checker.
// Если значение счетчика count достигает 20, флаг flag устанавливается в false, и происходит прерывание цикла.
// Если флаг flag равен false, происходит прерывание внешнего цикла.
void printCandidates(std::set<std::pair<int, int>> candidate_pairs1, std::set<std::pair<int, int>> candidate_pairs2, std::vector<std::string> sentences){
    std::set<std::pair<int, int>> *checker = new std::set<std::pair<int, int>>;
    int count = 0;
    std::cout << "First 20 candidate pairs:" << std::endl;
    bool flag = true;
    for (const auto& pair2 : candidate_pairs2) {
        for (const auto& pair1 : candidate_pairs1) {
            if (checker->count({pair1.first, pair1.second}) < 1 && sentences[pair1.first] != sentences[pair1.second] && sentences[pair2.first] == sentences[pair1.first] && sentences[pair2.second] == sentences[pair1.second]){
                std::cout << pair1.first << ")" << sentences[pair1.first] << " : " << pair1.second << ")" << sentences[pair1.second] << std::endl << std::endl;
                count++;
                checker->insert({pair1.first, pair1.second});
            }
            if (count >= 20) {
                flag = false;
                break;
            }
        }
        if (flag == false){
            break;
        }
    }
}
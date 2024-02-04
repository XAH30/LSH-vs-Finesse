class LSH {
    std::vector<std::unordered_map<std::string, std::vector<int>>> buckets;
    int counter;

public:
    LSH(int b) : buckets(b), counter(0) {
        for (int i = 0; i < b; i++) {
            buckets[i] = {};
        }
    }

    // Функция makeSubVecs создает подвекторы (subvecs) на основе входного вектора signature. Размер каждого подвектора 
    // определяется на основе количества корзин (buckets) в объекте LSH.

    // Аргумент функции:

    // signature: вектор, для которого нужно создать подвекторы.
    
    // Алгоритм функции:

    // Получается размер входного вектора l.
    // Проверяется, что l делится нацело на количество корзин (buckets.size()). В противном случае будет вызвано исключение assert.
    // Вычисляется размер каждого подвектора r путем деления l на количество корзин (buckets.size()).
    // Создается пустой двумерный вектор subvecs, который будет содержать подвекторы.
    // В цикле с шагом r проходится по входному вектору signature и на каждой итерации создается подвектор subvec. Подвектор 
    // создается путем выбора элементов из входного вектора signature в диапазоне от i до i + r (не включая i + r). 
    // Затем созданный подвектор добавляется в двумерный вектор subvecs.
    // В конце функция возвращает созданный двумерный вектор subvecs.
    std::vector<std::vector<int>> makeSubVecs(const std::vector<int>& signature) {
        int l = signature.size();
        assert(l % buckets.size() == 0);
        int r = l / buckets.size();
        std::vector<std::vector<int>> subvecs;
        for (int i = 0; i < l; i += r) {
            std::vector<int> subvec(signature.begin() + i, signature.begin() + i + r);
            subvecs.push_back(subvec);
        }
        return subvecs;
    }

    // Функция addHash добавляет хэш (hash) в объект LSH. Хэш создается путем разделения входного вектора 
    // signature на подвекторы и сохранения соответствующих хэш-значений в соответствующих корзинах (buckets) объекта LSH.

    // Аргумент функции:

    // signature: вектор, для которого нужно создать хэш и добавить его в объект LSH.
    
    // Алгоритм функции:

    // Создается пустой двумерный вектор subvecs путем вызова функции makeSubVecs с входным вектором signature. 
    // Функция makeSubVecs разделяет signature на подвекторы на основе количества корзин в объекте LSH.
    // В цикле проходится по каждому подвектору в subvecs с помощью индекса i.
    // Создается пустая строка subvec_str, которая будет использоваться для формирования строки хэша подвектора.
    // Во внутреннем цикле проходится по каждому элементу подвектора subvecs[i] с помощью индекса j.
    // Каждое значение элемента преобразуется в строку с помощью std::to_string и добавляется к subvec_str.
    // Если это не последний элемент подвектора, то к subvec_str добавляется запятая.
    // Проверяется, существует ли в корзине i элемент с ключом subvec_str. Если его нет, то создается пустой вектор в корзине i с ключом subvec_str.
    // Вектор counter добавляется в корзину i с ключом subvec_str.
    // Увеличивается значение счетчика counter на единицу.
    void addHash(const std::vector<int>& signature) {
        std::vector<std::vector<int>> subvecs = makeSubVecs(signature);
        for (int i = 0; i < subvecs.size(); i++) {
            std::string subvec_str = "";
            for (int j = 0; j < subvecs[i].size(); j++) {
                subvec_str += std::to_string(subvecs[i][j]);
                if (j < subvecs[i].size() - 1) {
                    subvec_str += ",";
                }
            }
            if (buckets[i].find(subvec_str) == buckets[i].end()) {
                buckets[i][subvec_str] = {};
            }
            buckets[i][subvec_str].push_back(counter);
        }
        counter++;
    }

    // Функция check_candidates выполняет проверку кандидатов для заданного вектора query в объекте LSH. 
    // Она использует хэш-таблицы и корзины объекта LSH для поиска потенциально близких векторов к query.

    // Аргументы функции:

    // query: вектор, для которого нужно найти потенциально близкие векторы.
    
    // Алгоритм функции:

    // Создается пустой вектор candidates, который будет содержать найденных кандидатов.
    // Создается двумерный вектор subvecs путем вызова функции makeSubVecs с входным вектором query. 
    // Функция makeSubVecs разделяет query на подвекторы в соответствии с количеством корзин в объекте LSH.
    // В цикле проходится по каждому подвектору в subvecs с помощью индекса i.
    // Создается пустая строка subvec_str, которая будет использоваться для формирования строки хэша подвектора.
    // Во внутреннем цикле проходится по каждому элементу подвектора subvecs[i] с помощью индекса j.
    // Каждое значение элемента преобразуется в строку с помощью std::to_string и добавляется к subvec_str.
    // Если это не последний элемент подвектора, то к subvec_str добавляется запятая.
    // Проверяется, существует ли корзина i в объекте LSH. Если это так, то выполняется поиск элемента с ключом subvec_str в корзине i.
    // Если элемент с ключом subvec_str найден, то его значения добавляются в вектор candidates.
    // Возвращается вектор candidates.
    std::set<std::pair<int, int>> check_candidates() {
        std::set<std::pair<int, int>> candidates;
        for (const auto& bucket_band : buckets) {
            for (const auto& bucket : bucket_band) {
                const std::vector<int>& hits = bucket.second;
                if (hits.size() > 1) {
                    for (int i = 0; i < hits.size(); i++) {
                        for (int j = i + 1; j < hits.size(); j++) {
                            candidates.insert({hits[i], hits[j]});
                        }
                    }
                }
            }
        }
        return candidates;
    }

    const std::vector<std::unordered_map<std::string, std::vector<int>>>& getBuckets() const {
        return buckets;
    }
};
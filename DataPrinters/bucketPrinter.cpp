// Вывод индексов рассматриваемых строк и строк, с которыми они похожи
void printBucket(std::vector<std::unordered_map<std::string, std::vector<int>>> buckets){
    for (int i = 0; i < buckets.size(); i++) {
        std::cout << "Bucket " << i << ":" << std::endl;
        const std::unordered_map<std::string, std::vector<int>>& bucket_band = buckets[i];
        for (const auto& bucket : bucket_band) {
            const std::string& subvec_str = bucket.first;
            const std::vector<int>& hits = bucket.second;
            std::cout << "  Subvector: " << subvec_str << ", Hits: ";
            for (int hit : hits) {
                std::cout << hit << " ";
            }
            std::cout << std::endl;
        }
    }
}
template <class T>
std::vector<T> set2vec(std::set<T> s){
    std::vector<T> v(s.begin(), s.end());
    return v;
}
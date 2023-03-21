mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T = int>
T rand(T l, T r) {
    return uniform_int_distribution<T>(l, r)(rng);
}
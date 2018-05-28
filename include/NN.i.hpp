template <typename T = type>
constexpr inline T sigmoid(T x)
{
    return (static_cast<T>(1)) / (static_cast<T>(1 + exp(-x)));
}
template <typename T = type>
constexpr inline T d_sigmoid(T x)
{
    return (static_cast<T>(exp(-x))) / (static_cast<T>(pow(1 + exp(-x), 2)));
}
template <typename T = type>
constexpr inline T randomize(T x)
{
    return static_cast<T>(1);
}

template <typename T>
void fillFromFile(const char *file, laobject::Vector<laobject::Vector<T>> &inputs, laobject::Vector<laobject::Vector<T>> &outputs, size_t h, size_t w, size_t outsize);
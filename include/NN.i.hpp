template <typename T = type> inline T sigmoid(T x)
{
    return (static_cast<T>(1)) / (static_cast<T>(1 + exp(-x)));
}
template <typename T = type> inline T d_sigmoid(T x)
{
    return (static_cast<T>(exp(-x))) / (static_cast<T>(pow(1 + exp(-x), 2)));
}
template <typename T> T randomize() { return -1; }
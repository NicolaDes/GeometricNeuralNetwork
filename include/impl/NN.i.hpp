template <typename T = type> inline T sigmoid(T x)
{
    return (static_cast<T>(1)) / (static_cast<T>(1 + exp(-x)));
}
template <typename T = type> inline T d_sigmoid(T x)
{
    return (static_cast<T>(exp(-x))) / (static_cast<T>(pow(1 + exp(-x), 2)));
}
template <typename T> T randomize() { return -1; }

template <typename T>
void NN::fillFromFile(std::string file, Vector<Vector<T>> &inputs,
                      Vector<Vector<T>> &outputs, size_t h, size_t w,
                      size_t outsize)
{
    std::ifstream fin(file);
    if (!fin.is_open()) {
        std::cerr << "Error, no file was found with name " << file << "\n";
        std::exit(2);
    }
    size_t training_set;
    training_set = inputs.size();
    for (size_t k = 0; k < training_set; ++k) {
        std::cout << "\r[" << activity_symbol(static_cast<unsigned>(k)) << "] "
                  << static_cast<int>(k * 100 / training_set) << "% "
                  << std::flush;
        Vector<T> input(h * w);
        Vector<T> output(outsize);
        char c;
        size_t out;
        fin >> c;
        out = c - '0';
        output[out] = 1;
        outputs[k] = output;
        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                fin >> c;
                while (c != ',') {
                    input[i * w + j] += c - '0';
                    fin >> c;
                }
            }
        }
        inputs[k] = input;
        fin >> c;
    }
    std::cout << "\r[" << activity_symbol(static_cast<unsigned>(4)) << "] "
          << static_cast<int>(100) << "% " << std::flush;
}

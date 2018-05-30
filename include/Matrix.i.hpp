
namespace laobject
{

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : LAObject<T>(rows * cols)
{
    this->values_ = new T[this->size_](); // without () the value is
                                          // initialized!
    this->leading_ = cols;
    this->row_offeset_ = rows;
}

template <typename T> Matrix<T>::~Matrix() { delete[] this->values_; }

template <typename T> size_t Matrix<T>::size() const { return this->size_; }

template <typename T> void Matrix<T>::print() const
{
    for (size_t i = 0; i < this->row_offeset_; ++i) {
        for (size_t j = 0; j < this->leading_; ++j)
            std::cout << this->values_[i * this->leading_ + j] << " ";
        std::cout << "\n";
    }
}

template <typename T> size_t Matrix<T>::rows() const
{
    return this->row_offeset_;
}

template <typename T> size_t Matrix<T>::cols() const { return this->leading_; }

template <typename T> T *Matrix<T>::operator[](size_t row) const
{
    return &this->values_[row * this->leading_];
}
template <typename T> T *Matrix<T>::operator[](size_t row)
{
    return &this->values_[row * this->leading_];
}
template <typename T> Matrix<T> Matrix<T>::operator~() const
{
    Matrix<T> c(this->leading_, this->row_offeset_);
    size_t i, j;
    for (i = 0; i < this->row_offeset_; ++i) {
        for (j = 0; j < this->leading_; ++j)
            c[j][i] = this->values_[i * this->leading_ + j];
    }
    return c;
}

template <typename T> Matrix<T> Matrix<T>::operator()(T (*fptr)(T val)) const
{
    Matrix<T> ret(this->row_offeset_, this->leading_);
    for (size_t i = 0; i < this->row_offeset_; ++i) {
        for (size_t j = 0; j < this->leading_; ++j)
            ret[i][j] = fptr(this->values_[i * this->leading_ + j]);
    }
    return ret;
}

template <typename T> Matrix<T> Matrix<T>::operator()(T (*fptr)()) const
{
    Matrix<T> ret(this->row_offeset_, this->leading_);
    for (size_t i = 0; i < this->row_offeset_; ++i) {
        for (size_t j = 0; j < this->leading_; ++j)
            ret[i][j] = fptr();
    }
    return ret;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m)
{
    if (this == &m)
        return *this;
    this->size_ = m.size_;
    this->leading_ = m.leading_;
    this->row_offeset_ = m.row_offeset_;
    delete[] this->values_;
    this->values_ = new T[this->size_];
    std::copy(m.values_, m.values_ + this->size_, this->values_);
    return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator+(const Matrix<T> &m)
{
    if (this->leading_ != m.leading_) {
        std::cerr << "Vector1.cols, Vector2.cols do not match!\n";
        std::exit(EXIT_FAILURE);
    }
    if (this->row_offeset_ != m.row_offeset_) {
        std::cerr << "Vector1.rows, Vector2.rows do not match!\n";
        std::exit(EXIT_FAILURE);
    }

    Matrix<T> ret(this->row_offeset_, this->leading_);
    for (size_t i = 0; i < this->row_offeset_; ++i) {
        for (size_t j = 0; j < this->leading_; ++j)
            ret[i][j] = this->values_[i * this->leading_ + j] +
                        m.values_[i * this->leading_ + j];
    }
    return ret;
}

template <typename T> Matrix<T> Matrix<T>::operator-(const Matrix<T> &m)
{
    if (this->leading_ != m.leading_) {
        std::cerr << "Vector1.cols, Vector2.cols do not match!\n";
        std::exit(EXIT_FAILURE);
    }
    if (this->row_offeset_ != m.row_offeset_) {
        std::cerr << "Vector1.rows, Vector2.rows do not match!\n";
        std::exit(EXIT_FAILURE);
    }

    Matrix<T> ret(this->row_offeset_, this->leading_);
    for (size_t i = 0; i < this->row_offeset_; ++i) {
        for (size_t j = 0; j < this->leading_; ++j)
            ret[i][j] = this->values_[i * this->leading_ + j] -
                        m.values_[i * this->leading_ + j];
    }
    return ret;
}

template <typename T> Matrix<T> Matrix<T>::operator*(const Matrix<T> &m)
{
    if (this->leading_ != m.row_offeset_) {
        std::cerr << "matrix1.cols, matrix2.rows do not match!\n";
        std::exit(EXIT_FAILURE);
    }

    Matrix<T> ret(this->row_offeset_, m.leading_);
    for (size_t i = 0; i < this->row_offeset_; ++i) {
        for (size_t j = 0; j < m.leading_; ++j) {
            for (size_t k = 0; k < this->leading_; ++k)
                ret[i][j] += this->values_[i * this->leading_ + k] *
                             m.values_[k * m.leading_ + j];
        }
    }
    return ret;
}

template <typename T> Matrix<T> Matrix<T>::operator,(const Matrix<T> &m)
{
    if (this->leading_ != m.leading_) {
        std::cerr << "Vector1.cols, Vector2.cols do not match!\n";
        std::exit(EXIT_FAILURE);
    }
    if (this->row_offeset_ != m.row_offeset_) {
        std::cerr << "Vector1.rows, Vector2.rows do not match!\n";
        std::exit(EXIT_FAILURE);
    }
    Matrix<T> ret(this->row_offeset_, this->leading_);
    for (size_t i = 0; i < this->row_offeset_; ++i) {
        for (size_t j = 0; j < this->leading_; ++j)
            ret[i][j] = this->values_[i * this->leading_ + j] *
                        m.values_[i * m.leading_ + j];
    }
    return ret;
}
} // namespace laobject
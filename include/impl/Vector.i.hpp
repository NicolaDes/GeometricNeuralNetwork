
template <typename T> Vector<T>::Vector(size_t size) : LAObject<T>(size)
{
    this->values_ = new T[size]();
}

template <typename T>
Vector<T>::Vector(const Vector<T> &v) : LAObject<T>(v.size_)
{
    this->size_ = v.size_;
    this->values_ = new T[this->size_];
    std::copy(v.values_, v.values_ + this->size_, this->values_);
}

template <typename T> Vector<T>::~Vector() { delete[] this->values_; }

template <typename T> size_t Vector<T>::size() const { return this->size_; }

template <typename T> void Vector<T>::print() const
{
    for (size_t i = 0; i < this->size_; i++)
        std::cout << this->values_[i] << "\n";
}

template <typename T> size_t Vector<T>::rows() const { return 1; }

template <typename T> size_t Vector<T>::cols() const { return this->size_; }

template <typename T> T Vector<T>::at(size_t index) const
{
    return this->values_[index];
}

template <typename T> T Vector<T>::operator[](size_t index) const
{
    return this->values_[index];
}

template <typename T> T &Vector<T>::operator[](size_t index)
{
    return this->values_[index];
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &v)
{
    if (this == &v)
        return *this;
    this->size_ = v.size_;
    delete[] this->values_;
    this->values_ = new T[this->size_];
    std::copy(v.values_, v.values_ + this->size_, this->values_);
    return *this;
}

template <typename T> Vector<T> Vector<T>::operator+(const Vector<T> &v)
{
    if (this->size_ != v.size_) {
        std::cerr << "v1.size_, v2.size_ do not match!\n";
        std::exit(EXIT_FAILURE);
    }
    Vector<T> ret(v.size_);
    for (size_t i = 0; i < v.size_; ++i)
        ret[i] = this->values_[i] + v.values_[i];
    return ret;
}

template <typename T> Vector<T> Vector<T>::operator-(const Vector<T> &v)
{
    if (this->size_ != v.size_) {
        std::cerr << "v1.size_, v2.size_ do not match!\n";
        std::exit(EXIT_FAILURE);
    }
    Vector<T> ret(this->size_);
    for (size_t i = 0; i < this->size_; ++i)
        ret[i] = this->values_[i] - v.values_[i];
    return ret;
}

template <typename T> Vector<T> Vector<T>::operator()(T (*fptr)(T val)) const
{
    Vector<T> ret(this->size_);
    for (size_t i = 0; i < this->size_; ++i) {
        ret[i] = fptr(this->values_[i]);
    }
    return ret;
}

template <typename T> Vector<T> Vector<T>::operator()(T (*fptr)()) const
{
    Vector<T> ret(this->size_);
    for (size_t i = 0; i < this->size_; ++i) {
        ret[i] = fptr();
    }
    return ret;
}

template <typename T> Vector<T> Vector<T>::operator,(const Vector<T> &v)
{
    if (this->size_ != v.size_) {
        std::cerr << "Vector1.size_, Vector2.size_ do not match!\n";
        std::exit(EXIT_FAILURE);
    }

    Vector<T> ret(this->size_);
    for (size_t i = 0; i < this->size_; ++i) {
        ret.values_[i] = this->values_[i] * v.values_[i];
    }
    return ret;
}

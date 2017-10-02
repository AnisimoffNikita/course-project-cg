#ifndef MATRIX_H
#define MATRIX_H

template <int M, int N, typename T>
class Matrix
{
public:
    Matrix();
    explicit Matrix(const T *values);

    const T& operator()(int row, int column) const;
    T& operator()(int row, int column);

    bool isIdentity() const;
    void setToIdentity();

    void fill(const T &value);

    Matrix<N, M, T> transposed() const;

    Matrix<M, N, T>& operator+=(const Matrix<M, N, T>& other);
    Matrix<M, N, T>& operator-=(const Matrix<M, N, T>& other);
    Matrix<M, N, T>& operator*=(T factor);
    Matrix<M, N, T>& operator/=(T divisor);
    bool operator==(const Matrix<M, N, T>& other) const;
    bool operator!=(const Matrix<M, N, T>& other) const;

    T *data() { return *m; }
    const T *data() const { return *m; }

    template<int MM, int NN, typename TT>
    friend Matrix<MM, NN, TT> operator+(const Matrix<MM, NN, TT>& m1, const Matrix<MM, NN, TT>& m2);
    template<int MM, int NN, typename TT>
    friend Matrix<MM, NN, TT> operator-(const Matrix<MM, NN, TT>& m1, const Matrix<MM, NN, TT>& m2);
    template<int NN, int M1, int M2, typename TT>
    friend Matrix<M1, M2, TT> operator*(const Matrix<M1, NN, TT>& m1, const Matrix<NN, M2, TT>& m2);
    template<int MM, int NN, typename TT>
    friend Matrix<MM, NN, TT> operator-(const Matrix<MM, NN, TT>& matrix);
    template<int MM, int NN, typename TT>
    friend Matrix<MM, NN, TT> operator*(TT factor, const Matrix<MM, NN, TT>& matrix);
    template<int MM, int NN, typename TT>
    friend Matrix<MM, NN, TT> operator*(const Matrix<MM, NN, TT>& matrix, TT factor);
    template<int MM, int NN, typename TT>
    friend Matrix<MM, NN, TT> operator/(const Matrix<MM, NN, TT>& matrix, TT divisor);

private:
    T m[N][M];

};

template <int M, int N, typename T>
Matrix<M, N, T>::Matrix()
{
}

template <int M, int N, typename T>
Matrix<M, N, T>::Matrix(const T *values)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            m[row][col] = values[row * N + col];
}

template <int M, int N, typename T>
const T& Matrix<M, N, T>::operator()(int row, int col) const
{
    return m[row][col];
}

template <int M, int N, typename T>
T& Matrix<M, N, T>::operator()(int row, int col)
{
    return m[row][col];
}

template <int M, int N, typename T>
bool Matrix<M, N, T>::isIdentity() const
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            if (row == col && m[row][col] != 1.0f)
               return false;
            else if (m[row][col] != 0.0f)
               return false;
    return true;
}

template <int M, int N, typename T>
void Matrix<M, N, T>::setToIdentity()
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            if (row == col)
                m[row][col] = 1.0f;
            else
                m[row][col] = 0.0f;
}

template <int M, int N, typename T>
void Matrix<M, N, T>::fill(const T& value)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            m[row][col] = value;
}

template <int M, int N, typename T>
Matrix<N, M, T> Matrix<M, N, T>::transposed() const
{
    Matrix<N, M, T> result;
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[col][row] = m[row][col];
    return result;
}

template <int M, int N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator+=(const Matrix<M, N, T>& other)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            m[row][col] += other.m[row][row];
    return *this;
}

template <int M, int N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator-=(const Matrix<M, N, T>& other)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            m[row][col] -= other.m[row][row];
    return *this;
}

template <int M, int N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator*=(T factor)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            m[row][col] *= factor;
    return *this;
}

template <int M, int N, typename T>
bool Matrix<M, N, T>::operator==(const Matrix<M, N, T>& other) const
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            if (m[row][col] != other.m[row][col])
                return false;
    return true;
}

template <int M, int N, typename T>
bool Matrix<M, N, T>::operator!=(const Matrix<M, N, T>& other) const
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            if (m[row][col] == other.m[row][col])
                return false;
    return true;
}

template <int M, int N, typename T>
Matrix<M, N, T>& Matrix<M, N, T>::operator/=(T divisor)
{
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            m[row][col] /= divisor;
    return *this;
}

template <int M, int N, typename T>
Matrix<M, N, T> operator+(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2)
{
    Matrix<M, N, T> result;
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[row][col] = m1.m[row][col] + m2.m[row][col];
    return result;
}

template <int M, int N, typename T>
Matrix<M, N, T> operator-(const Matrix<M, N, T>& m1, const Matrix<M, N, T>& m2)
{
    Matrix<M, N, T> result;
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[row][col] = m1.m[row][col] - m2.m[row][col];
    return result;
}

template <int N, int M1, int M2, typename T>
Matrix<M1, M2, T> operator*(const Matrix<M1, N, T>& m1, const Matrix<N, M2, T>& m2)
{
    Matrix<M1, M2, T> result;
    for (int row = 0; row < M1; ++row)
        for (int col = 0; col < M2; ++col) {
            T sum(0.0f);
            for (int j = 0; j < N; ++j)
                sum += m1.m[row][j] * m2.m[j][col];
            result.m[row][col] = sum;
        }
    return result;
}

template <int M, int N, typename T>
Matrix<M, N, T> operator-(const Matrix<M, N, T>& matrix)
{
    Matrix<M, N, T> result;
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[row][col] = -matrix.m[row][col];
    return result;
}

template <int M, int N, typename T>
Matrix<M, N, T> operator*(T factor, const Matrix<M, N, T>& matrix)
{
    Matrix<M, N, T> result;
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[row][col] = matrix.m[row][col]*factor;
    return result;
}

template <int M, int N, typename T>
Matrix<M, N, T> operator*(const Matrix<M, N, T>& matrix, T factor)
{
    Matrix<M, N, T> result;
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[row][col] = matrix.m[row][col]*factor;
    return result;
}

template <int M, int N, typename T>
Matrix<M, N, T> operator/(const Matrix<M, N, T>& matrix, T divisor)
{
    Matrix<M, N, T> result;
    for (int row = 0; row < M; ++row)
        for (int col = 0; col < N; ++col)
            result.m[row][col] = matrix.m[row][col]/divisor;
    return result;
}
#endif // MATRIX_H

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <utility>

template<typename T>
struct matrix_size;

template<typename T, size_t N>
struct matrix_size<T[N][N]>{
    typedef T type;
    static size_t const size = N;
};

template<typename Array>
bool CreateInvMatrix(Array const &in_, Array &out){
    typedef typename matrix_size<Array>::type type;
    size_t const n = matrix_size<Array>::size;
    Array in;
    /* 复制输入，并初始化out */
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != n; ++j) {
            in[i][j] = in_[i][j];
            out[i][j] = 0;
        }
        out[i][i] = 1;// 将out赋值为单位阵
    }

    type tmp = 1;
    for (size_t c = 0; c != n; ++c) {
        /* 选取列主元，避免出现in[c][c]为0或过小导致商溢出的情形 */
        size_t pivot = 0;
        type maximum = 0;
        for (size_t r = c; r != n; ++r) {
            type const tmp = std::abs(in[r][c]);
            if (tmp > maximum) {
                maximum = tmp;
                pivot = r;
            }
        }
        if (maximum == 0) return false;// 不可逆

        /* 交换c, pivot两行 */
        for (size_t i = c; i != n; ++i) std::swap(in[c][i], in[pivot][i]);
        for (size_t i = 0; i != n; ++i) std::swap(out[c][i], out[pivot][i]);

        /* 正规化 */
        for (size_t i = c + 1; i != n; ++i) {
            in[c][i] /= in[c][c];
        }
        for (size_t i = 0; i != n; ++i) {
            out[c][i] /= in[c][c];
        }

        tmp *= in[c][c];//记录除数以恢复

        // 行变换消元
        in[c][c] = 0;
        for (size_t r = 0; r != n; ++r) {
            for (size_t i = 0; i != n; ++i) {
                in[r][i] += in[c][i] * -in[r][c];
                out[r][i] += out[c][i] * -in[r][c];
            }
        }
    }

    tmp *= 9;
    //在上述的密钥中，为了将行列式值修改为26互质，
    //故需乘上倍数因子9，具体数值可在恢复为整数后，
    //再通过求行列式值与26的最大公约数为1的方法，
    //不断改变倍数因子以获得
    
    /* 将小数恢复为整数 */
    for (size_t i = 0; i != n; ++i)
        for (size_t j = 0; j != n; ++j)
            out[i][j] *= tmp;

    return true;
}

#endif // MATRIX_H

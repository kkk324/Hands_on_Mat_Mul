#include "matmul.h"

#include <stdio.h>

namespace matmul
{
    void MatmulOperator::mat_mul_reordering(const struct matmul_params *params)
    {
        int i,j,k;
        float Aik;
        // 從 params 結構中提取矩陣 A、B 和 C 的指針
        const struct matrix *A = &params->A, *B = &params->B, *C = &params->C;
        float *data_A = A->data_ptr, *data_B = B->data_ptr, *data_C = C->data_ptr;
        // 檢查矩陣是否符合乘法要求
        CHECK_MAT(A, B, C);
        //初始化矩陣 C 的所有元素為 0
        for(i=0; i < C->row; i++)
            for(j=0; j < C->column;j++)
        {
                data_C[i * C->column + j] = 0;
        }        
        // TODO: 實現矩陣乘法的核心計算，並使用循環重新排序優化
        /**
            關於如何實現和優化矩陣乘法的提示：
            基本矩陣乘法：
            通常，矩陣乘法的實現會先遍歷結果矩陣 C 的每一行（外層循環），然後遍歷 C 的每一列（中層循環），
            最後在內層循環中計算內積，累加到 C 的對應元素上。
            循環重新排序：
            循環重新排序的目的是改善內存訪問模式，從而提高緩存命中率。
            在矩陣乘法的情境下，將內層循環和中層循環交換（即先遍歷 A 的列，然後遍歷 C 的列）通常能夠提高性能，
            因為這樣可以減少對 B 矩陣的重複訪問。
            實現提示：
            在實現時，可以先將 A 矩陣的當前元素(Aik)存儲在一個臨時變量中，
            然後在內層循環中使用這個臨時變量與 B 矩陣的相應元素相乘，再將結果累加到 C 矩陣的對應元素上。
            for (i = 0; i < C->row; i++)
                for (j = 0; j < C->column; j++)
            {
                float acc = 0;
                for (k = 0; k < A->column; k++)
                    acc += data_A[i * A->column + k] * data_B[k + j*B->row];
				data_C[i*C->column+j] = acc;
            }
        
        
        **/
        for(i=0; i < C->row; i++)
            for(k=0; k < A->column; k++)
        {
                Aik = data_A[i*A->column + k];
                for(j=0; j < C->column; j++)
                {
                     data_C[i*C->column + j] += Aik * data_B[k*B->column+j];
                }
        }

        
    }
}
#include "matmul.h"

#include <sys/time.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define RUNS 1 //表示執行每種矩陣乘法實現的次數

namespace matmul
{
	void MatmulOperator::CHECK_MAT(const matrix *A, const matrix *B, const matrix *C){
		assert(A->column == B->row);
		assert(B->column == C->column);		
		assert(A->row == C->row);
	}

	void MatmulOperator::native_matmul(const struct matmul_params *params)
	{
		int i,j,k;
		//這段程式碼首先從一個結構體中提取三個矩陣結構體的指針，
		//然後從這些矩陣結構體中提取數據指針，最後調用一個函數來檢查這些矩陣是否滿足特定的條件

		//1.結構體指針的初始化
		//定義三個指向不同矩陣的指針 A、B 和 C，
		//這些指針都是不可修改所指向矩陣內容的。這樣的設計通常用於函數參數，以確保函數內部不會意外修改輸入的矩陣	
	    const struct matrix *A = &params->A, *B = &params->B, *C=&params->C; 
		
		//2. 提取矩陣數據的指針
        //定義一個指向 float 類型的指針 data_A，並將其賦值為指向結構體 A 中 data_ptr 成員的指針
        float *data_A = A->data_ptr, *data_B = B->data_ptr, *data_C = C->data_ptr;
		
		//3. 檢查矩陣條件的函數調用
        //函數調用，檢查這三個矩陣是否滿足某些條件，如尺寸相匹配
		CHECK_MAT(A, B, C);
        
		//矩陣乘法的核心思想是將第一個矩陣的每一行與第二個矩陣的每一列進行點乘（內積），
		//得到結果矩陣的對應元素。在 C++ 中實現矩陣乘法時，可以使用三層嵌套的 for 循環來計算每個元素的值。
		//給定兩個矩陣 A 和 B，其中 A 的大小為 m×n（m 行 n 列），B 的大小為 n×p（n 行 p 列），
		//它們的乘積 C 將是一個 m×p 的矩陣，其中每個元素 Cij（位於第 i 行第 j 列）可以通過以下方式計算
		//Cij = Σ (k=1 to n) Aik * Bkj

		//外層兩個循環（i 和 j）分別遍歷結果矩陣 C 的所有行和列。
		//內層循環（k）用於計算 C 的每個元素的值，通過將 A 的當前行與 B 的當前列進行點乘。
		//在訪問 A 和 B 的元素時，我們使用 i * A->column + k 和 k * B->column + j 來計算正確的索引。這是因為我們假設矩陣以行優先（row-major）順序存儲在一維數組中。
		//最後，計算出的累加值 acc 被賦值給 C 的對應元素。
		for (i = 0; i < C->row; i++)
            for (j = 0; j < C->column; j++)
            {
                float acc = 0;
                for (k = 0; k < A->column; k++)
                    acc += data_A[i * A->column + k] * data_B[k + j*B->row];
				data_C[i*C->column+j] = acc;
            }

	}

    float interval_to_ms(struct timeval *start, struct timeval *end)
    {
        float us_seconds = (end->tv_sec - start->tv_sec) * 1000000 + (end->tv_usec - start->tv_usec);
        return us_seconds / 1000;
    }

	void MatmulOperator::evaluate(IMP_TYPE type, const struct matmul_params *params){
		struct timeval start, end;
        int ms;
        std::string function_name;

        gettimeofday(&start, NULL);
        // choose implementation
        switch (type)
        {
        case NATIVE:
            function_name = "native_matmul";
            for (int i = 0; i < RUNS; i++)
                this->native_matmul(params);
            break;
		}
		gettimeofday(&end, NULL);
        ms = interval_to_ms(&start, &end);
        std::cout << function_name << ": " << ms << " ms" << std::endl;
	}
}

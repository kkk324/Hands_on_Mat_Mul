struct matrix{
	int row;
	int column;
	float *data_ptr;
};

struct matmul_params
{
	struct matrix A, B, C;
};

namespace matmul
{
	class MatmulOperator
	{
	public:			
		enum IMP_TYPE
		{
			NATIVE,
			UNROLL,
		};
		void native_matmul(const struct matmul_params *params);
		void mat_mul_reordering(const struct matmul_params *params);
		void evaluate(IMP_TYPE type, const struct matmul_params *params);
	private:
		void CHECK_MAT(const struct matrix *A, const struct matrix *B, const struct matrix *C);
	};		
};

// BPtest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<cmath>


template<class T>
struct Matrix
{
	int rows, columns;
	T **mat;//[rows][columns]

	Matrix()
	{
		mat = NULL;
		this->reSitSize(0, 0);
	}

	Matrix(int rows, int columns)
	{
		mat = NULL;
		this->reSitSize(rows, columns, 0, 0);
	}

	Matrix(int rows, int columns, T elem)
	{
		mat = NULL;
		this->reSitSize(rows, columns, elem, elem);
	}

	void reSitSize(int rows, int columns)
	{
		this->reSitSize(rows, columns, 0, 0);
	}

	void reSitSize(int rows, int columns, T s, T e)
	{
		
		//删除原来的数据
		if (mat != NULL)
		{
			for (int i = 0; i < this->rows; i++)
			{
				delete []mat[i];
			}
			delete []mat;
		}
		
		this->rows = rows;
		this->columns = columns;

		mat = new T *[rows];
		for (int i = 0; i < rows; i++)
		{
			mat[i] = new T[columns];
			for (int j = 0; j < this->columns; j++)
			{

				mat[i][j] = random(s, e);
			}
		}
	}

	Matrix& operator + (Matrix &mat2)
	{
		if (!this->isHomoType(mat2))
		{
			Matrix nMat(0, 0);
			return nMat;
		}
		Matrix nMat(rows, columns);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				nMat(i, j) = (*this)(i, j) + mat2(i, j);
			}
		}
		return nMat;
	}

	Matrix& operator * (Matrix &mat2)
	{
		if (mat2.rows != this->columns)
		{
			Matrix nMat(0, 0);
			return nMat;
		}
		Matrix nMat(this->rows, mat2.columns);
		T sum = 0;
		for (int i = 0; i < nMat.rows; i++)
		{
			for (int j = 0; j < nMat.columns; j++)
			{

				for (int l = 0; l < mat2.rows; l++)
				{
					sum += (*this)(i, l) * mat2(l, j);
				}
				//nMat.setMat(i, j, sum);
				nMat(i, j) = sum;
				sum = 0;
			}
		}
		return nMat;
	}

	bool isHomoType(const Matrix mat2)
	{
		if (mat2.rows == rows && mat2.columns == columns)
		{
			return 1;
		}
		else {
			return 0;
		}
	}

	T& operator () (int y, int x)
	{
		return (this->mat)[y][x];
	}

	void print()
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				std::cout << (*this)(i, j) << " ";
			}
			std::cout << std::endl;
		}
	}

	T random(T start, T end)
	{
		srand((unsigned)clock());
		return start + (end - start)*(T)rand() / (RAND_MAX + 1.0);
	}
};

int randomData(Matrix<double> &a)
{
	double sum = a.columns * a.rows;
	int x, y;
	a.reSitSize(a.rows, a.columns);
	srand((unsigned)clock());

	sum = (int)(sum*(double)rand() / (RAND_MAX + 1.0));
	int count = sum;
	while (count)
	{
		srand((unsigned)clock());
		x = (int)(a.columns*(double)rand() / (RAND_MAX + 1.0));
		srand((unsigned)clock());
		y = (int)(a.rows*(double)rand() / (RAND_MAX + 1.0));
		if (!a(y, x))
		{
			a(y, x) = 1;
			count--;
		}
	}
	return (int)sum;
}

Matrix<double>& sigmod(Matrix<double> x)
{
	Matrix<double> nMat(x.rows, x.columns);
	for (int i = 0; i < nMat.rows; i++)
	{
		for (int j = 0; j < nMat.columns; j++)
		{
			nMat(i, j) = 1 / (1 + exp(-x(i, j)));
		}
	}
	return nMat;
}

Matrix<double> a[4], w[4], b[4], z[4], dw[4], db[4], da[4], dz[4], y;

void train()
{
	int i = 1;
	while (i--)
	{
		y(0, 0) = randomData(a[0]) / 9;

		z[1] = w[1] * a[0] + b[1];
		a[1] = sigmod(z[1]);
		z[2] = w[2] * a[1] + b[2];
		a[2] = sigmod(z[2]);
		z[3] = w[3] * a[2] + b[3];
		a[3] = sigmod(z[3]);
		double C = pow(y(0, 0) - a[3](0, 0), 2);

	}
}

int main()
{

	a[0].reSitSize(9, 1);

	dw[1].reSitSize(16, 9);
	w[1].reSitSize(16, 9, -1, 1);

	db[1].reSitSize(16, 1);
	b[1].reSitSize(16, 1, -1, 1);
	dz[1].reSitSize(16, 1);
	z[1].reSitSize(16, 1);
	da[1].reSitSize(16, 1);
	a[1].reSitSize(16, 1);

	dw[2].reSitSize(16, 16);
	w[2].reSitSize(16, 16, -1, 1);

	db[2].reSitSize(16, 1);
	b[2].reSitSize(16, 1, -1, 1);
	dz[2].reSitSize(16, 1);
	z[2].reSitSize(16, 1);
	da[2].reSitSize(16, 1);
	a[2].reSitSize(16, 1);

	dw[3].reSitSize(1, 16);
	w[3].reSitSize(1, 16, -1, 1);

	db[3].reSitSize(1, 1);
	b[3].reSitSize(1, 1, -1, 1);
	dz[3].reSitSize(1, 1);
	z[3].reSitSize(1, 1);
	da[3].reSitSize(1, 1);
	a[3].reSitSize(1, 1);

	y.reSitSize(1, 1);

	randomData(a[0]);

	a[0].print();

	double &a12 = a[0](1, 2);

	std::cout << a[0](1, 2) << std::endl;
	a12 = 13;
	std::cout << a[0](1, 2);
	//while (1)std::cout << (unsigned long)clock() << std::endl;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

template <typename Cell = double>
class Matrix
{
private:
	int rows;
	int cols;

	Cell **cells;
	void AllocateCells(int,int);
	void FreeCells();
	
public:
	Matrix() : cols(0), rows(0), cells(nullptr) {}	// Конструктор по умолчанию
	Matrix(const Matrix&);					// Конструктор копирования
	Matrix(int,int);							// Конструктор нулевой матрицы
	Matrix(int,int, Cell*);						// Конструктор матрицы из списка
	~Matrix();								// Деструктор

	Cell &operator()(int i, int j) { return cells[i-1][j-1]; }
	
	Matrix& operator = (const Matrix&);		// Перегрузка оператора присваивания
	Matrix& operator % (const Matrix&);		//переприсваивание
	Matrix  operator + (const Matrix&);		// Сложение матриц
	Matrix  operator - (const Matrix&);		// Вычитание матриц
	Matrix  operator * (const Matrix&);		// Умножение матриц

	friend istream& operator >> <> (istream&, Matrix&);			// Перегрузка оператора >> для ввода матрицы
	friend ostream& operator << <> (ostream&, const Matrix&);	// Перегрузка оператора << для вывода матрицы




	Cell MatrGetX(int x)
	{
		return cells[0][x-1];
	}

	Cell MatrGetY(int y)
	{
		return cells[1][y-1];
	}

	Cell MatrGetZ(int z)
	{
		return cells[2][z-1];
	}
	Cell MatrGetO(int u)
	{
		return cells[3][u-1];
	}

	Cell MatrGetCellXY(int x, int y)
	{
		return cells[x-1][y-1];
	}
	void MatrSetCellXY(int x, int y, Cell value)
	{
		cells[x-1][y-1] = value;
	}
	Cell MatrGetOdn(int k)
	{
		return cells[3][k-1];
	}
	int getRows()
	{
		return rows;
	}
	int getCols()
	{
		return cols;
	}
};

template <typename Cell>
Matrix<Cell>::Matrix(const Matrix<Cell>& M)
{
	AllocateCells(M.rows,M.cols);
	for (int i=0; i<rows; i++)
	for (int j=0; j<cols; j++)
		cells[i][j] = M.cells[i][j];
}

template <typename Cell>
Matrix<Cell>::Matrix(int Rows, int Cols)
{
	AllocateCells(Rows,Cols);
	for (int i=0; i<Rows; i++)
	for (int j=0; j<Cols; j++)
		cells[i][j] = 0;
}

template <typename Cell>
Matrix<Cell>::Matrix(int Rows,int Cols, Cell* list)
{
	rows = Rows;
	cols = Cols;
	AllocateCells(rows,cols);
	
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			cells[i][j] = list[i*cols+j];
		}
	}
}

template <typename Cell>
Matrix<Cell>::~Matrix()
{
	FreeCells();
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator=(const Matrix& M)
{
	if ( rows != M.rows && cols!=M.cols)
	{
		FreeCells();
		AllocateCells(M.rows,M.cols);
	}

	for (int i=0; i<rows; i++)
	for (int j=0; j<cols; j++)
		cells[i][j] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell>& Matrix<Cell>::operator%(const Matrix& M)
{
	FreeCells();
	AllocateCells(M.cols,M.rows);

	for (int i=0; i<M.rows; i++)
	for (int j=0; j<M.cols; j++)
		cells[j][i] = M.cells[i][j];
	return *this;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator+(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if ( cols == M.cols && rows == M.rows)
	{
		for (int i=0; i<rows; i++)
		for (int j=0; j<cols; j++)
			res.cells[i][j] += M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator-(const Matrix& M)
{
	Matrix<Cell> res(*this);
	if ( cols == M.cols && rows == M.rows)
	{
		for (int i=0; i<rows; i++)
		for (int j=0; j<cols; j++)
			res.cells[i][j] -= M.cells[i][j];
	}
	return res;
}

template <typename Cell>
Matrix<Cell> Matrix<Cell>::operator*(const Matrix& M)
{
	Matrix<Cell> res_A(*this);
	Matrix<Cell> res_C(rows,M.cols);

	if ( cols == M.rows )
	{
		for (int i=0; i<rows; i++)
		for (int j=0; j<M.cols; j++)
		{
			Cell value = 0;
			for (int k = 0; k<cols; k++)
				value = value + res_A.cells[i][k]*M.cells[k][j];

			res_C.cells[i][j] = value;
		}	
	}
	return res_C;
}

template <typename Cell>
void Matrix<Cell>::AllocateCells(int Rows, int Cols = 0)
{
	rows = Rows;
	cols = Cols;
	if (Cols == 0) cols = Rows;
	cells = new Cell*[rows];
	for (int i=0; i<rows; i++)
		cells[i] = new Cell[cols];
}

template <typename Cell>
void Matrix<Cell>::FreeCells()
{
	for (int i=0; i<rows; i++)
		delete cells[i];
	delete cells;
	rows = 0;
	cols = 0;
}

template <typename Cell>
istream& operator >> (istream& fi, Matrix<Cell>& M)
{
	for (int i=0; i<M.rows; i++)
	for (int j=0; j<M.cols; j++)
		fi >> M.cells[i][j];
	return fi;
}


template <typename Cell>
ostream& operator << (ostream& fo, const Matrix<Cell>& M)
{
	for (int i=0; i<M.rows; i++)
	{
		fo << "  ";
		for (int j=0; j<M.cols; j++)
			fo << M.cells[i][j] << " \t";
		fo << endl;
	}
	return fo;
}
#endif MATRIX_H

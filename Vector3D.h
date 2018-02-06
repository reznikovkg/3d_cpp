#ifndef VECTOR_H
#define VECTOR_H

class Vector3D
{
private:
	int size;
	Cell *cells;
	void AllocateCells(int);
	void FreeCells();
public:
	Vector3D() : size(0), cells(nullptr) {}	// Конструктор по умолчанию
	Vector3D(const Vector3D &);					// Конструктор копирования
	Vector3D(int, Cell*);						// Конструктор матрицы из списка Cell
	Vector3D(int, istream &);					//Файлочитатель конструктор
	Vector3D(int, int, int);					//РАНДОМ конструктор
	~Vector3D();								// Деструктор

	Cell &operator()(int i) { return cells[i-1]; }

	Vector3D&operator=(const Vector3D &);	// Перегрузка оператора присваивания
	Vector3D operator+(const Vector3D &);	// Сложение векторов
	Vector3D operator-(const Vector3D &);	// Вычитание векторов
	Vector3D operator/(const Cell &);
	Vector3D operator^(const Vector3D &);	// Векторное умножение векторов
	Cell operator*(const Vector3D &);		// Скалярное умножение векторов

	friend istream &operator>>(istream &, Vector3D &);		// Перегрузка оператора >> для ввода матрицы
	friend ostream &operator<<(ostream &, const Vector3D &);	// Перегрузка оператора << для вывода матрицы

	Cell normaV()
{
	Cell b = 0;
	for (int i = 0; i<size; i++)
	{
		b+=cells[i]*cells[i];
	}
	return sqrt(b);
}
};



Vector3D::Vector3D(const Vector3D &v)
{
	AllocateCells(v.size);
	for (int i=0; i<size; i++)
		cells[i] = v.cells[i];
}

Vector3D::Vector3D(int Size, Cell* list=nullptr)
{
	AllocateCells(Size);
	if (list==nullptr)
		for (int i=0; i<size; i++)
			cells[i] = 0;
	else
		for (int i=0; i<size; i++)
			cells[i] = list[i];
}
Vector3D::Vector3D(int Size, istream &is)
{
	AllocateCells(Size);
	char InStr[255];
	is >> InStr;
	for (int i = 0; i<Size; i++)
	{
		cells[i] = atoi(&InStr[i * 2 + 2]);
	}
}
Vector3D::Vector3D(int Size, int min, int max=100)
{
	AllocateCells(Size);

	for (int i = 0; i<Size; i++)
	{
		cells[i] = rand() % (max)+min;

	}
}
Vector3D::~Vector3D()
{
	FreeCells();
}

Vector3D& Vector3D::operator=(const Vector3D &v)
{
	if (size != v.size)
	{
		FreeCells();
		AllocateCells(v.size);
	}
	for (int i=0; i<size; i++)
		cells[i] = v.cells[i];
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D &v)
{
	Vector3D res(*this);
	if (size == v.size)
	{
		for (int i=0; i<size; i++)
			res.cells[i]+=v.cells[i];
	}
	return res;
}

Vector3D Vector3D::operator-(const Vector3D &v)
{
	Vector3D res(*this);
	if (size == v.size)
	{
		for (int i = 0; i<size; i++)
			res.cells[i] -= v.cells[i];
	}
	return res;
}

Vector3D Vector3D::operator/(const Cell &v)
{
	Vector3D res(*this);
	for (int i = 0; i<size; i++)
			res.cells[i] /= v;
	return res;
}

Vector3D Vector3D::operator^(const Vector3D &v)
{
	Vector3D res(size);
	if (size == v.size)
	{
		res.cells[0] = cells[1]*v.cells[2]-cells[2]*v.cells[1];
		res.cells[1] = cells[2]*v.cells[0]-cells[0]*v.cells[2];
		res.cells[2] = cells[0]*v.cells[1]-cells[1]*v.cells[0];
	}
	return res;
}

Cell Vector3D::operator*(const Vector3D &v)
{
	Vector3D res(*this);
	if (size == v.size)
	{
		double t=0;
		for (int i = 0; i<size; i++)
			t+=res.cells[i] * v.cells[i];
		return t;
	}
	else
		return 0;
}



istream &operator>>(istream &fi, Vector3D &v)
{
	for (int i=0; i<v.size; i++)
		fi >> v.cells[i];
	return fi;
}

ostream &operator<<(ostream &fo, const Vector3D &v)
{
	for (int i=0; i<v.size; i++)
	{
		if (i!=0) fo << "\t";
		fo << v.cells[i];
	}
	return fo;
}

void Vector3D::AllocateCells(int Size)
{
	cells = new Cell[Size];
	size=Size;
}

void Vector3D::FreeCells()
{
	delete cells;
	size=0;
}

#endif VECTOR3D_H

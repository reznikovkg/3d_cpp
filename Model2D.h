#ifndef MODEL_2D_H
#define MODEL_2D_H
#include <string>
#include <fstream>
#include "Matrix.h"
#include "AffineTransform.h"

class Model2D
{
	private:
		int sizeVertices;
		Matrix<> Vertices;
		int sizeEdges;
		Matrix<int> Edges;
		Matrix<> CumulativeAT;
		Matrix<> InitialVertices;
	public:
		Model2D() : Vertices(), Edges() {}
		Model2D(const Matrix<> Vertices, const Matrix<int> Edges) :
			Vertices(Vertices), Edges(Edges) {}
		Matrix<> GetVertices() { return Vertices; }
		Matrix<> GetCumulativeAT() { return CumulativeAT; }
		Matrix<> GetInitialVertices() { return InitialVertices; }
		Matrix<int> GetEdges() { return Edges; }

	Model2D(string file_V, string file_E)
	{
		string InStr;
//============================================Ñ×ÈÒÛÂÀÍÈÅ Vertices
		ifstream fin(file_V);
		int vk;
		fin >> vk;
		getline(fin,InStr);
		
		sizeVertices = vk;

		Matrix<> Mij(3, vk);
		fin >> Mij;
		Vertices = Mij;
		fin.close();

//============================================Ñ×ÈÒÛÂÀÍÈÅ Edges
		ifstream fin2(file_E);
		int ek;
		fin2 >> ek;
		getline(fin2,InStr);
		
		sizeEdges=ek;

		Matrix<int> Mij2(ek, ek);

		fin2 >> Mij2;
		Edges = Mij2;
		fin2.close();


		InitialVertices = Vertices;
		CumulativeAT = Identity();
	}

	//template <typename Cell>
	void Apply(Matrix<> AffTran) 
	{
		CumulativeAT = AffTran*CumulativeAT;
		Vertices = CumulativeAT*InitialVertices;
	}




	double GetVertexX(int x)
	{
		return Vertices.MatrGetX(x);
	}
	double GetVertexY(int y) 
	{
		return Vertices.MatrGetY(y);
	}
	double GetVertexOdn(int k) 
	{
		return Vertices.MatrGetOdn(k);
	}

	double GetEdgesXY(int x, int y) 
	{
		return Edges.MatrGetCellXY(x,y);
	}



	int GetSizeVertex() 
	{
		return sizeVertices;
	}
	int GetSizeEdges()
	{
		return sizeEdges;
	}
};
#endif MODEL_2D_H
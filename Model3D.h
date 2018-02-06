#ifndef MODEL_3D_H
#define MODEL_3D_H
#include <string>
#include <fstream>

class Model3D
{
	private:
		Matrix<> Vertices;
		Matrix<> InitialVertices;
		Matrix<> ProjectedVertices;
		Matrix<int> Verges;
		Matrix<int> Edges;


		int sizeVertices;
		int sizeEdges;

	public:
		Model3D() : Vertices(), Edges() {}
		Model3D(const Matrix<> Vertices, const Matrix<int> Edges) :
			Vertices(Vertices), Edges(Edges) {}
		Matrix<> GetVertices() { return Vertices; }
		Matrix<int> GetVerges() { return Verges; }
		Matrix<int> GetEdges() { return Edges; }
		Matrix<> GetInitialVertices() { return InitialVertices; }
		
	Model3D(string file_V, string file_Ver) //==—читывание по файлам
	{
		string InStr;
//================================
		ifstream fin(file_V);
		fin >> sizeVertices;
		getline(fin,InStr);
		
		Matrix<> Mij(4, sizeVertices);
		fin >> Mij;
		Vertices = Mij;
		fin.close();

//========================
		ifstream fin2(file_Ver);
		int asd;
		fin2 >> asd;
		getline(fin2,InStr);
		
		Matrix<int> Mij2(asd, 3);
	
		fin2 >> Mij2;
		Verges = Mij2;
		fin2.close();

		InitialVertices =  Vertices;
		SetEdges();
	}
	void SetEdges()
	{
		int sei = Verges.getRows();
		
		int mk = Vertices.getCols();
		
		Matrix<int> Mij2(mk, mk);
		for (int i=1;i<=sei; i++)
		{
			
			Mij2.MatrSetCellXY(Verges.MatrGetCellXY(i,1),Verges.MatrGetCellXY(i,2),1);
			Mij2.MatrSetCellXY(Verges.MatrGetCellXY(i,2),Verges.MatrGetCellXY(i,1),1);


			Mij2.MatrSetCellXY(Verges.MatrGetCellXY(i,1),Verges.MatrGetCellXY(i,3),1);
			Mij2.MatrSetCellXY(Verges.MatrGetCellXY(i,3),Verges.MatrGetCellXY(i,1),1);


			Mij2.MatrSetCellXY(Verges.MatrGetCellXY(i,2),Verges.MatrGetCellXY(i,3),1);
			Mij2.MatrSetCellXY(Verges.MatrGetCellXY(i,3),Verges.MatrGetCellXY(i,2),1);

		}
		Edges = Mij2;

		sizeEdges = mk;
	}
	void Apply(Matrix<> AffTran) 
	{
		Vertices = AffTran*Vertices;
	}
	double GetVertexX(int x)
	{
		return Vertices.MatrGetX(x);
	}
	double GetVertexY(int y) 
	{
		return Vertices.MatrGetY(y);
	}
	double GetVertexZ(int z) 
	{
		return Vertices.MatrGetZ(z);
	}
	void Project(Matrix<> Project)
	{
		ProjectedVertices = Project*Vertices;
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






	double getProjX(int x)
	{
		return ProjectedVertices.MatrGetX(x)/ProjectedVertices.MatrGetZ(x);
	}
	double getProjY(int x)
	{
		return ProjectedVertices.MatrGetY(x)/ProjectedVertices.MatrGetZ(x);
	}
	double getProjZ(int x)
	{
		return ProjectedVertices.MatrGetZ(x);
	}
	double getProjOdn(int x)
	{
		return ProjectedVertices.MatrGetO(x);
	}
};
#endif MODEL_3D_H
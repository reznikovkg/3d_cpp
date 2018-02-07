#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera3D.h"

class Scene3D : public Camera3D
{
private:
	typedef double (*Func)(double);
	
public:
	Model3D model;

	Scene3D(double X0, double Y0, double px, double py, string fileV, string fileVer) : Camera3D(X0, Y0, px, py) {
		model = Model3D(fileV,fileVer);
	}
	
	void Project()
	{
		model.Project(WorldToProjectF());
	}

	void Render(HDC dc, bool axes=true)
	{
		if (axes) Axes(dc);

		Project();

		int kkk = model.GetSizeEdges();
		for (int i = 1; i<=kkk; i++)
		{
			for (int j = 1; j<=kkk; j++)
			{
				if (model.GetEdgesXY(i,j) == 1)
				{
					MoveTo(model.getProjX(i),model.getProjY(i));
					LineTo(dc,model.getProjX(j),model.getProjY(j));
				}
			}
		}
	}

};

#endif SCENE_3D_H

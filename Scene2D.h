#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
	
public:
	Model2D model;
	Scene2D(double X0, double Y0, double px, double py, string fileV, string fileE) : Camera2D(X0, Y0, px, py)
	{
		model = Model2D(fileV,fileE);
	}
	void Plot(HDC dc, Func f, bool axes=true)
	{
		if (axes)
			Axes(dc);

		MoveTo(L(),f(L()));

		for (double x=L();x<R();x+=1/px)
		{
			LineTo(dc,x,f(x));
		}
		

		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
	
	void TwoCenterBipolarPlot(HDC dc, Func TWOpolar_r1, Func TWOpolar_r2, Func TWOpolar_tmin, Func TWOpolar_tmax, bool axes=true)
	{
		if (axes) Axes(dc);

		double Xw = TWOpolar_to_Xout(c,TWOpolar_r1(TWOpolar_tmin(0)),TWOpolar_r2(TWOpolar_tmin(0)));
		double Yw = TWOpolar_to_Yout(c,TWOpolar_r1(TWOpolar_tmin(0)),TWOpolar_r2(TWOpolar_tmin(0)));
		MoveTo(Xw,Yw);

		for (double tttnow=TWOpolar_tmin(0);tttnow<TWOpolar_tmax(0);tttnow+=0.01)
		{
			Xw = TWOpolar_to_Xout(c,TWOpolar_r1(tttnow),TWOpolar_r2(tttnow));
			Yw = TWOpolar_to_Yout(c,TWOpolar_r1(tttnow),TWOpolar_r2(tttnow));
			LineTo(dc,Xw,Yw);
		}

		Xw = TWOpolar_to_Xout(c,TWOpolar_r1(TWOpolar_tmin(0)),TWOpolar_r2(TWOpolar_tmin(0)));
		Yw = TWOpolar_to_Yout(c,TWOpolar_r1(TWOpolar_tmin(0)),TWOpolar_r2(TWOpolar_tmin(0)),-1);
		MoveTo(Xw,Yw);

		for (double tttnow=TWOpolar_tmin(0);tttnow<TWOpolar_tmax(0);tttnow+=0.01)
		{
			Xw = TWOpolar_to_Xout(c,TWOpolar_r1(tttnow),TWOpolar_r2(tttnow));
			Yw = TWOpolar_to_Yout(c,TWOpolar_r1(tttnow),TWOpolar_r2(tttnow),-1);
			LineTo(dc,Xw,Yw);
		}
	}
	
	void Render(HDC dc, bool axes=true)
	{
		if (axes) Axes(dc);


		int kkk = model.GetSizeEdges();
		for (int i = 1; i<=kkk; i++)
		{
			for (int j = 1; j<=kkk; j++)
			{
				if (model.GetEdgesXY(i,j) == 1)
				{
					MoveTo(model.GetVertexX(i)/model.GetVertexOdn(i),model.GetVertexY(i)/model.GetVertexOdn(i));
					LineTo(dc,model.GetVertexX(j)/model.GetVertexOdn(j),model.GetVertexY(j)/model.GetVertexOdn(j));
				}
			}
		}
		
	}


};

#endif SCENE_2D_H

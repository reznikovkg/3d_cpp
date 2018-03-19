#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double X0, Y0;						// Экранные координаты начала мировой системы координат
	double px, py;						// Единицы масштаба мировой системы координат, выраженные в пикселях
	int W, H;							// Разрешение рабочей области окна

	int offsetX, offsetY;
	int color;
	bool isDragging;
	double previousX, previousY;


	int WorldToScreenX(double X)
	{
		return (int)(X0+px*X);
	}
	int WorldToScreenY(double Y)
	{
		return (int)(Y0-py*Y);
	}
	double ScreenToWorldX(int X)
	{
		return (X-X0+0.5)/px;
	}
	double ScreenToWorldY(int Y)
	{
		return -(Y-Y0+0.5)/py;
	}
	double L()
	{
		return -X0/px;
	}
	double R()
	{
		return (W-X0)/px;
	}
	double T()							
	{
		return Y0/py;
	}
	double B()							
	{
		return -(H-Y0)/py;
	}
private:
	double posX, posY;
	double oldW,oldH;
	double oldPX,oldPY;
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{
	}
	Camera2D()
	{
		oldW = 400;
		oldH = 400;
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc),&r);
		Rectangle(dc,0,0,r.right,r.bottom);
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc),&r);

		W = r.right+1;
		H = r.bottom+1;
		oldPX = px;
		oldPY = py;
		
		if (oldW == 0)
		{
			oldW = W;
		}
		if (oldH == 0)
		{
			oldH = H;
		}
		
		double
			kW = (double)W/oldW,
			kH = (double)H/oldH;

		X0=kW*X0;
		Y0=kW*oldPX/oldPY*Y0+((double)oldH/2)*(kH-kW*(oldPX/oldPY));
		px=kW*oldPX;
		py=kW*oldPX;
		

		oldW=W;
		oldH=H;
	}

	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
	}
	void LineTo(HDC dc, double X, double Y)
	{
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X,Y);
	}



	void sizeedit(double k, int XX, int YY)
	{
		if (k>0)
		{
			px *= k;
			py *= k;
			X0 -= (k-1)*px*ScreenToWorldX(XX);
			Y0 += (k-1)*py*ScreenToWorldY(YY);
		}
	}


	void StartDragging(int X, int Y)
	{
		isDragging = true;
		previousX = X-X0;
		previousY = Y-Y0;
	}
	void Drag(int X, int Y)
	{
		X0 = X-previousX;
		Y0 = Y-previousY;
	}
	void StopDragging()
	{
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}


	void Axes(HDC dc)
	{
		MoveTo(L(), 0);
		LineTo(dc, R(), 0);

		MoveTo(0,T());
		LineTo(dc, 0, B());

		int t = -100;
		while (t<=100)
		{
			MoveTo(t, 0.1);
			LineTo(dc,t, -0.1);

			MoveTo(0.1, t);
			LineTo(dc,-0.1,t);
			t++;
		}
		
	}
};

#endif CAMERA_2D_H

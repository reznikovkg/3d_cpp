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


	int WorldToScreenX(double X)		// Переход от мировых координат к экранным (для абсциссы)
	{
		return (int)(X0+px*X);
	}
	int WorldToScreenY(double Y)		// Переход от мировых координат к экранным (для ординаты)
	{
		return (int)(Y0-py*Y);
	}
	double ScreenToWorldX(int X)		// Переход от экранных координат к мировым (для абсциссы)
	{
		return X-X0+0.5;
	}
	double ScreenToWorldY(int Y)		// Переход от экранных координат к мировым (для ординаты)
	{
		return Y-Y0+0.5;
	}
	double L()							// Абсцисса левой границы рабочей области окна (в мировых координатах)
	{
		return -X0/px;
	}
	double R()							// Абсцисса правой границы рабочей области окна (в мировых координатах)
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
	double posX, posY;					// Позиция графического курсора в мировых координатах (для функций MoveTo и LineTo)
	double oldW,oldH;
	double oldPX,oldPY;
public:
	Camera2D(double X0, double Y0, double px, double py) : X0(X0), Y0(Y0), px(px), py(py)
	{

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
		
		if (oldW == 0)
		{
			oldW = W;
			oldPX = px;
		}
		if (oldH == 0)
		{
			oldH = H;
			oldPY = py;
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

		oldPX = px;
		oldPY = py;
		// Данная процедура вызывается при изменении размеров окна
		// В ней задаются значения величин W, H, а также настраиваются значения параметров X0, Y0, px, py таким образом, чтобы обеспечить одинаковые масштабы по координатным осям
	}

	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// Перемещение графического курсора (posX, posY)
		// Обратите внимание, что мы действуем в мировых координатах
	}
	void LineTo(HDC dc, double X, double Y)
	{
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X,Y);
		// Отрисовка линии из текущей позиции графического курсора в точку (X, Y) и его перемещение в эту точку
		// Обратите внимание, что мы действуем в мировых координатах
		// При отрисовке линии могут быть использованы WinApi функции
		// ::MoveToEx(dc, Xs, Ys, nullptr) и ::LineTo(dc, Xs, Ys)
	}
//==================================================
	void sizeedit(int param)
	{
		if (param>0)
		{
			px+=1;
			py+=k;
		}
		else if (px>1) { px-=1;py-=k;}
	}
//==================================================
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
//==================================================


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

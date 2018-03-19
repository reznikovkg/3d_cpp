#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double X0, Y0;						// �������� ���������� ������ ������� ������� ���������
	double px, py;						// ������� �������� ������� ������� ���������, ���������� � ��������
	int W, H;							// ���������� ������� ������� ����

	int offsetX, offsetY;
	int color;
	bool isDragging;
	double previousX, previousY;


	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return (int)(X0+px*X);
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		return (int)(Y0-py*Y);
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return X-X0+0.5;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return Y-Y0+0.5;
	}
	double L()							// �������� ����� ������� ������� ������� ���� (� ������� �����������)
	{
		return -X0/px;
	}
	double R()							// �������� ������ ������� ������� ������� ���� (� ������� �����������)
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
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
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
		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� X0, Y0, px, py ����� �������, ����� ���������� ���������� �������� �� ������������ ����
	}

	void MoveTo(double X, double Y)
	{
		posX = X;
		posY = Y;
		// ����������� ������������ ������� (posX, posY)
		// �������� ��������, ��� �� ��������� � ������� �����������
	}
	void LineTo(HDC dc, double X, double Y)
	{
		::MoveToEx(dc, WorldToScreenX(posX), WorldToScreenY(posY), nullptr);
		::LineTo(dc, WorldToScreenX(X), WorldToScreenY(Y));
		MoveTo(X,Y);
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
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

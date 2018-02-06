#ifndef CAMERA_3D_H
#define CAMERA_3D_H
#include "Camera2D.h"
#include "Vector3D.h"
#include <windows.h>

class Camera3D : public Camera2D
{
private:
	Vector3D Ov, T, N;

	double D;

	Matrix<> WorldToView;
	Matrix<> ViewToProject;
	Matrix<> WorldToProject;

	Vector3D vecK;
	Vector3D vecI;
	Vector3D vecJ;


public:
	void WorldToViewF()
	{
		double T[16] = {
			vecI(1), vecI(2), vecI(3), (vecI*Ov)*(-1),
			vecJ(1), vecJ(2), vecJ(3), (vecJ*Ov)*(-1),
			vecK(1), vecK(2), vecK(3), (vecK*Ov)*(-1),
			0, 0, 0, 1};
		WorldToView = Matrix<>(4,4, T);
	}

	void ViewToProjectF()
	{
		double T[12] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, (-1.0)/D, 1};
		ViewToProject = Matrix<>(3,4, T);
	}

	Matrix<> WorldToProjectF()
	{
		WorldToProject = ViewToProject*WorldToView;
		return WorldToProject;
	}

	Camera3D(double X0, double Y0, double px, double py) : Camera2D(X0, Y0, px, py)
	{
		setOv(0,0,0);
		setT(0,1,0);
		setN(0,0,1);
		
		setD(10);

		vecK = N/(N.normaV());
		vecI = (T^N)/((T^N).normaV());
		vecJ = vecK^vecI;
		

		UpdateCamera();
	}

	void setOv(double x, double y, double z)
	{
		Cell myOv[3] = {z, y, z};
		Vector3D newOv(3, myOv);
		Ov = newOv;
	}

	void setT(double x, double y, double z)
	{
		Cell myT[3] = {z, y, z};
		Vector3D newT(3, myT);
		T = newT;
	}

	void setN(double x, double y, double z)
	{
		Cell myN[3] = {x, y, z};
		Vector3D newN(3, myN);
		N = newN;
	}

	void setD(double d)
	{
		D = d;
	}


	void UpdateCamera()
	{
		WorldToViewF();
		ViewToProjectF();
		WorldToProjectF();
	}
};

#endif CAMERA_3D_H

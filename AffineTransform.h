#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H

Matrix<> Translation(double x, double y, double z)
{
	double T[16] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1};
	return Matrix<>(4,4, T);
}

Matrix<> Identity()
{
	double T[16] = {
		1,	0,	0, 0,
		0,	1,	0, 0,
		0,	0,	1, 0,
		0,	0,	0, 1};
	return Matrix<>(4,4, T);
}

Matrix<> RotationXX(double t)
{
	double T[16] = {
		1, 0, 0, 0,
		0,cos(t), -sin(t),0,
		0, sin(t), cos(t),	0,
		0, 0, 0, 1};
	return Matrix<>(4,4, T);
}

Matrix<> RotationYY(double t)
{
	double T[16] = {
		cos(t), 0, sin(t), 0,
		0, 1, 0, 0,
		-sin(t), 0, cos(t),	0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, T);
}

Matrix<> RotationZZ(double t)
{
	double T[16] = {
		cos(t), -sin(t), 0, 0,
		sin(t), cos(t), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	return Matrix<>(4, 4, T);
}

/*Matrix<> RotationX(double a, double b, double c, double t=0, double znak = 1)
{
	double mySQRT = sqrt((a)*(a)+(b)*(b)+(c)*(c));
	double mySQRT_BC = sqrt((b)*(b)+(c)*(c));

	double cA = (a)/mySQRT;
	double sA = mySQRT_BC/mySQRT;

	double cB = (b)/mySQRT_BC;
	double sB = (c)/mySQRT_BC;


	if (t)
	{
		double T[16] = {
			1, 0, 0, 0,
			0, cA, -sA*znak, 0,
			0, sA*znak, cA, 0,
			0, 0, 0, 1 };
		return Matrix<>(4, 4, T);
	}
	else
	{
		double T[16] = {
			1, 0, 0, 0,
			0, cB, -sB*znak, 0,
			0, sB*znak, cB, 0,
			0, 0, 0, 1 };
		return Matrix<>(4, 4, T);
	}
}

Matrix<> RotationY(double a, double b, double c, double t=0, double znak = -1)
{
	double mySQRT = sqrt((a)*(a)+(b)*(b)+(c)*(c));
	double mySQRT_BC = sqrt((b)*(b)+(c)*(c));

	double cA = (a)/mySQRT;
	double sA = mySQRT_BC/mySQRT;

	double cB = (b)/mySQRT_BC;
	double sB = (c)/mySQRT_BC;


	if (t)
	{
		double T[16] = {
			cA, 0, sA*znak, 0,
			0, 1, 0, 0,
			-sA*znak, 0, cA, 0,
			0, 0, 0, 1 };
		return Matrix<>(4, 4, T);
	}
	else
	{
		double T[16] = {
			cB, 0, sB*znak, 0,
			0, 1, 0, 0,
			-sB*znak, 0, cB, 0,
			0, 0, 0, 1 };
		return Matrix<>(4, 4, T);
	}
}

Matrix<> RotationZ(double a, double b, double c, double t=0, double znak = -1)
{
	double mySQRT = sqrt((a)*(a)+(b)*(b)+(c)*(c));
	double mySQRT_BC = sqrt((b)*(b)+(c)*(c));

	double cA = (a)/mySQRT;
	double sA = mySQRT_BC/mySQRT;

	double cB = (b)/mySQRT_BC;
	double sB = (c)/mySQRT_BC;


	if (t)
	{
		double T[16] = {
			cA, -sA*znak, 0, 0,
			sA*znak, cA, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
		return Matrix<>(4, 4, T);
	}
	else
	{
		double T[16] = {
			cB, -sB*znak, 0, 0,
			sB*znak, cB, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
		return Matrix<>(4, 4, T);
	}
}
*/
Matrix<> RotationX(double c, double s)
{
	double T[16] = {
			1, 0, 0, 0,
			0, c, -s, 0,
			0, s, c, 0,
			0, 0, 0, 1 };
	return Matrix<>(4, 4, T);
}
Matrix<> RotationY(double c, double s)
{
	double T[16] = {
			c, 0, s, 0,
			0, 1, 0, 0,
			-s, 0, c, 0,
			0, 0, 0, 1 };
	return Matrix<>(4, 4, T);
}
Matrix<> RotationZ(double c, double s)
{
	double T[16] = {
			c, -s, 0, 0,
			s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
	return Matrix<>(4, 4, T);
}

Matrix<> Scaling(double kx, double ky, double kz)
{
	double T[16] = {
		kx,	0,	0, 0,
		0,	ky,	0, 0,
		0, 0, kz, 0,
		0,	0, 0, 1};
	return Matrix<>(4,4, T);
}


Matrix<> Mapping(double x=1, double y=1, double z=1)
{
	double T[16] = {
		x, 0,	0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0,	0, 0, 1 };
	return Matrix<>(4, 4, T);
}


#endif AFFINE_TRANSFORM_H

#include <windows.h>
#include <windowsx.h>

#include "Data.h"

#include "Matrix.h"

#include "AffineTransform.h"

#include "Model3D.h"

#include "Scene3D.h"

LRESULT _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);						// прототип оконной процедуры
int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)		// основна€ процедура
{
	// ѕерва€ составл€юща€ часть основной процедуры - создание окна: сначала описываетс€ оконный класс wc, затем создаЄтс€ окно hWnd
	WNDCLASS wc;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;						// им€ оконной процедуры, закрепленной за данным классом
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;						// идентификатор приложени€, содержащий адрес начала выделенной ему области пам€ти
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName = 0;							// меню в оконном классе отсутствует
	wc.lpszClassName = (LPCSTR)"MainWindowClass";	// им€ оконного класса, используемое при создании экземпл€ров окна
	RegisterClass(&wc);								// регистраци€ класса wc

	HWND hWnd = CreateWindow(						// hWnd - дескриптор, идентифицирующий окно; функци€ создани€ окна заполн€ет дескриптор hWnd ненулевым значением
		(LPCSTR)"MainWindowClass",					// им€ оконного класса
		(LPCSTR)"Plot3D Viewer",					// заголовок окна
		WS_OVERLAPPEDWINDOW,						// стиль окна
		200,200,400,400,							// координаты на экране левого верхнего угла окна, его ширина и высота
		nullptr,nullptr,hInstance,nullptr);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	// ¬тора€ составл€юща€ часть основной процедуры - основной цикл обработки системных сообщений, который ожидает сообщени€ и рассылает их соответствующим окнам
	MSG msg;
	while(GetMessage(&msg,nullptr,0,0))				// функци€ GetMessage выбирает из очереди сообщение и заносит его в структуру msg
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);						// функци€ DispatchMessage оповещает систему о необходимости вызова оконной процедуры
	}

	return 0;
}

// ¬ основном модуле объ€вл€етс€ только одна глобальна€ переменна€ - создаЄтс€ объект класса Scene2D
// ¬се дальнейшие действи€ осуществл€ютс€ посредством обращени€ к методам, реализованным в этом классе
Scene3D scene(X0,Y0,px,py,"V.txt","Ver.txt");

LRESULT _stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)		// оконна€ процедура принимает и обрабатывает все сообщени€, отправленные окну
{
	switch(msg)
	{
	case WM_PAINT:
		{
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);

			scene.Render(dc);
			
			ReleaseDC(hWnd,dc);
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}

	case WM_SIZE:
		{
			HDC dc = GetDC(hWnd);
			scene.SetResolution(dc);
			ReleaseDC(hWnd,dc);
			InvalidateRect(hWnd,nullptr,false);
			return 0;
		}
	case WM_MOUSEWHEEL:
		{
			POINT P;
			P.x = GET_X_LPARAM(lParam);
			P.y = GET_Y_LPARAM(lParam);
			ScreenToClient(hWnd, &P);

			if (GET_WHEEL_DELTA_WPARAM(wParam)>0) 
			{
				scene.sizeedit(1.1,P.x, P.y);
			}
			else
			{
				scene.sizeedit(0.9,P.x, P.y);
			}

			

			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}
	case WM_LBUTTONDOWN:
		{
			POINT P;
P.x = GET_X_LPARAM(lParam);
P.y = GET_Y_LPARAM(lParam);
ScreenToClient(hWnd, &P);
scene.StartDragging(P.x, P.y);

			//scene.StartDragging(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		}
	case WM_MOUSEMOVE:
		{
			if (scene.IsDragging())
			{
				POINT P;
P.x = GET_X_LPARAM(lParam);
P.y = GET_Y_LPARAM(lParam);
ScreenToClient(hWnd, &P);

				scene.Drag(P.x, P.y);
				InvalidateRect(hWnd, nullptr, false);
			}
			return 0;
		}
	case WM_LBUTTONUP:
		{
			scene.StopDragging();
			return 0;
		}


	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}



	case WM_KEYDOWN:
		{
			HDC dc = GetDC(hWnd);
			
			switch (wParam)
			{
			case VK_LEFT:
				{
					scene.model.Apply( Translation(-1, 0, 0) );
					break;
				}
			case VK_RIGHT:
				{
					scene.model.Apply( Translation(1, 0, 0) );
					break;
				}
			case VK_UP:
				{
					scene.model.Apply( Translation(0, 1, 0) );
					break;
				}
			case VK_DOWN:
				{
					scene.model.Apply( Translation(0, -1, 0) );
					break;
				}
			case VK_NUMPAD1:
				{
					scene.model.Apply( RotationXX(M_PI/6) );
					break;
				}
			case VK_NUMPAD2:
				{
					scene.model.Apply(RotationYY(M_PI /6));
					break;
				}
			case VK_NUMPAD3:
				{
					scene.model.Apply(RotationZZ(M_PI /6));
					break;
				}
			case VK_NUMPAD4:
			{
				double x = scene.model.GetVertexX(1);
				double y = scene.model.GetVertexY(1);
				double z = scene.model.GetVertexZ(1);
				
				Matrix<> MyNewAP = Translation(-x, -y, -z);
				MyNewAP = RotationYY(M_PI/6)*MyNewAP;
				MyNewAP = Translation(x, y, z)*MyNewAP;
				scene.model.Apply( MyNewAP );
				scene.Project();
				break;
			}
			case VK_NUMPAD9:
			{
				scene.model.Apply(Scaling(2,2,2));
				break;
			}
			case VK_NUMPAD8:
			{
				scene.model.Apply(Scaling(0.5,0.5,0.5));
				break;
			}
			case VK_NUMPAD7:
			{
				double x1 = scene.model.GetVertexX(1)/scene.model.GetVertexOdn(1);
				double y1 = scene.model.GetVertexY(1)/scene.model.GetVertexOdn(1);
				double z1 = scene.model.GetVertexZ(1)/scene.model.GetVertexOdn(1);
				
				double x2 = scene.model.GetVertexX(5)/scene.model.GetVertexOdn(4);
				double y2 = scene.model.GetVertexY(5)/scene.model.GetVertexOdn(4);
				double z2 = scene.model.GetVertexZ(5)/scene.model.GetVertexOdn(4);
				
				double a = x1-x2;
				double b = y1-y2;
				double c = z1-z2;

				Matrix<> MyNewAP = Translation(-x1, -y1, -z1);
				if (c!=0)
				{
				
				double mySQRT = sqrt((a)*(a)+(b)*(b)+(c)*(c));
				double mySQRT_BC = sqrt((b)*(b)+(c)*(c));

				double cA = (a)/mySQRT;
				double sA = mySQRT_BC/mySQRT;

				double cB = (b)/mySQRT_BC;
				double sB = (c)/mySQRT_BC;


				MyNewAP = RotationX(cB,-sB)*MyNewAP;
				MyNewAP = RotationZ(cA,-sA)*MyNewAP;
				MyNewAP = RotationXX(M_PI/12)*MyNewAP;
				MyNewAP = RotationZ(cA,sA)*MyNewAP;
				MyNewAP = RotationX(cB,sB)*MyNewAP;
				
				}
				else
				{
					double mySQRT = sqrt((a)*(a)+(b)*(b));

					double cA = (a)/mySQRT;
					double sA = (b)/mySQRT;

					MyNewAP = RotationX(cA,-sA)*MyNewAP;
					MyNewAP = RotationXX(M_PI/12)*MyNewAP;
					MyNewAP = RotationX(cA,sA)*MyNewAP;

				}
				MyNewAP = Translation(x1, y1, z1)*MyNewAP;
				scene.model.Apply( MyNewAP );
				
				scene.Project();
				break;
			}

			case VK_NUMPAD6:
			{
				double x1 = scene.model.GetVertexX(1)/scene.model.GetVertexOdn(1);
				double y1 = scene.model.GetVertexY(1)/scene.model.GetVertexOdn(1);
				double z1 = scene.model.GetVertexZ(1)/scene.model.GetVertexOdn(1);
				
				double x2 = scene.model.GetVertexX(5)/scene.model.GetVertexOdn(5);
				double y2 = scene.model.GetVertexY(5)/scene.model.GetVertexOdn(5);
				double z2 = scene.model.GetVertexZ(5)/scene.model.GetVertexOdn(5);
				
				double a = x2-x1;
				double b = y2-y1;
				double c = z2-z1;

				double x3 = scene.model.GetVertexX(2)/scene.model.GetVertexOdn(5);
				double y3 = scene.model.GetVertexY(2)/scene.model.GetVertexOdn(5);
				double z3 = scene.model.GetVertexZ(2)/scene.model.GetVertexOdn(5);

				double a2 = x3-x2;
				double b2 = y3-y2;
				double c2 = z3-z2;

				Cell myOv[3] = {a, b, c};
				Vector3D newOv(3, myOv);

				Cell myOv2[3] = {a2, b2, c2};
				Vector3D newOv2(3, myOv2);
				
				newOv = newOv^newOv2;

				
				double mySQRT = sqrt(newOv(1)*newOv(1)+newOv(2)*newOv(2)+newOv(3)*newOv(3));
				double mySQRT_BC = sqrt(newOv(2)*newOv(2)+newOv(3)*newOv(3));

				double cA = (newOv(1))/mySQRT;
				double sA = mySQRT_BC/mySQRT;

				double cB = (newOv(2))/mySQRT_BC;
				double sB = (newOv(3))/mySQRT_BC;

				
				/*double cC = (newOv(2))/mySQRT_BC;
				double sC = (newOv(3))/mySQRT_BC;
				*/
				




				Matrix<> MyNewAP = Translation(-x1, -y1, -z1);
				
				MyNewAP = RotationX(cB,-sB)*MyNewAP;
				MyNewAP = RotationZ(cA,-sA)*MyNewAP;

				MyNewAP = Mapping(-1,1,1)*MyNewAP;
				
				MyNewAP = RotationZ(cA,sA)*MyNewAP;
				MyNewAP = RotationX(cB,sB)*MyNewAP;
				
				MyNewAP = Translation(x1, y1, z1)*MyNewAP;

				scene.model.Apply( MyNewAP );
				
				scene.Project();
				break;
			}

			/* ... */
			}
			InvalidateRect(hWnd, nullptr, false);
			return 0;
		}


	default:
		{
			return DefWindowProc(hWnd,msg,wParam,lParam);
		}
	}
	return 0;
}

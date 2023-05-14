#include <cmath>
#include <iostream>

using namespace std;

struct Point {double x;double y;};
Point rotatePoint(double x, double y, double ox, double oy, double theta) {
    double tx = x - ox,ty = y - oy;
    double radians = theta * M_PI / 180.0;
    double px = tx*cos(radians)-ty*sin(radians);
    double py = tx * sin(radians) + ty * cos(radians);
    px += ox,py += oy;
	return Point{px, py};
}
int main()
{
	//rotatePoint(10.f, 15.f, 15.f, 15.f, +90.f).x;
	//rotatePoint(10.f, 15.f, 15.f, 15.f, +90.f).y;
	//variabili indipendenti
	//coordinate nello spazio dei punti
	double p[][3] = {
		{3800,2400,600},
		{3600,2400,600},
		{3600,2400,800},
		{3800,2400,800},
		{3800,2600,600},
		{3600,2600,600},
		{3600,2600,800},
		{3800,2600,800}
	};
	//coordinate nello spazio del punto di osservazione O
	double O[3] = {5000,2500,3000};
	//theta
	double theta = 0;
	
	
	
	//variabili dipendenti
	//coordinate nel piano di O1 e O3
	double O1[2] = {-O[0],-O[2]};
	double O3[2] = {O[2],O[1]};
	
	
	
	//variabili semidipendenti
	//coordinate nel piano del punto d1 e d3
	double d1[2] = {-O[0],-O[2]+400};
	double d3[2] = {O[2]-300,O[1]};
	//coordinate nel piano dei punti a1,b1 e a3,b3.
	double a1[2] = {d1[0]-400,d1[1]};
	double b1[2] = {d1[0]+400,d1[1]};
	double a3[2] = {d3[0],d3[0]+300};
	double b3[2] = {d3[0],d3[0]-300};
	
	
	//variabili dipendenti
	//coordinate nel piano di ogni punto p1 e p3
	double p1[8][2];
	for (int i = 0; i < 8; i++) p1[i][0] = -p[i][0], p1[i][1] = -p[i][2];
	double p3[8][2];
	for (int i = 0; i < 8; i++) p3[i][0] = p[i][2], p3[i][1] = p[i][1];
	//coordinate nel piano del punto di intersezione pi1 tra p1O1 e a1b1
	//x1 = a1[0] x
	//y1 = a1[1] x
	//x2 = b1[0] x
	//y2 = b1[1] x
	//x3 = p1[][0] x
	//y3 = p1[][1] x
	//x4 = O1[0] x
	//y4 = O1[1] x
	double pi1[8][2];
	for (int i = 0; i < 8; i++) {
		pi1[i][0] = ((p1[i][1]-a1[1])*(b1[0]-a1[0])*(O1[0]-p1[i][0])+a1[0]*(b1[1]-a1[1])*(O1[0]-p1[i][0])-p1[i][0]*(O1[1]-p1[i][1])*(b1[0]-a1[0]))/((b1[1]-a1[1])*(O1[0]-p1[i][0])-(O1[1]-p1[i][1])*(b1[0]-a1[0]));
		pi1[i][1] = ((p1[i][1]-a1[1])*(b1[1]-a1[1])*(O1[0]-p1[i][0])+a1[1]*(b1[1]-a1[1])*(O1[0]-p1[i][0])-p1[i][1]*(O1[1]-p1[i][1])*(b1[0]-a1[0]))/((b1[1]-a1[1])*(O1[0]-p1[i][0])-(O1[1]-p1[i][1])*(b1[0]-a1[0]));
	}
	//coordinate nel piano del punto di intersezione pi3 tra p3O3 e a3b3
	//x1 = a3[0]
	//y1 = a3[1]
	//x2 = b3[0]
	//y2 = b3[1]
	//x3 = p3[][0]
	//y3 = p3[][1]
	//x4 = O3[0]
	//y4 = O3[1]
	double pi3[8][2];
	for (int i = 0; i < 8; i++) {
		pi3[i][0] = ((p3[i][1]-a3[1])*(b3[0]-a3[0])*(O3[0]-p3[i][0])+a3[0]*(b3[1]-a3[1])*(O3[0]-p3[i][0])-p3[i][0]*(O3[1]-p3[i][1])*(b3[0]-a3[0]))/((b3[1]-a3[1])*(O3[0]-p3[i][0])-(O3[1]-p3[i][1])*(b3[0]-a3[0]));
		pi3[i][1] = ((p3[i][1]-a3[1])*(b3[1]-a3[1])*(O3[0]-p3[i][0])+a3[1]*(b3[1]-a3[1])*(O3[0]-p3[i][0])-p3[i][1]*(O3[1]-p3[i][1])*(b3[0]-a3[0]))/((b3[1]-a3[1])*(O3[0]-p3[i][0])-(O3[1]-p3[i][1])*(b3[0]-a3[0]));
	}
	//x = [(y3 - y1)*(x2 - x1)*(x4 - x3) + x1*(y2 - y1)*(x4 - x3) - x3*(y4 - y3)*(x2 - x1)] / [(y2 - y1)*(x4 - x3) - (y4 - y3)*(x2 - x1)]
	//y = [(y3 - y1)*(y2 - y1)*(x4 - x3) + y1*(y2 - y1)*(x4 - x3) - y3*(y4 - y3)*(x2 - x1)] / [(y2 - y1)*(x4 - x3) - (y4 - y3)*(x2 - x1)]
	//coordinate nel piano dei punti pi1, a1 e b1 ruotati di -theta rispetto a d1
	double rpi1[8][2];
	for (int i = 0; i < 8; i++) {
		rpi1[i][0] = rotatePoint(pi1[i][0],pi1[i][1],d1[0],d1[1],-theta).x;
		rpi1[i][1] = rotatePoint(pi1[i][0],pi1[i][1],d1[0],d1[1],-theta).y;
	}
	double ra1[2] = {
		rotatePoint(a1[0],a1[0],d1[0],d1[1],-theta).x,
		rotatePoint(a1[0],a1[0],d1[0],d1[1],-theta).y
	};
	double rb1[2] = {
		rotatePoint(b1[0],b1[0],d1[0],d1[1],-theta).x,
		rotatePoint(b1[0],b1[0],d1[0],d1[1],-theta).y
	};
	//coordinate nel piano dei punti pi3, a3 e b3 ruotati di -theta rispetto a d3
	double rpi3[8][2];
	for (int i = 0; i < 8; i++) {
		rpi3[i][0] = rotatePoint(pi3[i][0],pi3[i][1],d3[0],d3[1],-theta).x;
		rpi3[i][1] = rotatePoint(pi3[i][0],pi3[i][1],d3[0],d3[1],-theta).y;
	}
	double ra3[2] = {
		rotatePoint(a3[0],a3[0],d3[0],d3[1],-theta).x,
		rotatePoint(a3[0],a3[0],d3[0],d3[1],-theta).y
	};
	double rb3[2] = {
		rotatePoint(b3[0],b3[0],d3[0],d3[1],-theta).x,
		rotatePoint(b3[0],b3[0],d3[0],d3[1],-theta).y
	};
	//coordinate nel piano del punto p2
	double p2[8][2];
	for (int i = 0; i < 8; i++) {
		p2[i][0] = rpi1[i][0];
		p2[i][1] = rpi3[i][1];
	}
	for (int i = 0; i < 8; i++)
	{
		cout << "\n|x|" << p2[i][0] << "\n|y|" << p2[i][1] << "\n|";
	}
}


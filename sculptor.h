#ifndef SCULPTOR_H_INCLUDED
#define SCULPTOR_H_INCLUDED

#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Voxel{
    float red,green,blue;
    float alpha;
    bool isOn;
};

class Sculptor{

private:
 Voxel ***v;
 int nl,nc,np;
 float r,g,b,a;

public:
 Sculptor(int _nx=0, int _ny=0, int _nz=0);
 ~Sculptor();

    void setColor(float _r, float _g, float _b, float alpha);

    void putVoxel(int x, int y, int z);

    void cutVoxel(int x, int y, int z);

    void putBox(int x0, int y0, int z0, int x1, int y1, int z1);

    void cutBox(int x0, int y0, int z0, int x1, int y1, int z1);

    void putSphere(int xcenter, int ycenter, int zcenter, int radius);

    void cutSphere(int xcenter, int ycenter, int zcenter, int radius);

    void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);

    void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);


    void writeOFF(string filename);
};

#endif // SCULPTOR_H_INCLUDED

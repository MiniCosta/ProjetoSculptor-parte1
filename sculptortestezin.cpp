#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include "sculptor.h"

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){

    nl=_nx; nc=_ny; np=_nz;

    v=new Voxel**[np];

    v[0]=new Voxel*[np*nc];

    v[0][0]=new Voxel[nl*nc*np];


    for(int i=1;i<np;i++){
        v[i]=v[i-1]+nc;
    }
    for(int i=1;i<(np*nc);i++){
        v[0][i]=v[0][i-1]+nl;
    }
}

Sculptor::~Sculptor(){
    if(nl==0||nc==0||np==0){
        return;
    }
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

void Sculptor::setColor(float r1, float g1, float b1, float a1){
    if((r1<=1||r1>=0)||(g1<=1||g1>=0)||(b1<=1||b1>=0)||(a1<=1||a1>=0)){
        r=r1;
        g=g1;
        b=b1;
        a=a1;
    }
    else {
        cout<<"Cores invalidas"<<endl;
        exit(1);
    }
}

void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn=true;
    v[x][y][z].red=r;
    v[x][y][z].blue=b;
    v[x][y][z].green=g;
    v[x][y][z].alpha=a;
}

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn=false;
}

void Sculptor::putBox(int x0, int y0, int z0, int x1, int y1, int z1){
    for(int i=x0;i<x1;i++){
        for(int j=y0;j<y1;j++){
            for(int k=z0;k<z1;k++){
                v[i][j][k].isOn=true;
                v[i][j][k].red=r;
                v[i][j][k].blue=b;
                v[i][j][k].green=g;
                v[i][j][k].alpha=a;
            }
        }
    }
}

void Sculptor::cutBox(int x0, int y0, int z0, int x1, int y1, int z1){
    for(int i=x0;i<=x1;i++){
        for(int j=y0;j<=y1;j++){
            for(int k=z0;k<=z1;k++){
                v[i][j][k].isOn=false;
            }
        }
    }
}

void Sculptor::putSphere(int centrox, int centroy, int centroz, int raio){
 double rr=raio/2.0;
 double d;
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                d = (i-centrox/2.0)*(i-centrox/2.0)/(rr*rr) +
                    (j-centroy/2.0)*(j-centroy/2.0)/(rr*rr) +
                    (k-centroz/2.0)*(k-centroz/2.0)/(rr*rr);

                if(d<=1.0){
                    v[i][j][k].isOn=true;
                    v[i][j][k].red=r;
                    v[i][j][k].blue=b;
                    v[i][j][k].green=g;
                    v[i][j][k].alpha=a;
                }
            }
        }
    }
}

void Sculptor::cutSphere(int centrox, int centroy, int centroz, int raio){
 double rr=raio/2.0;
 double d;
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                d = (i-centrox/2.0 )*(i-centrox/2.0)/(rr*rr) +
                    (j-centroy/2.0 )*(j-centroy/2.0)/(rr*rr) +
                    (k-centroz/2.0 )*(k-centroz/2.0)/(rr*rr);

                if(d<=1){
                    v[i][j][k].isOn=false;
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int centrox, int centroy, int centroz, int rx, int ry, int rz){
 double _rx=rx/2.0;
 double _ry=ry/2.0;
 double _rz=rz/2.0;
 double d;
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                d = (i-centrox/2.0)*(i-centrox/2.0)/(_rx *_rx) +
                    (j-centroy/2.0)*(j-centroy/2.0)/(_ry *_ry) +
                    (k-centroz/2.0)*(k-centroz/2.0)/(_rz *_rz);

                if((d<=1)&&(i<nl&&i>=0)&&(j<nc&&j>=0)&&(k<np&&k>=0)){
                    v[i][j][k].isOn=true;
                    v[i][j][k].red=r;
                    v[i][j][k].blue=b;
                    v[i][j][k].green=g;
                    v[i][j][k].alpha=a;
                }
            }
        }
    }

}

void Sculptor::cutEllipsoid(int centrox, int centroy, int centroz, int rx, int ry, int rz){
 double _rx=rx/2.0;
 double _ry=ry/2.0;
 double _rz=rz/2.0;
 double d;
    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                d = (i-centrox/2.0)*(i-centrox/2.0)/(_rx *_rx) +
                    (j-centroy/2.0)*(j-centroy/2.0)/(_ry *_ry) +
                    (k-centroz/2.0)*(k-centroz/2.0)/(_rz *_rz);

                if(d<=1){
                   v[i][j][k].isOn=false;
                }
            }
        }
    }
}


void Sculptor::writeOFF(string filename){
 ofstream fout2;
 int Nvertices=0;
 int Nfaces=0;
 int aux=0;

 fout2.open("C:/Users/paulo/OneDrive/Imagens/untitled3"+filename+".off");
 fout2<<"OFF"<<endl;

    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    Nvertices=Nvertices+8;
                    Nfaces=Nfaces+6;
                }
            }
        }
    }

    fout2<<Nvertices<<" "<<Nfaces<<" "<<0<<endl;

    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    fout2<<i-0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                    fout2<<i-0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                    fout2<<i+0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                    fout2<<i+0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                    fout2<<i-0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                    fout2<<i-0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                    fout2<<i+0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                    fout2<<i+0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                }
            }
        }
    }

    for(int i=0;i<nl;i++){
        for(int j=0;j<nc;j++){
            for(int k=0;k<np;k++){
                if(v[i][j][k].isOn){
                    fout2<<4<<" "<<aux+0<<" "<<aux+3<<" "<<aux+2<<" "<<aux+1<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+4<<" "<<aux+5<<" "<<aux+6<<" "<<aux+7<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+0<<" "<<aux+1<<" "<<aux+5<<" "<<aux+4<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+0<<" "<<aux+4<<" "<<aux+7<<" "<<aux+3<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+3<<" "<<aux+7<<" "<<aux+6<<" "<<aux+2<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    fout2<<4<<" "<<aux+1<<" "<<aux+2<<" "<<aux+6<<" "<<aux+5<<" "<<v[i][j][k].red<<" "
                    <<v[i][j][k].green<<" "<<v[i][j][k].blue<<" "<<v[i][j][k].alpha<<endl;
                    aux=aux+8;
                }
            }
        }
    }
}


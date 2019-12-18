#ifndef XYZ_H
#define XYZ_H
#include <iostream>

using namespace std;

class XYZ {
  public:
    double x;
    double y;
    double z;
    XYZ ();
    XYZ ( double a[] );
    XYZ ( double x0, double y0, double z0 );
    void set ( double x0, double y0, double z0 );
//    XYZ &getXYZ( XYZ &xyz );	//return by reference, this works also
    XYZ getXYZ();
    void getXYZ( double a[]  );
    void print();
};
#endif

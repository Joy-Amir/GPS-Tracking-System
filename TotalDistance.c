#include "TotalDistance.h"
#include "math.h"
#include "string.h"
#include "stdio.h"

 //the parameters are in Degree Decimal
 
float TotalDistance(float x1,float y1,float x2,float y2)     
{ 
	//declaring the variables needed in the function
	
	float horizontal;
	float vertical;
	float latitude;
	float longitude;
	float d;
	float distance;
	
	//converting the Co-ordinated into Radians by multiplying *(pi/180)
	
	x1=x1*3.141592654 / 180;
	x2=x2*3.141592654 / 180;
	y1=y1*3.141592654 / 180;
	y2=y2*3.141592654 / 180;
	
	// calculating the distance between two points using (latitude,longitude)coordinates and return distance in meters
	
	horizontal=(x1-x2)/2;
	vertical=(y1-y2)/2;
	latitude=sin(horizontal);
	longitude=sin(vertical);
	d=sqrt(pow(latitude,2)+cos(x1)*cos(x2)*pow(longitude,2));
	distance=2*6371*1000*asin(d);
	return distance;
}

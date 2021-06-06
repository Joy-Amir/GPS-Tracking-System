#include "distance.h"
#include "string.h"
#include "stdlib.h"  //for fn strtof
#include "fpu.h"

//typedef float float32_t;
float convert_latitude(char* latitude){

	char before_degree_Lat[3];
	char before_minute_Lat[9];
	char* pend;
	float before_degree_LatF;
	float before_minute_LatF;
	float latitude_after;
	
	memcpy (before_degree_Lat,&latitude[0],2);
	before_degree_Lat[2]='\0';
	
	memcpy (before_minute_Lat,&latitude[2],8);
	before_minute_Lat[8]='\0';	
	
	before_degree_LatF=strtof(before_degree_Lat,&pend);
	before_minute_LatF=strtof(before_minute_Lat,&pend);
	
	latitude_after=before_degree_LatF+ (before_minute_LatF/60.00);
	
	return latitude_after;
	
}

float convert_longitude(char* longitude){

	char before_degree_Long[4];
	char before_minute_Long[9];
	char* pend;
	float before_degree_LongF;
	float before_minute_LongF;
	float longitude_after;
	
	memcpy (before_degree_Long,&longitude[0],3);
	before_degree_Long[3]='\0';
	
	
	memcpy (before_minute_Long,&longitude[3],8);
	before_minute_Long[8]='\0';
	
	
	before_degree_LongF=strtof(before_degree_Long,&pend);
	before_minute_LongF=strtof(before_minute_Long,&pend);
	
	longitude_after=before_degree_LongF+ (before_minute_LongF/60.00);
	
	return longitude_after;
	
}



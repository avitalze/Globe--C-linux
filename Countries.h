/*
 * ‫‪Countries‬‬.h
 *
 *  Created on: Nov 12, 2018
 *      Author: ise
 */

#ifndef COUNTRIES_H_
#define COUNTRIES_H_

typedef enum e_bool {true, false } bool;
typedef enum e_status  {success, failure } status;

typedef struct City* City;
typedef struct AreaGeo* AreGeo;
typedef struct Country* Country;

struct City
{
	char* cityName;
	char* food;
	int numOfResidents;
};
struct AreaGeo{
	int x1L;
	int x2R;
	int y1L;
	int y2R;
};
struct Country{
	char* cntryName;
	int numOfCities;
	struct AreaGeo zone;
	City* citiesInCntry;
};


Country AddCountry (char *name, int x1l, int x2r,int y1l,int y2r);
status AddCity (Country pCountry, City newCity);
status DeleteCity ( Country pCountry, char* name);
bool IsInZone (int x, int y, Country pCountry);
Country DeepCopyCountry(Country state);
status FreeCountry(Country pCountry);
status PrintCountry (Country state);



#endif /* COUNTRIES_H_ */

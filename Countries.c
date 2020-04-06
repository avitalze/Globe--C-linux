/*
 * ‫‪Countries.c

 *
 *  Created on: Nov 12, 2018
 *      Author: ise
 */
/* linked list example */
#include "Countries.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>



Country AddCountry (char* name, int x1l, int x2r,int y1l,int y2r){
	if(x1l>=0 || x2r>=0 || y1l>=0 ||y2r>=0 || name != NULL){
		Country newCountry= (Country)malloc(sizeof(struct Country));
		if(newCountry ==NULL){
			free(newCountry);
			return NULL;
		}
		newCountry->zone.x1L=x1l;
		newCountry->zone.x2R = x2r;
		newCountry->zone.y1L=y1l;
		newCountry->zone.y2R= y2r;
		newCountry->cntryName=(char*)calloc(strlen(name)+1,sizeof(char));
		if(newCountry->cntryName ==NULL){
			free(newCountry->cntryName);
			free(newCountry);
			return NULL;
		}
		strcpy(newCountry->cntryName,name);
		newCountry->numOfCities=0;
		newCountry->citiesInCntry=NULL;
		return newCountry;
	}
	else return NULL;
}



status AddCity (Country pCountry, City newCity){
	if( newCity == (City)NULL || pCountry == (Country)NULL){
		return failure;
	}
	pCountry->numOfCities++;
	pCountry->citiesInCntry = (City*) (realloc(pCountry->citiesInCntry,(pCountry->numOfCities)*sizeof(City)));
	if(pCountry->citiesInCntry == NULL){// realloc didnt work
		return failure;
	}

	else{//do we need to add malloc for city*?!
		pCountry->citiesInCntry[(pCountry->numOfCities-1)]=(City)malloc(sizeof(struct City));
		pCountry->citiesInCntry[(pCountry->numOfCities-1)]->numOfResidents= newCity->numOfResidents;
		pCountry->citiesInCntry[(pCountry->numOfCities-1)]->cityName= (char*)calloc(strlen(newCity->cityName)+1,sizeof(char));

		if((pCountry->citiesInCntry[(pCountry->numOfCities-1)]->cityName) == (char*)NULL){
			free((pCountry->citiesInCntry[(pCountry->numOfCities-1)]->cityName));
			pCountry->citiesInCntry = (City*) (realloc(pCountry->citiesInCntry,(pCountry->numOfCities-1)*sizeof(City)));
			pCountry->numOfCities--;
			return failure;
		}
		strcpy((pCountry->citiesInCntry[(pCountry->numOfCities-1)]->cityName),newCity->cityName);

		pCountry->citiesInCntry[(pCountry->numOfCities-1)]->food= (char*)calloc(strlen(newCity->food)+1,sizeof(char));
		if((pCountry->citiesInCntry[(pCountry->numOfCities-1)]->food) == (char*)NULL){
			free((pCountry->citiesInCntry[(pCountry->numOfCities-1)]->food));
			free((pCountry->citiesInCntry[(pCountry->numOfCities-1)]->cityName));
			pCountry->citiesInCntry = (City*) (realloc(pCountry->citiesInCntry,(pCountry->numOfCities-1)*sizeof(City)));
			pCountry->numOfCities--;
			return failure;
		}
		strcpy((pCountry->citiesInCntry[(pCountry->numOfCities-1)]->food),newCity->food);
		return success;
	}
}



status DeleteCity ( Country pCountry, char* name){
	if(pCountry == NULL || name == NULL)
		return failure;
	int i;
	int indexCity;
	int sameName;
	bool flag=true;
	for(i=0; i<pCountry->numOfCities && flag; i++){ //find the city
		sameName= strcmp((pCountry->citiesInCntry[i]->cityName),name);
		if(sameName==0){
			indexCity=i;
			flag=false;
		}
	}
	if(flag == true){//the city is not found
		return failure;
	}
	if(indexCity != (pCountry->numOfCities-1)){//swap by address/value
		struct City temp;//malloc?!
		temp = *(pCountry->citiesInCntry[indexCity]);
		*(pCountry->citiesInCntry[indexCity])=*(pCountry->citiesInCntry[(pCountry->numOfCities-1)]);
		*(pCountry->citiesInCntry[(pCountry->numOfCities-1)])=temp;
	}
	pCountry->numOfCities--;
	pCountry->citiesInCntry=(City*)realloc(pCountry->citiesInCntry,sizeof(City)*(pCountry->numOfCities));// does it free the whole city in the last place?
	if(pCountry->citiesInCntry == NULL){
		return failure;
	}
	return success;
}

bool IsInZone (int x, int y, Country pCountry){
	if (x<0 || y<0 || pCountry == (Country)NULL){
		return false;
	}
	if ((x>= pCountry->zone.x1L) && (x<=pCountry->zone.x2R) && (y<=pCountry->zone.y1L) && (y>=pCountry->zone.y2R)){
		return true;
	}
	else {
		return false;
	}
}


status FreeCountry(Country pCountry){
	int i;
	for(i=0; i<(pCountry->numOfCities);i++){
		free(pCountry->citiesInCntry[i]->cityName);
		free(pCountry->citiesInCntry[i]->food);
		free(pCountry->citiesInCntry[i]);
	}
	free(pCountry->citiesInCntry);
	free(pCountry->cntryName);
	//free(pCountry->zone);?!?!?!?!?
	return success;
}


Country DeepCopyCountry(Country pCountry){//we need to free every step!!!!
	if(pCountry ==NULL){
		return NULL;
	}
	Country newCntry=(Country)malloc(sizeof(*pCountry));// maybe sizeof struct country?
	if(newCntry == NULL ){
		free(newCntry);
		return NULL;
	}
	newCntry->numOfCities=pCountry->numOfCities;//int

	newCntry->cntryName=(char*)malloc(strlen(pCountry->cntryName)+1);//name
	if (newCntry->cntryName==NULL){
		free(newCntry->cntryName);
		free(newCntry);
		return NULL;
	}
	strcpy(newCntry->cntryName,pCountry->cntryName);

	struct AreaGeo newZone = { pCountry->zone.x1L , pCountry->zone.x2R , pCountry->zone.y1L , pCountry->zone.y2R };//area
	newCntry->zone= newZone;

	newCntry->citiesInCntry=(City*)malloc(sizeof(*(newCntry->citiesInCntry)));//cities
	if ( newCntry->citiesInCntry == NULL){
		free(newCntry->citiesInCntry);
		free(newCntry->cntryName);
		free(newCntry);
		return NULL;
	}
	int i;
	for(i=0;i<pCountry->numOfCities;i++){
		newCntry->citiesInCntry[i]=(City)malloc(sizeof(*(pCountry->citiesInCntry[i])));//pCountry->citiesInCntry[i
		if (newCntry->citiesInCntry[i] == NULL){
			free(newCntry->citiesInCntry[i]);
			free(newCntry->citiesInCntry);
			free(newCntry->cntryName);
			free(newCntry);
			return NULL;
		}

		newCntry->citiesInCntry[i]->cityName= (char*)malloc(sizeof(pCountry->citiesInCntry[i]->cityName)+1);
		if (newCntry->citiesInCntry[i]->cityName == NULL){
			free(newCntry->citiesInCntry[i]->cityName);
			free(newCntry->citiesInCntry[i]);
			free(newCntry->citiesInCntry);
			free(newCntry->cntryName);
			free(newCntry);
			return NULL;
		}
		strcpy(newCntry->citiesInCntry[i]->cityName,pCountry->citiesInCntry[i]->cityName);
		newCntry->citiesInCntry[i]->food= (char*)malloc(sizeof(pCountry->citiesInCntry[i]->food)+1);
		if (newCntry->citiesInCntry[i]->food == NULL){
			free(newCntry->citiesInCntry[i]->food);
			free(newCntry->citiesInCntry[i]->cityName);
			free(newCntry->citiesInCntry[i]);
			free(newCntry->citiesInCntry);
			free(newCntry->cntryName);
			free(newCntry);
			return NULL;
		}
		strcpy(newCntry->citiesInCntry[i]->food,pCountry->citiesInCntry[i]->food);
		newCntry->citiesInCntry[i]->numOfResidents= pCountry->citiesInCntry[i]->numOfResidents;
	}
	return newCntry;
}


status PrintCountry (Country pCountry){
	if(pCountry ==NULL){
		return failure;
	}
	printf("Country %s coordinates: <%d,%d> , <%d,%d>\n",pCountry->cntryName,pCountry->zone.x1L, pCountry->zone.y1L, pCountry->zone.x2R, pCountry->zone.y2R);//right order?
	int i;
	for(i=0;i<pCountry->numOfCities;i++){
		PrintCity(pCountry->citiesInCntry[i]);
	}
	return success;
}

void PrintCity (City cCity){//private(!!!!) function to help the print
	printf("\t%s includes %d residents and their favorite food is %s.\n",cCity->cityName,cCity->numOfResidents,cCity->food);//check!!!!!
}




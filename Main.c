/*
 * Main.c
 *
 *  Created on: Nov 12, 2018
 *      Author: ise
 */
#include "Countries.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){

	Country AllTheCountries[argc-1];

	int counter=0;
	FILE* pFile;
	pFile= fopen(argv[2],"r");

	char* buffer= (char*)calloc(300,sizeof(char));
	while(fgets(buffer,300,pFile)!=NULL ){
		if(buffer[0]=='\t'){//city
			buffer++;
			char* pch;
			pch = strtok (buffer,",");
			char* CityName=pch;

			pch = strtok (NULL,",");
			char* CityFood = pch;

			pch = strtok (NULL,",");
			int residents = atoi(pch);

			City newCity=(City)malloc(sizeof(struct City));//need to free!!!!!!!!!!!!!!!!!!11
			newCity->cityName=(char*)malloc(sizeof(strlen(CityName)+1));
			newCity->cityName=CityName;
			newCity->food=(char*)malloc(sizeof(strlen(CityFood)+1));
			newCity->food=CityFood;
			newCity->numOfResidents=residents;

			status didItWork = AddCity(AllTheCountries[counter-1], newCity);
			didItWork = PrintCountry(AllTheCountries[counter-1]);
		}
		else{//country
			counter++;
			char* pch;
			pch = strtok (buffer,",");
			char* CntryName=pch;

			pch = strtok (NULL,",");
			int x1=atoi(pch);

			pch = strtok (NULL,",");
			int y1=atoi(pch);


			pch = strtok (NULL,",");
			int x2=atoi(pch);

			pch = strtok (NULL,",");
			int y2=atoi(pch);

			AllTheCountries[counter-1] = AddCountry(CntryName,x1,y1,x2,y2);
			status stat= PrintCountry(AllTheCountries[counter-1]);
		}

	}
	fclose(pFile);

	int fromUser;

	while( fromUser != 6 ) {//what to put?!
		printf("‫‪please‬‬ ‫‪choose‬‬ ‫‪one‬‬ ‫‪of‬‬ ‫‪the‬‬ ‫‪following‬‬ ‫‪numbers:‬‬\n");
		printf("‫‪1‬‬ ‫‪:‬‬ ‫‪print‬‬ ‫‪countries‬‬\n");
		printf("‫‪2‬‬ ‫‪:‬‬ ‫‪add‬‬ ‫‪city‬‬ ‫‪to‬‬ ‫‪country‬‬\n");
		printf("‫‪3‬‬ ‫‪:‬‬ ‫‪remove‬‬ ‫‪city‬‬ ‫‪from‬‬ ‫‪country‬‬\n");
		printf("‫‪4‬‬ ‫‪:‬‬ ‫‪find‬‬ ‫‪country‬‬ ‫‪in‬‬ ‫‪area‬‬\n");
		printf("‫‪5‬‬ ‫‪:‬‬ ‫‪print‬‬ ‫‪country‬‬ ‫‪by‬‬ ‫‪name‬‬\n");
		printf("‫‪6‬‬ ‫‪:‬‬ ‫‪exit‬‬\n");
		scanf("%d", &fromUser );

		switch( fromUser )
		{
		case 1:  // print countries
			for(int i=0;i< argc-1;i++){
				status stat=PrintCountry(AllTheCountries[i]);
				if(stat == failure){
					//???
				}
				break;

		case 2:  //‫‪add‬‬ ‫‪city‬‬ ‫‪to‬‬ ‫‪country

			printf("please enter a country name");
			char buffer[30];
			scanf("%s",buffer);
			char* countryName =(char*)malloc(strlen(buffer)+1);
			strcpy(countryName,buffer);
			bool found=false;
			int CountryNum;
			for(int i=0; i<argc-1 && !found;i++){
				if(strcmp(countryName,AllTheCountries[i]->cntryName)==0){
					found = true;
					CountryNum=i;
				}
			}
			if( found ==true){// see if city is already created
				printf("please enter a city name");
				scanf("%s",buffer);
				char* cityName =(char*)malloc(strlen(buffer)+1);
				strcpy(cityName,buffer);
				bool isInCountry = false;
				for( int j=0;j<AllTheCountries[CountryNum]->numOfCities && !isInCountry;j++){
					if (strcmp(cityName,AllTheCountries[CountryNum]->citiesInCntry[j]->cityName)==0){
						isInCountry = true;
					}
				}
				if(isInCountry == false){//build new city in country
					printf("please enter the city favorite food");
					scanf("%s",buffer);
					char* food= (char*)malloc(strlen(buffer)+1);
					strcpy(food,buffer);

					int number;
					printf("please enter number of residents in city");
					scanf("%d",&number);

					City newCity=(City)malloc(sizeof(struct City));//need to free!!!!!!!!!!!!!!!!!!11
					newCity->cityName=cityName;
					newCity->food=food;
					newCity->numOfResidents=number;
					status a= AddCity(AllTheCountries[CountryNum],newCity);// what if status fail?!!?!?!
				}
				else{// out of function
					printf("this city already exist in this country .");
					break;
				}
			}
			else{// out of function
				printf("country name not exist .");
				break;
			}
			break;

		case 3:  // ‫‪remove‬‬ ‫‪city‬‬ ‫‪from‬‬ ‫‪country‬‬
			printf("please enter a country name");
			char buff[30];
			scanf("%s",buff);
			char* nameOfcntry =(char*)malloc(strlen(buff)+1);
			strcpy(nameOfcntry,buff);
			bool exist=false;
			int Countrynumber;
			for( int i=0; i<argc-1 && !exist;i++){
				if(strcmp(nameOfcntry,AllTheCountries[i]->cntryName)==0){
					exist=true;
					Countrynumber=i;
				}
			}
			if (exist == false){// out of function
				printf("country name not exist.");
				break;
			}
			else{
				printf("please enter a city name");
				scanf("%s",buff);
				char* cityName =(char*)malloc(strlen(buff)+1);
				strcpy(cityName,buff);
				bool isInCountry = false;
				for(int j=0; j<AllTheCountries[Countrynumber]->numOfCities;j++){
					if( strcmp(cityName,AllTheCountries[Countrynumber]->citiesInCntry[j]->cityName)==0){
						isInCountry=true;
					}
				}
				if( isInCountry == false){// out of function
					printf("the city not exist in this country");
					break;
				}
				else{
					status worked = DeleteCity(AllTheCountries[Countrynumber], cityName);// if fail?!!?!?!?!?
				}
			}
			break;

			case 4:  // ‫‪find‬‬ ‫‪country‬‬ ‫‪in‬‬ ‫‪area
				printf("please enter x and y coordinations:x,y");
				int x,y;
				scanf("%d,%d",&x,&y);
				int i,count;
				bool ans;
				bool foundCoor;//what?!?!‬‬
				for(i=0; i< argc-1 && !foundCoor; i++){
					ans=IsInZone(x,y,AllTheCountries[i]);
					if (ans==true){
						foundCoor = true;
						count=i;
					}
				}
				if (foundCoor == true){
					printf("found in: %s",AllTheCountries[count]->cntryName);
					break;
				}
				else{
					printf("there is no country in the area");
					break;
				}
				break;

case 5:  //‫‪print‬‬ ‫‪country‬‬ ‫‪by‬‬ ‫‪name‬‬

	break;

case 6:	//exit

	break;

default:
	printf("‫‪please‬‬ ‫‪choose‬‬ ‫‪a‬‬ ‫‪valid‬‬ ‫‪number‬‬\n");
	//break?!
			}
		}
	}




	return 0;
}







*/
//end of main


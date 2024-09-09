#ifndef _ADDRESS_
#define _ADDRESS_ 

typedef struct 
{
	char* country;
	char* city;
}Address;

void	initAddress(Address* address, char* country, char* city);
void	printAddress(Address* address);
void	freeAddress(Address* address);




#endif
#ifndef SWIMMER
#define SWIMMER


typedef struct
{
	char* name;
	int age;
	int bestResult;
}Swimmer;

int		initSwimmer(Swimmer* swimmer, char* name, int age, int bestResult);
void	printSwimmer(const Swimmer* swimmer);
char*	getSwimmerName(Swimmer* swimmer);
void	freeSwimmer(Swimmer* swimmer);

#endif
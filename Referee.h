#ifndef REFEREE
#define REFEREE 

#define NUMBER_OF_REFEREES_PER_HEAT 3

typedef enum
{
	eSide, eSpingboard, eMain, eNumOfRef
}eRefType;

static const char* RefTypeStr[eNumOfRef];

typedef struct
{
	char* name;
	int age;
	char* country;
	eRefType refType;
}Referee;

int		initRef(Referee* ref, char* name, int age, char* country, eRefType refType);
void	printRef(const Referee* ref);
void	freeRef(Referee* ref);
eRefType getRefereeType();
#endif
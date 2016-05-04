#include "config.h"

int checkSO()
{
	#ifdef __unix__
		return 0;
	#elif defined(_WIN32) || defined(WIN32)
		return 1;
	#endif
}

void limparTela()
{
	int SO;
	SO = checkSO();
	if (SO==0) system ("clear");
	else system ("cls");
	return;
}

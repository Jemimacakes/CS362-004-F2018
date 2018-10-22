#include <stdlib.h>
#include <stdio.h>

enum SYMBOL
{
	eq,
	lt,
	gt,
	lte,
	gte
};

/**************************************************************************
 * Function: myAssert
 * Description: operand1 and operand2 are compared with the proper symbol.
 * If the comparison is true, myAssert returns 1
 * Else if exitValue is 1, myAssert terminates the program on a miscompare.
 * Else it returns 0.
 **************************************************************************/
int myAssert(int operand1, int operand2, int symbol, int exitValue)
{
	int result;

	switch(symbol)
	{
		case eq:
			result = (operand1 == operand2);
			break;

		case lt:
			result = (operand1 < operand2);
			break;

		case gt:
			result = (operand1 > operand2);
			break;

		case lte:
			result = (operand1 <= operand2);
			break;

		case gte:
			result = (operand1 >= operand2);
			break;
	}

	if(result == 0 && exitValue == 1)
	{
		printf("Assertion failed, exiting.\n");
		exit(0);
	}
	else
	{
		return result;
	}
}

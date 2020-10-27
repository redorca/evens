/*********************************************************************************************************************************
 *
 * Given a string of words, say a sentence, find those words with an even number of characters
 * and return the word with the greatest number. If more than one exists then return the first.
 *
 ********************************************************************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint8_t bignum, bigindex;
char *bigword;
char *sfx[] = {"th", "st"};

char err_string[] = " Something's up here.";

#define SFX(a)	(a%10 != 1 ? sfx[0] : sfx[1])

#define ISEVEN(a)	!(a & 0x1)
#define UPDATE_BIGGEST(a, b, c)	\
	if (b > bignum)	\
	{			\
		bignum = b;	\
		bigword = a;	\
		bigindex = c;	\
	}
/*
 * Sort of a strtok but returning the number of chars in
 * any word found.
 *
 */
int scan(char **sentence, char **word)
{
	char *wordy;
	uint8_t numchars;

	wordy = *sentence;
	while ((wordy != NULL) && (isspace(*wordy))) { wordy++; }

	*word = wordy;
	while ((wordy != NULL) && (isalpha(*wordy))) { wordy++; }

	numchars = wordy - *word;
	*sentence = wordy;
	if (*wordy != 0)
	{
		*(*sentence)++ = 0;
	}

	return numchars;
}

/*
 * In case the string enterd was not quoted
 * collect everything from the command line
 * and assemble into a string.
 */
char *foo(int count, char *stuff[])
{
	int i, total;

	if (count == 1) return stuff[count];

	for(i = 0; i <= count; i++)
	{
		total += strlen(stuff[i]);
	}
	return err_string;
}

int main(int argc, char *argv[])
{
	char *word, *sntnce, ordinal[8];
	uint8_t many, word_position;
	if (argc < 2)
	{
		printf("What? No words come to mind?\n");
		return -2;
	}

	bignum = 0;
	word_position = 1;	/* counting starts with 1 rather than 0. */
	sntnce = word = foo(argc -1, argv);
	while (*sntnce != 0)
	{
		many = scan(&sntnce, &word);
		if (ISEVEN(many)) { UPDATE_BIGGEST(word, many, word_position); }
		word_position++;
	}

	if (bignum == 0)
	{
		printf("There aren't any words of an even number of letters.\n");
		return -3;
	}
	snprintf(ordinal, 5, "%d%s", bigindex, SFX(bigindex));

	printf("The word with the most even number of letters [%d] is the %s word <%s> in the string.\n", bignum, ordinal, bigword);
}

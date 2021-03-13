#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i, j;
	int wordVal;
	char c0, c1;
	char fileDest[255];
	int reqWord = 0;
	int reqDec = 0;
	int reqSigned = 0;
	int reqSkip = 0;
	FILE *fp, *wp;

	if (argc < 2)
	{
		printf("File not valid");
		return -1;
	}

	// Looking for -w: Format as WORDS
	for (i = 0; i < argc; i++)
	{
		if ((int)strcmp("-w", argv[i]) == 0)
		{
			reqWord = 1;
			break;
		}
	}

	// Looking for -d: Format as DECIMAL
	for (i = 0; i < argc; i++)
	{
		if ((int)strcmp("-d", argv[i]) == 0)
		{
			reqDec = 1;
			break;
		}
	}

	// Looking for -s: Format as SIGNED
	for (i = 0; i < argc; i++)
	{
		if ((int)strcmp("-s", argv[i]) == 0)
		{
			reqSigned = 1;
			break;
		}
	}

	// Looking for -sk: Skip the defined number of elements (always in BYTES)
	for (i = 0; i < argc; i++)
	{
		if ((int)strcmp("-sk", argv[i]) == 0)
		{
			reqSkip = atoi(argv[i + 1]) + 1;
			break;
		}
	}

	// Get file name
	for (j = strlen(argv[1]); j >= 0; j--)
	{
		if (argv[1][j] == '.')
		{
			break;
		}
	}

	for (i = 0; i < j; i++)
	{
		fileDest[i] = argv[1][i];
	}

	fileDest[i] = '.';
	fileDest[i + 1] = 't';
	fileDest[i + 2] = 'x';
	fileDest[i + 3] = 't';
	fileDest[i + 4] = '\0';

	fp = fopen(argv[1], "rb");
	wp = fopen(fileDest, "w");

	while (!feof(fp))
	{
		fscanf(fp, "%c", &c0);
		if (reqSkip)
			reqSkip--;
		if (!reqSkip)
		{
			if (!reqWord)
			{
				if (!reqDec)
					fprintf(wp, "%.2X\n", c0 & 255);
				else
					fprintf(wp, "%d\n", !reqSigned ? c0 & 255 : c0);
			}
			else
			{
				fscanf(fp, "%c", &c1);
				wordVal = ((char)c0 * 256) + ((char)c1 & 255);

				if (!reqDec)
					fprintf(wp, "%.4X\n", wordVal & 65535);
				else
					fprintf(wp, "%d\n", !reqSigned ? wordVal & 65535 : wordVal);
			}
		}
	}

	fclose(fp);
	fclose(wp);

	return 1;
}

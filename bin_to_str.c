#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i, j;
	int wordVal;
	char c, c1;
	char fileDest[255];
	int reqWord = 0;
	int reqDec = 0;
	int reqSigned = 0;
	FILE *fp, *wp;

	if (argc < 2)
	{
		printf("File not valid");
		return -1;
	}

	// Looking for -w: Format as WORDS
	for (i = 0; i < argc; i++)
	{
		reqWord = (int)strcmp("-w", argv[i]);
		if (reqWord == 0)
		{
			reqWord = 1;
			break;
		}
	}

	// Looking for -d: Format as DECIMAL
	for (i = 0; i < argc; i++)
	{
		reqDec = (int)strcmp("-d", argv[i]);
		if (reqDec == 0)
		{
			reqDec = 1;
			break;
		}
	}

	// Looking for -d: Format as DECIMAL
	for (i = 0; i < argc; i++)
	{
		reqSigned = (int)strcmp("-s", argv[i]);
		if (reqSigned == 0)
		{
			reqSigned = 1;
			break;
		}
	}

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

	fp = fopen(argv[1], "rb");
	wp = fopen(fileDest, "w");

	while (!feof(fp))
	{
		fscanf(fp, "%c", &c);
		if (reqWord != 1)
		{
			if (reqDec != 1)
				fprintf(wp, "%.2X\n", c & 255);
			else
				fprintf(wp, "%d\n", reqSigned != 1 ? c & 255 : c);
		}
		else
		{
			fscanf(fp, "%c", &c1);
			wordVal = ((char)c * 256) + ((char)c1 & 255);

			if (reqDec != 1)
				fprintf(wp, "%.4X\n", wordVal & 65535);
			else
				fprintf(wp, "%d\n", reqSigned != 1 ? wordVal & 65535 : wordVal);
		}
	}

	fclose(fp);
	fclose(wp);

	return 1;
}

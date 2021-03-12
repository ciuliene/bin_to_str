#include <stdio.h>
#include <string.h>
//#include <windows.h>

int main(int argc, char **argv)
{
	int i, j;
	int hnib, lnib;
	char c;
	char fileDest[255];
	int newLine = 1;
	int reqWord = 0;
	FILE *fp, *wp;

	if (argc < 2)
	{
		//MessageBox(NULL, "Not valid", "BinToStr", MB_ICONERROR);
		printf("File not valid");
		return -1;
	}

	for (i = 0; i < argc; i++)
	{
		reqWord = (int)strcmp("-w", argv[i]);
		if (reqWord == 0)
		{
			newLine = 0;
			reqWord = 1;
			break;
		}
	}

	fp = fopen(argv[1], "rb");
	/* for (i = strlen(argv[1]); i >= 0; i--)
	{
		if (argv[1][i] == '\\')
		{
			break;
		}
	}

	printf("%s\n", argv[1]);

	for (j = 0; j < i; j++)
	{
		fileDest[j] = argv[1][j];
	}
	//fileDest[j] = '\\';
	fileDest[j] = 'r';
	fileDest[j + 1] = 'e';
	fileDest[j + 2] = 's';
	fileDest[j + 3] = '.';
	fileDest[j + 4] = 't';
	fileDest[j + 5] = 'x';
	fileDest[j + 6] = 't';
	fileDest[j + 7] = '\0';

	printf("%s", fileDest); */

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

	wp = fopen(fileDest, "w");

	while (!feof(fp))
	{
		fscanf(fp, "%c", &c);
		if (c < 0x10 && c >= 0x0)
		{
			fprintf(wp, "0");
		}

		if (c < 0)
		{
			hnib = (c & 240) / 0x10;
			lnib = (c & 15);
			fprintf(wp, "%X", hnib);
			if (newLine)
			{
				fprintf(wp, "%X\n", lnib);
			}
			else
			{
				fprintf(wp, "%X", lnib);
			}
		}
		else
		{
			if (newLine)
			{
				fprintf(wp, "%X\n", c);
			}
			else
			{
				fprintf(wp, "%X", c);
			}
		}

		if (reqWord == 1)
			newLine ^= 1;
		else
			newLine = 1;
	}

	fclose(fp);
	fclose(wp);

	return 1;
}

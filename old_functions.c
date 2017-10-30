
void put_mask(int teti)
{
	int i = 3, j;
	int tet = g_blk[teti];

	while (i >= 0)
	{
		j = 3;
		while (j >= 0)
		{
			if (TET_BIT(i, j) & tet)
				printf("%c", 65 + teti);
			else
				printf(".");
			j--;
		}
		printf("\n");
		i--;
	}
}
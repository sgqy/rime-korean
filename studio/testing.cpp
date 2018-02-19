
#include <cstdio>
#include <cstring>
#include "utils.hpp"

int main()
{
	printf("ph_t %d ch_t %d\n", sizeof(ph_t), sizeof(ch_t));
	return 0;

	uint16_t bom = 0xfeff;
	uint16_t tip[] = {' ', ':', ' '};
	uint16_t das[] = {' ', '-', ' '};
	uint16_t nr = 0x000a;

	FILE *fp = fopen ("o.txt", "wb");
	fwrite (&bom, 2, 1, fp);

	for (uint16_t i = 0xac00; i <= 0xd7a3; ++i) {
		fwrite (&i, 2, 1, fp);
		fwrite (tip, 2, 3, fp);

		auto seq = get_alpha_seq (i);
		for (auto j = seq.begin(); j != seq.end(); ++j) {
			fwrite (& (*j), 2, 1, fp);
			fwrite (das, 2, 3, fp);
		}

		fwrite (&nr, 2, 1, fp);
	}

	fclose (fp);

	return 0;
}

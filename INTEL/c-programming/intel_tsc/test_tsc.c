#include "tsc.h"
#include "ftw.h"

#define FTW_flag	1
#define _XOPEN_SOURCE 500

struct dirent **namelist;
int i, n;

int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf) {

	printf("%-3s %2d %7jd   %-40s %d %s\n",
		(tflag == FTW_D) ?   "d"   : (tflag == FTW_DNR) ? "dnr" :
		(tflag == FTW_DP) ?  "dp"  : (tflag == FTW_F) ?
		(S_ISBLK(sb->st_mode) ? "f b" :
		S_ISCHR(sb->st_mode) ? "f c" :
		S_ISFIFO(sb->st_mode) ? "f p" :
		S_ISREG(sb->st_mode) ? "f r" :
		S_ISSOCK(sb->st_mode) ? "f s" : "f ?") :
		(tflag == FTW_NS) ?  "ns"  : (tflag == FTW_SL) ?  "sl" :
		(tflag == FTW_SLN) ? "sln" : "?",
		ftwbuf->level, (intmax_t) sb->st_size,
		fpath, ftwbuf->base, fpath + ftwbuf->base);

	return 0;	/* To tell nftw() to continue */
}

void scan_dir(void) {
	struct dirent **namelist;
	int i,n;

	n = scandir(".", &namelist, 0, alphasort);
	if (n < 0)
		perror("scandir");
	else {
		for (i = 0; i < n; i++) {
			printf("%s\n", namelist[i]->d_name);
			free(namelist[i]);
		}
	}

	free(namelist);
}

int main(int argc, char *argv[]) {
	uint64_t start, end, overhead;
	int flags = 0;

	overhead = measure_tsc_overhead();
	start = bench_start();

	// code to benchmark
# if FTW_flag
	if (argc > 2 && strchr(argv[2], 'd') != NULL)
		flags |= FTW_DEPTH;

	if (argc > 2 && strchr(argv[2], 'p') != NULL)
		flags |= FTW_PHYS;

	if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags) == -1) {
		perror("nftw");

		return -1;
	}
#else
	scan_dir();
#endif
	end = bench_end();
	printf("Execution took %lu clock cycles\n", end - start - overhead);

	return 0;
}

/*
 * c2xx_memory_status.c - David Schaper
 * Net pointer to: https://davidschaper.nl/downloads/c2xx_memory_status.c
 * Must be run as root.
 *
 * Does apply up to Core 5 silicons (does not to Core 6, 7, 8, 9 and 10)
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define MCHBAR	 		0xFED10000
#define FILESIZE 		(32*1024)

#define MAD_DIMM_CH0		(0x5004/sizeof(int))
#define MAD_DIMM_CH1		(0x5008/sizeof(int))

#define ECC			0x3000000
#define ENH_INTERLEAVE		0x0400000
#define RI			0x0200000
#define DBW			0x0100000
#define DAW			0x0080000
#define DBNOR			0x0040000
#define DANOR			0x0020000
#define DAS			0x0010000

#define DIMM_B_SIZE		0xFF00
#define DIMM_A_SIZE		0x00FF

#define ECCERRLOG0_C0		(0x40C8/sizeof(int))
#define ECCERRLOG1_C0		(0x40CC/sizeof(int))
#define ECCERRLOG0_C1		(0x44C8/sizeof(int))
#define ECCERRLOG1_C1		(0x44CC/sizeof(int))

#define ERRBANK			0xE0000000
#define ERRRANK			0x18000000
#define ERRCHUNK		0x05000000
#define ERRSYND			0x00FF0000
#define MERRSTS			0x00000002
#define CERRSTS			0x00000001

#define ERRCOL			0xFFFF0000
#define ERRROW			0x0000FFFF

void printChannelErrorLog(int log0, int log1){
	printf("Error status:              ");
	if((log0 & CERRSTS) && (log0 & MERRSTS)){
		printf("Correctable error overwritten by uncorrectable error\n");
	} else if(log0 & CERRSTS){
		printf("Correctable error detected\n");
	} else if(log0 & MERRSTS){
		printf("Uncorrectable error detected\n");
	} else {
		printf("No ECC errors detected\n");
		return;
	}
	printf("Error bank:                %#Xh\n",	(log0 & ERRBANK) >> 29);
	printf("Error rank:                %#Xh\n",	(log0 & ERRRANK) >> 27);
	printf("Error chunk:               %#Xh\n",	(log0 & ERRCHUNK) >> 24);
	printf("Error syndrome:            %#Xh\n",	(log0 & ERRSYND) >> 16);
	printf("Error row:                 %#Xh\n",	(log1 & ERRROW));
	printf("Error column:              %#Xh\n",	(log1 & ERRCOL) >> 16);
}

void printChannelConfiguration(int configuration){
	printf("Size of DIMM A:            %u MiB\n",	(configuration & DIMM_A_SIZE) * 256);
	printf("Size of DIMM B:            %u MiB\n",	((configuration & DIMM_B_SIZE) >> 8) * 256);
	printf("DIMM A DDR width:          %s chips\n",	(configuration & DAW) ? "X16" : "X8");
	printf("DIMM B DDR width:          %s chips\n",	(configuration & DBW) ? "X16" : "X8");
	printf("DIMM A number of ranks:    %s rank\n",	(configuration & DANOR) ? "Dual" : "Single");
	printf("DIMM B number of ranks:    %s rank\n",	(configuration & DBNOR) ? "Dual" : "Single");
	printf("DIMM A select:             DIMM %s\n",	(configuration & DAS) ? "1" : "0");
	printf("Enhanced Interleave Mode:  %s\n",	(configuration & ENH_INTERLEAVE) ? "On" : "Off");
	printf("Rank Interleave:           %s\n",	(configuration & RI) ? "On" : "Off");
	printf("ECC:                       %s\n",	(configuration & ECC) ? "On" : "Off");
}

int main(int argc, char *argv[]){
	int fd = -1;
	int *map;

	fd = open("/dev/mem", O_RDONLY|O_SYNC);
	if (fd == -1) {
		perror("Error opening /dev/mem for reading");
		exit(EXIT_FAILURE);
    	}

	map = mmap(0, FILESIZE, PROT_READ, MAP_SHARED, fd, MCHBAR);
	if (map == MAP_FAILED) {
		close(fd);
		perror("Error mmapping the file");
		exit(EXIT_FAILURE);
	}

	printf("Intel C2xx memory status\n\n");
	printf("Channel 0\n");
	printf("-------------------------------------------------------------------------------\n");
	printChannelConfiguration(map[MAD_DIMM_CH0]);
	printChannelErrorLog(map[ECCERRLOG0_C0], map[ECCERRLOG1_C0]);
	printf("\nChannel 1\n");
	printf("-------------------------------------------------------------------------------\n");
	printChannelConfiguration(map[MAD_DIMM_CH1]);
	printChannelErrorLog(map[ECCERRLOG0_C1], map[ECCERRLOG1_C1]);

	// Unmap the file
	if (munmap(map, FILESIZE) == -1) {
		perror("Error un-mmapping the file");
    	}

	close(fd);
	return 0;
}

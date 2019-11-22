#include "cachelab.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct {//line structure
	int valid;
	unsigned long long int tag;
	int counter;
}lines;

typedef struct {//set structure
	lines * line;
}sets;

typedef struct {//cache structure
	sets * set;
}cache;

int countIndexBit, countLine, countBlockBit, countHit = 0, countMiss = 0, countEvict = 0;
cache caches;
//My cache simulator function
void cache_simulator(unsigned long long int addr) {

	int sizeTag = (64-(countIndexBit+countBlockBit)); //size of the tag bit
	unsigned long long int indexValue = addr << sizeTag >> (countBlockBit + sizeTag);//value of index
	unsigned long long int newTagValue = addr >> (64 - sizeTag);//value of new tag value
	sets set_l= caches.set[indexValue];//determines which sets to look up to

	int isCacheFull = 1;  //value 1 determines cache is full and 0 is empty
	//If the cache is full at a line or not
	int MRU = 0, LRU = 0;//initialized most recently used and least recently used
	for(int i = 0; i < countLine;i++) {//check each line if its valid or not
		if(!set_l.line[i].valid) {//if not valid, then cache is empty
			isCacheFull = 0;
		}
		else if (set_l.line[i].tag == newTagValue) {//if not, then its a hit, increment countHit and counter 
			set_l.line[i].counter++;
			countHit++;
			return;
		}
	
		if(set_l.line[LRU].counter > set_l.line[i].counter) {//updating the most recently used value
			LRU = i;
		}
		else if (set_l.line[MRU].counter < set_l.line[i].counter) {//updating the least recently used value
			MRU = i;
		}
	}
	
	lines newLine = (lines) {//use new line to insert the new tag value with counter greater than MRU
		.valid = 1, .tag = newTagValue, .counter = set_l.line[MRU].counter + 1
		};
	
	//Implementing whether its eviction or hitMiss
	if(isCacheFull) {//evict when cache is full
		set_l.line[LRU] = newLine;
		countEvict++;
	}
	else {
		for(int i = 0;i<countLine;i++) {
			if(!set_l.line[i].valid) {//if not valid then miss
				set_l.line[i] = newLine;
				break;
			}
		}
	}
		countMiss++;
		
 }


int main(int argc, char **argv)
{
	//converting the argv to Index bit, line count and block bit
	countIndexBit = atoi(argv[2]);//2nd argument is Total index bit
	countLine = atoi(argv[4]);//4th argument is total line per set
	countBlockBit = atoi(argv[6]);//6th argument is total block bit

	FILE *traceFile = fopen(argv[argc-1], "r");//opening the trace files passed

	char instruct, buff[256];//instruction in the trasefile (I,L,S,M) and buff for incrementation each line of data from tracefiles 

	unsigned long long int addr; //address from tracefiles
	unsigned long long int countTotalSet = pow(2, countIndexBit);//total sets
	int sizeOfOperation;  //size from trace files
	
	if(!traceFile) {
		exit(0);
}

	//Memory required for caches, total sets in cache and total lines in each set
	//Allocating memory using malloc for all of them
	
	caches.set = malloc(sizeof(sets)*countTotalSet);//memory for all sets
	for (int i = 0; i < countTotalSet; i++){
		caches.set[i].line = malloc(sizeof(lines)*countLine);//memory for all the lines
		for(int j =0; j < countLine; j++){//setting val, tag and counter = 0 for all lines.
			caches.set[i].line[j]=(lines){ .valid=0, .tag=0, .counter=0
			};
		}
	}

	//Will seperate the instruction, address and size of operation from  trace file and will run the cache simulator
	while(fgets(buff,sizeof(buff), traceFile)){//pass the values from traceFile to buff
		if (sscanf(buff," %c %llx,%d", &instruct, &addr, &sizeOfOperation) == 3) {//getting the values from traceFile to their respective values
			if(instruct == 'S' || instruct == 'L') {
				cache_simulator(addr);//only runs once if data store and data load
			}
			else if (instruct == 'M' ) {
				cache_simulator(addr);//runs twice for data modified
				cache_simulator(addr);
			}//not working with instruction load (I)
		}
	}
	
	fclose(traceFile);//closing the traceFile pointer
	
	for(int i = 0; i<countTotalSet;i++) {//freeing all the lines in each sets
		free(caches.set[i].line);
	}
	free(caches.set);//freeing all the sets

    printSummary(countHit, countMiss, countEvict);
    return 0;
}

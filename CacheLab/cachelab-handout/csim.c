/*
 * csim.c - A cache simulator that can replay traces from Valgrind
 *     and output statistics such as number of hits, misses, and
 *     evictions.  The replacement policy is MRU.
 *
 *
 * The function printSummary() is given to print output.
 * Please use this function to print the number of hits, misses and evictions.
 * This is crucial for the driver to evaluate your work.
 */
#include <assert.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cachelab.h"

//#define DEBUG_ON
#define ADDRESS_LENGTH 64

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;

/* Type: Cache line
   MRU is a counter used to implement MRU replacement policy  */
typedef struct cache_line {
  char valid;
  mem_addr_t tag;
  unsigned long long int mru;
} cache_line_t;

typedef cache_line_t *cache_set_t;
typedef cache_set_t *cache_t;

/* Globals set by command line args */
int verbosity = 0; /* print trace if set */
int s = 0;         /* set index bits */
int b = 0;         /* block offset bits */
int E = 0;         /* associativity */
char *trace_file = NULL;

/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int mru_counter = 1;

/* The cache we are simulating */
cache_t cache;
mem_addr_t set_index_mask;

/*
 * initCache - Allocate memory, write 0's for valid and tag and MRU
 * also computes the set_index_mask
 */
void initCache() {
  // printf("SIZES: %lu %lu\n", sizeof(cache_set_t), sizeof(cache_line_t));
  cache = (cache_set_t *)malloc(S * sizeof(cache_set_t));
  for (int i = 0; i < S; ++i) {
    cache[i] = (cache_line_t *)malloc(E * sizeof(cache_line_t));
    for (int j = 0; j < E; ++j) {
      cache[i][j].valid = 0;
      cache[i][j].tag = 0;
      cache[i][j].mru = 0;
    }
  }
  set_index_mask = S - 1;
}

/*
 * freeCache - free allocated memory
 */
void freeCache() {
  int i;
  for (i = 0; i < S; i++) {
    free(cache[i]);
  }
  free(cache);
}

/*
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increast hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(mem_addr_t addr) {
  int i;
  int tag = addr >> (s + b);
  int s_ind = (addr >> b) & set_index_mask;
  int l_ind = 0;
  char flag = 0;
  int first_free = -1;
  cache_set_t set = cache[s_ind];
  unsigned long long highest_mru = 0;
  for (i = 0; i < E; ++i) {
    if (set[i].valid && set[i].tag == tag) {
      // hit
      flag = 1;
      hit_count += 1;
      if (verbosity) printf("hit ");
      set[i].mru = mru_counter++;
      break;
    }

    // if (set[i].mru > highest_mru) {
    //   l_ind = i;
    //   highest_mru = set[i].mru;
    // }
    // if (!set[i].valid) {
    //   first_free = i;
    // }

    // if (verbosity) printf("%d ", set[i].valid);
  }

  // char flag = 0;  // found free line
  // for (i = 0; i < E; ++i) {
  //   if (!set[i].valid) {
  //     l_ind = i;
  //     flag = 1;
  //     break;
  //   } else if (set[i].mru > highest_mru) {
  //     highest_mru = set[i].mru;
  //     l_ind = i;
  //   }
  // }
  // if (!flag) {
  //   eviction_count += 1;
  //   if (verbosity) printf("eviction ");
  // }
  // set[l_ind].valid = 1;
  // set[l_ind].tag = tag;
  // set[l_ind].mru = highest_mru++;
  if (!flag) {
    // missed
    miss_count += 1;
    if (verbosity) printf("miss ");

    flag = 0;
    for (i = 0; i < E; ++i) {
      if (set[i].mru > highest_mru) {
        highest_mru = set[i].mru;
        l_ind = i;
      }
      if (!set[i].valid) {
        first_free = i;
        flag = 1;
        break;
      }
    }
    if (!flag) {
      eviction_count += 1;
      if (verbosity) printf("eviction ");
      set[l_ind].valid = 1;
      set[l_ind].tag = tag;
      set[l_ind].mru = mru_counter++;
    } else {
      // line is free
      set[first_free].valid = 1;
      set[first_free].tag = tag;
      set[first_free].mru = mru_counter++;
    }
  }
}

/*
 * replayTrace - replays the given trace file against the cache
 */
void replayTrace(char *trace_fn) {
  char buf[1000];
  mem_addr_t addr = 0;
  unsigned int len = 0;
  char type;
  FILE *trace_fp = fopen(trace_fn, "r");

  if (!trace_fp) {
    fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
    exit(1);
  }

  while (fgets(buf, 1000, trace_fp) != NULL) {
    /* buf[Y] gives the Yth byte in the trace line */

    /* Read address and length from the trace using sscanf
       E.g. sscanf(buf+3, "%llx,%u", &addr, &len);
     */
    sscanf(buf, "%c", &type);
    if (type == ' ') {
      sscanf(buf + 1, "%c", &type);
    }
    switch (type) {
      case 'I':
        break;
      case 'L':
      case 'S':
      case 'M':
        sscanf(buf + 3, "%llx,%u", &addr, &len);
        break;
    }
    /*
     *    ACCESS THE CACHE, i.e. CALL accessData
     *    Be careful to handle 'M' accesses
     */
    if (verbosity) printf("%c %llx,%u ", type, addr, len);
    switch (type) {
      case 'M':
        accessData(addr);
      case 'L':
      case 'S':
        accessData(addr);
        break;
    }
    if (verbosity) printf("\n");
  }

  fclose(trace_fp);
}

/*
 * printUsage - Print usage info
 */
void printUsage(char *argv[]) {
  printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
  printf("Options:\n");
  printf("  -h         Print this help message.\n");
  printf("  -v         Optional verbose flag.\n");
  printf("  -s <num>   Number of set index bits.\n");
  printf("  -E <num>   Number of lines per set.\n");
  printf("  -b <num>   Number of block offset bits.\n");
  printf("  -t <file>  Trace file.\n");
  printf("\nExamples:\n");
  printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
  printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
  exit(0);
}

/*
 * main - Main routine
 */
int main(int argc, char *argv[]) {
  char c;

  while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1) {
    switch (c) {
      case 's':
        s = atoi(optarg);
        break;
      case 'E':
        E = atoi(optarg);
        break;
      case 'b':
        b = atoi(optarg);
        break;
      case 't':
        trace_file = optarg;
        break;
      case 'v':
        verbosity = 1;
        break;
      case 'h':
        printUsage(argv);
        exit(0);
      default:
        printUsage(argv);
        exit(1);
    }
  }

  /* Make sure that all required command line args were specified */
  if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
    printf("%s: Missing required command line argument\n", argv[0]);
    printUsage(argv);
    exit(1);
  }

  /* Compute S, E and B from command line args */
  // S =  ?
  // B =  ?
  S = 1 << s;
  B = 1 << b;

  /* Initialize cache */
  initCache();

#ifdef DEBUG_ON
  printf("DEBUG: S:%u E:%u B:%u trace:%s\n", S, E, B, trace_file);
  printf("DEBUG: set_index_mask: %llu\n", set_index_mask);
#endif

  /* Read the trace and access the cache */
  replayTrace(trace_file);

  /* Free allocated memory */
  freeCache();

  /* Output the hit and miss statistics for the autograder */
  printSummary(hit_count, miss_count, eviction_count);
  return 0;
}

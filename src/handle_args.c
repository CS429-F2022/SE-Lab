/**************************************************************************
 * STUDENTS: DO NOT MODIFY.
 * 
 * C S 429 architecture emulator
 * 
 * handle_args.c - Module for handling command-line arguments.
 * 
 * Copyright (c) 2022. S. Chatterjee. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include <unistd.h>
#include "archsim.h"

static char printbuf[BUF_LEN];

int s, b, E, d;

void handle_args(int argc, char **argv) {
    int option;
    infile = stdin;
    outfile = stdout;
    errfile = stderr;

    while ((option = getopt(argc, argv, "i:o:v:s:b:E:d:")) != -1) {
        switch(option) {
            case 'i':
                infile_name = optarg;
                break;
            case 'o':
                if ((outfile = fopen(optarg, "w")) == NULL) {
                    assert(strlen(optarg) < BUF_LEN);
                    sprintf(printbuf, "failed to open output file %s", optarg);
                    logging(LOG_FATAL, printbuf);
                    return;
                }
                break;
            case 'v':
                sprintf(printbuf, "Verbose debug logging enabled.");
                logging(LOG_INFO, printbuf);
                switch (*optarg) {
                    case '0':
                        debug_level = 0;
                        break;
                    case '1':
                        debug_level = 1;
                        break;
                    case '2':
                        debug_level = 2;
                        break;
                    default:
                        sprintf(printbuf, "Invalid logging level, options are 1 and 2. Defaulting to 1.");
                        logging(LOG_INFO, printbuf);
                        debug_level = 1;
                        break;
                }

                sprintf(printbuf, "Logging at level %d", debug_level);
                logging(LOG_INFO, printbuf);
                
                break;
#ifdef CACHE
            case 's':
                s = atoi(optarg);
            case 'b':
                b = atoi(optarg);
            case 'E':
                E = atoi(optarg);
            case 'd':
                d = atoi(optarg);
#endif
            default:
                sprintf(printbuf, "Ignoring unknown option %c", optopt);
                logging(LOG_INFO, printbuf);
                break;
        }
    }
    for(; optind < argc; optind++) { // when some extra arguments are passed
        assert(strlen(argv[optind])< BUF_LEN);
        sprintf(printbuf, "Ignoring extra argument %s", argv[optind]);
        logging(LOG_INFO, printbuf);
    }
//    if (infile == NULL) infile = stdin;
    return;
}

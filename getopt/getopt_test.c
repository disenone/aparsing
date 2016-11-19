// test getopt

#include <getopt.h>
#include <stdio.h>
#include <string.h>

static struct option long_options[] =
{
    {"add", required_argument, 0, 'a'},
    {"append", no_argument, 0, 0},
    {"delete", required_argument, 0, 0},
    {"verbose", no_argument, 0, 0},
    {"create", no_argument, 0, 0},
    {"file", required_argument, 0, 0},
    {"help", no_argument, 0, 0},
    {0, 0, 0, 0}
};

static char simple_options[] = "a:bc:d:0123456789";

void usage()
{
    char buf[1024] = "\0";
    struct option *op = long_options;
    while(op->name)
    {
        char opbuf[128] = "\0";
        if(op->has_arg)
            sprintf(opbuf, "[--%s arg] ", op->name);
        else
            sprintf(opbuf, "[--%s] ", op->name);

        strncat(buf, opbuf, sizeof(buf));
        op += 1;
    }

    printf("usage: getopt_test [-%s] %s", simple_options, buf);
}

int main (int argc, char **argv)
{
    if(argc == 1)
    {
        usage();
        return 0;
    }

    int c;
    int digit_optind = 0;

    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int longindex = -1;

        c = getopt_long(argc, argv, simple_options, long_options, &longindex);
        if (c == -1)
        break;

        switch (c)
        {
            // long option
            case 0:
                if(long_options[longindex].has_arg == required_argument)
                {
                    printf("option '%s' with value '%s'\n", long_options[longindex].name, optarg);
                }
                else
                {
                    printf("option '%s'\n", long_options[longindex].name);
                }

                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (digit_optind != 0 && digit_optind != this_option_optind)
                    printf ("digits occur in two different argv-elements.\n");

                digit_optind = this_option_optind;
                printf ("option %c\n", c);
                break;

            case 'a':
                printf ("option a with value '%s'\n", optarg);
                break;

            case 'b':
                printf ("option b\n");
                break;

            case 'c':
                printf ("option c with value '%s'\n", optarg);
                break;

            case '?':
                break;

            default:
                printf ("?? getopt returned character code 0%o ??\n", c);
        } // switch
    } // while

    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
        printf ("%s ", argv[optind++]);
        printf ("\n");
    }

    return 0;
}


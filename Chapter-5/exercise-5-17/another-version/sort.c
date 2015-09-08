#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define AUTHOR "Robert Taylor"
#define CREATION_DATE "May, 2014"
#define LAST_UPDATE __DATE__ /* last date that binary was compiled */
static char *program_name;
/* My solution to Exercise 5-17 
 * of the C Programming Language (second edition)
 * by Brian W. Kernighan 
 * and Denis M. Ritchie
 *
 * To compile:
 * gcc -Os -Wall -s -o sort sort.c
 *
 * For help:
 * ./sort --h
 */

#define MAXLEN 1000 /* max length of any input line */
#define MAXLINES 500000 /* max # of lines to be sorted */
#define ALLOCSIZE 15000000 /* size of space to store lines */
#define NUMDIGITS 5 /* 4 digits plus the '\0' terminator
		     for input of numeric option values */
static char *lineptr[MAXLINES]; /* pointers to text lines */

static int getLine(char *s, int lim);
static int readlines(char *lineptr[], int nlines);
static void writelines(char *lineptr[], int nlines);
static void my_qsort(void *lineptr[], int left, int right, int (*comp)(const void*, const void*));
static int numcmp(const char *s1, const char *s2);
static int str_cmp(const char *s1, const char *s2);
static int compare(const char *s1, const char *s2);
static void swap(void *v[], int i, int j);
static int parse_args(int argc, char *argv[]);
static void recordinit(void); /* initialize each new field record */
static void dump_field_records(void); /* dump field records for analysis */
static void print_help(void); /* provide help on program usage */
static void substr(char *s1, const char *s2, int p1, int p2);
static void use_record(const char *s1, const char *s2, int n);
static void substr_delim(char *s1, const char *s2, int n);
static void dump_parsed_fields(char *lineptr[], int nlines);
static void dump_parsed_fields_xml(char *lineptr[], int nlines);

static int reverse = 0; /* 1 if sort in reverse order */
static int fold = 0; /* if fold = 1 it means case insensitive sort */
static int directory = 0; /* if directory = 1 ignore invalid characters */
static int numeric = 0; /* 1 if numeric sort */
static int num_lines_to_ignore = 0; /* ignore sorting the first n lines */
static char line1[MAXLEN];/* two lines for comparison, possibly substrings */
static char line2[MAXLEN];/* of the lines read */
static int sample_field_parse = 0; /* if 1, output the data from the fields
				      defined, one field per line, no sorting
				      is performed in this case*/
static int dump_as_xml = 0; /* when dumping parsed fields, format as xml data */
static int include_line = 0; /* when dumping fields, output source line 
				as well. */

/* logic to handle field records */
#define RECORDSIZE		9 /* number of values in the record */
#define RECORDTYPE		0 /* offset within a record to the record type */
#define FIELDSTART		1 /* start of field as offset into the line */
#define FIELDEND			2 /* end of field as offset into the line */
#define FIELDDELIM		1 /* also could store delim char here */
#define FIELDQUOTE		2 /* also could store quote char here */
#define FIELDNUMERIC	3 /* numeric sort for this field? */
#define FIELDREV			4 /* sort this field in reverse order? */
#define FIELDFOLD			5 /* fold (case insensitive) sort for this field? */
#define FIELDDIR			6 /* directory sort for this field? */
#define FIELDOFFSET		7 /* offset of field (counting from left to right) */
#define FIELDESC			8 /* escape character typically \ */

#define RECORDTYPEOFFSET 0 /* 0 if we are considering offsets into the line */
#define RECORDTYPEDELIM 1 /* 1 if we are considering parsing delimited type data */

#define RECORDNUM 100 /* maximum number of field records */

#define MAXFIELDS RECORDNUM * RECORDSIZE /* room to hold RECORDNUM field records */
static int fieldinfo[MAXFIELDS]; /* array to hold field record data */
static int numfields = 0; /* number of fields for which options were read */
static int curfield = 0; /* field we are currently considering */

/* variables used to carry over default/last-set values between one field
 * record and the next */
static int recordtype = RECORDTYPEOFFSET; /* offsets within lines */
static int field_delim = ','; /* delimiter between fields */
static int field_quote = '"'; /* quote character */
static int field_esc = '\\'; /* for escaping field_delim, field_quote
			        field_esc etc.*/

/* Sort input lines... sorts lines of input data (STDIN) and sends sorted
 * lines to output (STDOUT). Run with --h to see help.
 */

int main(int argc, char *argv[])
{
	int nlines; /* number of input lines read */
	recordinit();/* initialize the first field record */
	if (parse_args(argc, argv)) /* parse command line arguments */
		return 1;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
		if (sample_field_parse){
			if (dump_as_xml){
				dump_parsed_fields_xml(lineptr, nlines);		
			} else {
				dump_parsed_fields(lineptr, nlines);
			}
		} else {
			my_qsort((void **) lineptr, 0, nlines -1, 
					(int (*)(const void*,const void*))compare);
			writelines(lineptr, nlines);
		}
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}
/* parse_args: create field records from command line arguments */
static int parse_args(int argc, char *argv[])
{
	int i = 0; /* index into each argument string */
	int j = 0; /* index into numstring */
	int no_room = 0; /* if 1 stop collecting field records */
	int temp = 0; /* temporary storage of numbers */
	char numstring[NUMDIGITS];/* space to store passed number as a string */
	program_name = &(*argv)[0];
	while (--argc > 0){
		if (no_room)
			break; /* stop collecting field records */
                ++argv; /* look at the next command line argument */
		i = 0;
		j = 0;
		if (((*argv)[i] == ':') || ((*argv)[i] == ',')){
			recordinit();
			if (numfields >= RECORDNUM)
				break; /* no room to store more field records */
			continue;
		}
		if ((*argv)[i] == '-'){
			while ((*argv)[i] != '\0'){ /* allow for mashed together options */
				if (no_room)
					break; /* stop collecting field records */
				i++;
				switch((*argv)[i]){
				case 'n':
					numeric = 1;
					fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDNUMERIC] = numeric;	
					break;
				case 'r':
					reverse = 1;
					fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDREV] = reverse;
					break;
				case 'f':
					fold = 1;
					fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDFOLD] = fold;
					break;
				case 'd':
					directory = 1;
					fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDDIR] = directory;
					break;
				case 's':
					i++;
					j = 0;
					while ((*argv)[i] != '\0' && isdigit((*argv)[i])){
						numstring[j++] = (*argv)[i++];
						if (j >= NUMDIGITS) /* do not read too many digits */
							break;
					}
					i--;
					numstring[j] = '\0';
					temp = atoi(numstring); /* offset starts at 0 for first char */
					if (temp >= MAXLEN){
						printf("ERROR: The value provided for the s option"
								" is too large\n");
						return 1;
					} else {
						fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDSTART] = temp;
					}
					break;
				case 'e':
					i++;
					j = 0;
					/* slight alteration to support passing a negative number */
					while ((*argv)[i] != '\0' && (isdigit((*argv)[i]) || (*argv)[i] == '-')){
						numstring[j++] = (*argv)[i++];
						if (j >= NUMDIGITS) /* do not read too many digits */
							break;
					}
					i--;
					numstring[j] = '\0';
					temp = atoi(numstring);
					if (temp >= MAXLEN){
						printf("ERROR: The value provided for the e option"
								" is too large\n");
						return 1;
					} else {
						fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDEND] = temp;
					}
					break;
				case 'o':
					i++;
					j = 0;
					while ((*argv)[i] != '\0' && isdigit((*argv)[i])){
						numstring[j++] = (*argv)[i++];
						if (j >= NUMDIGITS) /* do not read too many digits */
							break;
					}
					i--;
					numstring[j] = '\0';
					temp = atoi(numstring);
					if (temp >= MAXLEN){
						printf("ERROR: The value provided for the o option"
								" is too large\n");
						return 1;
					} else {
						fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDOFFSET] = temp;
					}
					break;
				case 't':
					i++;
					j = 0;
					while ((*argv)[i] != '\0' && isdigit((*argv)[i])){
						numstring[j++] = (*argv)[i++];
						if (j >= NUMDIGITS) /* do not read too many digits */
							break;
					}
					i--;
					numstring[j] = '\0';
					temp = atoi(numstring);
					if (temp != RECORDTYPEOFFSET && temp != RECORDTYPEDELIM){
						printf("ERROR: This is an ivalid value for the"
								" t option\n");
						return 1;
					} else {
						recordtype = temp;
						fieldinfo[((numfields - 1) * RECORDSIZE) + RECORDTYPE] = recordtype;
						if (recordtype == RECORDTYPEDELIM){
							if (fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDDELIM] == 0){
								fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDDELIM] = field_delim;
							}
							if (fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDQUOTE] <= 0){
								fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDQUOTE] = field_quote;
							}
							if (fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDESC] == 0){
								fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDESC] =	field_esc;
							}
						}
					}
					break;
				case 'm':
					i++;
					if ((*argv)[i] == '1'){
						i++;
						if ((*argv)[i] != '\0'){
							if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'P'){
								field_delim = ' ';
								i++;
							} else if ((*argv)[i] == 'T' && (*argv)[i + 1] == 'A'){
								field_delim = '\t';
								i++;
							} else if ((*argv)[i] == 'V' && (*argv)[i + 1] == 'E'){
								field_delim = '|';
								i++;
							} else if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'E'){
								field_delim = ';';
								i++;
							} else if ((*argv)[i] == 'B' && (*argv)[i + 1] == 'A'){
								field_delim = '\\';
								i++;
							} else if ((*argv)[i] == 'P' && (*argv)[i + 1] == 'E'){
								field_delim = '%';
								i++;
							} else if ((*argv)[i] == 'D' && (*argv)[i + 1] == 'O'){
								field_delim = '$';
								i++;
							} else if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'Q'){
								field_delim = '\'';
								i++;
							} else if ((*argv)[i] == 'D' && (*argv)[i + 1] == 'Q'){
								field_delim = '"';
								i++;
							} else {
								field_delim = (*argv)[i];
							}
							fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDDELIM] = field_delim;
						} else {
							printf("ERROR: Please provide the field delimiter character"
									" immediately following the -m1 option\n");
							return 1;
						}
					} else if ((*argv)[i] == '2'){
						i++;
						if ((*argv)[i] != '\0'){
							if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'P'){
								field_quote = ' ';
								i++;
							} else if ((*argv)[i] == 'T' && (*argv)[i + 1] == 'A'){
								field_quote = '\t';
								i++;
							} else if ((*argv)[i] == 'V' && (*argv)[i + 1] == 'E'){
								field_quote = '|';
								i++;
							} else if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'E'){
								field_quote = ';';
								i++;
							} else if ((*argv)[i] == 'B' && (*argv)[i + 1] == 'A'){
								field_quote = '\\';
								i++;
							} else if ((*argv)[i] == 'P' && (*argv)[i + 1] == 'E'){
								field_quote = '%';
								i++;
							} else if ((*argv)[i] == 'D' && (*argv)[i + 1] == 'O'){
								field_quote = '$';
								i++;
							} else if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'Q'){
								field_quote = '\'';
								i++;
							} else if ((*argv)[i] == 'D' && (*argv)[i + 1] == 'Q'){
								field_quote = '"';
								i++;
							} else if ((*argv)[i] == 'N' && (*argv)[i + 1] == 'U'){
								field_quote = '\0';
								i++;
							} else {
								field_quote = (*argv)[i];
							}
							fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDQUOTE] = field_quote;
						} else {
							printf("ERROR: Please provide the field quote character"
									" immediately following the -m2 option\n");
							return 1;
						}
					} else if ((*argv)[i] == '3'){
						i++;
						if ((*argv)[i] != '\0'){
							if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'P'){
								field_esc = ' ';
								i++;
							} else if ((*argv)[i] == 'T' && (*argv)[i + 1] == 'A'){
								field_esc = '\t';
								i++;
							} else if ((*argv)[i] == 'V' && (*argv)[i + 1] == 'E'){
								field_esc = '|';
								i++;
							} else if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'E'){
								field_esc = ';';
								i++;
							} else if ((*argv)[i] == 'B' && (*argv)[i + 1] == 'A'){
								field_esc = '\\';
								i++;
							} else if ((*argv)[i] == 'P' && (*argv)[i + 1] == 'E'){
								field_esc = '%';
								i++;
							} else if ((*argv)[i] == 'D' && (*argv)[i + 1] == 'O'){
								field_esc = '$';
								i++;
							} else if ((*argv)[i] == 'S' && (*argv)[i + 1] == 'Q'){
								field_esc = '\'';
								i++;
							} else if ((*argv)[i] == 'D' && (*argv)[i + 1] == 'Q'){
								field_esc = '"';
								i++;
							} else if ((*argv)[i] == 'N' && (*argv)[i + 1] == 'U'){
								field_esc = '\0';
								i++;
							} else {
								field_esc = (*argv)[i];
							}
							fieldinfo[((numfields - 1) * RECORDSIZE) + FIELDESC] = field_esc;
						} else {
							printf("ERROR: Please provide the desired escape character"
									" immediately following the -m3 option\n");
							return 1;
						}
					}
					break;
				case 'i':
					i++;
					j = 0;
					while ((*argv)[i] != '\0' && isdigit((*argv)[i])){
						numstring[j++] = (*argv)[i++];
						if (j >= NUMDIGITS) /* do not read too many digits */
							break;
					}
					i--;
					numstring[j] = '\0';
					num_lines_to_ignore = atoi(numstring);
					break;
				case '-':
					i++;
					/* --help or --HELP or --h or --H */
					if ((*argv)[i] == 'h' || (*argv)[i] == 'H'){
						print_help();
						return 1; /* exit */
					}
					/* --dump_records or --DUMP_RECORDS or --d or --D etc. */
					if ((*argv)[i] == 'd' || (*argv)[i] == 'D'){
						dump_field_records();
						return 1; /* exit */
					}
					/* --sample_field_parse or --SAMPLE_FIELD_PARSE or --s or --S */
					if ((*argv)[i] == 's' || (*argv)[i] == 'S'){
						sample_field_parse = 1;
						break; /* in case we add more ifs below */
					}
					/* --xml or --XML or --x or --X */
					if ((*argv)[i] == 'x' || (*argv)[i] == 'X'){
						dump_as_xml = 1;
						break; /* in case we add more ifs below */
					}
					/* --include_line or --INCLUDE_LINE or --i or --I */
					if ((*argv)[i] == 'i' || (*argv)[i] == 'I'){
						include_line = 1;
						break; /* in case we add more ifs below */
					}
					break;
				case ':':
					recordinit();
					if (numfields >= RECORDNUM){
						no_room = 1; /* no room to store more field records */
					}
					break;
				case ',':
					recordinit();
					if (numfields >= RECORDNUM){
						no_room = 1; /* no room to store more field records */
					}
					break;
				default:
					break;
				}
			}
		}
	}
	return 0;
}

/* Initialize some values for each new field record added */
static void recordinit(void)
{
	fieldinfo[(numfields * RECORDSIZE) + RECORDTYPE] = recordtype;
	if (recordtype){
		fieldinfo[(numfields * RECORDSIZE) + FIELDDELIM] = field_delim;
		fieldinfo[(numfields * RECORDSIZE) + FIELDQUOTE] = field_quote;
	} else {
		fieldinfo[(numfields * RECORDSIZE) + FIELDSTART] = 0;
		fieldinfo[(numfields * RECORDSIZE) + FIELDEND] = -1;
	}
	fieldinfo[(numfields * RECORDSIZE) + FIELDNUMERIC] = 0;
	fieldinfo[(numfields * RECORDSIZE) + FIELDREV] = 0;
	fieldinfo[(numfields * RECORDSIZE) + FIELDFOLD] = 0;
	fieldinfo[(numfields * RECORDSIZE) + FIELDDIR] = 0;
	fieldinfo[(numfields * RECORDSIZE) + FIELDOFFSET] = 0;
	fieldinfo[(numfields * RECORDSIZE) + FIELDESC] = field_esc;
	numfields++;
	return;
}

/* use_record: Setup to use the values from the specified 
 * field record.
 */
static void use_record(const char *s1, const char *s2, int n)
{
	int fieldnum, p1, p2;
	/* set some sourcefile scoped global variables */
	recordtype = fieldinfo[(n * RECORDSIZE) + RECORDTYPE];
	numeric = fieldinfo[(n * RECORDSIZE) + FIELDNUMERIC];
	reverse = fieldinfo[(n * RECORDSIZE) + FIELDREV];
	fold = fieldinfo[(n * RECORDSIZE) + FIELDFOLD];
	directory = fieldinfo[(n * RECORDSIZE) + FIELDDIR];
	/* set type specific variables and initialize line1 and line2 */
	if (recordtype){
		field_delim = fieldinfo[(n * RECORDSIZE) + FIELDDELIM];
		field_quote = fieldinfo[(n * RECORDSIZE) + FIELDQUOTE];
		fieldnum = fieldinfo[(n * RECORDSIZE) + FIELDOFFSET];
		field_esc = fieldinfo[(n * RECORDSIZE) + FIELDESC];
		substr_delim(line1, s1, fieldnum);
		substr_delim(line2, s2, fieldnum);
	} else {
		p1 = fieldinfo[(n * RECORDSIZE) + FIELDSTART];
		p2 = fieldinfo[(n * RECORDSIZE) + FIELDEND];
		substr(line1, s1, p1, p2);
		substr(line2, s2, p1, p2);
	}
	//printf("line1 is %s line2 is %s\n", line1, line2);
	return;
}

/* my_qsort: sort v[left] ... v[right] into 
 * increasing or decreasing order depending on
 * the value of reverse.*/
static void my_qsort(void *v[], int left, int right,
		int (*comp)(const void*, const void*))
{
	int i, last;
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	my_qsort(v, left, last - 1, comp);
	my_qsort(v, last + 1, right, comp);
}
/* compare: Parent process for comparisons. I am able
 * to dynamically make decisions concerning whether numcmp 
 * or str_cmp should be called in here.
 * Whether you code the reverse logic here or in qsort, it
 * needs to support changing dynamically based on what field
 * record is currently loaded.
 */
static int compare(const char *s1, const char *s2)
{
	int retval;
	curfield = 0;
	do{
		use_record(s1, s2, curfield);
		if (numeric)
			retval = numcmp(line1, line2);
		else
			retval = str_cmp(line1, line2);
		if (retval == 0){
			curfield++;
		}
	} while (retval == 0 && curfield < numfields);
	if (reverse){
		if (retval > 0){
			retval = -1;
		} else if (retval < 0){
			retval = 1;
		}
	}
	return retval;
}

/* numcmp: compare s1 and s2 numerically */
static int numcmp(const char *s1, const char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}
/* str_cmp: replaces standard library strcmp to add
 * more features for types of comparison. Supports
 * case insensitive comparison for example. Supports
 * ignoring invalid characters. Borrowed version of this
 * function by Barrett Drawdy as it was cleaner than 
 * mine.
 */
static int str_cmp(const char *s1, const char *s2)
{
	if (directory){
		while (!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
			++s1; /* ignore bad characters */
		while (!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
			++s2; /* ignore bad characters */
	}
	while (fold ? (tolower(*s1) == tolower(*s2)) : (*s1 == *s2)){
		if (*s1 == '\0')
			return 0;
		++s1;
		++s2;
		if (directory){
			while (!isdigit(*s1) && !isalpha(*s1) && !isspace(*s1) && *s1)
				++s1; /* ignore bad characters */
			while (!isdigit(*s2) && !isalpha(*s2) && !isspace(*s2) && *s2)
				++s2; /* ignore bad characters */
		}
	}
	return fold ? (tolower(*s1) - tolower(*s2)) : (*s1 - *s2);
}
/* copy characters from offset p1 to p2 (inclusive) of s2 to s1 */
static void substr(char *s1, const char *s2, int p1, int p2)
{
	int i, j;
	int length = strlen(s2);
	if (p1 + 1 >= length){ /* desired field is missing from line */
		s1[0] = '\0';
		return;
	}
	if (p2 < p1)
		p2 = length;
	/* if p2 is too big we will simply set s1 to whatever is left */
	for (i = p1, j = 0; i <= p2 && s2[i] != '\0'; i++, j++)
		s1[j] = s2[i];
	s1[j] = '\0';
	return;
}

/* substr_delim: copy characters from the delimited field number n of
 * s2 to s1.
 * field_delim is counted if it is outside of a pair of field_quote 
 * (a quoted field), and not escaped with a field_esc. Otherwise
 * it is just copied as part of the data.
 *
 * If field_esc is followed by field_esc, field_delim, or field_quote
 * it is skipped and the following character is copied as part of
 * the data. Otherwise field_esc is just copied as part of the data.
 *
 * field_quote only has special meaning if it is at the very beginning
 * of a field, or if it is at the very end of a field and follows a 
 * field_quote that was at the very beginning of a field. If field_quote
 * is seen in the middle of the field it is just considered part of the
 * data.
 *
 * This logic should allow substr_delim to work with data that has been
 * prepared using strict quoting and escaping rules, while allowing
 * the most flexibility for handling data that was not strictly quoted
 * and escaped.
 *
 */
static void substr_delim(char *s1, const char *s2, int n)
{
	int delim_count = 0; /* the first field is number 0 */
	int field_quote_on = 0; /* are we inside of quotes? */
	/* i, j,  indexes into s2 and s1 */
	int i = 0;
	int j = 0;
	while (s2[i] != '\0'){
		if (i == 0 && s2[i] == field_quote){
			field_quote_on = 1;
			++i;
			continue;
		}
		if (s2[i] == field_esc){
			if (s2[i + 1] == field_quote ||
					s2[i + 1] == field_delim ||
					s2[i + 1] == field_esc){
				++i; /* skip this field_esc and copy the next char */
	                        s1[j++] = s2[i++];
	                        continue;
			}
		}
		if (field_quote_on == 1 && 
				s2[i] == field_quote &&
				(s2[i + 1] == field_delim || s2[i + 1] == '\0')){
			field_quote_on = 0;
			++i;
			continue;
		}
		if (field_quote_on == 0 && s2[i] == field_delim){
			++delim_count;
			++i;
			if (s2[i] == field_quote){
				field_quote_on = 1;
				++i;
			}
			continue;
		}
		if (delim_count == n){
			s1[j++] = s2[i];
		} else if (delim_count > n){
			break;
		}
		++i;
	}
	s1[j] = '\0';
	return;
}

/* swap pointers: void * is used so that swap can work on any pointer type.
 * Any pointer can be cast to void * and back again without loss of 
 * information
 */
static void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

static char *alloc(int);
/* readlines: read input lines */
static int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = getLine(line, MAXLEN)) > 0)
		if (num_lines_to_ignore){
			if (!sample_field_parse) /* if we are sampling fields we may not
						    want the ignored lines output */
				printf("%s", line);
			--num_lines_to_ignore;
		} else {
			if(nlines >= maxlines || (p = alloc(len)) == NULL)
				return -1;
			else {
				line[len - 1] = '\0'; /* delete newline */
				strcpy(p, line);
				lineptr[nlines++] = p;
			}
		}
	return nlines;
}

/* writelines: write output lines */
static void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* getLine: read a line into s, return length */
static int getLine(char *s, int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */
static char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n){ /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} else {
		return NULL;
	}
}


/* dump_parsed_fields: Apply the field position/offset/delimiters
 * defined and dump the resulting field contents, one field per
 * line, repeat for all input lines. Useful for debugging how
 * the field position and contents are identified for the sort
 */
static void dump_parsed_fields(char *lineptr[], int nlines)
{
	int n = 0;
	int i = 1;
	int fieldnum, p1, p2;
	while (i <= nlines){
		if (include_line)
			printf("%s\n", *lineptr);
		n = 0;
		do{
			recordtype = fieldinfo[(n * RECORDSIZE) + RECORDTYPE];
			if (recordtype){
				field_delim = fieldinfo[(n * RECORDSIZE) + FIELDDELIM];
				field_quote = fieldinfo[(n * RECORDSIZE) + FIELDQUOTE];
				fieldnum = fieldinfo[(n * RECORDSIZE) + FIELDOFFSET];
				field_esc = fieldinfo[(n * RECORDSIZE) + FIELDESC];
				substr_delim(line1, *lineptr, fieldnum);
			} else {
				p1 = fieldinfo[(n * RECORDSIZE) + FIELDSTART];
				p2 = fieldinfo[(n * RECORDSIZE) + FIELDEND];
				substr(line1, *lineptr, p1, p2);
			}
			printf("%s\n", line1);/* output the parsed field */
			n++;
		} while (n < numfields);
		lineptr++;
		i++;
	}
	return;
}
/* dump_parsed_fields_xml: Apply the field position/offset/delimiters
 * defined and dump the resulting field contents, in an xml format.
 */
static void dump_parsed_fields_xml(char *lineptr[], int nlines)
{
	int n = 0;
	int i = 1;
	int fieldnum, p1, p2;
	printf("<root>\n");
	while (i <= nlines){
		printf("\t<line%d>", i);
		n = 0;
		do{
			recordtype = fieldinfo[(n * RECORDSIZE) + RECORDTYPE];
			if (recordtype){
				field_delim = fieldinfo[(n * RECORDSIZE) + FIELDDELIM];
				field_quote = fieldinfo[(n * RECORDSIZE) + FIELDQUOTE];
				fieldnum = fieldinfo[(n * RECORDSIZE) + FIELDOFFSET];
				field_esc = fieldinfo[(n * RECORDSIZE) + FIELDESC];
				substr_delim(line1, *lineptr, fieldnum);
			} else {
				p1 = fieldinfo[(n * RECORDSIZE) + FIELDSTART];
				p2 = fieldinfo[(n * RECORDSIZE) + FIELDEND];
				substr(line1, *lineptr, p1, p2);
			}
			printf("<f%d>%s</f%d>", n, line1, n);/* output the parsed field */
			n++;
		} while (n < numfields);
		printf("</line%d>\n", i);
		lineptr++;
		i++;
	}
	printf("</root>\n");
	return;
}

/* dump_field_records: for debugging purposes you may wish to
 * dump all the field records that have been stored
 */
static void dump_field_records(void)
{
	int i;
	int c;
	printf("\n---------------------------| Field Record Dump |-----------------------------\n");
	printf("Record	| COL0	| COL1	| COL2	| COL3	| COL4	| COL5	| COL6	| COL7	| COL8\n");
	for (i = 0; i < numfields; i++){
		printf(" %d\t", i);
		printf("| %d\t", fieldinfo[(i * RECORDSIZE) + RECORDTYPE]);
		if (fieldinfo[(i * RECORDSIZE) + RECORDTYPE] == RECORDTYPEOFFSET){
			printf("| %d\t", fieldinfo[(i * RECORDSIZE) + FIELDSTART]);
			printf("| %d\t", fieldinfo[(i * RECORDSIZE) + FIELDEND]);
		} else {
			c = fieldinfo[(i * RECORDSIZE) + FIELDDELIM];
			if (c == '\t'){
				printf("| TAB\t");
			} else if (c == ' '){
				printf("| SPACE\t");
			} else {
				printf("| %c\t", c);
			}
			c = fieldinfo[(i * RECORDSIZE) + FIELDQUOTE];
			if (c == '\t'){
				printf("| TAB\t");
			} else if (c == ' '){
				printf("| SPACE\t");
			} else if (c == '\0'){
				printf("| NULL\t");
			} else {
				printf("| %c\t", c);
			}
		}
		printf("| %d\t",fieldinfo[(i * RECORDSIZE) + FIELDNUMERIC]);
		printf("| %d\t",fieldinfo[(i * RECORDSIZE) + FIELDREV]);
		printf("| %d\t",fieldinfo[(i * RECORDSIZE) + FIELDFOLD]);
		printf("| %d\t",fieldinfo[(i * RECORDSIZE) + FIELDDIR]);
		printf("| %d\t",fieldinfo[(i * RECORDSIZE) + FIELDOFFSET]);
		c = fieldinfo[(i * RECORDSIZE) + FIELDESC];
		if (c == '\t'){
			printf("| TAB\t");
		} else if (c == ' '){
			printf("| SPACE\t");
		} else if (c == '\0'){
			printf("| NULL\t");
		} else {
			printf("| %c\t", c);
		}		
	}
	printf("\nWhere COL0 = RECORDTYPE, COL1 = FIELDSTART or FIELDDELIM\n");
	printf("COL2 = FIELDEND or FIELDQUOTE, COL3 = FIELDNUMERIC, COL4 = FIELDREV\n");
	printf("COL5 = FIELDFOLD, COL6 = FIELDDIR, COL7 = FIELDOFFSET, COL8 = FIELDESC\n\n");	
	printf("RECORDTYPE is set by -t\n");
	printf("FIELDSTART is set by -s\n");
	printf("FIELDDELIM is set by -m1\n");
	printf("FIELDEND is set by -e\n");
	printf("FIELDQUOTE is set by -m2\n");
	printf("FIELDNUMERIC is set by -n\n");
	printf("FIELDREV is set by -r\n");
	printf("FIELDFOLD is set by -f\n");
	printf("FIELDDIR is set by -d\n");
	printf("FIELDOFFSET is set by -o\n");
	printf("FIELDESC is set by -m3\n");
	printf("For more info use the --h (help) option.\n\n");
	return;
}

static void print_help(void)
{
	printf("Program: %s\n", program_name);
	printf("Author: %s\n", AUTHOR);
	printf("Creation Date: %s\n", CREATION_DATE);
	printf("Last Update: %s\n", LAST_UPDATE);
	printf("usage: cat sourcefile | ./sort -options [> outputfile]\n\n");
	printf("This sort program expects input from STDIN (output from cat for\n");
	printf("example) and sends output to STDOUT (the screen for example).\n\n");
	printf("If you fail to provide input from cat or similar you will be in\n");
	printf("an interactive input mode. This means you can enter lines using\n");
	printf("the keyboard and press CTRL-D on an empty line to process them.\n\n");
	printf("Pressing CTRL-C will abort the program.\n\n");
	printf("%s is quite sophisticated, permitting you to break a line\n", program_name);
	printf("into fields that can have separate sorting options applied to\n");
	printf("them.\n\n");
	printf("It is always lines that are sorted, not the fields within the line.\n");
	printf("However defining fields and specifying sort options for them permits\n");
	printf("sophisticated sorting behavior for the lines.\n\n");
	printf("You do not need to provide sorting options for every field on a line.\n");
	printf("Only specify those fields that have the data that you wish to use\n");
	printf("to sort the lines.\n\n");
	printf("The order that you specify the fields on the command line is the order\n");
	printf("of precedence for sorting.\n\n");
	printf("For example...\n");
	printf("if one field has a username and another has a date, you can sort\n");
	printf("by increasing (ascending) username and then by decreasing (descending)\n");
	printf("date simply by specifying those 2 fields and their sort options on the\n");
	printf("command line. Specify the username field first and the date field\n");
	printf("next. The way the logic works is only if there are equal values\n");
	printf("found in the first field, is the second field examined, and only if\n");
	printf("there are equal values found in the second field is the third field\n");
	printf("examined, and so on until either a difference is found between the\n");
	printf("two fields in question, or we run out of fields that we have defined\n");
	printf("for sorting. If we run out of fields that we have defined for sorting\n");
	printf("and no difference has been found, the lines are considered equal.\n\n");
	printf("This sort program supports the use of up to %d fields with unique\n", RECORDNUM);
	printf("sort options permitted for each field. The data can have any number of\n");
	printf("fields, but you can only specify sort options for %d fields.\n", RECORDNUM);
	printf("Actually the data is limited in fields per line by the setting\n");
	printf("for the maximum line length of %d characters and the size of the fields.\n\n",MAXLEN);
	printf("The field definitions (size/location) along with the sort options\n");
	printf("are saved internally in records. There is a handy option that\n");
	printf("permits dumping these internal records so that you can evaluate\n");
	printf("how the program has interpreted the command line options that you\n");
	printf("have provided. Place this option --d (--dump_records) after all\n");
	printf("the options that you desire to audit have been specified on the command\n");
	printf("line.\n\n");
	printf("--d	dump field records, place after other options on the command line.\n");
	printf("	If you use this option the sort is not performed, this option is used\n");
	printf("	strictly for debugging your sort options that you have defined\n\n");
	printf("%s allows you to specify fields using character offsets, from the\n", program_name);
	printf("start of the line at position 0, or using delimiters and quote characters.\n");
	printf("Each field definition can optionally use either method.\n");
	printf("-t#	type of field definition, where # is %d for the character offset method\n", RECORDTYPEOFFSET);
	printf("	and %d for the delimited field method. This option should be listed\n", RECORDTYPEDELIM);
	printf("	first in the field definition, but inherits from left to right so\n");
	printf("	if all field definitions are of the same type it only needs to be\n");
	printf("	specified for the first field for example. The default is the\n");
	printf("	character offset method\n");
	printf("-s#	starting character position, where # is a number that is less than\n");
	printf("	the maximum line length of %d\n", MAXLEN);
	printf("-e#	ending character position, where # is a number that is less than\n");
	printf("	the maximum line length of %d\n", MAXLEN);
	printf("If you choose to use the character offset method of defining a field you must\n");
	printf("set -s and -e for each field to the correct offsets, sort will not check to\n");
	printf("see that you did.\n\n");
	printf("If you set -e to less than -s, it means that you want from -s to the end of\n");
	printf("the line. The default setting for sort is to use the character offset method\n");
	printf("and -s is set to 0 (the beginning) and -e is set to -1 (the rest of the line).\n");
	printf("Because of the special meaning of -e set to be less than -s, -e supports\n");
	printf("passing a negative number -e-1 for -1.\n\n");
	printf("The default delimiters for delimited data is to use a comma ',' to separate\n");
	printf("fields and to use double quotes '\"', to quote fields. The quotes surround the\n");
	printf("fields to indicate that any commas that are found within the fields can be\n");
	printf("ignored.\n\n");
	printf("In order to support the possibility of a double quote found within the data\n");
	printf("an escape character can be used and the default escape character is a\n");
	printf("backslash '\\'.\n\n");
	printf("In actuality, this program is coded to be more flexible than that. An escape\n");
	printf("character 'can' be used to escape the delimiter, the quote character or an\n");
	printf("escape character, either inside or outside of a quoted field. If the escape\n");
	printf("character is found in front of anything else it is considered part of the data.\n\n");
	printf("If the quote character is found anywhere besides the start or end of a field it\n");
	printf("is considered part of the data and as such, technically, does not need to be\n");
	printf("escaped. So this program should be able to handle data formatted according to a\n");
	printf("variety of specifications.\n\n");
	printf("If this is not enough, the quote and/or the escape character can also be\n");
	printf("disabled in cases where they are not required and yet may be found in the data\n");
	printf("(see the NU code below).\n\n");
	printf("You can define what characters to use to separate fields, to quote fields,\n");
	printf("and to escape quote characters.\n\n");
	printf("-m1n	field separator, where n is the desired character\n");
	printf("-m2n	quote character, where n is the desired character\n");
	printf("-m3n	escape character, where n is the desired escape character\n\n");
	printf("In the above 3 options instead of specifying the literal character desired\n");
	printf("as n you can use the following 2 letter (uppercase) codes:\n\n");
	printf("SP	to mean a SPACE\n");
	printf("TA	to mean a TAB\n");
	printf("VE	to mean a VERTICAL BAR '|'\n");
	printf("SE	to mean a SEMICOLON ';'\n");
	printf("BA	to mean a BACKSLASH '\\'\n");
	printf("PE	to mean a PERCENT SIGN '%%'\n");
	printf("DO	to mean a DOLLAR SIGN '$'\n");
	printf("SQ	to mean a SINGLE QUOTE '\n");
	printf("DQ	to mean a DOUBLE QUOTE \"\n\n");
	printf("NU	to mean NULL '\\0', is supported for the quote or escape character.\n");
	printf("	Since such a character will not be seen in the data (it is the string\n");
	printf("	terminator) it is used to disable the operation of the quote or escape\n");
	printf("	character if that is ever desired.\n\n");
	printf("When using the delimited field method to specify fields it is important to\n");
	printf("indicate which field in the data we are referring to. Counting from 0 for the\n");
	printf("leftmost field on a line you can indicate field numbers using the -o option.\n");
	printf("-o#	indicate which delimited field, where # is a number from 0 to however\n");
	printf("	many fields exist in the data\n\n");
	printf("Every new field record initializes -o to be 0, referring to the first field, if\n");
	printf("this is not the field you want you must set the -o option to the correct field\n");
	printf("number.\n\n");
	printf("Using either method of specifying a field, the character offset method or the\n");
	printf("delimited method, if a specified field does not exist in the line in question\n");
	printf("it is treated as an empty field. If a large number of lines are missing this\n");
	printf("field and it is the only sort field that you indicated the sort will be slow.\n");
	printf("Qsort does not like it when too many lines evaluate to be equal.\n\n");
	printf("Between field definitions, to indicate the start of a new field, you can use\n");
	printf("either a colon ':' or a comma ','. Be careful not to place a field separator at\n");
	printf("the beginning as by default it will indicate to use the entire line with the\n");
	printf("default sorting options as the first field for sorting.\n\n");
	printf("The sorting options are:\n\n");
	printf("-n	numeric sort, puts numbers in order of value\n");
	printf("-r	reverse the sort order, instead of increasing order it would be\n");
	printf("	decreasing order\n");
	printf("-f	fold upper and lower case together, or in other words do a case\n");
	printf("	insensitive sort\n");
	printf("-d	directory sort, this ignores any character that is not a letter,\n");
	printf("	number or space\n\n");
	printf("The default sort options are set to have all of these options off, which\n");
	printf("means punctuation characters, or other special characters have a sorting\n");
	printf("value, the sort is in increasing order, upper and lower case letters\n");
	printf("have different sorting values, 17 would be considered lower than 2\n");
	printf("(numeric value is not considered).\n\n");
	printf("Options can be specified individually on the command-line separated by\n");
	printf("spaces...\n");
	printf("cat sourcefile | ./sort -t1 -o1 -n , -o0 -f -d\n\n");
	printf("or they can be mashed together...\n");
	printf("cat sourcefile | ./sort -t1o1n,o0fd\n\n");
	printf("However do not put spaces between an option and its value. -s 99 is not\n");
	printf("an accepted parameter, the option should be indicated as -s99. Also the\n");
	printf("use of an equals sign '=' is not supported between an option and its\n");
	printf("value.\n\n");
	printf("Do not confuse the use of the -s (start) and -e (end) options together\n");
	printf("with the delimited field option. It will replace whatever is being used\n");
	printf("for the delimiter and quote character with whatever character happens to\n");
	printf("equal the numeric value you provide. If you really know what you are\n");
	printf("doing it can be useful, otherwise avoid it.\n\n");
	printf("There is an option to ignore the first x number of lines. You might use\n");
	printf("this option if your data includes a header line with column titles for\n");
	printf("example and you do not want this line sorted in with the data.\n");
	printf("-i#	ignore the first # of lines, where # is a number between 0 and 9999.\n");
	printf("	0 in this case has no logical meaning since we start counting lines\n");
	printf("	with 1 as the first line.\n\n");
	printf("A Sorting Example:\n");
	printf("cat sourcefile | ./sort -t1o1n,o0fd\n\n");
	printf("Means use the delimited field method (-t1), the primary sort field is the\n");
	printf("second field (o1), do a numerical sort on that field (n), if two identical\n");
	printf("numbers are found in the second field, look at the first field (o0), doing a\n");
	printf("case insensitive directory sort of the first field, decide the order for\n");
	printf("the two lines. The default delimiter, quote character, and escape character\n");
	printf("is used.\n\n");
	printf("If the sort appears to be excessively slow, it could be because the fields and\n");
	printf("options that you have selected result in too many lines that would have an\n");
	printf("equal sort order. I think this is a limitation of the qsort logic since\n");
	printf("specifying more fields and more options, so that the lines which evaluate\n");
	printf("to be equal are reduced, significantly speeds up the sort.\n\n");
	printf("A few additional options have been added to aid in debugging the\n");
	printf("specification of fields. You may find other uses for them as well. The option\n\n");
	printf("--s	for sample field parsing\n\n");
	printf("found anywhere in the options will signify that instead of sorting the input\n");
	printf("you want to output the data from the fields that you have indicated. This\n");
	printf("will assist you in debugging delimiters and offset etc. when specifying\n");
	printf("fields for delimited data, and identifying errors in character offset\n");
	printf("specification when using the character offset method of identifying fields.\n");
	printf("It can be most useful when analyzing one field specifier at a time as the\n");
	printf("fields will be dumped one field per line so as not to introduce new field\n");
	printf("separators to confuse the issue when identifying what data was exactly\n");
	printf("pulled.\n\n");
	printf("There is a further specifier that can be added to also dump the source line\n");
	printf("that the fields were pulled from\n\n");
	printf("--i	for include line with the field parse dump\n\n");
	printf("For assisting with debugging what is parsed when multiple fields are specified\n");
	printf("there is an option to format the fields into an xml document. No effort is made\n");
	printf("to escape invalid characters found in the data, the data is left as is.\n\n");
	printf("--x	format parsed fields into an xml document format\n\n");
	printf("If you specify to use the xml format, the --i option is ignored, there is no\n");
	printf("option to include the original line in the xml format. The field numbering\n");
	printf("used in the xml output is not the number of the field with respect to the\n");
	printf("data but the number of the field record specified on the command line, staring\n");
	printf("with 0 as the leftmost field record specified\n\n");
	printf("Unless --s is specified --x and --i will be ignored.\n\n");
	return;
}


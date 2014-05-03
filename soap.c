/* See LICENSE file for copyright and license details. */
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

typedef struct {
	const char *regex;
	const char *action;
} Pair;

#include "config.h"

int
main(int argc, char *argv[]){
	int g, h, i;
	char cmd[BUFSIZ], sharg[BUFSIZ];
	regex_t regex;

	/* we only take one argument */
	if (argc != 2)
		return EXIT_FAILURE;

	/* make the argument shell-ready
	 *   1) start with '
	 *   2) escape ' to '\''
	 *   3) close with '\0
	 */
	sharg[0] = '\'';
	for (g=0, h=1; argv[1][g] && h < BUFSIZ-1-3-2; ++g, ++h) {
		sharg[h] = argv[1][g];
		if (argv[1][g] == '\'') {
			sharg[++h] = '\\';
			sharg[++h] = '\'';
			sharg[++h] = '\'';
		}
	}
	sharg[h] = '\'';
	sharg[++h] = 0;

	/* check regex and launch action if it matches argv[1] */
	for (i=0; i < sizeof(pairs)/sizeof(*pairs); ++i) {
		if (regcomp(&regex, pairs[i].regex, REG_EXTENDED))
			fprintf(stderr, "invalid regex: %s\n", pairs[i].regex);
		if (!regexec(&regex, argv[1], 0, NULL, 0)) {
			snprintf(cmd, sizeof cmd, pairs[i].action, sharg);
			system(cmd);
			return EXIT_SUCCESS;
		}
		regfree(&regex);
	}

	/* alternatively, fall back to xdg-open_ */
	snprintf(cmd, sizeof cmd, "xdg-open_ %s", sharg);
	system(cmd);
	return EXIT_SUCCESS;
}

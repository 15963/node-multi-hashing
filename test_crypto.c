#include "cryptonight.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char *bin2hex(const unsigned char *p, size_t len)
{
	int i;
	char *s = malloc((len * 2) + 1);
	if (!s)
		return NULL;

	for (i = 0; i < len; i++)
		sprintf(s + (i * 2), "%02x", (unsigned int) p[i]);

	return s;
}

int hex2bin(unsigned char *p, const char *hexstr, size_t len)
{
	char hex_byte[3];
	char *ep;

	hex_byte[2] = '\0';

	while (*hexstr && len) {
		if (!hexstr[1]) {
			//applog(LOG_ERR, "hex2bin str truncated");
			return 0;
		}
		hex_byte[0] = hexstr[0];
		hex_byte[1] = hexstr[1];
		*p = (unsigned char) strtol(hex_byte, &ep, 16);
		if (*ep) {
			//applog(LOG_ERR, "hex2bin failed on '%s'", hex_byte);
			return 0;
		}
		p++;
		hexstr += 2;
		len--;
	}

	return (len == 0 && *hexstr == 0) ? 1 : 0;
}


int main()
{
	char data[13]={0};
	hex2bin(data,"63617665617420656d70746f72",sizeof(data));

	char hash[32]={0};
	cryptonight_hash(data,hash,sizeof(data),0);

	char *hashstr=bin2hex(hash,sizeof(hash));

	printf("%s\r\n",hashstr);

	return 0;
}

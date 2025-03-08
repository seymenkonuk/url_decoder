#include <stdio.h>
#include <stdlib.h>

#include "../src/url_decoder.h"

int	main(int argc, char** argv)
{
	char*	decoded_url;

	if (argc != 2)
	{
		printf("Lutfen parametre giriniz!\n");
		return (0);
	}

	decoded_url = decode_url(argv[1]);

	printf("Encoded URL: %s\n", argv[1]);
	printf("Decoded URL: %s\n", decoded_url);

	free(decoded_url);
	return (0);
}

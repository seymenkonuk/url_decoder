#include "url_decoder.h"

// HEX KARAKTERİ ONLUK TABANA DÖNÜŞTÜRÜR
// @param ch: hexadecimal karakter
// @return success: hex karakterin decimal karşılığı.
// @return error: ch hexadecimal değilse -1.
static int	hex2dec_1char(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (ch - '0');
	if (ch >= 'a' && ch <= 'f')
		return (ch - 'a' + 10);
	if (ch >= 'A' && ch <= 'F')
		return (ch - 'A' + 10);
	return (-1);
}

// İKİ KARAKTERLİK HEX METNİ ONLUK TABANA DÖNÜŞTÜRÜR
// @param str: hexadecimal metin 
// @return success: hex metnin ilk iki karakterinin decimal karşılığı.
// @return error: str hexadecimal değilse veya 2 karakterden az ise -1.
static int	hex2dec_2char(char* str)
{
	int	ch1;
	int	ch2;

	if (str == NULL || str[0] == '\0' || str[1] == '\0')
		return (-1);
	ch1 = hex2dec_1char(str[0]);
	ch2 = hex2dec_1char(str[1]);
	if (ch1 == -1 || ch2 == -1)
		return (-1);
	return (ch1 * 16 + ch2);
}

// METİNDEKİ İLK URL ENCODE'UN İNDEXİNİ BULUR
// @param str: metin
// @return success: str'nin içindeki ilk ("%??") kısmının indexi.
// @return error: str NULL ise veya str'nin içinde url encode yok ise -1.
static int	find_encode_char(char* str)
{
	int	i;

	if (str == NULL)
		return (-1);
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == '%' && hex2dec_2char(str + i + 1) != -1)
			return (i);
	return (-1);
}

// METNİN URL DECODE İŞLEMİ SONRASI OLUŞACAK YENİ UZUNLUĞUNU BULUR
// @param str: metin
// @return success: str'nin url decode sonrası uzunluğu.
// @return error: str NULL ise 0.
static int	find_new_length(char* str)
{
	int	result;
	int	i;

	if (str == NULL)
		return (0);
	result = 0;
	while (1)
	{
		i = find_encode_char(str);
		if (i == -1)
			break;
		result += i;
		result += 1;
		str = str + i + 3;
	}
	result += strlen(str);
	return (result);
}

// KARAKTERİ DECODE EDER
// @param chr: karakter
// @return success: karakterin decode edilmiş hali.
static char	decode_char(char chr)
{
	if (chr == '+')
		return (' ');
	return (chr);
}

// URL DECODE İŞLEMİ YAPAR
// @param str: metin
// @return success: url decode yapılmış metin.
// @return error: str NULL ise veya MALLOC error olur ise NULL döner.
char*		decode_url(char* str)
{
	char*	result;
	int		length;
	int		temp;
	int		i, j;

	if (str == NULL)
		return (NULL);
	i = 0;
	length = find_new_length(str);
	result = (char*)malloc((length + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (1)
	{
		temp = find_encode_char(str);
		if (temp == -1)
			break;
		for (j = 0; j < temp; j++)
			result[i++] = decode_char(str[j]);
		result[i++] = hex2dec_2char(str + temp + 1);
		str = str + temp + 3;
	}
	for (j = 0; str[j] != '\0'; j++)
		result[i++] = decode_char(str[j]);
	result[i] = '\0';
	return (result);
}

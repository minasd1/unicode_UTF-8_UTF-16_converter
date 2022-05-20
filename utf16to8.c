#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	long int c1, c2, c3, c4; 		
	long int char_enc2, char_enc4;	/*2 or 4 byte encoding*/
	long int byte3_4;
	int flag_encoding;				 /*Check which of the encodings will be implemented each time (2 or 4 byte) */
	long int byte1, byte2, byte3, byte4;
	long int uni;					
	long int a1, a2, b1, b2, b;		/*Used in 4 byte encoding*/
	
	
	c1 = getchar();
	c2 = getchar();
	do
	{
			flag_encoding = 0;				/*2 BYTE ENCODING*/
			char_enc2 = (c1 << 8) | c2;
			if((char_enc2 >= 0x0000 && char_enc2 <= 0xD7FF) || (char_enc2 >= 0xE000 && char_enc2 <= 0xFFFF))
			{
				if(char_enc2 >= 0x0000 && char_enc2 <= 0x007F) 
				{
					putchar(char_enc2);		/*We do not have to transform it, it already has the desired form 0XXXXXXX*/
					flag_encoding = 1;
				}
				else if (char_enc2 >= 0x0080 && char_enc2 <= 0x07FF)
				{
					byte1 = ((char_enc2 & 0x7C0) >> 6) | 0xC0;		/*byte1 should have the form 110XXXXX, where x are the first 5 digits of char_enc2*/		
					byte2 = (char_enc2 & 0x3F) | 0x80;				/*byte2 should have the form 10XXXXXX, where x are the 6 lasts digits of char_enc2*/
					putchar(byte1);
					putchar(byte2);
					flag_encoding = 1;
				}
				else if ((char_enc2 >= 0x800 && char_enc2 <= 0xD7FF) || (char_enc2 >= 0xDFFF && char_enc2 <= 0xFFFF))
				{
					byte1 = ((char_enc2 & 0xF000) >> 12) | 0xE0;		/*byte1 should have the form 1110XXXX, where x are the first 4 digits of char_enc2*/
					byte2 = ((char_enc2 & 0xFC0) >> 6) | 0x80;			/*Suggested forms of byte2, byte3*/
					byte3 = (char_enc2 & 0x3F) | 0x80;
					putchar(byte1);
					putchar(byte2);
					putchar(byte3);
					flag_encoding = 1;
				}
			}
			
			if(flag_encoding == 0)			/*4 BYTE ENCODING*/
			{
					c3 = getchar();
					c4 = getchar();
					/* UTF-16 to Unicode, inverse procedure*/
					
					if(c3 != EOF || c4 != EOF)
					{
						byte3_4 = (c3 << 8) | c4;																		
						if((char_enc2 >= 0xD800 && char_enc2 <= 0xDBFF) && (byte3_4 >= 0xDC00 && byte3_4 <= 0xDFFF))	
						{
						a1 = (c1 << 8) | c2;			
						a2 = (c3 << 8) | c4;
						b1 = a1 - 0xD800;
						b2 = a2 - 0xDC00;
						b = (b1 << 10) | b2;
						uni = b + 0x010000;
						byte1 = ((uni & 0x1C0000) >> 18) | 0xF0;
						byte2 = ((uni & 0x03F000) >> 12) | 0x80;
						byte3 = ((uni & 0x000FC0) >> 6) | 0x80;
						byte4 = (uni & 0x00003F) | 0x80;
						putchar(byte1);
						putchar(byte2);
						putchar(byte3);
						putchar(byte4);
						flag_encoding = 1;
						}
					
					}
			}		
		    c1 = getchar();
		    c2 = getchar();
		    if(flag_encoding == 0)		/*Current character does not belong in any of the above encodings*/
		    {
		    	printf("Erron in UTF-16 to UTF-8 encoding, invalid code\n");
		    	exit(0);
			}
	}while(c1 != EOF || c2 != EOF);
	
	return 0;
}

/*Note: due to int type lack of capacity, variables are declared as long int*/

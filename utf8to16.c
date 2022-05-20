#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	long int char_enc1, char_enc2, char_enc3, char_enc4;	/*Characters read for each of the encodings*/
	long int uni;
	int flag_encoding;						/*Check which of the 4 encodings will be implemented each time (1,2,3 or 4 byte)*/
	long int part1, part2, part3, part4;	/*Parts of unicode character*/
	long int byte1, byte2, byte3, byte4;
	long int b, b1, b2 , a1, a2;			/*Used in 4 byte encoding*/
	
	char_enc1  = getchar();
	while(char_enc1 != EOF)
	{
		flag_encoding = 0;
		if(char_enc1 >= 0x0000 && char_enc1 <= 0x007F)		/*1 BYTE UTF-8 ENCODING*/
		{		
			part1 = 0x00;									/*2 byte encoding of utf-16, add 0x00 at start to have 2 bytes*/	
			putchar(part1);
			putchar(char_enc1);
			flag_encoding = 1;	
		}
		if(flag_encoding == 0)								/*2 BYTE ENCODING*/
		{
			char_enc2 = getchar();
			if(char_enc2 != EOF)
			{
				if((char_enc1 & 0xE0) == 0xC0 && (char_enc2 & 0xC0) == 0x80)	/*If it's an acceptable character, which mean that it has the form 110XXXXX 10XXXXXX*/
				{
					part1 = (char_enc1 & 0x1F) << 6;							/*We take the 5 last bits of char_enc1*/
					part2 = char_enc2 & 0x3F;									/*Likewise, we take the last 6 bits of char_enc2*/
					uni = part1 | part2;					
					byte1 = (uni & 0xFF00) >> 8;								/*We split uni in 2 separate bytes*/
					byte2 = uni & 0x00FF;
					if(uni >= 0x0080 && uni <= 0x07FF)		
					{
					putchar(byte1);
					putchar(byte2);
					flag_encoding = 1;
					}
				}
			}
				
		}
		if(flag_encoding == 0)							/*3 BYTE ENCODING*/
		{
			char_enc3 = getchar();
			if(char_enc3 != EOF)
			{
				if((char_enc1 & 0xF0) == 0xE0 && (char_enc2 & 0xC0) == 0x80 && (char_enc3 & 0xC0) == 0x80)		/*Acceptable character*/
				{
					part1 = char_enc1 & 0x0F;				/*4 last bits of char_enc1*/
					part2 = char_enc2 & 0x3F;				/*Last 6 bits of char_enc2*/
					part3 = char_enc3 & 0x3F;				
					uni = (part1 << 12) | (part2 << 6) | part3;
					byte1 = (uni & 0xFF00) >> 8;				/*Split in 2 separate bytes*/
					byte2 = uni & 0x00FF; 
					if(uni >= 0x0800 && uni <= 0xFFFF)
					{
					putchar(byte1);
					putchar(byte2);
					flag_encoding = 1;
					}
				}
			}
		}
		if(flag_encoding == 0)							/*4 BYTE ENCODING*/
		{
			char_enc4 = getchar();
			if(char_enc4 != EOF)
			{
				if((char_enc1 & 0xF8) == 0xF0 && (char_enc2 & 0xC0) == 0x80 && (char_enc3 & 0xC0) == 0x80 && (char_enc4 & 0xC0) == 0x80)
				{
					part1 = char_enc1 & 0x07;			/*Same as the implementations above, we isolate the bits accordingly*/
					part2 = char_enc2 & 0x3F;
					part3 = char_enc3 & 0x3F;
					part4 = char_enc4 & 0x3F;
					uni = ((part1 << 18) | (part2 << 12) | (part3 << 6) | part4);
					
					if(uni >= 0x010000 && uni <= 0x10FFFF)
					{
					b = uni - 0x010000;					
					b1 = (b & 0x0FFC00) >> 10;
					b2 = b & 0x0003FF;
					a1 = b1 + 0xD800;
					a2 = b2 + 0xDC00;
					byte1 = (a1 & 0xFF00) >> 8;
					byte2 = a1 & 0x00FF;
					byte3 = (a2 & 0xFF00) >> 8;
					byte4 = a2 & 0x00FF;
					putchar(byte1);
					putchar(byte2);
					putchar(byte3);
					putchar(byte4);
					flag_encoding = 1;
					}
					 
				}
			}
		}
		char_enc1 = getchar();		
		if(flag_encoding == 0)		/*Current character does not belong in any of the above encodings*/
		{
			printf("Error in UTF-8 to UTF-16 encoding, invalid code\n");
			exit(0);
		}
	}
	return 0;
}
/*Note: due to int type lack of capacity, variables are declared as long int*/

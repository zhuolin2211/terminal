#include "cli_string.h"
#include "terminal_config.h"

void _strcpy(const char* src, uint16_t offsetSrc, char* dst, uint16_t offsetDst, uint16_t length);
//char* _trim(const char* src);
uint8_t _strcmp(const char* str1, const char* str2);
uint32_t _strlen(const char* strSrc);
uint16_t _getCountSeparator(const char* str, const char* separator);

/// \brief Splitting a string by a given separator
void split(char* strSrc, const char separator, Params_s* dst)
{
    // uint8_t count_sep = _getCountSeparator(strSrc, separator);
    // uint16_t lenSep = _strlen((char*)separator);

    // //dst->argv = (char**) malloc(sizeof(char*) * count_sep);
    // dst->argc = count_sep;

    // int start_index = 0;
    // int size_word = 0;

    // int co = 0;
    // int co_arg = 0;
    // while(1)
    // {

    //     uint16_t s = 0;

    //     for(; s < lenSep; s++){
            
    //         if((strSrc[co] == separator[s]) || (strSrc[co] == '\0'))
    //         {
    //             size_word = co - start_index;

    //             //dst->argv[co_arg] = malloc(sizeof(char) * (size_word + 1));
    //             dst->argv[co_arg][size_word] = '\0';
    //             _strcpy(strSrc, start_index, dst->argv[co_arg], 0, size_word);

    //             start_index = co + 1;
    //             co_arg++;
    //             break;
    //         }
    //     }

    //     if (strSrc[co] == '\0')
    //         break;

    //     co++;
    // }
    int str_index=0;
    int start_index=0;
    int start_flag=0;
    dst->argc=0;
    while(1)
    {
        if(strSrc[str_index]=='\0')
        {
            break;
        }
        if(strSrc[str_index]==separator && strSrc[str_index+1]!=separator)
				{
					start_index=str_index+1;
          start_flag=1;
				}
        else if(str_index==0 && strSrc[str_index]!=separator)
        {
            start_index=str_index;
            start_flag=1;
        }
        if( start_flag==1 && strSrc[str_index]!=separator && \
        (strSrc[str_index+1]==separator || strSrc[str_index+1]=='\0'))
        {
            _strcpy(strSrc,start_index,dst->argv[dst->argc],0,str_index-start_index+1);
            dst->argc++;
            start_flag=0;
        }
        str_index++;
    }


}

/// \brief free memory
/// \return none
void ArgDestroy(Params_s* src)
{
	/*
    for(int8_t i = src->argc - 1; i > 0; i--)
    {
    	free((src->argv[i]));
    }

    free(src->argv);
    */
    src->argc = 0;
}

// ****************** private methods **********************

void _strcpy(const char* src, uint16_t offsetSrc, char* dst, uint16_t offsetDst, uint16_t length)
{
    uint16_t i = 0;
    for(; i < length; i++)
        dst[i + offsetDst] = src[i + offsetSrc];
}

// char* _trim(const char* src)
// {
//     int16_t lengthDst;
//     char* result;
//     int16_t i = 0;
//     int16_t len = _strlen(src);
//     int16_t coStart = 0, coEnd = 0;

//     for(; i < len; i++){
//     	if (!((src[i] > 0x00) && (src[i] < 0x21)))
//     		break;
//         coStart++;
//     }

//     if (coStart == len){
//         result = cli_malloc(sizeof(char));
//         result[0] = '\0';
//         return result;
//     }

//     for(i = len - 1; i >= 0; i++){
//         if (!((src[i] > 0x00) && (src[i] < 0x21)))
//             break;
//         coEnd++;
//     }

//     lengthDst = len - coStart - coEnd;
//     result = cli_malloc(sizeof(char) * lengthDst);
//     _strcpy(src, coStart, result, 0, lengthDst);
//     return result;
// }

uint32_t _strlen(const char* strSrc)
{
    int32_t co = 0;
    while((strSrc != NULL) && (*strSrc != '\0')){
        strSrc++;
        co++;
    }

    return co;
}

uint16_t _getCountSeparator(const char* strSrc, const char* separator)
{
    uint8_t i = 0;
    uint16_t result = 0;
    uint16_t count_separator = _strlen((char*) separator);

    for(; strSrc[i] != '\0'; i++)
    {
        uint16_t j = 0;
        for(; j < count_separator; j++)
            if (strSrc[i] == separator[j]){
                result++;
                break;
            }
    }

    return result + 1;
}

uint8_t _strPartCmp(const char* str1, const char* str2)
{
	uint8_t co = 0;
	while(((str1 + co) != NULL) && (*(str1 + co) != '\0') &&
          ((str2 + co) != NULL) && (*(str2 + co) != '\0')){

        if (str1[co] != str2[co])
            return 0;

        co++;
    }
    
    return 1;
}

uint8_t _strcmp(const char* str1, const char* str2)
{
    uint16_t co = 0;

	if (_strlen(str1) != _strlen(str2))
		return 0;

    while(((str1 + co) != NULL) && (*(str1 + co) != '\0') &&
          ((str2 + co) != NULL) && (*(str2 + co) != '\0')){

        if (str1[co] != str2[co])
            return 0;

        co++;
    }

    if  (
            (((str1 + co) == NULL) && ((str2 + co) != NULL)) ||
            (((str2 + co) == NULL) && ((str1 + co) != NULL)) ||
            (((str1 + co) != NULL) && ((str2 + co) != NULL) && (*(str2 + co) != *(str1 + co)))
         )
        return 0;


    return 1;
}

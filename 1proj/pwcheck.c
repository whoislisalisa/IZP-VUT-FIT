/////////////////////////////
//////Frederika KmeĹĽovĂĄ//////
//////////xkmeto00///////////
//////////30.10.2021/////////
//////////IZP PROJECT////////
/////////////////////////////

//libraries used
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//definitions to be used more times
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 102
 
//declaration of functions used in main
int has_lower(char password[MAX_SIZE]);
int has_upper(char password[MAX_SIZE]);
int has_numbers(char password[MAX_SIZE]);
int has_characters(char password[MAX_SIZE]);
int level1(char password[MAX_SIZE]);
int level2(char password[MAX_SIZE]);
int level2_4(char password[MAX_SIZE]);
int level3(char *argv[], char password[MAX_SIZE]);
int level4(char password[MAX_SIZE],long int param);
int str_str(char *sub_string, char password[MAX_SIZE], int substr_length);
int str_len(char password[MAX_SIZE]);
int str_cmp(char *a, char *b);

int main(int argc, char *argv[])
{
    // getting password and arguments from stdin
    char password[MAX_SIZE];
    long int level = strtol(argv[1], NULL, 10);
    long int param = strtol(argv[2], NULL, 10);
    
    //viariabiles for stats
    int currpos = 0;
    int pass_len_all = 0;
    float pass_count = 0;
    int min_pass = 0;
    int password_len = 0;
    int count = 0;
    int char_set_len = 128;
    bool unique_chars[char_set_len];

    //setting unique characters to false
    for (int i = 0; i < char_set_len; i++)
    {
        unique_chars[i] = FALSE;
    }

    //checking safety by declared functions below for passwords given by fgets
    while (fgets(password, 102, stdin) != NULL)
    {
        password_len = str_len(password);

        //the password cannot be longer than 100 characters
        if(password_len >= 102)
        {
            fprintf(stderr, "ERROR! Length of password is longer than 100 characters.\n");
        }

        //counting password length, current position, counting passwords in total etc.
        pass_len_all += password_len;
        pass_count++;
        if (password_len <= min_pass || min_pass == 0)
        {
            min_pass = password_len;
        }
        
        currpos = 0;

        for (int i = 0; i < password_len; i++)
        {
            currpos = password[i];
            unique_chars[currpos] = TRUE;
        }

        //checking safety of passwords given
        if ((level == 1 && param == 1) || (level == 2 && param == 2) || (level == 2 && param == 1) || (level == 1 && param >= 1))
        {
            if (level1(password) == TRUE)
            {
                printf("%s", password);    
            }
        }

        if (level == 2 && param == 3)
        {
            if (level2(password) == TRUE)
            {
              printf("%s", password);
            }
        }

        if ((level == 2 && param >= 4 ) || (level == 3 && param == 1))
        {
            if (level2_4(password) == TRUE)
            {
                printf("%s", password);
            }

        }

        if (level == 3 && param >= 2)
        {
            if(level3(argv, password) == TRUE && level1(password) && level2(password) == TRUE)
            {
                printf("%s", password);
            }
        }

        if (level == 4 && param >= 2)
        {
           if (level4(password, param) == TRUE && level1(password) == TRUE && level2(password) == TRUE && level3(argv, password) == TRUE)
            {
                printf("%s", password);
            }
        }

        //checking positive numbers for level, parameters and length of arguments given 
        if (param < 1)
        {
            fprintf(stderr, "ERROR! Parameter number must be a positive number.\n");
            return 1;
        }
        if (level < 1 && param < 1)
        {
            fprintf(stderr, "ERROR! Level and parameter must be a positive number!\n");
        }
        
        if (level < 1)
        {
            fprintf(stderr, "ERROR! Level number is negative. Must be a positive number.\n");
            return 1;
        }

        if (level > 4)
        {
            fprintf(stderr, "ERROR! Level number is bigger than levels for controlling password.\n");
        }
        
        if (argc >= 5)
        {
            fprintf(stderr, "ERROR! Too much arguments.\n");
            return 1;
        }
    }

    //chceking if statistics should be printed or not 
    if (argc == 4 && str_cmp(argv[3], "--stats") == TRUE)
    {
        for (int i = 0; i < char_set_len; i++)
        {
            if (unique_chars[i] == TRUE)
            {
                count++;
            }
        }
        printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", count, min_pass, pass_len_all / pass_count); 
    }
    if(argc == 4 && str_cmp(argv[3], "--stats") == FALSE)
    {
        fprintf(stderr, "ERROR! Fourth argument is different than statistics\n");
    }
}

//definition of a function to check whether the password contains lowercase letters 
int has_lower(char password[MAX_SIZE])
{
    int idx = 0;
    while(password[idx] != '\0')  
    {
        if (password[idx] >= 'a' && password[idx] <= 'z') 
        {
            return TRUE;
        }
        idx++;
    }
    return FALSE;
}

//definition of a function to check whether the password contains uppercase letters 
int has_upper(char password[MAX_SIZE])
{
    int idx = 0;
    while (password[idx] != '\0')
    {
        if (password[idx] >= 'A' && password[idx] <= 'Z')
        {
            return TRUE;
        }
        idx++;
    }
    return FALSE;   
}

//definition of a function to check whether the password contains numbers
int has_numbers(char password[MAX_SIZE])
{
    int idx = 0;
    while (password[idx] != '\0')
    {
        if (password[idx] >= '0' && password[idx] <= '9')
        {
            return TRUE;
        }
        idx++;
    }
    return FALSE;
}

//definition of a function to check whether the password contains characters in ASCII
int has_characters(char password[MAX_SIZE])
{
    int idx = 0;
    while (password[idx] != '\0')
    {
        if ((password[idx] >= 32 && password[idx] <= 47) || (password[idx] >= 58 && password[idx] <= 64) || 
        (password[idx] >= 91 && password[idx] <= 96) || (password[idx] >= 123 && password[idx] <= 126))
        {
            return TRUE;
        }
        idx++;
    }
    return FALSE;
}

//definition of a function to check whether a password splna level 1
int level1(char password[MAX_SIZE])
{
    if (has_lower(password) && has_upper(password))
    {
        return TRUE;
    }
    return FALSE;
}

//definition of a function to check whether a password splna level 2
int level2(char password[MAX_SIZE])
{
    if ((has_lower(password) && has_upper(password)) && (has_numbers(password) || has_characters(password)))
    {
        return TRUE;  
    }
    return FALSE;
}

//definition of a function to check whether a password splna level 2 and 4 parameters
int level2_4(char password[MAX_SIZE])
{
    if (level1(password) == 1 && has_numbers(password) && has_characters(password))
    {
        return TRUE;
    }
    return FALSE;
}

//definition of a function to check whether a password splna level 3
int level3(char *argv[], char password[MAX_SIZE])
{
    long int sequencesamechar;
    sequencesamechar = strtol(argv[2],NULL, 10);
    int char_number = 100;
    char before_char = '\0';
    int counter = 0;
    for (int i = 0; i < char_number; i++)
    {
        if (before_char == '\0' || password[i] != before_char)
        {
            before_char = password[i];
            counter = 1;
        }
        else
        {
            counter++;
        }
        if (counter == sequencesamechar)
        {
            return FALSE;
        }
        
    }
    return TRUE;
}

//definition of function to check if a password contains same substrings
int level4(char password[MAX_SIZE],long int param)
{
    int password_len = str_len(password);
    for (int i = 0; i+param < password_len; i++)
    {
        if(str_str(password+i, password+i+param, param) == TRUE) 
        {
            return FALSE;
        }
    }   
    return TRUE;
}

//definition of function to check if a password contains substring
int str_str(char *sub_string, char password[MAX_SIZE], int substr_length)
{
    int string_match = 0;
    char *default_sub = sub_string;
    sub_string = sub_string - substr_length;
    while (*password != '\0') 
    {
        while (*sub_string == *password && *sub_string != '\0') 
        {
            string_match++;
            sub_string++;
            password++;
        }
        if (string_match == substr_length)
        {
            return TRUE;
        }
        string_match = 0;
        sub_string = default_sub; 
        password++;
    }
    return FALSE;
}

//definition of function to get a length of a password
int str_len(char password[MAX_SIZE])
{
    int i = 0;
    int len = 0;
    while (password[i] != '\0' && password[i] != '\n')
    {
        len++;
        i++;
    }
    return len;
}

//definition of function to compare strings
int str_cmp(char *a, char *b)
{
    if(str_len(a) != str_len(b))
    {
        return FALSE;
    }
    while (*a != '\n' && *a != '\0')
    {
        if(*a != *b)
        {
           return FALSE;
        } 
        a++;
        b++;
    }
    return TRUE;
}

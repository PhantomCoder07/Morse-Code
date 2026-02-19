#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define total_sym 60
struct map
{
    char *code;
    char *symbol;
};
struct map morse[total_sym];
void morse_codes()
{
    struct map temp[total_sym]=
    {
        {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, {"-..", "D"},
        {".", "E"}, {"..-.", "F"}, {"--.", "G"}, {"....", "H"},
        {"..", "I"}, {".---", "J"}, {"-.-", "K"}, {".-..", "L"},
        {"--", "M"}, {"-.", "N"}, {"---", "O"}, {".--.", "P"},
        {"--.-", "Q"}, {".-.", "R"}, {"...", "S"}, {"-", "T"},
        {"..-", "U"}, {"...-", "V"}, {".--", "W"}, {"-..-", "X"},
        {"-.--", "Y"}, {"--..", "Z"}, {"-----", "0"}, {".----", "1"},
        {"..---", "2"}, {"...--", "3"}, {"....-", "4"}, {".....", "5"},
        {"-....", "6"}, {"--...", "7"}, {"---..", "8"}, {"----.", "9"},
        {".-.-.-", "."}, {"--..--", ","}, {"..--..", "?"}, {".----.", "'"},
        {"-..-.", "/"}, {"-.--.", "("}, {"-.--.-", ")"}, {"---...", ":"},
        {"-...-", "="}, {".-.-.", "+"}, {"-....-", "-"}, {".-..-.", "\""},
        {".--.-.", "@"}, {"---.", "!"}, {".-...", "&"}, {"-.-.-.", ";"},
        {"..--.-", "_"}, {"...-..-", "$"}, {"...-.-", "End of Work"},
        {"........", "Error"}, {"-.-.-", "Start"}, {"...-.", "Verified"}
    };
    for (int i=0; i<total_sym; i++)
        morse[i]=temp[i];
}
void decode_word (char *token)
{
    for (int i=0; i<total_sym; i++)
    {
        if (strcmp(token,morse[i].code)==0)
        {
            printf("%s",morse[i].symbol);
            return;
        }
    }
    printf(" ");
}
void decode_sms (char *sms)
{
    char token[20];
    int pos=0;
    for (int i=0; ; i++)
    {
        if (sms[i]!=' ' && sms[i]!='/' && sms[i]!='\n' && sms[i]!='\0')
        {
            token[pos++]=sms[i];
        }
        else
        {
            if (pos>0)
            {
                token[pos]='\0';
                pos=0;
                decode_word(token);
            }
            if (sms[i]=='/')
            {
                printf(" ");
            }
            if (sms[i]=='/' && sms[i+1]=='/')
            {
                printf("\n");
                i++;
            }
            if (sms[i]=='\0' || sms[i]=='\n')
                break;
        }
    }
    printf("\n");
}
bool is_valid (char *s)
{
    for (int i=0; s[i]!='\n'; i++)
    {
        if (s[i]!=' ' && s[i]!='.' && s[i]!='-' && s[i]!='/')
            return false;
    }
    return true;
}
void encode_sms (char *sms)
{
    int l=strlen(sms);
    for (int i=0; i<l; i++)
    {
        char c=toupper(sms[i]);
        if (c==' ')
        {
            printf("/ ");
            continue;
        }
        char temp[2];
        temp[0]=c;
        temp[1]='\0';
        bool f=false;
        for (int j=0; j<total_sym; j++)
        {
            if (strcmp(morse[j].symbol,temp)==0)
            {
                printf("%s ",morse[j].code);
                f=true;
                break;
            }
        }
        if (!f)
            printf(" ");
    }
    printf("\n");
}
int main()
{
    char s[2000];
    morse_codes();
    int n;
    printf("---------------//Welcome to Morse Code Converter\\\\---------------\n");
    while (1)
    {
        printf("1 - For Encode Morse Code\n");
        printf("2 - For Decode Morse Code\n");
        printf("0 - If you want to exit\n");
        printf("---------------------------------------------------------------\n");
        printf("Enter number according to your choice: ");
        scanf("%d",&n);
        printf("---------------------------------------------------------------\n");
        switch (n)
        {
        case 0:
            printf("Thank you.\n");
            break;
        case 1:
            printf("Enter text to encode:\n");
            scanf("\n");
            fgets(s,sizeof(s),stdin);
            s[strcspn(s,"\n")]='\0';
            printf("Encoded Morse:\n");
            encode_sms(s);
            break;
        case 2:
            printf("Enter your code:\n");
            scanf("\n");
            fgets(s,sizeof(s),stdin);
            if (is_valid(s))
            {
                printf("Meaning of your code:\n");
                decode_sms(s);
            }
            else
                printf("Your massage is invalid\n");
            break;
        default:
            printf("Wrong entry\n");
            printf("---------------------------------------------------------------\n");
            printf("Choice carefully\n");
        }
        printf("---------------------------------------------------------------\n");
        if (n==0)
            break;
        printf("Do you want to continue?\n");
        printf("1 - Yes\n");
        printf("0 - No\n");
        printf("---------------------------------------------------------------\n");
        printf("Make your choice: ");
        scanf("%d",&n);
        if (n==0)
        {
            printf("---------------------------------------------------------------\n");
            printf("Thank you.\n");
            break;
        }
        else
        {
            printf("---------------------------------------------------------------\n");
            continue;
        }
    }
    return 0;
}

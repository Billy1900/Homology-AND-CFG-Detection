
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

/* Print message */

static void
croak(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    fflush(stderr);
}

/* Signal error and bail out */

static void
barf(const char *msg) {
    croak(msg);
    exit(1);
}


void maliciousCode()
{
    printf("Successfully executed malicious code!\n");
}

void inputDataProcessing(){
    char dataBuffer[50];

    printf("Get Input Data Stream:\n");
    gets(dataBuffer);
    printf("Input Data Stream: %s\n", dataBuffer);  
}



int check_authentication (char *password){
    int auth_flag = 0;
    // int no_smash = 145;          // This is the stack canary value.  Works with hard coded, which is a bad practice.  Better to randomize it each                            // time.  However, gcc pushes stack_can before password_buffer, so stack canary can be overwritten.
    char password_buffer[64];       // Order of these declarations is important; auth_flag is declared first, so pushes first;
    // int stack_can = no_smash;        // If declared in the opposite order (password_buffer before auth_flag), no overflow possible into auth_flag.
    
    strcpy (password_buffer,password);

    if (strcmp(password_buffer, "brillig") == 0)
        auth_flag = 1;
    
    if (strcmp(password_buffer, "outgrabe") == 0)
        auth_flag = 1;
    
    // Rob's Stack Canary!
    // Uncomment the below lines to enable a Rob-written stack canary.
    //
    //if (no_smash != 145)      // Note hard coded stack value.
    //{
    //  auth_flag = 0;
    //  printf("\nYour Jedi mind tricks will not work on me, boy!\n");
    //}
    //
    // Rob's Stack Canary ends here

    return auth_flag;

}

int bof() {
    char buffer[8];
    FILE *badfile;
    badfile = fopen("badfile", "r");
    fread(buffer, sizeof(char), 1024, badfile);
    return 1;
}


int main (int argc, char *argv[])
{
     FILE *f, *fp;
    void *code;
    int i, l;
    int m = 15;          /* max # of bytes to print on one line */
    struct stat sbuf;
    size_t f_len;        /* Note: assume files are < 2**32 bytes long ;-) */

    if(argc < 2) barf("Binary file must be specified");
    if(stat(argv[1], &sbuf)) barf("failed to stat file");
    f_len = (size_t) sbuf.st_size;
    if(!(code = malloc(f_len))) barf("failed to grab required memory");
    if(!(fp = fopen(argv[1], "rb"))) barf("failed to open file");
    if(fread(code, 1, f_len, fp) != f_len) barf("failed to slurp file");
    if(fclose(fp)) barf("failed to close file");
    f = fopen("./exec_shell_code.c", "w");
    fprintf(f, "#define SHELL_CODE \\\n");
    l = m;
    for(i = 0; i < f_len; ++i) {
        if(l >= m) {
            if(i) fprintf(f, "\" \\\n");
            fprintf(f, "\t\"");
            l = 0;
        }
        ++l;
        fprintf(f, "\\x%02x", ((unsigned char *)code)[i]);
    }
    fprintf(f, "\"\n\n");
    fprintf(f, "int main() {\n"
               "    void (*fptr)(void);\n"
               "    fptr = (void (*)(void))&SHELL_CODE;\n"
               "    (*fptr)();\n"
               "}");
    fclose(f);
    


    if (argc < 2)
    
    {
        printf("Usage: %s <password>\n", argv[0]);      // Fusses at you for not entering an argument & closes
        exit(0);
    }

    if (check_authentication (argv[1]))

    {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("    Access Granted.\n");
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    }
    else
    {   
        printf("\nAccess Denied. :(\n");
    }
    
    if (argc >100)
    {   
        printf("\nYou found the easter egg!!!\n");
    }

    inputDataProcessing();

    bof();
    printf("Not gonna do it!\n");

    return 0;
}
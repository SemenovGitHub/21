#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void char_cesar(char * ch, int shift);
void process_file(FILE *file, int shift);
void process_directory(char path[], int shift);

int main() {

    int n;
    char filename[150] = "";

    while (scanf("%d", &n) == 1 && n != -1) {

        if(n == 1) {

            fflush(stdin);
            scanf("%s", filename);
            FILE *fp = fopen(filename, "r");
            if (fp == NULL) {
                printf("n/a\n");
                continue;
            }

            fseek(fp, 0, SEEK_END);
            long size = ftell(fp);
            rewind(fp);

            char *buffer = (char*)malloc(size + 1);
            if (buffer == NULL) {
                printf("n/a\n");
                fclose(fp);
                continue;
            }

            fread(buffer, size, 1, fp);

            buffer[size] = '\0';
  
            printf("%s\n", buffer);
        
            free(buffer);
            fclose(fp);
            fflush(stdin);
            
        }
        if(n == 2){
            
            fflush(stdin);
            char message[1000];
            scanf("%s", message);
            FILE *fp = fopen(filename, "a");

            if(fp){
                fprintf(fp, "%s", message);
                fclose(fp);
                fp = fopen(filename, "r");
                if(fp){
                    char buffer[100000];
                    while((fgets(buffer, 100000, fp))!=NULL) {
                        printf("\n%s\n", buffer);
                    }
                    fclose(fp);
                }
                else {
                    printf("n/a\n");
                    continue;
                }
            }
            else {
                printf("n/a\n");
                continue;
            }
        }
        if(n == 3){
            
            int shift;
            scanf("%d", &shift);
            fflush(stdin);
            char path[200];
            printf("Enter the path to the directory: ");
            scanf("%s", path);
            process_directory(path, shift);
        }
    }
    return 0;
}

void char_cesar(char * ch, int shift){

    int k = shift%26;

    for(int i = 0; i < (int)strlen(ch); ++i) {
        if ((ch[i] >= 97 && ch[i] <= 122) && ch[i] + k > 122) {
        ch[i] = ch[i] + k - 26;
        }
        if ((ch[i] >= 65 && ch[i] <= 90) && ch[i] + k > 90) {
        ch[i] = ch[i] + k - 26;
        }
        if ((ch[i] >= 97 && ch[i] <= 122) && ch[i] + k <= 122) {
        ch[i] = ch[i] + k;
        }
        if ((ch[i] >= 65 && ch[i] <= 90) && ch[i] + k <= 90) {
        ch[i] = ch[i] + k;
        }
    }
}

void process_file(FILE *file, int shift) {
    if(file != NULL) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);
        
        char *buffer = (char*)malloc(size + 1);
        if (buffer == NULL) {
            printf("n/a\n");
            exit(1);
        }
        
        fread(buffer, size, 1, file);
        buffer[size] = '\0';
        
        char_cesar(buffer, shift);
        
        rewind(file);
        fwrite(buffer, size, 1, file);
        
        free(buffer);
    }
    else {
        printf("n/a\n");
        exit(2);
    }
}

void process_directory(char path[], int shift) {
    
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Cannot open directory: %s\n", path);
        return;
    }

    struct dirent *entry;
    char full_path [300];
    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name + strlen(entry->d_name) - 2, ".c") == 0){
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            FILE *fp = fopen(full_path, "r+");
            printf("%s\n", full_path);
           process_file(fp, shift);
           fclose(fp);
        }
        if(strcmp(entry->d_name + strlen(entry->d_name) - 2, ".h") == 0){
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
            FILE *fp = fopen(full_path, "w");
            printf("%s\n", full_path);
           fclose(fp);
        }
    }
    closedir(dir);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ascend and descend are adapted from the c documentation of qsort
int ascend (const void *a, const void *b) {
   int arg1=*(const int*)a;
   int arg2=*(const int*)b;
   return (arg1>arg2)-(arg1<arg2);
}

int descend (const void *a, const void *b) {
   int arg1=*(const int*)a;
   int arg2=*(const int*)b;
   return (arg1<arg2)-(arg1>arg2);
}

void sort_query(char **query_strs, int arr_len, int query_num, int security)
{
   // read data from data.txt
   FILE *file;
   file = fopen("data.txt", "r");
   int id=1;
   char line[100];
   char idString[4];
   char idx[8];
   char data_strs[256][100];
   int file_size=0;
   strcpy(idx, "A: ");
   if (file) {
      // count number of lines in file
      while (fgets(line, 100, file)!=NULL) {
         file_size++;
      }

      // return to beginning of file (thanks OS)
      fseek(file, 0, SEEK_SET);

      while (fgets(line, 100, file)!=NULL) {
         if (id<255) line[strlen(line)-1]='\0';
         sprintf(idString, "%d", id);
         strcat(idx, idString);
         strcat(idx, " ");
         strcat(idx, line);
         strcpy(data_strs[id-1], idx);
         strcpy(idx, "A: ");
         id++;
      }
   }
   fclose(file);

   printf("\n//Query %d\n", query_num);

   int positive=0;
   char sign=query_strs[1][strlen(query_strs[1])-5];
   if (sign=='-') positive=-1;
   else positive=1;

   char sortChar[2]={query_strs[1][0], '\0'};
   char trueArr[256*3][100];
   int trueIdx=0;

   for (int i=0; i<256; i++) {
      if (strstr(data_strs[i], sortChar)) {
         strcpy(trueArr[trueIdx], data_strs[i]);
         trueIdx++;
      }
   }

   char secureArr[256][100];
   int secureIdx=0;
   char *retVal;
   retVal=(char*)malloc(100);
   char *compVal;
   compVal=(char*)malloc(100);

   if (security==0) {
      for (int i=0; i<trueIdx; i++) {
         strcpy(secureArr[i], trueArr[i]);
         secureIdx++;
      }
   }
   else {
      char *securityStr;
      securityStr=(char*)malloc(2);
      char *fieldName;
      fieldName=(char*)malloc(4);
      sprintf(securityStr, "%d", security);
      strcpy(fieldName, "Y: ");
      for (int i=0; i<trueIdx; i++) {
         char temp[100];
         strcpy(temp, trueArr[i]);
         retVal=strstr(temp, fieldName);
         if (retVal) {
            retVal+=3;
            compVal=strtok(retVal, " ");
            if (atoi(compVal)<=atoi(securityStr)) {
               strcpy(secureArr[secureIdx], trueArr[i]);
               secureIdx++;
            }
         }
      }
   }

   int toSort[secureIdx];
   int unique=1;
   for (int i=0; i<secureIdx; i++) {
      char temp[100];
      strcpy(temp, secureArr[i]);
      retVal=strstr(temp, sortChar);
      if (retVal) {
         retVal+=3;
         compVal=strtok(retVal, " ");
         for (int j=0; j<i; j++) {
            if (atoi(compVal)==toSort[j]) unique=0;
         }
         if (unique==1) toSort[i]=atoi(compVal);
         unique=1;
      }
   }

   if (positive==1) {
      qsort(toSort, secureIdx, sizeof(int), ascend);
      for (int i=0; i<secureIdx; i++) {
         for (int j=0; j<secureIdx; j++) {
            char temp[100];
            strcpy(temp, secureArr[j]);
            retVal=strstr(temp, sortChar);
            if (retVal) {
               retVal+=3;
               compVal=strtok(retVal, " ");
               if (atoi(compVal)==toSort[i]) {
                  printf("%s\n", secureArr[j]);
               }
            }
         }
      }
   }
   else {
      qsort(toSort, secureIdx, sizeof(int), descend);
      for (int i=0; i<secureIdx; i++) {
         for (int j=0; j<secureIdx; j++) {
            char temp[100];
            strcpy(temp, secureArr[j]);
            retVal=strstr(temp, sortChar);
            if (retVal) {
               retVal+=3;
               compVal=strtok(retVal, " ");
               if (atoi(compVal)==toSort[i]) {
                  printf("%s\n", secureArr[j]);
               }
            }
         }
      }
   }
}

void find_query(char **query_strs, int arr_len, int query_num, int security)
{
   // read data from data.txt
   FILE *file;
   file = fopen("data.txt", "r");
   int id=1;
   char line[100];
   char idString[4];
   char idx[8];
   char data_strs[256][100];
   int file_size=0;
   strcpy(idx, "A: ");
   if (file) {
      // count number of lines in file
      while (fgets(line, 100, file)!=NULL) {
         file_size++;
      }

      // return to beginning of file (thanks OS)
      fseek(file, 0, SEEK_SET);

      while (fgets(line, 100, file)!=NULL) {
         if (id<255) line[strlen(line)-1]='\0';
         sprintf(idString, "%d", id);
         strcat(idx, idString);
         strcat(idx, " ");
         strcat(idx, line);
         strcpy(data_strs[id-1], idx);
         strcpy(idx, "A: ");
         id++;
      }
   }
   fclose(file);

   printf("\n//Query %d\n", query_num);
   char trueArr[256*3][100];
   int trueIdx=0;
   char fitsAll[256][100];
   int fitsIdx=0;
   if (strstr(query_strs[1], "Z")) {
      for (int i=0; i<file_size; i++) {
         strcpy(fitsAll[fitsIdx], data_strs[i]);
         fitsIdx++;
      }
   }
   else {
      int opCount=0;
      for (int i=1; i<arr_len-1; i++) {
         char *line;
         line=(char*)malloc(strlen(query_strs[i]));
         strcpy(line, query_strs[i]);
         char fieldName[2]={query_strs[i][0], '\0'};
         char *valueStr;
         valueStr=(char*)malloc(strlen(query_strs[i])-4);
         strncpy(valueStr, &query_strs[i][4], strlen(query_strs[i]));
         valueStr[strlen(valueStr)-1]='\0';
         int value=atoi(valueStr);
         strcat(fieldName, ": ");

         char *retVal;
         retVal=(char*)malloc(100);
         char *compVal;
         compVal=(char*)malloc(100);

         // equals comparison operator
         if (strstr(query_strs[i], "=")) {
            opCount++;
            strcat(fieldName, valueStr);
            strcat(fieldName, " ");
            for (int j=0; j<256; j++) {
               if (strstr(data_strs[j], fieldName)) {
                  strcpy(trueArr[trueIdx], data_strs[j]);
                  trueIdx++;
               }
            }
         }

         // greater than comparison operator
         else if (strstr(query_strs[i], ">")) {
            opCount++;
            for (int j=0; j<256; j++) {
               char temp[100];
               strcpy(temp, data_strs[j]);
               retVal=strstr(temp, fieldName);
               if (retVal) {
                  retVal+=3;
                  compVal=strtok(retVal, " ");
                  if (atoi(compVal)>atoi(valueStr)) {
                     strcpy(trueArr[trueIdx], data_strs[j]);
                     trueIdx++;
                  }
               }
            }
         }

         // less than comparison operator
         else if (strstr(query_strs[i], "<")) {
            opCount++;
            for (int j=0; j<256; j++) {
               char temp[100];
               strcpy(temp, data_strs[j]);
               retVal=strstr(temp, fieldName);
               if (retVal) {
                  retVal+=3;
                  compVal=strtok(retVal, " ");
                  if (atoi(compVal)<atoi(valueStr)) {
                     strcpy(trueArr[trueIdx], data_strs[j]);
                     trueIdx++;
                  }
               }
            }
         }
      }
      int allCount=1;
      if (opCount>1) {
         for (int i=0; i<trueIdx; i++) {
            int allCount=1;
            for (int j=i+1; j<trueIdx; j++) {
               if (strcmp(trueArr[i], trueArr[j])==0) {
                  allCount++;
               }
            }
            if (allCount==opCount) {
               strcpy(fitsAll[fitsIdx], trueArr[i]);
               fitsIdx++;
            }
         }
      }
      else {
         for (int i=0; i<trueIdx; i++) {
            strcpy(fitsAll[fitsIdx], trueArr[i]);
            fitsIdx++;
         }
      }
   }

   char secureArr[256][100];
   int secureIdx=0;
   char *retVal;
   retVal=(char*)malloc(100);
   char *compVal;
   compVal=(char*)malloc(100);

   if (security==0) {
      for (int i=0; i<fitsIdx; i++) {
         strcpy(secureArr[i], fitsAll[i]);
         secureIdx++;
      }
   }
   else {
      char *securityStr;
      securityStr=(char*)malloc(2);
      char *fieldName;
      fieldName=(char*)malloc(4);
      sprintf(securityStr, "%d", security);
      strcpy(fieldName, "Y: ");
      for (int i=0; i<fitsIdx; i++) {
         char temp[100];
         strcpy(temp, fitsAll[i]);
         retVal=strstr(temp, fieldName);
         if (retVal) {
            retVal+=3;
            compVal=strtok(retVal, " ");
            if (atoi(compVal)<=atoi(securityStr)) {
               strcpy(secureArr[secureIdx], fitsAll[i]);
               secureIdx++;
            }
         }
      }
   }

   char *projectFields;
   projectFields=(char*)malloc(strlen(query_strs[arr_len-1]));
   int projectIdx=0;
   char temp[100];
   char printArr[24][100];
   int printIdx=0;

   if (strstr(query_strs[arr_len-1], "X")) {
      for (int i=0; i<secureIdx; i++) {
         printf("%s\n", secureArr[i]);
      }
   }
   else {
      char *projectFieldsArr[arr_len/2];
      char *pField=strtok(query_strs[arr_len-1], " ");
      while (pField!=NULL) {
         projectFieldsArr[projectIdx]=pField;
         pField=strtok(NULL, " ");
         projectIdx++;
      }
      for (int j=0; j<secureIdx; j++) {
         int projectSomething=0;
         printIdx=0;
         for (int i=0; i<projectIdx-1; i++) {
            if (strstr(secureArr[j], projectFieldsArr[i])) {
               projectSomething=1;
               strcpy(temp, secureArr[j]);
               retVal=strstr(temp, projectFieldsArr[i]);
               retVal+=3;
               strtok(retVal, " ");
               strcpy(printArr[printIdx], projectFieldsArr[i]);
               printIdx++;
            }
         }
         if (projectSomething==1) {
            for (int k=0; k<strlen(secureArr[j]); k++) {
               for (int i=0; i<printIdx; i++) {
                  if (secureArr[j][k]==printArr[i][0]) {
                     strcpy(temp, secureArr[j]);
                     char keyStr[2]={printArr[i][0], '\0'};
                     retVal=strstr(temp, keyStr);
                     retVal+=3;
                     strtok(retVal, " ");
                     printf("%s: %s ", printArr[i], retVal);
                  }
               }
            }
            printf("\n");
         }
      }
   }
}

int main()
{
   char c;
   char line[53];
   FILE *file;
   file = fopen("final.txt", "r");
   int query_num=1;
   int file_size=0;
   if (file) {
      // count number of lines in file
      while (fgets(line, 53, file)!=NULL) {
         file_size++;
      }

      // return to beginning of file (thanks OS)
      fseek(file, 0, SEEK_SET);

      // allocate array of strings
      char **query_strs=malloc(53*file_size);

      // parse through file and call respective
      // query function
      int query_idx=0;
      int security=0;
      while (fgets(line, 53, file)!=NULL) {
         if (line[strlen(line)-3]==' ' && query_idx==0) {
            char securityStr=line[strlen(line)-2];
            security=securityStr-'0';
         }
         else if (query_idx==0) security=0;
         query_strs[query_idx]=(char*)malloc(strlen(line));
         strcpy(query_strs[query_idx], line);
         query_idx++;
         if (line[strlen(line)-2]==';') {
            char *query;
            query=(char*)malloc(strlen(query_strs[0]));
            strcpy(query, query_strs[0]);
            strtok(query, " ");
            if (strcmp(query, "FIND\n")==0 || strcmp(query, "FIND")==0) {
               find_query(query_strs, query_idx, query_num, security);
            }
            else if (strcmp(query, "SORT\n")==0 || strcmp(query, "SORT")==0) {
               sort_query(query_strs, query_idx, query_num, security);
            }
            else {
               printf("\n//Query %d\nERROR -- no such operation\n", query_num);
            }
            query_num++;
            query_idx=0;
         }
      }
      fclose(file);
   }

   return 0;
}

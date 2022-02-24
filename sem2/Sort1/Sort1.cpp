#include <iostream>
#include <stdio.h>
using namespace std;

bool fileNULL(const char* fileName)
{
    FILE* f1;
    fopen_s(&f1, fileName, "rt");
    if (feof(f1))
        return 0;
    return 1;
}

bool createFileWithRandomNumbers(const char *fileName, const int numbersCount, const int maxNumberValue)
{
    FILE *f1;
    fopen_s(&f1,fileName, "wt");
    if (f1 == NULL) {
        cout << "Ошибка при открытии файла";
        return 0;
    }
    for (int i = 0; i < numbersCount; i++)
    {
        int x = rand() % maxNumberValue;
        fprintf(f1, " %d", x);
    }
    fclose(f1);
    return 1;
}

bool isFileContainsSortedArray(const char* fileName)
{
    FILE* f1;
    fopen_s(&f1, fileName, "rt");
    int x,x2;
    fscanf_s(f1, "%d", &x);
    while (!feof(f1))
    {
        fscanf_s(f1, "%d", &x2);
        if (x > x2) {
            fclose(f1);
            return 0;
        }
        x = x2;
    }
    fclose(f1);
    return 1;
}

void sortFile(const char* fileName)
{
    FILE *f1, *fileA, * fileB, * fileC, * fileD;
    const char* filenameA = "fa.txt", * filenameB = "fb.txt", * filenameC = "fc.txt", * filenameD = "fd.txt";
    fopen_s(&f1, fileName, "rt");
    fopen_s(&fileA, filenameA, "wt");
    fopen_s(&fileB, filenameB, "wt");
    int x0, x1;
    while (!feof(f1))
    {
        fscanf_s(f1, "%d", &x0);
        fprintf(fileA, " %d", x0);
        fscanf_s(f1, "%d", &x1);
        fprintf(fileB, " %d", x1);
    }
    fclose(fileA);
    fclose(fileB);
    fclose(f1);
    int p=1;
    bool n = 1;
    while ((fileNULL(filenameB)))
    {
        fopen_s(&fileA, filenameA, "rt");
        fopen_s(&fileB, filenameB, "rt");
        fopen_s(&fileC, filenameC, "wt");
        fopen_s(&fileD, filenameD, "wt");
        {
            fscanf_s(fileA, "%d", &x0);
            fscanf_s(fileB, "%d", &x1);
            int k = 0;
            n=1-n;
            while ((!feof(fileA)) && (!feof(fileB)))
            {
                int i = 0, j = 0;
                while ((!feof(fileA)) && (!feof(fileB)) && (i < p) && (j < p))
                {
                    if (x0 < x1)
                    {
                        if (n == 0)
                            fprintf(fileC, " %d", x0);
                        else
                            fprintf(fileD, " %d", x0);
                        fscanf_s(fileA, "%d", x0);
                        i++;
                    }
                    else
                    {
                        if (n == 0)
                            fprintf(fileC, " %d", x1);
                        else
                            fprintf(fileD, " %d", x1);
                        fscanf_s(fileB, "%d", x1);
                        j++;
                    }
                }
                while (!feof(fileA) && (i < p))
                {
                    if (n == 0)
                        fprintf(fileC, "%d ", x0);
                    else
                        fprintf(fileD, "%d ", x0);
                    fscanf_s(fileA, "%d", x0);
                    i++;
                }
                while (!feof(fileB) && (j < p))
                {
                    if (n == 0)
                        fprintf(fileC, " %d", x1);
                    else
                        fprintf(fileD, " %d", x1);
                    fscanf_s(fileB, "%d", x1);
                    j++;
                }
                n = n-1;
            }
            while (!feof(fileA))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x0);
                else
                    fprintf(fileD, " %d", x0);
                fscanf_s(fileA, "%d", x0);
            }
            while (!feof(fileB))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x1);
                else
                    fprintf(fileD, " %d", x1);
                fscanf_s(fileB, "%d", x1);
            }
        }
        fclose(fileA);
        fclose(fileB);
        fclose(fileC);
        fclose(fileD);
        p = p * 2;
        fopen_s(&fileC, filenameA, "wt");
        fopen_s(&fileD, filenameB, "wt");
        fopen_s(&fileA, filenameC, "rt");
        fopen_s(&fileB, filenameD, "rt");
        {
            fscanf_s(fileA, "%d", &x0);
            int k = 0;
            n = 1 - n;
            while ((!feof(fileA)) && (!feof(fileB)))
            {
                int i = 0, j = 0;
                while ((!feof(fileA)) && (!feof(fileB)) && (i < p) && (j < p))
                {
                    if (x0 < x1)
                    {
                        if (n == 0)
                            fprintf(fileC, " %d", x0);
                        else
                            fprintf(fileD, " %d", x0);
                        fscanf_s(fileA, "%d", x0);
                        i++;
                    }
                    else
                    {
                        if (n == 0)
                            fprintf(fileC, " %d", x0);
                        else
                            fprintf(fileD, " %d", x0);
                        fscanf_s(fileB, "%d", x1);
                        j++;
                    }
                }
                while (!feof(fileA) && (i < p))
                {
                    if (n == 0)
                        fprintf(fileC, " %d", x0);
                    else
                        fprintf(fileD, " %d", x0);
                    fscanf_s(fileA, "%d", x0);
                    i++;
                }
                while (!feof(fileB) && (j < p))
                {
                    if (n == 0)
                        fprintf(fileC, " %d", x1);
                    else
                        fprintf(fileD, " %d", x1);
                    fscanf_s(fileB, "%d", x1);
                    j++;
                }
                n = n - 1;
            }
            while (!feof(fileA))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x0);
                else
                    fprintf(fileD, " %d", x0);
                fscanf_s(fileA, "%d", x0);
            }
            while (!feof(fileB))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x1);
                else
                    fprintf(fileD, " %d", x1);
                fscanf_s(fileB, "%d", x1);
            }
        }
        p = p * 2;
        fclose(fileA);
        fclose(fileB);
        fclose(fileC);
        fclose(fileD);
    }
    fopen_s(&f1, fileName, "rt");
    fopen_s(&fileA, filenameA, "wt");
    int x=0;
    while (!feof(fileA))
    {
        fscanf_s(fileA, "%d",x);
        fprintf(f1, " %d", x);
    }
}

int createAndSortFile(const char* fileName, const int numbersCount, const int maxNumberValue)
{
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }
    sortFile(fileName); //Вызов вашей функции сортировки
    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }
    return 1;
}

int main()
{
    const char* fileName = "file.txt";
    const int numbersCount = 10;
    const int maxNumberValue = 10;
    createFileWithRandomNumbers(fileName,numbersCount,maxNumberValue);
    for (int i = 0; i < 1; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue)) {
        case 1:
            std::cout << "Test passed." << std::endl;
            break;

        case -1:
            std::cout << "Test failed: can't create file." << std::endl;
            break;

        case -2:
            std::cout << "Test failed: file isn't sorted." << std::endl;
            break;
        }
        return 0;
    }
}
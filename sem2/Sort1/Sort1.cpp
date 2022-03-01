﻿#include <iostream>
#include <stdio.h>
using namespace std;

struct File
{
    FILE* file;
    File(const char* fileName, const char* openMode)
    {
        fopen_s(&file, fileName, openMode);
    }
    ~File()
    {
        if (file != NULL)
            fclose(file);
    }
    operator FILE* () const
    {
        return file;
    }
    void rediscoveryFile(const char *newname,const char *openMode)
    {
        fclose(file);
        fopen_s(&file, newname, openMode);
    }
};

bool fileNULL(const char* fileName)
{
    File f1(fileName, "rt");
    if (feof(f1))
        return 0;
    return 1;
}

bool createFileWithRandomNumbers(const char *fileName, const int numbersCount, const int maxNumberValue)
{
    File f1(fileName, "wt");
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
    File f1(fileName, "rt");
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
    const char* filenameA = "fa.txt", * filenameB = "fb.txt", * filenameC = "fc.txt", * filenameD = "fd.txt";
    File f1(fileName,"rt");
    File fileA(filenameA, "wt");
    File fileB(filenameB, "wt");
    File fileC(filenameC, "wt");
    File fileD(filenameD, "wt");
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
        fileA.rediscoveryFile(filenameA, "rt");
        fileB.rediscoveryFile(filenameB, "rt");
        fileC.rediscoveryFile(filenameC, "wt");
        fileD.rediscoveryFile(filenameD, "wt");
        {
            fscanf_s(fileA, "%d", &x0);
            fscanf_s(fileB, "%d", &x1);
            int k = 0;
            n=1-n;
            do
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
                        if (!feof(fileA))
                        fscanf_s(fileA, "%d", &x0);
                        i++;
                    }
                    else
                    {
                        if (n == 0)
                            fprintf(fileC, " %d", x1);
                        else
                            fprintf(fileD, " %d", x1);
                        if (!feof(fileB))
                        fscanf_s(fileB, "%d", &x1);
                        j++;
                    }
                }
                while (!feof(fileA) && (i < p))
                {
                    if (n == 0)
                        fprintf(fileC, " %d", x0);
                    else
                        fprintf(fileD, " %d", x0);
                    if (!feof(fileA))
                    fscanf_s(fileA, "%d", &x0);
                    i++;
                }
                while (!feof(fileB) && (j < p))
                {
                    if (n == 0)
                        fprintf(fileC, " %d", x1);
                    else
                        fprintf(fileD, " %d", x1);
                    if (!feof(fileB))
                    fscanf_s(fileB, "%d", &x1);
                    j++;
                }
                n = n-1;
            } while ((!feof(fileA)) && (!feof(fileB)));
            while (!feof(fileA))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x0);
                else
                    fprintf(fileD, " %d", x0);
                if (!feof(fileA))
                fscanf_s(fileA, "%d", &x0);
            }
            while (!feof(fileB))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x1);
                else
                    fprintf(fileD, " %d", x1);
                if (!feof(fileB))
                fscanf_s(fileB, "%d", &x1);
            }
        }
        fclose(fileA);
        fclose(fileB);
        fclose(fileC);
        fclose(fileD);
        p = p * 2;
        //Так как алгоритм разбиения чисел по файлам одинаковый, целесообразно взять туже функцию, но в ссылках на файлы указать противоположные им имена
        // т.е. файл С под именем A, а файл D под B
        fileC.rediscoveryFile(filenameA, "wt");
        fileD.rediscoveryFile(filenameB, "wt");
        fileA.rediscoveryFile(filenameC, "rt");
        fileB.rediscoveryFile(filenameD, "rt");
        {
            fscanf_s(fileA, "%d", &x0);
            fscanf_s(fileB, "%d", &x1);
            int k = 0;
            n = 1 - n;
            do
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
                        if (!feof(fileA))
                        fscanf_s(fileA, "%d", &x0);
                        i++;
                    }
                    else
                    {
                        if (n == 0)
                            fprintf(fileC, " %d", x0);
                        else
                            fprintf(fileD, " %d", x0);
                        if (!feof(fileB))
                        fscanf_s(fileB, "%d", &x1);
                        j++;
                    }
                }
                while (!feof(fileA) && (i < p))
                {
                    if (n == 0)
                        fprintf(fileC, " %d", x0);
                    else
                        fprintf(fileD, " %d", x0);
                    if (!feof(fileA))
                    fscanf_s(fileA, "%d", &x0);
                    i++;
                }
                while (!feof(fileB) && (j < p))
                {
                    if (n == 0)
                        fprintf(fileC, " %d", x1);
                    else
                        fprintf(fileD, " %d", x1);
                    if (!feof(fileB))
                    fscanf_s(fileB, "%d", &x1);
                    j++;
                }
                n = n - 1;
            } while ((!feof(fileA)) && (!feof(fileB)));
            while (!feof(fileA))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x0);
                else
                    fprintf(fileD, " %d", x0);
                if (!feof(fileA))
                fscanf_s(fileA, "%d", &x0);
            }
            while (!feof(fileB))
            {
                if (n == 0)
                    fprintf(fileC, " %d", x1);
                else
                    fprintf(fileD, " %d", x1);
                if (!feof(fileB))
                fscanf_s(fileB, "%d", &x1);
            }
        }
        p = p * 2;
        fclose(fileA);
        fclose(fileB);
        fclose(fileC);
        fclose(fileD);
    }
    f1.rediscoveryFile(fileName, "rt");
    fileA.rediscoveryFile(filenameA, "wt");
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
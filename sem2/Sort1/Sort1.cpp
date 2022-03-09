#include <iostream>
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
    int a, readRes;
    if (feof(f1))
       return false;
    readRes = fscanf_s(f1, "%d", &a);
    if (readRes == EOF)
        return false;
    return true;

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
void fragmintationFile(const char* fileName, const char* filenameA, const char* filenameB)
{
    File f1(fileName, "rt");
    File fileA(filenameA, "wt");
    File fileB(filenameB, "wt");
    int x;
    while (!feof(f1))
    {
        if (!feof(f1)) {
            fscanf_s(f1, "%d", &x);
            fprintf(fileA, "%d\n", x);
        }
        if (!feof(f1)) {
            fscanf_s(f1, "%d", &x);
            fprintf(fileB, "%d\n", x);
        }
    }
}

void integrationFile(const char* fileNameA, const char* fileNameB, const char* fileNameC, const char* fileNameD, int p)
{
    File fileA(fileNameA, "rt");
    File fileB(fileNameB, "rt");
    File fileC(fileNameC, "wt");
    File fileD(fileNameD, "wt");
    int x0, x1;
    fscanf_s(fileA,"%d",&x0);
    fscanf_s(fileB,"%d",&x1);
    int k = 0;
    bool n = 0;
    while (!feof(fileA) && !feof(fileB))
        {
            int i = 0, j = 0;
            while (!feof(fileA) && (!feof(fileB)) && (i < p) && (j < p))
            {
                            if (x0 < x1)
                            {
                                if (n == 0)
                                    fprintf(fileC, "%d\n", x0);
                                else
                                    fprintf(fileD, "%d\n", x0);
                                if(!feof(fileA))
                                    fscanf_s(fileA, "%d", &x0);
                                i++;
                            }
                            else
                            {
                                if (n == 0)
                                    fprintf(fileC, "%d\n", x1);
                                else
                                    fprintf(fileD, "%d\n", x1);
                                if(!feof(fileB))
                                    fscanf_s(fileB, "%d", &x1);
                                j++;
                            }
                n = 1 - n;
            }
            while (!feof(fileA))
            {
                    if (n == 0)
                        fprintf(fileC, "%d\n", x0);
                    else
                        fprintf(fileD, "%d\n", x0);
                    if (!feof(fileA))
                    fscanf_s(fileA, "%d", &x0);
                    i++;
            }
            while (!feof(fileB))
            {
                    if (n == 0)
                        fprintf(fileC, "%d\n", x1);
                    else
                        fprintf(fileD, "%d\n", x1);
                    if (!feof(fileB))
                        fscanf_s(fileB, "%d", &x1);
                    j++;
        }
    }
}

void sortFile(const char* fileName)
{
    const char* fileNameA = "fa.txt", * fileNameB = "fb.txt", * fileNameC = "fc.txt", * fileNameD = "fd.txt";
    fragmintationFile(fileName, fileNameA, fileNameB);
    int p = 1;
    integrationFile(fileNameA, fileNameB, fileNameC, fileNameD, p);
    p = p * 2;
    while ((fileNULL(fileNameB) == 1 )|| (fileNULL(fileNameD) == 1))
    {
        integrationFile(fileNameA, fileNameB, fileNameC, fileNameD, p);
        p = p * 2;
        if ((fileNULL(fileNameB) == 1) || (fileNULL(fileNameD) == 1))
        {
            integrationFile(fileNameC, fileNameD, fileNameA, fileNameB, p);
            p = p * 2;
        }
    }
    if ((fileNULL(fileNameB) == 1)) {
        File fileA(fileNameA, "rt");
        File f1(fileName, "wt");
        int readRes = EOF + 1;
        int x;
        while (!feof(fileA) && readRes != EOF)
        {
            readRes = fscanf_s(fileA, "%d", &x);
            if (readRes != EOF)
                fprintf(f1, " %d\n", x);
        }
    }
    else
    {
        File fileC(fileNameC, "rt");
        File f1(fileName, "wt");
        int readRes = EOF + 1;
        int x;
        while (!feof(fileC) && readRes != EOF)
        {
            readRes = fscanf_s(fileC, "%d", &x);
            if (readRes != EOF)
                fprintf(f1, " %d\n", x);
        }
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
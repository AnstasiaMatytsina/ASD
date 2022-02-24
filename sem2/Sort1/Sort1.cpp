#include <iostream>
#include <stdio.h>
using namespace std;
/*int createAndSortFile(const char* fileName, const int numbersCount, const int maxNumberValue)
{
    if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
        return -1;
    }
    sortFile(fileName); //Вызов вашей функции сортировки
    if (!isFileContainsSortedArray(fileName)) {
        return -2;
    }
    return 1;
}*/

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
        fprintf(f1, "%d ", x);
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
    const char* filenameA = "fa", * filenameB = "fb", * filenameC = "fc", * filenameD = "fd";
    fopen_s(&f1, fileName, "rt");
    fopen_s(&fileA, filenameA, "wt");
    fopen_s(&fileB, filenameB, "wt");
    int bufferA, bufferB;
    while (!feof(f1))
    {
        fscanf_s(f1, "%d", &bufferA);
        fscanf_s(f1, "%d", &bufferB);
    }
    fclose(fileA);
    fclose(fileB);
    int p=1;

}

int main()
{
    const char* fileName = "file.txt";
    const int numbersCount = 100;
    const int maxNumberValue = 100;
    createFileWithRandomNumbers(fileName,numbersCount,maxNumberValue);
    /*for (int i = 0; i < 10; i++) {
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
    */
}
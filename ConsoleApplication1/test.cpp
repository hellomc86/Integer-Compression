#include <iostream>
#include <fstream>
#include "randomNumber.h"
#include "compress.h"
#include <time.h>

void testInRange(std::vector<int>& numVec, std::vector<int>& deSerNumVec, std::string& str,
    int min, int max, int N);
void printVector(std::vector<int>& numVec);
void printVectorToFile(std::vector<int>& numVec, std::ofstream& myfile);
void printToFile(std::vector<int>& numVec, std::vector<int>& deSerNumVec, std::ofstream& myfile,
    std::string strCompress, std::string strNonCompress);
void test50(std::ofstream& myfile);
void test100(std::ofstream& myfile);
void test500(std::ofstream& myfile);
void test1000(std::ofstream& myfile);
void testOneDigit(std::ofstream& myfile);
void testTwoDigit(std::ofstream& myfile);
void testThreeDigit(std::ofstream& myfile);
void testEachThree(std::ofstream& myfile);

void serializeNonCompress(std::vector<int>& numVec, std::string& str);

int main()
{
    srand(time(NULL));
    std::ofstream myfile;
    myfile.open("myTest.txt");

    test50(myfile);
    test100(myfile);
    test500(myfile);
    test1000(myfile);
    testOneDigit(myfile);    
    testTwoDigit(myfile);
    testThreeDigit(myfile);
    testEachThree(myfile);

    std::cout << "Hello World!\n";
    
    myfile.close();

    return 0;
}

void serializeNonCompress(std::vector<int>& numVec, std::string& str)
{
    for (int i : numVec) str += std::to_string(i) + ",";    
}

void testInRange(std::vector<int>& numVec, std::vector<int>& deSerNumVec, std::string& str,
    int min, int max, int N) {
    makeNrandomNumber(numVec, N, min, max);
    
    serializeCompress(numVec, str);
    
    deSerializeCompress(deSerNumVec, str);
    
}

void testEachNumThreeTimes(std::vector<int>& numVec, std::vector<int>& deSerNumVec, std::string& str) 
{
    for (int i = 1; i < 301; i++)
        for (int j = 0; j < 3; j++)
            numVec.push_back(i);

    serializeCompress(numVec, str);

    deSerializeCompress(deSerNumVec, str);
}

void printVector(std::vector<int>& numVec)
{
    std::cout << std::endl;

    for (int i : numVec) std::cout << i << " " ;

    std::cout << std::endl;
}

void printVectorToFile(std::vector<int>& numVec, std::ofstream& myfile)
{
    myfile << std::endl;

    for (int i : numVec) myfile << i << " ";

    myfile << std::endl;
}

void printToFile(std::vector<int>& numVec, std::vector<int>& deSerNumVec, std::ofstream& myfile,
    std::string strCompress, std::string strNonCompress)
{
    float ratio = (float)strCompress.length() / strNonCompress.length();
    myfile << "compressed length: " << strCompress.length() << std::endl;
    myfile << "non compressed length: " << strNonCompress.length() << std::endl;
    myfile << "compressed length / non compressed length: " << ratio
        << std::endl;

    printVectorToFile(numVec, myfile);
    printVectorToFile(deSerNumVec, myfile);
}

void test50(std::ofstream& myfile)
{
    myfile << "min 1 max 300 number of samples 50" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testInRange(numVec, deSerNumVec, strCompress, 1, 300, 50);
    
    serializeNonCompress(numVec, strNonCompress);
    
    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);

}

void test100(std::ofstream& myfile)
{
    myfile << "min 1 max 300 number of samples 100" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testInRange(numVec, deSerNumVec, strCompress, 1, 300, 100);

    serializeNonCompress(numVec, strNonCompress);
    
    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);
       
}

void test500(std::ofstream& myfile)
{
    myfile << "min 1 max 300 number of samples 500" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testInRange(numVec, deSerNumVec, strCompress, 1, 300, 500);

    serializeNonCompress(numVec, strNonCompress);
    
    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);
}

void test1000(std::ofstream& myfile)
{
    myfile << "min 1 max 300 number of samples 1000" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testInRange(numVec, deSerNumVec, strCompress, 1, 300, 1000);

    serializeNonCompress(numVec, strNonCompress);
    
    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);
}

void testOneDigit(std::ofstream& myfile)
{
    myfile << "min 1 max 9 number of samples 900 Only single digit numbers" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testInRange(numVec, deSerNumVec, strCompress, 1, 9, 900);

    serializeNonCompress(numVec, strNonCompress);
    
    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);
}

void testTwoDigit(std::ofstream& myfile)
{
    myfile << "min 10 max 99 number of samples 900 Only two digit numbers" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testInRange(numVec, deSerNumVec, strCompress, 10, 99, 900);

    serializeNonCompress(numVec, strNonCompress);

    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);
}

void testThreeDigit(std::ofstream& myfile)
{
    myfile << "min 100 max 300 number of samples 900 Only three digit numbers" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testInRange(numVec, deSerNumVec, strCompress, 100, 300, 900);

    serializeNonCompress(numVec, strNonCompress);

    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);
}

void testEachThree(std::ofstream& myfile)
{
    myfile << "min 1 max 300 number of samples 900 each number three times" << std::endl;
    std::vector<int> numVec, deSerNumVec; std::string strCompress, strNonCompress;
    testEachNumThreeTimes(numVec, deSerNumVec, strCompress);

    serializeNonCompress(numVec, strNonCompress);

    printToFile(numVec, deSerNumVec, myfile, strCompress, strNonCompress);
}
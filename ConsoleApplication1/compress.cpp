#include "compress.h"


void getCountBySize(std::vector<int>& numVec, int& halfByteCount, int& byteCount)
{
	halfByteCount = byteCount = 0;
	for (auto i : numVec)
		if (i < 16) halfByteCount++;
		else if (i < 256) byteCount++;

	if (halfByteCount & 1) { // if halfByteCount is odd make it even
		halfByteCount--;
		byteCount++;
	}

}

int comparator(const void* p, const void* q)
{
	// Get the values at given addresses 
	const int* A = (const int*)p;
	const int* B = (const int*)q;
	return (*A > *B) - (*A < *B);
}


void serializeCompress(std::vector<int>& numVec, std::string& resultData)
{
	if (numVec.empty()) return;
		
	int vecCount = 0;

	std::qsort(numVec.data(), numVec.size(), sizeof(int), comparator);

	int halfByteCount, byteCount;

	getCountBySize(numVec, halfByteCount, byteCount);

	serializeCountHeaders(resultData, halfByteCount, byteCount);

	serializeHalfByteNumbers(resultData, vecCount, halfByteCount, numVec);

	serializeByteNumbers(resultData, vecCount, byteCount, numVec);

	serializeTwoByteNumbers(resultData, vecCount, numVec);

	
}

void serializeCountHeaders(std::string& str, int halfByteCount, int byteCount)
{
	str += (char)(halfByteCount / 256);
	str += (char)(halfByteCount % 256);
	str += (char)(byteCount / 256);
	str += (char)(byteCount % 256);
}

void serializeHalfByteNumbers(std::string& str, int& vecCount, int halfByteCount, std::vector<int>& numVec)
{
	unsigned char tempByte;
	bool isMostSignificant = true;
	unsigned int vecElement;

	for (; vecCount < halfByteCount; vecCount++)
		if (numVec[vecCount] < 16) {

			vecElement = numVec[vecCount];

			if (isMostSignificant) {
				//vecElement << 4;
				tempByte = vecElement << 4;
				isMostSignificant = false;
			}
			else {
				tempByte |= vecElement;
				str += tempByte;
				isMostSignificant = true;
			}
		}
}

void serializeByteNumbers(std::string& str, int& vecCount, int byteCount, std::vector<int>& numVec)
{
	int lastEl = vecCount + byteCount;
	for (; vecCount < lastEl; vecCount++)
	{
		str += (unsigned char)numVec[vecCount];
	}
}

void serializeTwoByteNumbers(std::string& str, int& vecCount, std::vector<int>& numVec)
{
	unsigned int vecElement;

	for (; vecCount < numVec.size(); vecCount++)
	{
		vecElement = (unsigned int) numVec[vecCount];

		str += (unsigned char)(vecElement >> 8);
		str += (unsigned char)(vecElement & 0xFF);
	}
}


void deSerializeCompress(std::vector<int>& numVec, std::string& resultData)
{
	if (resultData.empty()) return;

	int strCount = HEADER_COUNT;
	
	int halfByteCount, byteCount;		

	deSerializeCountHeaders(resultData, halfByteCount, byteCount);

	deSerializeHalfByteNumbers(resultData, strCount, halfByteCount, numVec);

	deSerializeByteNumbers(resultData, strCount, byteCount, numVec);

	deSerializeTwoByteNumbers(resultData, strCount, byteCount, numVec);
}

void deSerializeCountHeaders(std::string& str, int& halfByteCount, int& byteCount)
{
	halfByteCount = (unsigned char)str[0] * 256 + (unsigned char)str[1];
	byteCount = (unsigned char)str[2] * 256 + (unsigned char)str[3];
}

void deSerializeHalfByteNumbers(std::string& str, int& strCount, int halfByteCount, std::vector<int>& numVec)
{
	
	bool isMostSignificant = true;
	unsigned char strElement;
	int bytesUsed = halfByteCount / 2;

	for (; strCount < bytesUsed + HEADER_COUNT; strCount++)
		{

		strElement = (unsigned char) str[strCount];
		numVec.push_back(strElement >> 4);

		numVec.push_back(strElement & 0xF);
		}
	
}

void deSerializeByteNumbers(std::string& str, int& strCount, int byteCount, std::vector<int>& numVec)
{
	int lastByteEl = strCount + byteCount;
	int strElement;
	for (; strCount < lastByteEl; strCount++)
	{
		strElement = (unsigned char) str[strCount];
		numVec.push_back(strElement);		
	}
}

void deSerializeTwoByteNumbers(std::string& str, int& strCount, int byteCount, std::vector<int>& numVec)
{	
	unsigned int strElement;

	for (; strCount < str.length(); strCount +=2)
	{
		strElement = (unsigned char) str[strCount] * 256 + (unsigned char)str[strCount + 1];
		numVec.push_back(strElement);		
	}
}

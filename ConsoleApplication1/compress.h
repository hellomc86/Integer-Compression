#pragma once

#include <string>
#include <vector>

#define HEADER_COUNT 4

#ifdef __cplusplus                                                              
extern "C" int comparator(const void* p, const void* q);
#else                                                                           
int comparator(const void* p, const void* q);  /* macro is automatically */
#endif                                    /* defined by the C++/MVS compiler  */


void getCountBySize(std::vector<int>& numVec, int& halfByteCount, int& byteCount);

int comparator(const void* p, const void* q);

void serializeCompress(std::vector<int>& numVec, std::string& resultData);

void serializeCountHeaders(std::string& str, int halfByteCount, int byteCount);

void serializeHalfByteNumbers(std::string& str, int& vecCount, int halfByteCount, std::vector<int>& numVec);

void serializeByteNumbers(std::string& str, int& vecCount, int byteCount, std::vector<int>& numVec);

void serializeTwoByteNumbers(std::string& str, int& vecCount, std::vector<int>& numVec);

void deSerializeCompress(std::vector<int>& numVec, std::string& resultData);

void deSerializeCountHeaders(std::string& str, int& halfByteCount, int& byteCount);

void deSerializeHalfByteNumbers(std::string& str, int& strCount, int halfByteCount, std::vector<int>& numVec);

void deSerializeByteNumbers(std::string& str, int& strCount, int byteCount, std::vector<int>& numVec);

void deSerializeTwoByteNumbers(std::string& str, int& strCount, int byteCount, std::vector<int>& numVec);

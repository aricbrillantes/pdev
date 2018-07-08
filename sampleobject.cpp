
// BEGIN: Generated from SampleObject.definition
#include "sampleobject.h"
#include "standardfilesystem.h"
#include <string>

SampleObject::SampleObjectTypeDesc SampleObject::s_Desc;

SampleObject::SampleObjectTypeDesc::SampleObjectTypeDesc()
{
	m_name = "SampleObject";
	m_memberDesc.push_back(MemberDesc("MyIntVariable", Type_Int, 1, offsetof(SampleObject, m_MyIntVariable)));
	m_memberDesc.push_back(MemberDesc("MyBoolVariable", Type_Bool, 1, offsetof(SampleObject, m_MyBoolVariable)));
	m_memberDesc.push_back(MemberDesc("MyFloatVariable", Type_Float, 1, offsetof(SampleObject, m_MyFloatVariable)));
	m_memberDesc.push_back(MemberDesc("MyDoubleVariable", Type_Double, 1, offsetof(SampleObject, m_MyDoubleVariable)));
	m_memberDesc.push_back(MemberDesc("MyArray", Type_Int, 12, offsetof(SampleObject, m_MyArray)));
}

SampleObject::SampleObject() : m_MyIntVariable(0), m_MyBoolVariable(false), m_MyFloatVariable(0.0f), m_MyDoubleVariable(0.0), m_MyArray{0}
{
}

SampleObject::~SampleObject()
{

}
// END: Generated from SampleObject.definition

// BEGIN: Custom Code
#include <iostream>
void SampleObject::myCustomFunction()
{
	std::cout << "Custom Function!" << std::endl;
}
void SampleObject::Save(StandardFileSystem fs, const char* filename)
{
    int intVar;
	bool boolVar;
	float floatVar;
	double doubleVar;
	int intArray[12];

	std::string toSave;


    std::cout << "Saving In Function!" << std::endl;
    if (fs.fileExists(filename))
	{
		fs.deleteFile(filename);
	}
    //writeBuffer must contain the data to save, this is where we implement the parser
    //const char* writeBuffer = "Hello World";
	IFile* createdFile = fs.createFile(filename);
	if (!createdFile)
	{
		std::cout << "Failed to create a file (infunction)" << std::endl;
		return;
	}


    const TypeDesc& desc = this->typeDescription();
	std::cout << desc.name() << " Contents" << std::endl;
    toSave = desc.name();
    std::cout << toSave << std::endl;

	this->getMemberValue("MyIntVariable", intVar);
    std::string bufferInt = std::to_string(intVar);
    toSave = toSave + "|" + bufferInt;
    std::cout << toSave << std::endl;

	this->getMemberValue("MyBoolVariable", boolVar);
    std::string bufferBool = std::to_string(boolVar); // 1 or 0 yung isave
    toSave = toSave + "|" + bufferBool;
    std::cout << toSave << std::endl;

    this->getMemberValue("MyFloatVariable", floatVar);
    std::string bufferFloat = std::to_string(floatVar);
    toSave = toSave + "|" + bufferFloat;
    std::cout << toSave << std::endl;

    this->getMemberValue("MyDoubleVariable", doubleVar);
    std::string bufferDouble = std::to_string(doubleVar);
    toSave = toSave + "|" + bufferDouble;
    std::cout << toSave << std::endl;

    toSave = toSave + "|";
    this->getMemberArray("MyArray", intArray, 12);
    for (int i = 0; i < 12; i++)
		{
			std::string bufferArray = std::to_string(intArray[i]);
			toSave = toSave + bufferArray + ",";
		}
    toSave = toSave + "^"; // ^ is end of file
    std::cout << toSave << std::endl;

    char *toSaveChar = new char[toSave.length() + 1];
    strcpy(toSaveChar, toSave.c_str());

	if (!createdFile->write(toSaveChar, strlen(toSaveChar) + 1 /* add 1 to length for null terminator */))
	{
		std::cout << "Failed to write to file (infunction)" << std::endl;
	}
	delete createdFile;
	std::cout << "Successfully created file" << std::endl;

}
void SampleObject::Load(StandardFileSystem fs, const char* filename)
{
    std::cout << "Loading In Function!" << std::endl;

    IFile* openedFile = fs.openFile(filename);
	if (!openedFile)
	{
		std::cout << "Failed to open file (infunction)" << std::endl;
	}
	size_t size = openedFile->length();
	char* destBuffer = new char[size];
	if (!openedFile->read(destBuffer, size))
	{
		std::cout << "Failed to read from file (infunction)!" << std::endl;
	}
	else
	{
		std::cout << "(infunction) File Contents:" << std::endl;
		//destBuffer must be parsed into an object

		std::cout << destBuffer << std::endl;
	}
	// Close the file
	delete openedFile;

}
// END: Custom Code

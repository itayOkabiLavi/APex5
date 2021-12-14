

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

class StandardIO: public DefaultIO {
public:
    StandardIO() { }
    string read() override {
        string data;
        std::cin>>data;
        return data;
    }
    void read(float *f) override {
        // ???
    }
    void write(string text) override { std::cout<<text; }
    void write(float f) override { this->write(to_string(f)); }
    ~StandardIO() { }
};
// you may add here helper classes


// you may edit this class
class Command{
	DefaultIO* dio;
    string description;
public:
	Command(DefaultIO* dio, string description):dio(dio), description(description){}
	virtual void execute()=0;
    DefaultIO* getDIO() { return this->dio; }
    void printDescription() { this->getDIO()->write(description); }
	virtual ~Command(){}
};

class UploadTimeSeries : public  Command {
public:
    UploadTimeSeries(DefaultIO* dio): Command(dio,
                                              "") { }
    void execute() override{}
};

class AlgorithmSettingsCMD : public Command {
public:
    AlgorithmSettingsCMD(DefaultIO* dio): Command(dio,
                                                  "algorithm settings.") { }
    void execute() override{}
};

class DetectAnomaliesCMD : public Command{
public:
    DetectAnomaliesCMD(DefaultIO* dio): Command(dio,
                                                "") { }
    void execute() override{}
};

class ExitCMD : public Command{
public:
    ExitCMD(DefaultIO* dio): Command(dio,
                                     "exit.") { }
    void execute() override {
        exit(0);
    }
    ~ExitCMD(){ }
};



// implement here your command classes



#endif /* COMMANDS_H_ */

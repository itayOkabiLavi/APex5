#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->cmd_list.push_back(UploadTimeSeries(dio));
    this->cmd_list.push_back(AlgorithmSettingsCMD(dio));
    this->cmd_list.push_back(DetectAnomaliesCMD(dio));

    this->cmd_list.push_back(ExitCMD(dio));
}

void CLI::start(){
    while (true) {
        for (std::vector<Command>::iterator cmd = cmd_list.begin(); cmd != cmd_list.end(); ++cmd) {
            cmd->printDescription();
        }
        int i;
        std::cin>>i;
        cmd_list.at(i).execute();
    }
}


CLI::~CLI() {
}


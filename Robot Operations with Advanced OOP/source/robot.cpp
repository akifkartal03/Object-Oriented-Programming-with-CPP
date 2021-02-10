#include "robot.h"

namespace eagle{
    Robot::Robot():Robot(rover,2,5.0){
        //delegation
    }
    Robot::Robot(robotType type,int engineNumber,double loadAmount):type(type),
    engineNumber(engineNumber),loadAmount(loadAmount){

    }
    int Robot::getEngineNumber() const{
        return engineNumber;
    }
    robotType Robot::getRobotType() const{
        return type;
    }
    double Robot::getLoadAmount() const{
        return loadAmount;
    }
    void Robot::setEngineNumber(int engineNumber){
        this->engineNumber = engineNumber;
    }
    void Robot::setRobotType(robotType type){
        this->type = type;
    }
    void Robot::setLoadAmount(double loadAmount){
        this->loadAmount = loadAmount;
    }
}
#ifndef ROBOT_H
#define ROBOT_H
#include<iostream>
#include<string>
using namespace std;
namespace eagle{
    enum robotType { rover, wheeled, crawler, spider,
                    hibrit,series,parallel,not_rover};
    class Robot{
        public:
            Robot();
            Robot(robotType type,int engineNumber,double loadAmount);
            /*----getters and setters----*/
            robotType getRobotType() const;
            void setRobotType(robotType type);
            int getEngineNumber() const;
            void setEngineNumber(int engineNumber);
            double getLoadAmount() const;
            void setLoadAmount(double loadAmount);
        protected:
            robotType type;
            int engineNumber;
            double loadAmount;
    };
}


#endif
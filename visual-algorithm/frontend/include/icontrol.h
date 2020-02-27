#ifndef ICONTROL_H
#define ICONTROL_H

class IControl
{
public:
    /**
     * @brief 等待下一步执行
     */
    virtual void waitForNextStep()=0;
};

#endif // ICONTROL_H


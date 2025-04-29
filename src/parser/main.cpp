#include "MooreStateFactory.h"
#include <iostream>
#include <vector>

int main()
{
    StateFactory factory;
    factory.createState("S1", "Output1")->addTransition('a', factory.createState("S2", "Output2"));
    factory.createState("S2", "Output2")->addTransition('b', factory.createState("S3", "Final Output"));
    const std::vector<char> inputs = {'a', 'b'};
    IMooreState *current = factory.getState("S1");

    for (char input : inputs)
    {
        if (!current)
            break;

        std::cout << "Current: " << current->getName()
                  << " | Input: '" << input << "'"
                  << " | Output: " << current->getOutput() << std::endl;

        current = current->getNextState(input);
    }

    if (current)
    {
        std::cout << "Final state: " << current->getName()
                  << " | Final output: " << current->getOutput() << std::endl;
    }

    return 0;
}
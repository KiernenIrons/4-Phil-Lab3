#pragma once
#include <list>
#include <stack>
#include <vector>

#include "LegoFactory.h"
#include "ClayFactory.h"
#include "ConcreteFactory.h"
#include "Globals.h"

class Command
{
public:
    virtual ~Command(){};
    virtual void execute() = 0;
    virtual void undo(){};
    virtual void redo(){};
    virtual void add(){counter++;}
    virtual void remove(){counter--;}
    virtual int getAmount(){return counter;}
protected:
    Command(){};
    int counter = 0;
};

class MacroCommand : public Command
{
public:
    MacroCommand(){};
    virtual ~MacroCommand();

    virtual void addCommand(Command* command)
    {
        command->add();
        commands.push_back(command);
    };

    virtual void removeCommand()
    {
        if (commands.size() > 0)
        {
            std::cout << "Remove" << std::endl;
            URCommands.push(commands.at(commands.size()-1));
            commands.pop_back();
            URCommands.top()->remove();
        }
    };

    virtual void undo()
    {
         if(commands.size() > 0)
        {
            std::cout << "Undo" << std::endl;
            URCommands.push(commands.at(commands.size()-1));
            commands.pop_back();
            URCommands.top()->remove();
        }
    };

    virtual void redo(Command* command)
    {
        if(URCommands.size() > 0)
        {
            std::cout << "Redo" << std::endl;
            URCommands.top()->add();
            commands.push_back(URCommands.top());
            URCommands.pop();
        }
    };

    virtual void execute()
    {
        if(commands.size() > 0)
        {
            for(Command* command : commands)
            {
                command->execute();
            }
        }
    };

private:
    std::vector<Command*> commands;
    std::stack<Command*> URCommands;
};

class BuildLego : public Command
{ 
public:
    BuildLego() = default;
    ~BuildLego(){};
    virtual void execute() 
    {
        std::cout << "Order Lego" << std::endl;
        Factory* factory = new LegoFactory();
        m_bricks.push_back(factory->getBricks());
        counter = 0;
        add();
    }

    virtual void undo()
    {
        m_bricks.pop_back();
        legoCounter--;
        std::cout << "Remove Lego" << std::endl;
    }
};

class BuildClay : public Command
{
public:
    BuildClay() = default;
    ~BuildClay(){};
    virtual void execute() 
    {
        std::cout << "Order Clay" << std::endl;
        Factory* factory = new ClayFactory();
        m_bricks.push_back(factory->getBricks());
        counter = 0;
    }

    virtual void undo()
    {
        m_bricks.pop_back();
        clayCounter--;
        std::cout << "Remove Clay" << std::endl;
    }
};

class BuildConcrete : public Command
{
public:
    BuildConcrete() = default;
    ~BuildConcrete(){};
    virtual void execute() 
    {
        std::cout << "order Concrete" << std::endl;
        Factory* factory = new ConcreteFactory();
        m_bricks.push_back(factory->getBricks());
        counter = 0;
    }

    virtual void undo()
    {
        m_bricks.pop_back();
        concreteCounter--;
        std::cout << "Remove Concrete" << std::endl;
    }
};
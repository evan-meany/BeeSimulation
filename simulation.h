#pragma once

#include "pch.h"
#include "bee.h"
#include "tile.h"

static void ClearScreen()
{
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

class Simulation
{
public:
   Simulation(const size_t population) : m_BeeColony(population) {}

   void Start()
   {
      while(1)
      {
         Calendar& cal = Calendar::GetInstance();
         cal.PrintDate();

         std::string command = GetUserInput();
         if (command == "a")
         {
            Advance(1);
         }
         else if (command == "s")
         {
            break;
         }
         else if (command == "t")
         {
            TileMap& tileMap = TileMap::GetInstance();
            tileMap.PrintTileMap();
         }
         else if (command == "c")
         {
            m_BeeColony.PrintColonyInfo();
         }
         else if (command == "cmds")
         {
            std::cout << "These are the commands: " << std::endl;
         }
         else if (command == "cls")
         {
            ClearScreen();
         }
         else if (command == "days")
         {
            std::cout << "Days since start: " << 
            Calendar::GetInstance().DaysSince(Date(1,1,1)) << std::endl;
         }
         else 
         {
            std::cout << "Unknown command" << std::endl;
         }
      }
   }

private:
   Colony m_BeeColony;
   // Eventually have 'modes' so that can either do
   // sim of individual bees or en masse
private:
   std::string GetUserInput()
   {
      std::string command;
      std::cout << "Enter a command: ";
      std::getline(std::cin, command);
      return command;
   }

   void Advance(size_t time)
   {
      Calendar& cal = Calendar::GetInstance();
      cal.AdvanceDay();
   }
};


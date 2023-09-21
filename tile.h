#pragma once

#include "pch.h"
#include "bee.h"

enum TileType
{
   COLONY, POLLEN, EMPTY
};

struct TileData
{
   std::unordered_set<BeePtr> bees;
};

struct Tile
{
   TileType type;
   std::unique_ptr<TileData> data;

   Tile(TileType type = TileType::EMPTY) : type(type) {}
};

class TileMap
{
private:
   const size_t m_Width = 31, m_Height = 15;
   Tile m_TileMap[31][15];
   TileMap()
   {
      ClearTileMap();
      SetColonyTile(16, 8);
      SetPollenTile(2, 3);
   }

public:
   TileMap(const TileMap&) = delete;
   TileMap& operator=(const TileMap&) = delete;

   static TileMap& GetInstance()
   {
      static TileMap instance;
      return instance;
   }

   void ClearTileMap()
   {
      for (size_t i = 0; i < m_Width; i++)
      {
         for (size_t j = 0; j < m_Height; j++)
         {
            m_TileMap[i][j] = Tile(TileType::EMPTY);
         }
      }
   }

   void SetColonyTile(size_t xpos, size_t ypos)
   {
      m_TileMap[xpos][ypos] = Tile(TileType::COLONY);
   }

   void SetPollenTile(size_t xpos, size_t ypos)
   {
      m_TileMap[xpos][ypos] = Tile(TileType::POLLEN);
   }

   void PrintTileMap()
   {
      std::cout << "Tile Map: " << std::endl;
      std::string dashLine;

      for (int y = m_Height - 1; y >= 0; y--)
      {
         std::string line;
         for (size_t x = 0; x < m_Width; x++)
         {
            char symbol;
            switch (m_TileMap[x][y].type)
            {
               case COLONY:
                  symbol = 'C';
                  break;
               case POLLEN:
                  symbol = 'P';
                  break;
               case EMPTY:
               default:
                  symbol = ' ';
                  break;
            }
            line += "|" + std::string(1, symbol);
         }
         line += '|';
         if (dashLine.empty()) 
         { 
            for (size_t i = 0; i < line.size(); i++) { dashLine += '-'; } 
         }
         std::cout << dashLine << std::endl << line << std::endl; 
      }   
      std::cout << dashLine << std::endl;
   }
};
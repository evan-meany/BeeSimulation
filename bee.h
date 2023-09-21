#pragma once

#include "pch.h"
#include "date.h"

static size_t s_GlobalBeeID = 0;

enum BeeJob
{
   QUEEN, FORAGER, NURSE, HOUSE, GUARD, DRONE, NONE
};

struct Bee
{
   BeeJob job;
   // Date birthDate;
   size_t age;
   size_t id;

   Bee(const BeeJob job) : job(job), age(0)
   {
      // birthDate = Calendar::GetInstance().GetDate();
      id = s_GlobalBeeID++;
   }
};

typedef std::shared_ptr<Bee> BeePtr; 
typedef std::shared_ptr<const Bee> ConstBeePtr; 

class Colony
{
public:
   Colony(const size_t population)
   {
      m_Pollen = population * 2;

      // Set bee demographics
      double percentForager  = 0.50;
      double percentNurse    = 0.33;
      double percentHouse    = 0.15;
      double percentGuard    = 0.02;
      size_t numForager  = population * percentForager;
      size_t numNurse    = population * percentNurse;
      size_t numHouse    = population * percentHouse;
      size_t numGuard    = population * percentGuard;
      
      // Add queen
      AddBee(BeeJob::QUEEN);

      // Add foragers
      for (size_t i = 0; i < numForager; i++)
      {
         AddBee(BeeJob::FORAGER);
      }

      // Add nurses
      for (size_t i = 0; i < numNurse; i++)
      {
         AddBee(BeeJob::NURSE);
      }      

      // Add house
      for (size_t i = 0; i < numHouse; i++)
      {
         AddBee(BeeJob::HOUSE);
      }

      // Add guards
      for (size_t i = 0; i < numGuard; i++)
      {
         AddBee(BeeJob::GUARD);
      }            
   }

   void SimulateDay()
   {
      Forage();
      Nurse();
      House();
      Guard();
   }

   void PrintColonyInfo()
   {
      std::cout << "|======== BEE COLONY INFO ========|" << std::endl;
      std::cout << std::endl;
      for (const auto& [job, jobSet] : m_BeeJobSets)
      {
         std::cout << " Job: " << job << std::endl;
         std::cout << " Size: " << jobSet.size() << std::endl;
      }
      std::cout << std::endl;
      std::cout << "|=================================|" << std::endl;
   }

private:
   std::unordered_map<size_t, BeePtr> m_Bees;
   std::unordered_map<BeeJob, std::unordered_set<BeePtr>> m_BeeJobSets;
   size_t m_Pollen = 0;
   size_t m_BeesIncubating = 0;
   size_t m_UnfedBees = 0;

private:
   void AddBee(BeePtr bee) 
   { 
      // Add to m_Bees
      m_Bees.insert({bee->id, bee}); 

      // Add to m_BeeJobSets
      auto lookup = m_BeeJobSets.find(bee->job);
      if (lookup != m_BeeJobSets.end()) {lookup->second.insert(bee);}
      else
      {
         std::unordered_set<BeePtr> jobSet;
         jobSet.insert(bee);
         m_BeeJobSets.insert({bee->job, jobSet});
      }
   }
   void AddBee(BeeJob job) 
   { 
      BeePtr bee = std::make_shared<Bee>(Bee(job));
      AddBee(bee);
   }

   void Forage()
   {

   }
   void Nurse()
   {

   }
   void House()
   {

   }
   void Guard()
   {

   }
   void FeedBees()
   {
      if (m_Bees.size() > m_Pollen) 
      { 
         m_Pollen = 0; 
         m_UnfedBees = m_Bees.size() - m_Pollen;
      }
      else { m_Pollen -= m_Bees.size(); }
   }
   void KillBees()
   {
      std::random_device rd;
      std::mt19937 gen(rd());

      while(m_UnfedBees > 0)
      {
         std::uniform_int_distribution<> dis(0, m_Bees.size() - 1);
         int random_index = dis(gen);
         auto it = std::begin(m_Bees);
         std::advance(it, random_index);
         while(it->second->job == BeeJob::QUEEN)
         {
            random_index = dis(gen);
            std::advance(it, random_index);
         }
         m_Bees.erase(it);
         m_UnfedBees--;
      }
   }
};
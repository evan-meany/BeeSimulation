#pragma once

#include "pch.h"
#include "date.h"

static size_t s_GlobalBeeID = 0;

enum BeeJob
{
   QUEEN, CLEANER, NURSE, FOOD, HOUSE, GUARD, FORAGER, DRONE, NONE
};

static std::string BeeJobToString(const BeeJob job)
{
   if (job == BeeJob::QUEEN) { return "Queen"; }
   if (job == BeeJob::CLEANER) { return "Cleaner"; }
   if (job == BeeJob::NURSE) { return "Nurse"; }
   if (job == BeeJob::FOOD) { return "Food"; }
   if (job == BeeJob::HOUSE) { return "House"; }
   if (job == BeeJob::GUARD) { return "Guard"; }
   if (job == BeeJob::FORAGER) { return "Forager"; }
   if (job == BeeJob::DRONE) { return "Drone"; }
   if (job == BeeJob::NONE) { return "No job"; }
   return "";
}

struct BeeTraits
{
   size_t longevity = 90;
   double speed = 1.0;
   double vision = 1.0;
   size_t carryCapacity = 20;
   double diseaseResistance = 1.0;
};

enum BeeTask
{
   NONE,               // No specific task, might be resting or in transition
   EAT,                // Consuming honey/nectar for energy
   COLLECT_POLLEN,     // Foraging task for collecting pollen
   COLLECT_NECTAR,     // Foraging task for collecting nectar
   FEED_LARVAE,        // Feeding the larvae, typically a nurse bee task
   LAY_EGGS,           // Exclusive to the queen
   CLEAN_CELL,         // Cleaning cells, usually a task for young bees
   BUILD_COMB,         // Constructing or repairing comb structure
   GUARD_ENTRANCE,     // Guarding the hive entrance against intruders
   RECEIVE_NECTAR,     // Receiving nectar from foragers and storing/processing it
   GROOM_SELF,         // Self-grooming to remove debris or parasites
   GROOM_OTHERS,       // Grooming other bees, a form of social interaction
   VENTILATE,          // Using wings to ventilate and regulate hive temperature
   DANCE,              // Foragers communicate locations of food sources
   MATE                // Exclusive to drones when they encounter a queen on her mating flight
};

struct Bee
{
   size_t id;
   BeeJob job;
   size_t age;
   BeeTraits traits;
   double energy = 1.0;
   BeeTask task;
   // Date birthDate;

   Bee(const BeeJob job, BeeTraits traits) : 
      id(s_GlobalBeeID++), job(job), age(0), traits(traits) {}
   Bee(const BeeJob job) : Bee(job, BeeTraits()) {}
};

struct Hive
{
   size_t waxCombCells;
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
   }

   void PrintColonyInfo()
   {
      std::cout << "|======== BEE COLONY INFO ========|" << std::endl;
      std::cout << std::endl;
      std::cout << " Pollen: " << m_Pollen << std::endl;
      std::cout << " Incubating: " << m_BeesIncubating << std::endl;
      for (const auto& [job, jobSet] : m_BeeJobSets)
      {
         std::cout << " " << BeeJobToString(job) << ": " << jobSet.size() << std::endl;
      }
      std::cout << std::endl;
      std::cout << "|=================================|" << std::endl;
   }

private:
   std::unordered_map<size_t, BeePtr> m_Bees;
   std::unordered_map<BeeJob, std::unordered_set<BeePtr>> m_BeeJobSets;
   size_t m_Pollen = 0;
   size_t m_BeesIncubating = 0;

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
};
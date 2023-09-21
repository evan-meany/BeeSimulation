#pragma once

#include "pch.h"

struct Date
{
   size_t day, month, year;

   Date() : day(1), month(1), year(1) {}
   Date(size_t d, size_t m, size_t y) : day(d), month(m), year(y) {}
};

class Calendar
{
public:
   static Calendar& GetInstance()
   {
      static Calendar instance;
      return instance;
   }

   void AdvanceDay()
   {
      m_Date.day++;
      if (m_Date.day > DaysInMonth(m_Date.year, m_Date.month))
      {
         m_Date.day = 1;
         m_Date.month++;

         if (m_Date.month > 12)
         {
            m_Date.month = 1;
            m_Date.year++;
         }
      }
   }

   void PrintDate() const
   {
      std::cout << "Date: " << m_Date.month << "/" << 
                               m_Date.day << "/" << 
                               m_Date.year << std::endl;
   }

   size_t DaysSince(const Date& pastDate)
   {
      size_t totalDays = 0;
      for(size_t y = pastDate.year; y <= m_Date.year; ++y)
      {
         size_t startMonth = (y == pastDate.year) ? pastDate.month : 1;
         size_t endMonth = (y == m_Date.year) ? m_Date.month : 12;

         for(size_t m = startMonth; m <= endMonth; ++m)
         {
            size_t startDay = (m == pastDate.month && y == pastDate.year) ? pastDate.day : 1;
            size_t endDay = (m == m_Date.month && y == m_Date.year) ? m_Date.day : DaysInMonth(y, m);

            totalDays += endDay - startDay + 1;
         }
      }

      return totalDays - 1; // Subtract one to not count the start date
   }

   Date GetDate() {return m_Date;}

private:
   Date m_Date;
private:
   Calendar() : m_Date{1, 1, 1} {}
   Calendar(const Calendar&) = delete;
   Calendar& operator=(const Calendar&) = delete;

   size_t DaysInMonth(size_t year, size_t month) const
   {
      switch (month)
      {
      case 1: case 3: case 5: case 7: case 8: case 10: case 12:
         return 31;
      case 4: case 6: case 9: case 11:
         return 30;
      case 2:
         if (IsLeapYear(year))
            return 29;
         else
            return 28;
      default:
         return 0;  // This should never happen
      }
   }

   bool IsLeapYear(size_t year) const
   {
      return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
   }
};
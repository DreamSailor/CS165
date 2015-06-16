/***********************************************************************
* Program:
*    Assignment 28, Member Operator overloading
*    Brother McCracken, CS165
* Author:
*    Jeffry Simpson
* Summary: 
*    This header file describes all the interfaces associated with
*    manipulating dates.
************************************************************************/


#ifndef DATE_H
#define	DATE_H
#define assertDate(date) assertDateProc( __FILE__ , __LINE__)

#include <string>
using std::string;



// three fields in the date array
enum {DAY, MONTH, YEAR};

//
// Class structure
//

class Date
{
    public:
        Date();           //Default Constructor
        Date(int year,int month=1, int day =1);
        Date(const Date & rhs );
        ~Date();
     
        bool setDate(int year, int month, int day);
        bool setYear(int year);
        bool setMonth(int month);
        bool setDay(int day);
        void display();
      
     
     
        // insertion and extraction operators
        friend std::ostream & operator << (std::ostream & out, const Date & date);
        friend std::istream & operator >> (std::istream & in,        Date & date);
   
        // increment and decrement ... only changing rank
        Date & operator ++ ();              // prefix
        Date & operator -- ();              // prefix
        Date operator ++ (int postfix);   // postfix
        Date operator -- (int postfix);   // postfix

        // change a card by adding or subtracting one
        Date operator + (const int input) const;
        friend Date operator + (const int input, const Date & lhs);
        Date operator - (const int input) const;
        int operator - ( Date & rhs);
        Date & operator += (const int input);
        Date & operator -= (const int input);
        
         // assignment
        Date & operator = (const Date & rhs);
        Date & operator () (int year, int month, int day);

        // Relative comparison... only comparing rank
        bool operator >  (const Date & rhs) const;//{return (rhs.isGreater(lhs,rhs));}
        bool operator <  (const Date & rhs) const;//{return (rhs.isGreater(rhs,lhs));}
        bool operator <= (const Date & rhs) const;
//        {
//             if(lhs == rhs)
//                return true;
//            else return (rhs.isGreater(rhs,lhs));
//        }
        bool operator >= (const Date & rhs) const;
//        {
//            if(lhs == rhs)
//                return true;
//            else return (rhs.isGreater(lhs,rhs));
//        }
       
        

        // Absolute comparision... comparing both rank and suit
        // this is done with member methods
        bool operator == (const Date & rhs) const;//{return(lhs.isEquals(lhs,rhs));}
        bool operator != (const Date & rhs) const;//{return !(lhs == rhs);}
    
      
        //inline public functions
        inline int getDay() const  { return data[DAY]; }
        inline int getMonth() const { return data[MONTH]; }
        inline int getYear() const  { return data[YEAR]; }
        inline void setLong() {isShort = false;}
        inline void setShort() { isShort = true;}
        inline bool getDisplayInfo() const {return isShort;}
      
 
      
    private:
        int *data;  // dynamically allocated
        bool static isShort;
        void displayLong();
        void displayShort();
        
        void adjustDay(int adjustment);
        void adjustMonth( int adjustment);
        void adjustYear(int adjustment);
        int daysMonth(int month, int year); // How many days are in the current month? 
        bool isLeapYear(int year); // Is the current year a leap year?
        
        int difference( Date lhs,  Date rhs);
        bool isGreater(const Date & lhs, const Date & rhs) const;
        bool isEquals(const Date & lhs, const Date & rhs) const;
        
        void assertDateProc( const char * file, int line);
        
   

};




////
//// Initialize and uninitialize
////
//
//// Initialize the date
//void initialize(Date & date);
//
//// Uninitialize the date
//void uninitialize(Date & date);
//
////
//// Read and write to a file
////
//
//// read the date from a file
//bool read(Date & date, const string & fileName);
//
//// write the date to a file
//bool write(const Date & date, const string & fileName);
//
////
//// Compare dates (no pun intended)
////
//
//bool isEquals(const Date & lhs, const Date & rhs);
//inline bool isNotEquals(const Date & lhs, const Date & rhs)
//{
//   return !(isEquals(lhs, rhs));
//}
//
//bool isGreater(const Date & lhs, const Date & rhs);
//
//int difference(Date lhs, Date rhs);
//
////
//// Set and adjust
////
//
//// Set the current year 
//bool setYear(Date & date, int year);
//
//// Set the current month
//bool setMonth(Date & date, int month);
//
//// Set the current day
//bool setDay(Date & date, int day);
//
//// set the current date
//bool setDate(Date & date, int year, int month, int day);
//
//// adjust the date by a fixed number of days
//void adjustDay(Date & date, int adjustment);
//
//// adjust the date by a fixed number of months
//void adjustMonth(Date & date, int adjustment);
//
//// adjust the date by a fixed number of years
//void adjustYear(Date & date, int adjustment);
//
////
//// Utility functions
////
//
//// How many days are in the current month?
//int daysMonth(int month, int year);
//
//// Is the current year a leap year?
//bool isLeapYear(int year);
//
//
//
//// Display the current date
//void display(const Date & date, bool isShort);
//
//// Short version of the display
//void displayShort(const Date & date);
//
//// Long version of the same
//void displayLong(const Date & date);
//
//// This is some debug code designed to catch common errors with
//// dates, such as going to an action movie or asking her to pay.  If
//// you want to use the assertDate() code, then these #defines will
//// be needed in your .h file.  Also, don't forget to copy over the
//// assertDateProc() which is currently in date.cpp
//
//// Gather input from the user
//void input(Date & date);
//
//// this is the function that actually does the work.
//void assertDateProc(const Date & date, const char * file, int line);
//
//// This part is weird.  We are adding two new parameters: the file
//// name and the line number.  The compiler will turn these two
//// special macros into the file name and the line number of the code
//// where this function is called from. This is how assert() knows
//// the file name and line number of the code when an assert fires!
////#define assertDate(date) assertDateProc(date, __FILE__ , __LINE__)



#endif	/* DATE_H */


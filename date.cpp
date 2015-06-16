/***********************************************************************
* Program:
*    Assignment 28, Member Operator overloading
*    Brother McCracken, CS165
* Author:
*    Jeffry Simpson
* Summary: 
*    Implement the date manipulation functions specified in date.h
************************************************************************/

#include <iostream>   // for COUT, CIN, CERR
#include <cassert>    // for ASSERT
#include <cstdlib>    // for EXIT
#include "date.h"
using namespace std;


/*************************************************************
 *************************************************************
 ************* NON-MEMBER OPERATOR OVERLOADING ***************
 *************************************************************
 *************************************************************/

/*****************************
 * Insertion  cout << x;
 * RETURN:    ostream by reference   (so we can say (cout << x) << y;)
 * PARAMETER: ostream by reference   (we do not want a copy of cout)
 *            constant by reference  (we do not want to make a copy or change)
 *****************************/
ostream & operator << (ostream & out, const Date & rhs)
{
 
   if(rhs.isShort == true)
      out << rhs.data[MONTH] << "/" << rhs.data[DAY] << "/" << rhs.data[YEAR];
   else
   {
//      int day;
//      day = rhs.getDay();
      
      out << rhs.data[DAY]; 
      switch (rhs.data[DAY])
      {
         case 1:
         case 21:
         case 31:
            out << "st";
            break;
         case 2:
         case 22:
            out << "nd";
            break;
         case 3:
         case 23:
            out << "rd";
            break;
         default:
            out << "th";
      }

      // month
      const char MONTHS[12][10] =
         { "January", "February", "March",     "April",   "May",      "June",
           "July",    "August",   "September", "October", "November", "December"};

      out << " of " << MONTHS[rhs.data[MONTH] - 1] << ", ";

      // year
      out << rhs.data[YEAR];
   }
 

   // return the output stream
   return out;
}

/*****************************
 * Extraction    cin >> x;
 * RETURN:    istream by reference  (so we can say (cin >> x) >> y;)
 * PARAMETER: istream by reference  (we do not want a copy of cin)
 *            by reference          (no copies but we do want to change this) 
 *****************************/
istream & operator >> (istream & in, Date & rhs)
{
   int day;
   int month;
   int year;
   
   in >> day >> month >> year;
   rhs.setDate( year, month, day);

   // return the input stream
   return in;
}

/*********************************
 * Equivelence
 * RETURN:    Bool                  (either equal or not)
 * PARAMETER: constant by reference (do not make a copy)
 ********************************/
bool Date :: operator == (const Date & rhs) const
{
   //bool flag;
   return(isEquals(*this,rhs));
   //return flag;0
  // return ((lhs.getDay() == rhs.getDay()) && (lhs.getMonth() == rhs.getMonth()) && (lhs.getYear() == rhs.getYear()));
}

/*********************************
 * Difference
 * RETURN:    Bool                  (either equal or not)
 * PARAMETER: constant by reference (do not make a copy)
 ********************************/
bool Date :: operator != (const Date & rhs) const
{
   // should be inline
   return !(isEquals(*this,rhs));
}

/*********************************
 * Greater than or equal to
 * RETURN:    Bool
 * PARAMETER: constant by reference (do not make a copy)
 ********************************/
bool Date :: operator >= (const Date & rhs) const
{
   if(*this == rhs)
      return true;
   else return (isGreater(*this,rhs));

}

/*********************************
 * Greater than 
 * RETURN:    Bool
 * PARAMETER: constant by reference (do not make a copy)
 ********************************/
bool Date :: operator > (const Date & rhs) const
{
   return (isGreater(*this,rhs));
  
}

/*********************************
 * Less than or equal to
 * RETURN:    Bool
 * PARAMETER: constant by reference (do not make a copy)
 *
 * In most cases, we can simply say:
 *     return !(lhs > rhs);
 ********************************/
bool Date :: operator <= (const Date & rhs) const
{
   if(*this == rhs)
      return true;
   else return (isGreater(rhs,*this));
}

/*********************************
 * Less than 
 * RETURN:    Bool
 * PARAMETER: constant by reference (do not make a copy)
 *
 * In most cases, we can simply say:
 *     return !(lhs >= rhs);
 ********************************/
bool Date :: operator < (const Date & rhs) const
{
   return (isGreater(rhs,*this));
}

/***************************
 * Plus Equals
 * RETURN:    Self by reference    (so we can say (x += 1) += 3;)
 * PARAMETER: Self by reference
 *            Whatever makes sense (card += 2 make sense, not card1 += card2;)
 **************************/
Date & Date :: operator += (const int input)
{
   adjustDay(input);
   
   return *this;

}

/*****************************
 * Minus Equals
 * RETURN:    Self by reference    (so we can say (x -= 1) -= 3;)
 * PARAMETER: Self by reference
 *            Whatever makes sense (card += 2 make sense, not card1 -= card2;)
 *****************************/
Date & Date :: operator -= (const int input)
{
   // This should be inline.  Just call +=
   return *this += -input;
}

/***************************
 * Increment: prefix (++x)
 * RETURN:    Self by reference  (so we can say ++(++x) )
 * PARAMETER: By reference       (we will change the lhs)
 **************************/
Date & Date :: operator ++ ()
{
   // call the += opeator, this should be inline
   return *this += 1;
}

/***************************
 * Increment: postfix (x++)
 * RETURN:    Self by value      (we are returning the old copy of this)
 * PARAMETER: By reference       (we will change the lhs)
 *            integer            (this parameter is ignored)
 *
 * The difference between ++x and a++ is that the prefix notation (++x)
 * is changing a before the expression is evaluated and the postfix
 * notation (x++) is changed after.  This means:
 *     int x = 5;
 *     cout << ++x << endl;      // display 6
 * Wherease
 *     int x = 5;
 *     cout << x++ << endl;      // display 5
 * Therefore, postfix increment (x++) must return the value of this before
 * the change was made. This means we need to make a copy
 **************************/
Date Date :: operator ++ (int postfix)
{
   // remember the old value of the left hand side so we can return it
   Date oldValue(*this);

   // actually increment using the += operator
   *this += 1;

   // create a copy of the old version
   return Date (oldValue) ;
}

/**************************
 * Decrement: prefix (--x)
 * RETURN:    Self by reference    (so we can say --(--x) )
 * PARAMETER  By reference         (we will change the lhs)
 **************************/
Date & Date :: operator -- ()
{
   // should be inline
   return *this -= 1;
}

/***************************
 * Decrement: postfix  (x--)
 * RETURN:    Self by value       (we are returning the old copy of this)
 * PARAMETER: By reference        (we will change the lhs)
 *            integer             (this parameter is ignored)
 *
 * Again we need to return a copy of the old value.
 **************************/
Date Date :: operator -- (int postfix)
{
   // remember the old value of the left hand side so we can return it
   Date oldValue(*this);

   // actually increment using the += operator
   *this -= 1;

   // create a copy of the old version
   return Date (oldValue);
}

/*************************
 * Addition
 * RETURN:    Self by value         (we are creating a new card to return)
 * PARAMETER: Const by reference    (we do not want to change the lhs)
 *            Whatever makes sense  (usually the same parameter as +=
 *
 * From the following:
 *     cout << x + y << endl;
 * We do not expect x or y to change.  Therefore, both are const
 *************************/
Date Date :: operator + (const int input) const
{
 
    Date dateReturn(*this);  // copy constructor
    dateReturn += input;    // call += operator
    return dateReturn;      // another copy constructor

   // we could also have said:
   // Date cardReturn(this);  // copy constructor
   // cardReturn += input;    // call += operator
   // return cardReturn;      // another copy constructor
}

/*************************
 * Addition
 * This is the same as above except the parameters are in a different order
 *************************/
Date operator + (const int input, const Date & rhs)
{
   return rhs + input;
}

/*************************
 * Subtraction
 * This is the same as above except the parameters are in a different order
 *************************/
Date Date :: operator - (const int input) const
{
     Date dateReturn(*this);  // copy constructor
    dateReturn += -input;    // call += operator
    return dateReturn;      // another copy constructor
}

/*************************
 * Subtraction
 *************************/
int Date :: operator - (Date & rhs)
{
   int x = difference( *this, rhs);
   return x;

}


/*************************************
 * ASSIGNMENT
 * RETURN:    *this by reference
 * PARAMETER: a constant Card
 * METHOD:    not const
 *************************************/
Date & Date :: operator = (const Date & rhs)
{

   data[DAY] = rhs.data[DAY];
   data[MONTH] = rhs.data[MONTH];
   data[YEAR] = rhs.data[YEAR];
   return *this;
}

/*************************************
 * FUNCTION
 * RETURN:    *this by reference
 * PARAMETER: a constant Card
 * METHOD:    not const
 *************************************/
Date & Date :: operator () (int year, int month, int day)
{
   cout << "Here I am\n";
   data[DAY] = day;
   data[MONTH] = month;
   data[YEAR] = year;
   
   cout << data[DAY]  << data[MONTH] << data[YEAR] <<endl;
   
   return *this;
}



/**********************************************************************
 *  Default Constructor  Initialize the year to 1/1/2000
 *  OUTPUT: date:  the adjusted date
 ***********************************************************************/
Date :: Date()
{
   try
   {
      data = new int[3];
      assert(data != NULL); // exception handling should catch this
   }
   catch (bad_alloc)
   {
      cerr << "ERROR: Unable to allocate only 12 bytes of data!\n";
      exit(1);   // a bit sloppy, I know.
   }
   data[DAY] = 1;
   data[MONTH] = 1;
   data[YEAR] = 2000;
   assertDate();
}


Date :: Date(int year, int month, int day)
{
      try
   {
      data = new int[3];
      assert(data != NULL); // exception handling should catch this
   }
   catch (bad_alloc)
   {
      cerr << "ERROR: Unable to allocate only 12 bytes of data!\n";
      exit(1);   // a bit sloppy, I know.
   }
   data[DAY] = day;
   data[MONTH] = month;
   data[YEAR] = year;
   assertDate();
}


Date :: Date(const Date & rhs)
{
   try
   {
      data = new int[3];
      assert(data != NULL); // exception handling should catch this
   }
   catch (bad_alloc)
   {
      cerr << "ERROR: Unable to allocate only 12 bytes of data!\n";
      exit(1);   // a bit sloppy, I know.
   }
   //this->data = rhs.data;
   data[DAY] = rhs.data[DAY];
   data[MONTH] = rhs.data[MONTH];
   data[YEAR] = rhs.data[YEAR];
   assertDate();
}

/********************************************************
 * Destructor.  Free up the memory we allocated
 *  INPUT:  date:  What we will be freeing up
 *  OUTPUT: date:  No longer ready for use
 ********************************************************/
 Date :: ~Date()
{
  
   delete [] data;
   data = NULL;
 
}

/**********************************************************************
 * SET YEAR.  Set the year to a given value.  Validate it
 *  INPUT: date:   the current date.  Will only use month and day
 *         year:   the new year
 *  OUTPUT: date:  the adjusted date
 *          return whether we succeeded
 ***********************************************************************/
bool Date :: setYear(int year) 
{
   assertDate();

   if (year < 1753 || year > 2500)
      return false;

   data[YEAR] = year;
   assertDate();
   return true;
}

/**********************************************************************
 * SET Month.  Set the month to a given value.  Validate it
 *  INPUT: date:   the current date.  Will only use month and day
 *         month:   the new month
 *  OUTPUT: date:  the adjusted date
 *          return whether we succeeded
 ***********************************************************************/
bool Date :: setMonth(int month)
{
   assertDate();

   if (month < 1 || month > 12)
      return false;

   data[MONTH] = month;
   assertDate();
   return true;
}


/**********************************************************************
 * SET DAY.  Set the day to a given value.  Validate it
 *  INPUT: date:   the current date.  Will only use month and day
 *         day:   the new day
 *  OUTPUT: date:  the adjusted date
 *          return whether we succeeded
 ***********************************************************************/
bool Date :: setDay(int day)
{
   assertDate();

   if (day < 1 || day > daysMonth(data[MONTH], data[YEAR]))
      return false;

   data[DAY] = day;
   assertDate();
   return true;
}

/*********************************************************
 * SET DATE.  Set all 3 fields of the date type and doing error checking
 *   INPUT  day    Day between 1 and 31 (or 28, depending)
 *          month  Month between 1 and 12
 *          year   After 1753, before something crazy
 *   OUTPUT date   The newly formed type
 *          return Success?
 **********************************************************/
bool Date :: setDate(int year, int month, int day)
{
   // validation
   if (year < 1753 || year > 2500)
      return false;
   if (month < 1 || month > 12)
      return false;
   if (day < 1 || day > daysMonth(month, year))
      return false;

   // assignment
   data[YEAR] = year;
   data[MONTH] = month;
   data[DAY] = day;

   assertDate(date);

   return true;
}


/*****************************************************
 * DAYS MONTH.  How many days are there in the current month?
 *   INPUT  month    the month we are inquiring about
 *          year     we only care about this when month == 2
 *   OUTPUT return   return the number
 *****************************************************/
int Date :: daysMonth(int month, int year)
{
   if (month > 12 || month < 1)
   {
      assert(false);
      return 0;
   }
   
   const int DAYS[13] =
       /* JAN FEB MAR APR MAY JUN JUL AUG SEP OCT NOV DEC */
      { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

   // special case the one leap month
   if (month == 2 && isLeapYear(year))
      return 29;

   assert(month > 0 && month < 13);
   return DAYS[month];
}

/***********************************************
 * IS LEAP YEAR.  Is the passed year a leap year?
 *   INPUT   year    The current year
 *   OUTPUT  return  True if we are in a leap year
 **********************************************/
bool Date :: isLeapYear(int year)
{
   // no leap years before 1753
   assert(year >= 1753);

   // what, are you Buck Rogers?
   assert(year < 2500);

   // Not a leap year if not evenly divisible by 4
   // This will eliminate 75% of all years
   if (year % 4 != 0)
      return false; // 2001, 2002, 2003, 2005, etc.
   assert(year % 4 == 0);

   // Is a leap year if not divisible by 100
   // This will eliminate 96% of the rest
   if (year % 100 != 0)
      return true; // 1996, 2004, 2008, 2012, etc.
   // We better be 1800, 1900, 2000, 2100 at this point
   assert(year % 100 == 0);

   // Is a leap year if on the quad century
   if (year % 400 == 0)
      return true; // 1600, 2000, 2400, etc.
   // It better be something like 1800, 1900, 2100, etc.
   assert(year % 400 != 0);

   // the balance better be 1900, 1800, etc.
   assert(year == 1800 || year == 1900 || year == 2100 || year == 2200);
   return false;
}



/**********************************************
 * DISPLAY.  Display the current date
 *  INPUT date   the current date
 *        short  Are we using the short format?
 *********************************************/
void Date :: display()
{

   if (isShort)
      displayShort();
   else
      displayLong();

}

/**********************************************
 * DISPLAY SHORT.  Display the current date: 1/3/2010
 *  INPUT date   the current date
 *********************************************/
void Date :: displayShort()
{
   assertDate(date);
   cout << data[MONTH] << "/" << data[DAY] << "/" << data[YEAR];
}


/**********************************************
 * DISPLAY LONG.  Display the current date: 1st of October, 2009
 *  INPUT date   the current date
 *********************************************/
void Date :: displayLong()
{
   assertDate(date);

   // day
   cout << data[DAY];
   switch (data[DAY])
   {
      case 1:
      case 21:
      case 31:
         cout << "st";
         break;
      case 2:
      case 22:
         cout << "nd";
         break;
      case 3:
      case 23:
         cout << "rd";
         break;
      default:
         cout << "th";
   }
   
   // month
   const char MONTHS[12][10] =
      { "January", "February", "March",     "April",   "May",      "June",
        "July",    "August",   "September", "October", "November", "December"};

   cout << " of " << MONTHS[data[MONTH] - 1] << ", ";

   // year
   cout << data[YEAR];
}


/************************************************
 * ASSERT DATE.  Validate date
 *   INPUT date: the date to be validated
 ***********************************************/
void Date :: assertDateProc(const char * file, int line)
{
   // validate the year.  Keep it real
   if (data[YEAR] < 1753 || data[YEAR] > 2500)
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.year=" << data[YEAR] << " outside valid range\n";
      exit(1);
   }

   // valide the month
   if (data[MONTH] < 1 || data[MONTH] > 12)
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.month=" << data[MONTH] << " outside valid range\n";
      exit(1);
   }

   // finally the day.
   if (data[DAY] < 1
       || data[DAY] > daysMonth(data[MONTH], data[YEAR]))
   {
      cerr << "Assert: " << file << ": " << line
           << ": date.day=" << data[DAY] << " outside valid range\n";
      exit(1);
   }
}


/***************************************************
 * ADJUST DAY.  Adjust the current date by a given number of days
 *  INPUT  date        date we are adjusting
 *         adjustment  how many days we will adjust
 *  OUTPUT date
 ***************************************************/
void Date :: adjustDay(int adjustment)
{
   assertDate(date);
   int days = daysMonth(data[MONTH], data[YEAR]);

   // adjust down if negative
   while (adjustment < 0)
   {
      data[DAY]--;
      if (data[DAY] == 0)
      {
         data[DAY] = 28; // to keep it valid at all points in time
         adjustMonth( -1 /*adjustment*/);
         days = daysMonth(data[MONTH], data[YEAR]);
         data[DAY] = days; // last day of the new month
      }
      adjustment++;
   }

   // adjust up if positive
   while (adjustment > 0)
   {
      data[DAY]++;
      if (data[DAY] > days)
      {
         data[DAY] = 1; // first day of the new month
         adjustMonth( 1 /*adjustment*/);
         days = daysMonth(data[MONTH], data[YEAR]);
      }
      adjustment--;
   }

   assertDate();
}

/*********************************************************
 * ADJUST MONTH.  Adjust the current date by a given number of months
 *  INPUT  date       date we are adjusting
 *         adjustment how many months we will adjust
 *  OUTPUT date
 *********************************************************/
void Date :: adjustMonth( int adjustment)
{
   assertDate();

   // adjust down if negative
   while (adjustment < 0)
   {
      data[MONTH]--;
      if (data[MONTH] == 0)
      {
         data[MONTH] = 12;  // last month of the new year
         adjustYear( -1 /*adjustment*/);
      }
      adjustment++;
   }

   // adjust up if positive
   while (adjustment > 0)
   {
      data[MONTH]++;
      if (data[MONTH] > 12)
      {
         data[MONTH] = 1; // first month of the new year
         adjustYear( 1 /*adjustment*/);
      }
      adjustment--;
   }

   assertDate();
}

/****************************************************
 * ADJUST YEAR.  Adjust the year bug a given number of years
 *  INPUT  date       date we are adjusting
 *         adjustment how many years we will adjust
 *  OUTPUT date
 *********************************************************/
void Date :: adjustYear(int adjustment)
{
   assertDate();
   data[YEAR] += adjustment;
   assertDate();
}

/***************************************************
 * IS EQUALS
 *  INPUT  rhs       Right hand side of the equation
 *         lhs       Left hand side of the equation
 *  OUTPUT bool      is rhs == lhs?
 **************************************************/
bool Date :: isEquals(const Date & lhs, const Date & rhs) const
{
   return lhs.data[YEAR ] == rhs.data[YEAR ] &&
          lhs.data[MONTH] == rhs.data[MONTH] &&
          lhs.data[DAY  ] == rhs.data[DAY  ];
}

/*************************************************
 * IS GREATER
 *   INPUT  rhs       Right hand side of the equation
 *          lhs       Left hand side of the equation
 *  OUTPUT bool       is rhs > lhs?
 **************************************************/
bool Date :: isGreater(const Date & lhs, const Date & rhs) const
{
   

   // First check the year.  If the years are different, then there is
   // no point in looking at the months or dates.  Note that 1/1/2000 is
   // greater than 12/31/1999 because the year is greater!
   if (lhs.data[YEAR] > rhs.data[YEAR])
      return true;
   if (lhs.data[YEAR] < rhs.data[YEAR])
      return false;
   assert(lhs.data[YEAR] == rhs.data[YEAR]);

   // Next check the month.  See the above comment
   if (lhs.data[MONTH] > rhs.data[MONTH])
      return true;
   if (lhs.data[MONTH] < rhs.data[MONTH])
      return false;
   assert(lhs.data[MONTH] == rhs.data[MONTH]);

   // Only check the day if the month and year are the same
   return (lhs.data[DAY] > rhs.data[DAY]);
}

/*****************************************************
 * DIFFERENCE.  How many days are between the left-hand-side
 *              and teh right-hand-side.
 *   INPUT  lhs         the left-hand-side.  Note that this is
 *                      by-value because we are going to change
 *                      our copy of the parameter
 *          rhs         the right-hand-side, also by-value
 *   OUTPUT difference  the number of days between
 *****************************************************/
int Date :: difference(Date lhs, Date rhs)
{
   // initially the difference is zero
   int diff = 0;

   // as long as lhs is greater than rhs, increase rhs by one
   while (isGreater(lhs, rhs))
   {
      rhs.adjustDay(1);
      diff++;
   }

   // as long as rhs is greater than lhs, increase lhs by one
   while (isGreater(rhs, lhs))
   {
      lhs.adjustDay(1);
      diff--;
   }

   // return the difference
   return diff;
}





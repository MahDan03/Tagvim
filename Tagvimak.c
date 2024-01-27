#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int programSituation;

int isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0 && year % 100 == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int getDaysInMonth(int month, int year)
{
    int daysInMonth[] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
    if (month == 1 && isLeapYear(year))
    {
        return 30;
    }
    else
    {
        return daysInMonth[month - 1];
    }
}
int calculateDays(int day, int month, int year)
{
    int days = 0;

    for (int i = 1; i < year; i++)
    {
        days += isLeapYear(i) ? 366 : 365;
    }

    for (int i = 1; i < month; i++)
    {
        days += getDaysInMonth(i, year);
    }

    days += day;

    return days;
}

void shamsi_to_gregorian(int *gregorianYear, int *gregorianMonth, int *gregorianDay,
                         int shamsiYear, int shamsiMonth, int shamsiDay)
{
    int g_days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int j_days_in_month[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
    int gy, gm, gd;
    int shy, shm, shd;
    long g_day_no, j_day_no;
    int leap;

    int i;

    shy = shamsiYear - 979;
    shm = shamsiMonth - 1;
    shd = shamsiDay - 1;

    j_day_no = 365 * shy + (shy / 33) * 8 + (shy % 33 + 3) / 4;
    for (i = 0; i < shm; ++i)
        j_day_no += j_days_in_month[i];

    j_day_no += shd;

    g_day_no = j_day_no + 79;

    gy = 1600 + 400 * (g_day_no / 146097);
    g_day_no = g_day_no % 146097;

    leap = 1;
    if (g_day_no >= 36525)
    {
        g_day_no--;
        gy += 100 * (g_day_no / 36524);
        g_day_no = g_day_no % 36524;

        if (g_day_no >= 365)
            g_day_no++;
        else
            leap = 0;
    }

    gy += 4 * (g_day_no / 1461);
    g_day_no %= 1461;

    if (g_day_no >= 366)
    {
        leap = 0;

        g_day_no--;
        gy += g_day_no / 365;
        g_day_no = g_day_no % 365;
    }

    for (i = 0; g_day_no >= g_days_in_month[i] + (i == 1 && leap); i++)
        g_day_no -= g_days_in_month[i] + (i == 1 && leap);
    gm = i + 1;
    gd = g_day_no + 1;

    *gregorianYear = gy;
    *gregorianMonth = gm;
    *gregorianDay = gd;
}

int calculateDayOfWeek(int day, int month, int year)
{
    int gregorianYear, gregorianMonth, gregorianDay;
    shamsi_to_gregorian(&gregorianYear, &gregorianMonth, &gregorianDay, year, month, day);

    if (gregorianMonth < 3)
    {
        gregorianMonth += 12;
        gregorianYear--;
    }

    int k = gregorianYear % 100;
    int j = gregorianYear / 100;

    int dayOfWeek = (gregorianDay + (13 * (gregorianMonth + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;

    if (dayOfWeek < 0)
    {
        dayOfWeek += 7;
    }

    return dayOfWeek;
}

void age()
{
    int day1, month1, year1;
    int day2, month2, year2;
    int year, month, day;
    int backmenu;
    printf("[0] Back to menu \n");
    printf("--------------------------------\n");
    printf("Enter your birthday :\n ");

    printf("Year : ");
    scanf("%d", &year1);
    if ((year1) == 0)
    {
        system("cls");
        programSituation = -1;
        return;
    }

    do
    {
        printf(" Month : ");
        scanf("%d", &month1);
        if (month1 == 0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        if (0 < month1 && month1 <= 12)
        {
            break;
        }
        else
        {
            printf("Wrong input!\n");
            continue;
        }
    } while (month1);

    do
    {
        printf(" Day : ");
        scanf("%d", &day1);
        if (day1 == 0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        else if (0 < day1 && day1 <= 31)
        {
            break;
        }
        else
        {
            printf("Wrong input!\n");
            continue;
        }

    } while (day1);

    system("cls");
    printf("back to menu [0] \n");
    printf("--------------------------------\n");
    printf("Enter today's date :\n ");
    printf("Year : ");
    scanf("%d", &year2);
    if ((year2) == 0)
    {
        system("cls");
        programSituation = -1;
        return;
    }

    do
    {
        printf(" Month : ");
        scanf("%d", &month2);
        if (month2 == 0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        if (0 < month2 && month2 <= 12)
        {
            break;
        }
        else
        {
            printf("Wrong input!\n");
            continue;
        }
    } while (month2);

    do
    {
        printf(" Day : ");
        scanf("%d", &day2);
        if (day2 == 0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        else if (0 < day2 && day2 <= 31)
        {
            break;
        }
        else
        {
            printf("Wrong input!\n");
            continue;
        }

    } while (day2);

    system("cls");
    int days1 = calculateDays(day1, month1, year1);
    int days2 = calculateDays(day2, month2, year2);
    int diff = days2 - days1 + 1;
    year = year2 - year1;
    month = month2 - month1 - 1;
    month <= 0 ? month += 12 : month;
    day = day2 - day1;
    day < 0 ? day += 30 : day;
    system("cls");
    printf("your birthdate is: %d / %d / %d \n", year1, month1, day1);
    printf("The number of days you lived: %d\n", diff);
    printf("You are %d years, %d months, %d days old\n", year, month, day);

    // Calculate the day of the week
    int dayOfWeek = calculateDayOfWeek(day1, month1, year1);

    // Print the result
    printf("You were born on ");
    switch (dayOfWeek)
    {
    case 0:
        printf("'Saturday'");
        break;
    case 1:
        printf("'Sunday'");
        break;
    case 2:
        printf("'Monday'");
        break;
    case 3:
        printf("'Tuesday'");
        break;
    case 4:
        printf("'Wednesday'");
        break;
    case 5:
        printf("'Thursday'");
        break;
    case 6:
        printf("'Friday'");
        break;
    default:
        printf("Invalid day");
        break;
    }

    
    printf("\n------------------------------\n");

    printf("[0] BACK TO MENU\n[1] BACK TO AGE CALCULATE\n");
    scanf("%d", &backmenu);
    if (backmenu == 0)
    {
        system("cls");
        programSituation = -1;
        return;
    }
    else if (backmenu == 1)
    {
        system("cls");
        return age();
    }
    
    return;
}

void Conversion()
{
    int backmenu;
    int y, m, d, a;
    printf("[0] Back to menu \n");
    printf("--------------------------------\n");
    printf("Year: ");
    scanf("%d", &y);
    
    do
    {
        printf("Month: ");
        scanf("%d", &m);
        
        if (m == 0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        if (0 < m && m <= 12)
        {
            break;
        }
        else
        {
            printf("Wrong input!\n");
            continue;
        }
    } while (m);

    do 
    {
        printf("Day: ");
        scanf("%d", &d);
    
            if (d == 0)
            {
            system("cls");
            programSituation = -1;
            return;
            }
         else if (0 < d  && d <= 31)
        {
            break;
        }   
            else
            {
            printf("Wrong input!\n");
            continue;
            }
    }while (d);
    system("cls");
    printf("[0] Back to menu \n");
    printf("--------------------------------\n");
    printf("[1] Shamsi to Miladi\n");
    printf("[2] Shamsi to Gamari\n");
    printf("Select Option: ");
    scanf("%d", &a);
    if (a==0)
    {
        system("cls");
        run();
    }
    

    if (a == 1)
    {
        char *monthnames[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        int gregorianYear, gregorianMonth, gregorianDay;
        shamsi_to_gregorian(&gregorianYear, &gregorianMonth, &gregorianDay, y, m, d);

        system("cls");
        printf("Date: %d / %d / %d\n", y, m,d);
        printf("     ***Miladi Date***\n");
        printf("Year: %d\n", gregorianYear);
        printf("Month: %s\n", monthnames[gregorianMonth]);
        printf("Day: %d\n", gregorianDay);
        printf("--------------------------------\n");
        
        printf("[0] BACK TO MAIN MENU\n[1] BACK TO CONVERSION MENU\n");
           scanf("%d",&backmenu);
        if (backmenu==0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        else if (backmenu == 1)
        {
            system("cls");
            return Conversion();
        }
    }
    else if (a == 2)
    {
        int Days4 = 0, Days5, Days6;
        char *monthnames2[] = {"", "Ramazan", "Shavval", "Zigada", "Zihaja", "Moharram", "Safar", "Rabiolaval", "Rabiolsani", "Jamadiolaval", "Jamadiolsani", "Rajab"};
        Days4 += floor((y + 1) * 365 + (m + 3) * 29.5 + d + 7 + 10.875 * y);
        Days5 = Days4;
        Days4 /= 365;
        Days5 %= 365;
        Days6 = Days5;
        Days6 %= 30;
        Days5 /= 30;
        system("cls");
        printf("Date: %d / %d / %d\n", y, m,d);
        printf("     ***Gamari Date***\n");
        printf("Year: %d\n", Days4);
        printf("Month: %s\n", monthnames2[Days5]);
        printf("Day: %d \n", Days6);
        printf("-------------------------------");
        printf("\n[0] BACK TO MAIN MENU\n[1] BACK TO CONVERTION MENU\n");
        scanf("%d",&backmenu);
       
        if (backmenu==0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        else if (backmenu == 1)
        {
            system("cls");
            return Conversion();
        }
    }
    else
    {
        printf(" >> Please Enter Valid Input <<\n");
    }
    printf("[0] BACK TO MENU\n");
    scanf("%d", &backmenu);
    if (backmenu == 0)
    {
        system("cls");
        programSituation = -1;
        return;
    }
    return;
}
void Calender()
{
    int y, m, yearmiladi ;
    int backmenu;
    int shlip, daynum, fday, daymon, weekday;
    int dayinMonth[] = {0, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 29};
    char *monthname[13] = {" ", "Farvardin", "Ordibehesht", "Khordad", "Tir", "Mordad", "Shahrivar", "Mehr", "Aban", "Azar", "Dey", "Bahman", "Esfand"};
    printf("[0] Back to menu \n");
    printf("--------------------------------\n");
    printf("enter year: ");
    scanf("%d", &y);
    
    do
    {
        printf("enter Month : ");
        scanf("%d", &m);
        if (m == 0)
        {
            system("cls");
            programSituation = -1;
            return;
        }
        if (0 < m && m <= 12)
        {
            break;
        }
        else
        {
            printf("Wrong input!\n");
            continue;
        }
       
        

    } while (m);

    system("cls");

    for (int i = 1206; i < y; i++)
    {
        if (isLeapYear(i) == 1)
        {
            shlip++;
        }
    }

    daynum = (y - 1206) * 365 + shlip;
    if (m <= 7)
    {
        daynum += (m - 7) * 31 + 1;
    }
    else
    {
        daynum += 6 * 31 + (m - 6) * 30 + 1 ;
    }
    fday = (daynum % 7 + 5) % 7;
    daymon = dayinMonth[m ];
    printf("\t   ***********%s**********\t\t\n\n", monthname[m]);
    printf("sat    sun    mon    tue    wed    thu    fri\n\n");
    for (weekday = 0; weekday < fday; weekday++)
    {
        printf("       ");
    }
    for (int day = 1; day < daymon; day++)
    {
        printf("%02d     ", day);
        weekday ++;
        if (weekday > 6)
        { 
            printf("\n");
            weekday = 0 ;
        }
    }
        yearmiladi = y + 622;
        printf("\n<< %d ", yearmiladi);
    
        if (m==1)
        {
            printf("April >>");
        }
        if (m==2)
        {
            printf("May >>");
        }
        if (m==3)
        {
            printf("June >>");
        }
        if (m==4)
        {
            printf("July >>");
        }
        if (m==5)
        {
            printf("August >>");
        }
        if (m==6)
        {
            printf("September >>");
        }
        if (m==7)
        {
            printf("October >>");
        }
        if (m==8)
        {
            printf("November >>");
        }
        if (m==9)
        {
            printf("December >>");
        }
        if (m==10)
        {
            printf("January >>");
        }
        if (m==11)
        {
            printf("Febuary >>");
        }
        if (m==12)
        {
            printf("March >>");
        }
        
    printf("\n------------------------------------");
    printf("\n[0] BACK TO MENU\n[1] BACK TO CALENDER\n");
    scanf("%d", &backmenu);
    if (backmenu == 0)
    {
        system("cls");
        programSituation = -1;
        return;
    }
    else if (backmenu == 1)
    {
        system("cls");
        return Calender();
    }
    
    return;
}

void run()
{
    do
    {

        printf("___________________Menu__________________\n");
        printf("[0] Quit\n");
        printf("[1] Age\n");
        printf("[2] Conversion\n");
        printf("[3] Calender\n");
        printf("========================================\n");
        printf("Select option: ");
        scanf("%d", &programSituation);
        system("cls");
        switch (programSituation)
        {
        case 1:
            age();
            break;
        case 2:
            Conversion();
            break;
        case 3:
            Calender();
            break;
        case 0:
            system("cls");
            printf("bye! :3");
            break;

        default:
            printf(" >> Please Enter Valid Input <<\n");
            sleep(2);
            break;

        }

    } while (programSituation != 0);
}

int main()
{
    run();
    return 0;
}
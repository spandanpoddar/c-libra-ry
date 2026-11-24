#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct books
{
    int b_id;
    char b_name[50];
    char a_name[50];
    char date[12];
}b[100];

struct member
{
    int m_id;
    char m_name[50];
    char phone[15];
}m[100];

FILE *fp;

int Add_book();
int Member_list();
int Add_member();
int Book_list();
int dateToDays(int day, int month, int year);
int Issue_book();
int Issued_book(int book_id);
void Show_issued_books();
int Return_book();
int main()
{
    int c,f,z;
    char p;
    while (1)
    {
        
        printf("LIBRARY MANAGEMENT SYSTEM \n");
        printf("---------------------------------------------------------------------------\n");
        printf("1. New Member\n 2. Old member\n 3.Employe\n");
        printf("Enter choice: ");
        scanf("%d",&f);// for the choice of member employe or new member
        switch (f)
        {
        case 1:
            
            printf("please become a member 1st,contact help desk");
            break;
        case 2:
            printf("1.Book list\n 2.Issue book\n 3.Issued list book\n 4.Return book\n 0.Exit\n ");
            printf("enter choice: ");
            scanf("%d",&c);// c is for the member case where the user will choice what he want to do 

            if(c==0)
            {
            printf("Thanks For visiting");
            break;
           }
           else if (c==1)
           {
                Book_list();
                break;
           }
           else if (c==2)
            {
               Issue_book();
               break;
            }
            else if (c==3)
            {
               Show_issued_books(); 
               break;
            }
            else if (c==4)
            {
               Return_book();
               break;
            }
            else
            {
               printf("Wrong Choise");
            }
        
        break;
        case 3:
            printf("Enter password: ");
            scanf(" %c",&p);
            if (p=='*')
            {
              printf("1. Add books\n 2. Members list\n 3. Add New Member");
              printf("enter choice: ");
              scanf("%d",&z);
              switch (z)
              {
              case 1:
                Add_book();
                break;
            
              case 2:
                Member_list();
                break;

                case 3:
                  Add_member();
                  break;
              default:
                break;
              }
              break;
            }
        default:
            printf("wrong choice");
            break;
        }
    }
}


int Add_book()
{
    fp = fopen("book.txt", "a");

    if (fp == NULL)
   {
      printf("Error opening file\n");
      return 1;
   }

    int n;
    printf("enter number of book u want to store: ");
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
      printf("enter book id: ");
      scanf("%d",& b[i].b_id);

      printf("enter book title: ");
      scanf("%s", b[i].b_name);

      

      printf("enter author name: ");
      scanf("%s", b[i].a_name);

      printf("enter book date in dd/mm/yyyy format: ");
      scanf("%s", b[i].date);


        fprintf(fp, "%d\t%s\t%s\t%s\t\n", b[i].b_id, b[i].b_name, b[i].a_name, b[i].date);

      
    }

    fclose(fp);
    printf("Data written to book.txt successfully.\n");
}

int Member_list()
{
    FILE *fp = fopen("members.txt", "r");
    if (fp == NULL)
    {
        printf("No members found.\n");
        return 0;
    }

    printf("\nMember ID\tName\t\tPhone\n");
    printf("----------------------------------------\n");

    int id;
    char name[50], phone[15];

    while (fscanf(fp, "%d %49s %14s", &id, name, phone) == 3)
    {
        printf("%d\t\t%s\t\t%s\n", id, name, phone);
    }

    fclose(fp);
    return 1;

}

int Add_member()
{
    FILE *fp = fopen("members.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening members file\n");
        return 0;
    }

    int n;
    printf("How many members do you want to add? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Member ID: ");
        scanf("%d", &m[i].m_id);

        printf("Enter Member Name: ");
        scanf("%s", m[i].m_name);

        printf("Enter Phone Number: ");
        scanf("%s", m[i].phone);

        fprintf(fp, "%d %s %s\n", m[i].m_id, m[i].m_name, m[i].phone);
    }

    fclose(fp);
    printf("\nMember(s) added successfully.\n");
    return 1;
}

int Book_list()
{
    fp = fopen("book.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    printf("Book ID\tBook Name\tAuthor Name\tDate\n");
    printf("------------------------------------------------\n");

    int i = 0;

    // Read until we successfully get 4 items
    while (fscanf(fp, "%d %49s %49s %11s", &b[i].b_id, b[i].b_name, b[i].a_name, b[i].date) == 4)
    {
        printf("%d\t%s\t%s\t%s\n", b[i].b_id, b[i].b_name, b[i].a_name, b[i].date);
        i++;

        if (i >= 100) break;   // safety: don't overflow the array
    }

    fclose(fp);

    if (i == 0)
        printf("No books found.\n");

    return 0;
}

int dateToDays(int day, int month, int year)
{
    int monthDays[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};// Cumulative days at the start of each month (non-leap year)

    // If leap year and month is after February, February has 29 days
    if ((month > 2) && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        monthDays[2] = 60;   // 31 + 29

    int days = year * 365 + day;
    days += monthDays[month - 1];

    // Past leap days
    days += (year / 4) - (year / 100) + (year / 400);

    return days;
}

int Issue_book()
{
    int book_id, member_id;
    char issue_date[12];

    printf("Enter Book ID to issue: ");
    scanf("%d", &book_id);

    // Check if already issued
    if (Issued_book(book_id))
    {
        printf("This book is already issued. Cannot issue again.\n");
        return 0;
    }

    printf("Enter Member ID: ");
    scanf("%d", &member_id);

    printf("Enter issue date (DD/MM/YYYY): ");
    scanf("%s", issue_date);

    FILE *fp = fopen("issued.txt", "a");
    if (fp == NULL) {
        printf("Error opening issued file\n");
        return 0;
    }

    fprintf(fp, "%d %d %s\n", book_id, member_id, issue_date);
    fclose(fp);

    printf("Book issued successfully.\n");
    return 1;
}

int Issued_book(int book_id)
{
    FILE *fp = fopen("issued.txt", "r");
    if (fp == NULL)
        return 0;

    int id, mid;
    char date[12];

    while (fscanf(fp, "%d %d %s", &id, &mid, date) == 3)
    {
        if (id == book_id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void Show_issued_books()
{
    FILE *fp = fopen("issued.txt", "r");
    if (fp == NULL)
    {
        printf("No books are currently issued.\n");
        return;
    }

    int id, mid;
    char date[12];

    printf("\nBook ID\tMember ID\tIssue Date\n");
    printf("--------------------------------\n");

    while (fscanf(fp, "%d %d %s", &id, &mid, date) == 3)
    {
        printf("%d\t%d\t\t%s\n", id, mid, date);
    }
    fclose(fp);
}

int Return_book()
{
    int book_id, member_id;
    char issue_date[12], return_date[12];
    int id, mid;
    int issue_d, issue_m, issue_y;
    int return_d, return_m, return_y;
    int days, fine;
    int found = 0;

    printf("Enter Book ID to return: ");
    scanf("%d", &book_id);

    printf("Enter Member ID: ");
    scanf("%d", &member_id);

    printf("Enter return date (DD/MM/YYYY or DD/MM/YY): ");
    scanf("%s", return_date);

    // Find the issue date from file
    FILE *fp = fopen("issued.txt", "r");
    if (fp == NULL) {
        printf("No issued books found\n");
        return 0;
    }

    while (fscanf(fp, "%d %d %s", &id, &mid, issue_date) == 3)
    {
        if (id == book_id && mid == member_id)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("This book was not issued to this member\n");
        return 0;
    }

    // ----- Extract Issue Date -----
    issue_d = (issue_date[0] - '0') * 10 + (issue_date[1] - '0');
    issue_m = (issue_date[3] - '0') * 10 + (issue_date[4] - '0');

    if (strlen(issue_date) >= 10)   // DD/MM/YYYY
    {
        issue_y = (issue_date[6] - '0') * 1000
                + (issue_date[7] - '0') * 100
                + (issue_date[8] - '0') * 10
                + (issue_date[9] - '0');
    }
    else   // DD/MM/YY
    {
        issue_y = (issue_date[6] - '0') * 10 + (issue_date[7] - '0');
        issue_y += (issue_y < 50) ? 2000 : 1900;
    }

    // ----- Extract Return Date -----
    return_d = (return_date[0] - '0') * 10 + (return_date[1] - '0');
    return_m = (return_date[3] - '0') * 10 + (return_date[4] - '0');

    if (strlen(return_date) >= 10)   // DD/MM/YYYY
    {
        return_y = (return_date[6] - '0') * 1000
                 + (return_date[7] - '0') * 100
                 + (return_date[8] - '0') * 10
                 + (return_date[9] - '0');
    }
    else   // DD/MM/YY
    {
        return_y = (return_date[6] - '0') * 10 + (return_date[7] - '0');
        return_y += (return_y < 50) ? 2000 : 1900;
    }

    // Calculate days
    days = dateToDays(return_d, return_m, return_y)
         - dateToDays(issue_d, issue_m, issue_y);

    printf("\nDays the book was kept: %d\n", days);

    if (days > 15) {
        fine = (days - 15) * 2;
        printf("Fine to be paid: %d\n", fine);
    } else if (days >= 0) {
        printf("No fine. Returned on time.\n");
    } else {
        printf("Invalid dates (return date is before issue date).\n");
        return 0;
    }

    printf("Book returned successfully.\n");
    return 1;
}
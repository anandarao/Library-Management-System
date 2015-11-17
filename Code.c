#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

char password[8]="library";
struct book
{
    int id;
    char name[20];
    char author[20];
    int copies;
    int copiesleft;
}b,bc;
struct date
{
    int dd,mm,yy;
};
struct user
{
    int id;
    char name[20];
    int bookid;
    struct date issue;
    struct date due;
}u,uc;
FILE *pb,*pu;

void main_menu(void);
void admin(void);
void user(void);
void exitcheck(void);
void bookmenu(void);
void addbook(void);
void editbook(void);
void deletebook(int);
void usermenu(void);
void adduser(void);
void edituser(void);
void deleteuser(int);
void listbook(void);
void listuser(void);
void issuebook(void);
void collectbook(void);
void searchbook(void);
void userinfo(void);
int bidcheck(int);
int uidcheck(int);
int validdatecheck(struct date);
void duedate(void);
int fine(struct date,int);


int main(void)
{
    system("cls");
    printf("\n\n\n\t\t\t Library Management Software \n\n\n\n\n\t\t\t\t\t\t\t\t By \n\t\t\t\t\t\t\t\t Ananda Rao \n\t\t\t\t\t\t\t\t Nikhil BM");
    printf("\n Press any key to continue");
    getch();
    main_menu();
    return 0;
}

void main_menu(void)
{
    int choice;
    do
    {
        system("cls");
        printf("\n\n\n\t\t\t Main Menu");
        printf("\n\n\t\t 1.Administrator ");
        printf("\n\t\t 2.User ");
        printf("\n\t\t 3.Exit ");
        printf("\n\n\t\t Please enter the choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: admin();
                    break;
            case 2: user();
                    break;
            case 3: exitcheck();
                    break;
            default: printf(" \n Invalid Choice ");
                    getch();
        }
    }while(1);
    getch();
}

void admin(void)
{
    system("cls");
    printf("\n\n\t\t Please enter the password : ");
    char str[20];
    char ch;int i=0;

    while((ch=getch())!='\r'&&i<20)
    {
        putch('*');
        str[i++]=ch;
    }
    str[i]='\0';
    if(strcmp(str,password)==0)
        {
            printf("\n\n\t\t Authentication successful");
            printf("\n\n\t\t Press any key to continue");
            getch();
        }
    else
        {
            printf("\n\n\t\t Incorrect password entered");
            printf("\n\n\t\t Press any key to continue");
            getch();
            return;
        }
    int choice;
    do
    {
    system("cls");
    printf("\n\n\t\t\t\t Administrator Menu");
    printf("\n\n\t\t 1. Add/Edit Book \n\t\t 2. Add/Edit User \n\t\t 3. List Books \n\t\t 4. List Users \n\t\t 5. Issue Book \n\t\t 6. Collect Book \n\t\t 7. Main Menu \n\t\t 8. Exit");
    printf("\n\n\t\t Please Enter the choice : ");
    scanf("%d",&choice);
    switch(choice)
        {
            case 1: bookmenu();break;
            case 2: usermenu();break;
            case 3: listbook();break;
            case 4: listuser();break;
            case 5: issuebook();break;
            case 6: collectbook();break;
            case 7: return;
            case 8: exitcheck();break;
            default: printf("\n\n\t\t Invalid Choice");
                 getch();
        }
    }while(1);
}
void bookmenu(void)
{
    int choice;
    do
    {
        system("cls");
        printf("\n\n\t\t\t\t Book Menu");
        printf("\n\n\t\t 1. Add Book \n\t\t 2. Edit Book Details \n\t\t 3. Delete Book \n\t\t 4. Administrator Menu \n\t\t 5. Exit");
        printf("\n\n\t\t Please Enter the choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:addbook();break;
            case 2:editbook();break;
            case 3:deletebook(0);break;
            case 4:return;
            case 5:exitcheck();break;
            default: printf("\n\n\t\t Invalid Choice");
                     getch();
        }
    }while(1);
}
void addbook(void)
{
    pb=fopen("Books.txt","a");
    char ch;
    do
    {
        label:
        system("cls");
        printf("\n\n\t\t\t Add Book");
        printf("\n\n\t\t Please Enter the following details");
        printf("\n\n\t BookId : ");
        scanf("%d",&b.id);
        if(bidcheck(b.id)==0)
        {
            printf("\n\t Book Name : ");
            scanf(" %[^\n]s",b.name);
            printf("\n\t Author : ");
            scanf(" %[^\n]s",b.author);
            printf("\n\t Number of copies :");
            scanf("%d",&b.copies);
            b.copiesleft=b.copies;
            fwrite(&b,sizeof(struct book),1,pb);
            printf("\n\t Book Successfully added");
            printf("\n\t Do you want to enter details of another book? (Y/N)");
            scanf(" %c",&ch);
        }
        else
        {
            printf("\n\t BookId already exists ");
            printf("\n\t Press any key to continue ");
            getch();
            goto label;
        }
    }while(ch=='Y'||ch=='y');
    fclose(pb);
    return;
}
int bidcheck(int id)
{
    FILE *b;
    int i=0;
    b=fopen("Books.txt","r");
    while(!feof(b))
    {
        if(fread(&bc,sizeof(struct book),1,b)==1)
            if(bc.id==id)
        {
            i=1;
            break;
        }
    }
    fclose(b);
    return i;
}
void editbook(void)
{
    int id,choice;
    char ch;
    system("cls");
    printf("\n\n\t\t\t\t Edit Book Details");
    printf("\n\t Enter the BookId you want to edit : ");
    scanf("%d",&id);
    if(bidcheck(id)==1)
    {
        deletebook(id);
        struct book be;
        be=bc;
        l2:
        printf("\n\t Existing Book Information : ");
        printf("\n\t BookId : %d \n\t 1. Book Name : %s \n\t 2. Author : %s \n\t 3. Number of copies : %d ",be.id,be.name,be.author,be.copies);
        printf("\n\n\t Please Enter the field to edit : ");
        scanf("%d",&choice);
        switch(choice)
        {
            /*case 1: l1:
                    printf("\n\n\t Enter the new bookid : ");
                    scanf("%d",&be.id);
                    if(bidcheck(be.id)==1)
                    {
                        printf("\n\n\t BookId already exists");
                        printf("\n\n\t Press any key to continue");
                        getch();
                        goto l1;
                    }
                    break;*/
            case 1: printf("\n\n\t Enter the new book name : ");
                    scanf(" %[^\n]s",be.name);
                    break;
            case 2: printf("\n\n\t Enter the new author name : ");
                    scanf(" %[^\n]s",be.author);
                    break;
            case 3: printf("\n\n\t Enter the new number of copies : ");
                    int temp;
                    temp=be.copies;
                    scanf("%d",&be.copies);
                    be.copiesleft=be.copiesleft+be.copies-temp;
                    break;
            default: printf("\n\n\t Invalid choice");
                     printf("\n\\nt Press any key to continue");
                     getch();
                     goto l2;
        }
        printf("\n\n\t Do you want to edit anything else ? (Y/N)");
        scanf(" %c",&ch);
        if(ch=='Y'||ch=='y')
                goto l2;
        pb=fopen("Books.txt","a");
        fwrite(&be,sizeof(struct book),1,pb);
        fclose(pb);
        printf("\n\t Book Successfully updated ");
        printf("\n\t Press any key to continue ");
        getch();
    }
    else
    {
        printf("\n\n\t Entered BookId does not exist");
        printf("\n\n\t Press any key to continue");
        getch();
    }
    return;
}
void deletebook(int id)
{
    FILE *temp;
    int flag=0;
    temp=fopen("temp.txt","w");
    if(id==0)
    {
        flag=1;
        label:
        system("cls");
        printf("\n\n\t\t Delete Book");
        printf("\n\t Enter the BookId to be deleted : ");
        scanf("%d",&id);
        if(bidcheck(id)==0)
        {
            printf("\n\t BookId does not exist");
            printf("\n\t Press any key to continue");
            getch();
            goto label;
        }
    }
    pb=fopen("Books.txt","r");
    while(!feof(pb))
    {
        if(fread(&b,sizeof(struct book),1,pb)==1)
            if(b.id!=id)
                fwrite(&b,sizeof(struct book),1,temp);
    }
    fclose(pb);
    fclose(temp);
    remove("Books.txt");
    rename("temp.txt","Books.txt");
    if(flag)
    {
        printf("\n\t Book successfully deleted");
        printf("\n\t Press any key to continue");
        getch();
    }
    return;
}
void usermenu(void)
{
    int choice;
    do
    {
        system("cls");
        printf("\n\n\t\t\t\t User Menu");
        printf("\n\n\t\t 1. Add User \n\t\t 2. Edit User Details \n\t\t 3. Delete User \n\t\t 4. Administrator Menu \n\t\t 5. Exit");
        printf("\n\n\t\t Please Enter the choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:adduser();break;
            case 2:edituser();break;
            case 3:deleteuser(0);break;
            case 4:return;
            case 5:exitcheck();break;
            default: printf("\n\n\t\t Invalid Choice");
                     getch();
        }
    }while(1);
}
void adduser(void)
{
    pu=fopen("Users.txt","a");
    char ch;
    do
    {
        label:
        system("cls");
        printf("\n\n\t\t\t Add User");
        printf("\n\n\t\t Please Enter the following details");
        printf("\n\n\t UserId : ");
        scanf("%d",&u.id);
        if(uidcheck(u.id)==0)
        {
            printf("\n\t Name : ");
            scanf(" %[^\n]s",u.name);
            u.bookid=0;
            u.issue.dd=u.issue.mm=u.issue.yy=u.due.dd=u.due.mm=u.due.yy=0;
            fwrite(&u,sizeof(struct user),1,pu);
            printf("\n\t User Successfully added");
            printf("\n\t Do you want to enter details of another user? (Y/N)");
            scanf(" %c",&ch);
        }
        else
        {
            printf("\n\t UserId already exists");
            printf("\n\t Press any key to continue");
            getch();
            goto label;
        }
    }while(ch=='Y'||ch=='y');
    fclose(pu);
    return;
}
int uidcheck(int id)
{
    FILE *u;
    int i=0;
    u=fopen("Users.txt","r");
    while(!feof(u))
    {
        if(fread(&uc,sizeof(struct user),1,u)==1)
            if(uc.id==id)
        {
            i=1;
            break;
        }
    }
    fclose(u);
    return i;
}
void edituser(void)
{
    int id,choice;
    char ch;
    system("cls");
    printf("\n\n\t\t\t\t Edit User Details");
    printf("\n\t Enter the UserId you want to edit : ");
    scanf("%d",&id);
    if(uidcheck(id)==1)
    {
        deleteuser(id);
        struct user ue;
        ue=uc;
        l2:
        printf("\n\t Existing User Information : ");
        printf("\n\t 1. UserId : %d \n\t 2. User Name : %s ",ue.id,ue.name);
        printf("\n\n\t Please Enter the field to edit : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: l1:
                    printf("\n\n\t Enter the new userid : ");
                    scanf("%d",&ue.id);
                    if(uidcheck(ue.id)==1)
                    {
                        printf("\n\n\t UserId already exists");
                        printf("\n\n\t Press any key to continue");
                        getch();
                        goto l1;
                    }
                    break;
            case 2: printf("\n\n\t Enter the new user name");
                    scanf(" %[^\n]s",ue.name);
                    break;
            default: printf("\n\n\t Invalid choice");
                     printf("\n\\nt Press any key to continue");
                     getch();
                     goto l2;
        }
        printf("\n\n\t Do you want to edit anything else ? (Y/N)");
        scanf(" %c",&ch);
        if(ch=='Y'||ch=='y')
                goto l2;
        pu=fopen("Users.txt","a");
        fwrite(&ue,sizeof(struct user),1,pu);
        fclose(pu);
        printf("\n\t Book Successfully updated ");
        printf("\n\t Press any key to continue ");
        getch();
    }
    else
    {
        printf("\n\n\t Entered BookId does not exist");
        printf("\n\n\t Press any key to continue");
        getch();
    }
    return;
}
void deleteuser(int id)
{
    FILE *temp;
    int flag=0;
    temp=fopen("temp.txt","w");
    if(id==0)
    {
        flag=1;
        label:
        system("cls");
        printf("\n\n\t\t Delete User");
        printf("\n\t Enter the UserId to be deleted : ");
        scanf("%d",&id);
        if(uidcheck(id)==0)
        {
            printf("\n\t UserId does not exist");
            printf("\n\t Press any key to continue");
            getch();
            goto label;
        }
    }
    pu=fopen("Users.txt","r");
    while(!feof(pu))
    {
        if(fread(&u,sizeof(struct user),1,pu)==1)
            if(u.id!=id)
                fwrite(&u,sizeof(struct user),1,temp);
    }
    fclose(pu);
    fclose(temp);
    remove("Users.txt");
    rename("temp.txt","Users.txt");
    if(flag)
    {
        printf("\n\t User successfully deleted");
        printf("\n\t Press any key to continue");
        getch();
    }
    return;
}
void listbook(void)
{
    pb=fopen("Books.txt","r");
    system("cls");
    printf("\n\n\t\t Book Record");
    printf("\n %5s %20s %20s %12s %11s","Id","Book Name","Author Name","No.of Copies","Copies Left");
    while(!feof(pb))
    {
        if(fread(&b,sizeof(struct book),1,pb)==1)
        printf("\n %5d %20s %20s %12d %11d",b.id,b.name,b.author,b.copies,b.copiesleft);
    }
    fclose(pb);
    printf("\n\n\t Press any key to continue");
    getch();
    return;
}
void listuser(void)
{
    pu=fopen("Users.txt","r");
    system("cls");
    printf("\n\n\t\t User Record");
    printf("\n %5s %20s %6s %11s %11s","Id","Name","BookId","Issue Date ","Due Date   ");
    while(!feof(pu))
    {
        if(fread(&u,sizeof(struct user),1,pu)==1)
        printf("\n %5d %20s %6d %2d-%2d-%4d %2d-%2d-%4d",u.id,u.name,u.bookid,u.issue.dd,u.issue.mm,u.issue.yy,u.due.dd,u.due.mm,u.due.yy);
    }
    fclose(pu);
    printf("\n\n\t Press any key to continue");
    getch();
    return;
    return;
}
void issuebook(void)
{
    system("cls");
    printf("\n\n\t\t\t Issue Book");
    printf("\n\t Enter the UserId : ");
    int idb,idu;
    scanf("%d",&idu);
    if(uidcheck(idu)==1)
    {
        if(uc.bookid>0)
        {
            printf("\n\t One Book is already issued");
            printf("\n\t Press any key to continue");
            getch();
        }
        else
        {
            printf("\n\t Enter the BookId to be issued : ");
            scanf("%d",&idb);
            if(bidcheck(idb)==1)
            {
                if(bc.copiesleft==0)
                {
                    printf("\n\t Book not available now");
                    printf("\n\t Press any key to continue");
                    getch();
                }
                else
                {
                    do
                    {
                        printf("\n\t Enter the date of issue : (dd-mm-yyyy) : ");
                        scanf("%d-%d-%d",&uc.issue.dd,&uc.issue.mm,&uc.issue.yy);
                        if(validdatecheck(uc.issue))
                            break;
                        printf("\n\t Enter a valid date");
                        getch();
                    }while(1);
                    duedate();
                    printf("\n\t The due date is : %d-%d-%d ",uc.due.dd,uc.due.mm,uc.due.yy);
                    deleteuser(uc.id);
                    pu=fopen("Users.txt","a");
                    uc.bookid=idb;
                    fwrite(&uc,sizeof(struct user),1,pu);
                    fclose(pu);
                    deletebook(bc.id);
                    pb=fopen("Books.txt","a");
                    bc.copiesleft--;
                    fwrite(&bc,sizeof(struct book),1,pb);
                    fclose(pb);
                    printf("\n\t Book Issued Successfully");
                    printf("\n\t Press any key to continue");
                    getch();
                }
            }
            else
            {
                printf("\n\t BookId does not exist");
                printf("\n\t Press any key to continue");
                getch();
            }
        }
    }
    else
    {
        printf("\n\t UserId does not exist");
        printf("\n\t Press any key to continue");
        getch();
    }
    return;
}
int validdatecheck(struct date a)
{
    if((a.dd>=1)&&(a.dd<=30)&&(a.mm>=1)&&(a.mm<=12)&&(a.yy>2000))
        return 1;
    else
        return 0;
}
void duedate(void)
{
    uc.due=uc.issue;
    uc.due.dd+=30;
    if(uc.due.dd>30)
    {
        uc.due.dd-=30;
        uc.due.mm++;
        if(uc.due.mm>12)
        {
            uc.due.mm-=12;
            uc.due.yy++;
        }
    }
    return;
}
void collectbook(void)
{
    system("cls");
    printf("\n\n\t\t\t Collect Book");
    int idu;
    printf("\n\t Enter the UserId : ");
    scanf("%d",&idu);
    if(uidcheck(idu)==0)
    {
        printf("\n\t UserId does not exist");
        printf("\n\t Press any key to continue");
        getch();
    }
    else
    {
        if(uc.bookid==0)
        {
            printf("\n\t UserId %d has not issued any book",idu);
            printf("\n\t Press any key to continue");
            getch();
        }
        else
        {
            struct date r;
            int f;
            do
            {
                do
                {
                    printf("\n\t Enter the date of return (dd-mm-yy) : ");
                    scanf("%d-%d-%d",&r.dd,&r.mm,&r.yy);
                    if(validdatecheck(r))
                        break;
                    printf("\n\t Enter a valid date");
                    getch();
                }while(1);
                f=fine(r,0);
                if(f>0)
                {
                    printf("\n\t The due date is %d-%d-%d",uc.due.dd,uc.due.mm,uc.due.yy);
                    printf("\n\t The fine to be collected is %d",f);
                    getch();
                    break;
                }
                else if(f<0)
                {
                    if(fine(r,1)<0)
                    {
                        printf("\n\t The issue date is %d-%d-%d",uc.issue.dd,uc.issue.mm,uc.issue.yy);
                        printf("\n\t Please enter a date after the issue date");
                        getch();
                    }
                    else
                        break;
                }
            }while(1);
            bidcheck(uc.bookid);
            bc.copiesleft++;
            deletebook(uc.bookid);
            pb=fopen("Books.txt","a");
            fwrite(&bc,sizeof(struct book),1,pb);
            fclose(pb);
            deleteuser(idu);
            uc.bookid=0;
            uc.issue.dd=uc.issue.mm=uc.issue.yy=uc.due.dd=uc.due.mm=uc.due.yy=0;
            pu=fopen("Users.txt","a");
            fwrite(&uc,sizeof(struct book),1,pu);
            fclose(pu);
            printf("\n\t Book Successfully Returned");
            printf("\n\t Press any key to continue");
            getch();
        }
    }
    return;
}
int fine(struct date r,int i)
{
    int f;
    if(i)
    {
        f=(uc.issue.yy-r.yy)*360+(uc.issue.mm-r.mm)*30+uc.issue.dd-r.dd;
        return -f;
    }
    else
    {
        f=(uc.due.yy-r.yy)*360+(uc.due.mm-r.mm)*30+uc.due.dd-r.dd;
        return -f;
    }
}
void user(void)
{
    int choice;
    do
    {
        system("cls");
        printf("\n\n\t\t\t\t User Menu");
        printf("\n\n\t\t 1. Search Book \n\t\t 2. UserInfo \n\t\t 3. Main Menu \n\t\t 4. Exit");
        printf("\n\n\t\t Please Enter Choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: searchbook();break;
            case 2: userinfo();break;
            case 3: main_menu();break;
            case 4: exitcheck();break;
            default: printf("\n\n\t\t Invalid Choice");
                     getch();
        }
    }while(1);
}
void searchbook(void)
{
    pb=fopen("Books.txt","r");
    char ch,name[20];int i;
    do
    {
        system("cls");
        i=0;
        rewind(pb);
        printf("\n\n\t\t\t\t Book Search ");
        printf("\n\t Enter the name of the book to search : ");
        scanf(" %[^\n]s",name);
        while(!feof(pb))
        {
            if(fread(&b,sizeof(struct book),1,pb)==1)
            if(strcmpi(b.name,name)==0)
            {
                i++;
                printf("\n\t Search Result : %d",i);
                printf("\n\t BookId : %d \n\t Book Name : %s \n\t Author : %s \n\t Number of copies : %d \n\t Number of copies left : %d",b.id,b.name,b.author,b.copies,b.copiesleft);
            }
        }
    if(i==0)
        printf("\n\t No such book found");
    printf("\n Do you want to search for any other book ? (Y/N)");
    scanf(" %c",&ch);
    }while(ch=='Y'||ch=='y');
    fclose(pb);
    return;
}
void userinfo(void)
{
    pu=fopen("Users.txt","r");
    char ch;int id,i;
    do
    {
        system("cls");
        i=0;
        rewind(pu);
        printf("\n\n\t\t\t\t User Info ");
        printf("\n\t Enter the UserId : ");
        scanf(" %d",&id);
        while(!feof(pu))
        {
            if(fread(&u,sizeof(struct user),1,pu)==1)
            if(u.id==id)
            {
                i++;
                printf("\n\t Search Successful ");
                printf("\n\t UserId : %d \n\t Name : %s \n\t Book Id : %d \n\t Issue date : %d-%d-%d \n\t Due Date : %d-%d-%d ",u.id,u.name,u.bookid,u.issue.dd,u.issue.mm,u.issue.yy,u.due.dd,u.due.mm,u.due.yy);
            }
        }
    if(i==0)
        printf("\n\t No such user found");
    printf("\n Do you want to search for any other user ? (Y/N)");
    scanf(" %c",&ch);
    }while(ch=='Y'||ch=='y');
    fclose(pu);
    return;
}
void exitcheck(void)
{
    system("cls");
    printf("\n\n\t\t Do you really want to exit ?(Y/N) : ");
    char ch;
    scanf(" %c",&ch);
    if(ch=='Y'||ch=='y')
        exit(1);
    return;
}

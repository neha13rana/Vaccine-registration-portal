#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
typedef struct node
{
    int id;
    char name[20];
    int password;
    struct node *left;
    struct node *right;
    char Hospital[25];
} node;
typedef struct hs
{
    char hos[20];
    int spaceAvailable;
} hs;
hs arrayofHospital[4] = {{"SolaCivil", 5}, {"Zydus", 5}, {"CityHospital", 5}, {"AIMS", 5}};
node *root = NULL;
void Register();
void preorder(node *);
void Login();
node *search(char *, node *);
void print(node *);
void allocateHospital(node *);
void receipt(node *);
void ForgotPassword(node *);
int main()
{
    int choice;
    // printf("enter choices\n");
    do
    {
        // Head();
        printf("\n\tMain menu\n");
        printf("1.Register for vaccine\n");
        printf("2.Login\n");
        printf("3.To exit\n");
        printf("4.print all peeps\n\n");
        printf("enter choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            Register();
            // print();
            break;
        case 2:
            Login();
            break;
        case 3:
            printf("Thankyou for booking Vaccine Slot....\n");
            exit(0);
        case 4:
            preorder(root);
            printf("\n");
            break;
        default:
            printf("the entered input is invalid. Please input valid input\n");
            break;
        }
    } while (choice);
    return 0;
}
// -----------------------------------------------------------------------------------------------------------------

// printing the data
void preorder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    preorder(root->left);
    printf("[%s", root->name);
    printf(" , %d , %d]", root->id, root->password);
    preorder(root->right);
}
// Taking input and store it in Binary Search Tree
void Register()
{
    srand(time(NULL));
    node *newnode = (node *)malloc(sizeof(node));
    printf("input name : ");
    scanf("%s", newnode->name);
    printf("set your password : ");
    scanf("%d", &newnode->password);
    newnode->id = rand();
    newnode->left = NULL;
    newnode->right = NULL;
    if (root == NULL)
    {
        root = newnode;
        return;
    }
    // char NAME [20];
    // strcpy(NAME,newnode->name);
    // node * p = search(NAME,root);
    // // check from here
    // if(root != NULL)
    // {
    // printf("You have already ready exits\n");
    // // printf("Plese en");
    // return;
    // }
    node *tmp = root;
    while (1)
    {
        char n1[20];
        strcpy(n1, tmp->name);
        char n2[20];
        strcpy(n2, newnode->name);
        if ((strcmp(n2, n1) > 0) && tmp->right == NULL)
        {
            tmp->right = newnode;
            return;
        }
        else if ((strcmp(n2, n1) > 0) && tmp->right != NULL)
        {
            tmp = tmp->right;
        }
        else if ((strcmp(n2, n1) < 0) && tmp->left == NULL)
        {
            tmp->left = newnode;
            return;
        }
        else
        {
            tmp = tmp->left;
        }
    }
}
void Login()
{
    printf("input your name : ");
    char name[20];
    scanf("%s", name);
    printf("input your password : ");
    int pass;
    scanf("%d", &pass);
    node *ptr = search(name, root);
    if (ptr->password == pass)
    {
        // printing msg of successfull login
        print(ptr);
        allocateHospital(ptr);
        receipt(ptr);
    }
    else
    {
        printf("\nincorrect password please enter valid password\n");
        printf("1.Forgot Password\n2.Login Again \n");
        int n;
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            ForgotPassword(ptr);
            break;
        case 2:
            Login();
            break;
        default:
            break;
        }
    }
}
node *search(char name[], node *ptr)
{
    char n1[20];
    char n2[20];
    strcpy(n1, ptr->name);
    strcpy(n2, name);
    if (ptr == NULL)
    {
        return NULL;
    }
    else if (strcmp(n2, n1) == 0)
    {
        return ptr;
    }
    else if (strcmp(n2, n1) > 0)
    {
        return search(name, ptr->right);
    }
    else
    {
        return search(name, ptr->left);
    }
}
void print(node *ptr)
{
    printf("\n\t\t\tLogin Successfull\n");
    printf("Your unique Id is : %d\n", ptr->id);
}
void receipt(node *ptr)
{
    printf("\n\n------------------ Your registration process is finish. Now you are eligible for vaccine ------------------ \n");
    printf("\n*************** Here is your login details ************ :\n");
    printf("\n\nName of the patient : ");
    printf("%s\n", ptr->name);
    printf("generated id of the patient is: ");
    printf("%d\n", ptr->id);
    // printf("")
    printf("Allocated hospital is:");
    printf("%s\n\n", ptr->Hospital);
    // printf("\n");
}
void allocateHospital(node *ptr)
{
    printf("\nthe available hospital are\n");
    for (int i = 0; i < 4; i++)
    {
        if (arrayofHospital[i].spaceAvailable <= 0)
        {
            continue;
        }
        printf("%s ", arrayofHospital[i].hos);
        printf("%d\n", arrayofHospital[i].spaceAvailable);
    }
    printf("\ninput hospital choice\n");
    char choice[20];
    scanf("%s", choice);
    for (int i = 0; i < 4; i++)
    {
        if (strcmp(choice, arrayofHospital[i].hos) == 0)
        {
            arrayofHospital[i].spaceAvailable--;
            strcpy(ptr->Hospital, choice);
            return;
        }
    }
    printf("please enter valid input\n");
    allocateHospital(ptr);
}
void ForgotPassword(node *ptr)
{
    printf("input newpassword : ");
    int pass;
    scanf("%d", &pass);
    ptr->password = pass;
    printf("the password is set seuccessfully !\n");
    Login();
}
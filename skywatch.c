#include <stdio.h>
#include <string.h>

#define MAX 50
#define TEL 5

struct Request {
    int id;
    char organization[30];
    char status[15];
};

struct Telescope {
    char name[30];
    int free;
};

struct Request queue[MAX];
struct Telescope telescope[TEL];

int front = 0, rear = -1;
int nextID = 1, telescopeCount = 0;

void submitRequest()
{
    if (rear == MAX - 1) {
        printf("Request limit is full.\n");
        return;
    }

    rear++;
    queue[rear].id = nextID++;

    printf("Organization Name: ");
    scanf(" %[^\n]", queue[rear].organization);

    strcpy(queue[rear].status, "Pending");
    printf("Request submitted successfully. Request ID: %d\n",
           queue[rear].id);
}

void checkStatus()
{
    int id, i;

    printf("Enter Request ID: ");
    scanf("%d", &id);

    for (i = 0; i <= rear; i++)
        if (queue[i].id == id) {
            printf("Organization: %s | Status: %s\n",
                   queue[i].organization, queue[i].status);
            return;
        }

    printf("Request not found.\n");
}

void addTelescope()
{
    if (telescopeCount == TEL) {
        printf("Maximum telescope limit reached.\n");
        return;
    }

    printf("Telescope Name: ");
    scanf(" %[^\n]", telescope[telescopeCount].name);

    telescope[telescopeCount].free = 1;
    telescopeCount++;

    printf("Telescope added successfully.\n");
}

void viewRequests()
{
    int i;

    if (front > rear) {
        printf("No observation requests are waiting.\n");
        return;
    }

    for (i = front; i <= rear; i++)
        printf("ID: %d | Organization: %s | Status: %s\n",
               queue[i].id, queue[i].organization,
               queue[i].status);
}

void assignTelescope()
{
    int i;

    if (front > rear) {
        printf("No observation request is waiting.\n");
        return;
    }

    for (i = 0; i < telescopeCount; i++)
        if (telescope[i].free) {
            telescope[i].free = 0;
            strcpy(queue[front].status, "Observing");

            printf("Request %d assigned to Telescope: %s\n",
                   queue[front].id, telescope[i].name);
            front++;
            return;
        }

    printf("No telescope is currently available.\n");
}

void releaseTelescope()
{
    int number;

    printf("Enter Telescope Number: ");
    scanf("%d", &number);

    if (number < 1 || number > telescopeCount)
        printf("Invalid telescope number.\n");
    else {
        telescope[number - 1].free = 1;
        printf("Telescope released successfully.\n");
    }
}

void organizationPanel()
{
    int choice;

    do {
        printf("\n--- Organization Panel ---\n");
        printf("1. Submit Observation Request\n");
        printf("2. Check Request Status\n");
        printf("3. Back\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) submitRequest();
        else if (choice == 2) checkStatus();

    } while (choice != 3);
}

void adminPanel()
{
    int choice;

    do {
        printf("\n--- Observation Station Admin ---\n");
        printf("1. Add Telescope\n");
        printf("2. View Observation Requests\n");
        printf("3. Assign Telescope\n");
        printf("4. Release Telescope\n");
        printf("5. Back\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) addTelescope();
        else if (choice == 2) viewRequests();
        else if (choice == 3) assignTelescope();
        else if (choice == 4) releaseTelescope();

    } while (choice != 5);
}

int main()
{
    int choice;

    do {
        printf("\n=== ASTEROID OBSERVATION STATION ===\n");
        printf("1. Organization Panel\n");
        printf("2. Observation Station Admin\n");
        printf("3. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) organizationPanel();
        else if (choice == 2) adminPanel();

    } while (choice != 3);

    return 0;
}
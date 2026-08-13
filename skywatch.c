#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    int requestID;
};

struct Request queue[MAX];
struct Telescope telescope[TEL];

int front = 0, rear = -1;
int nextID = 1, requestCount = 0;
int telescopeCount = 0;

void submitRequest()
{
    char input[50];

    if (requestCount == MAX) {
        printf("Request queue is full.\n");
        return;
    }

    if (rear == MAX - 1)
        rear = 0;
    else
        rear++;

    queue[rear].id = nextID++;

    printf("Organization Name: ");
    fgets(queue[rear].organization, 30, stdin);
    queue[rear].organization[strcspn(queue[rear].organization, "\n")] = '\0';

    strcpy(queue[rear].status, "Pending");
    requestCount++;

    printf("Request submitted successfully. Request ID: %d\n",
           queue[rear].id);
}

void checkStatus()
{
    char input[20];
    int id, i;

    printf("Enter Request ID: ");
    fgets(input, sizeof(input), stdin);
    id = atoi(input);

    for (i = 0; i < MAX; i++) {
        if (queue[i].id == id) {
            printf("Organization: %s | Status: %s\n",
                   queue[i].organization,
                   queue[i].status);
            return;
        }
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
    fgets(telescope[telescopeCount].name, 30, stdin);
    telescope[telescopeCount].name[
        strcspn(telescope[telescopeCount].name, "\n")
    ] = '\0';

    telescope[telescopeCount].free = 1;
    telescope[telescopeCount].requestID = 0;
    telescopeCount++;

    printf("Telescope added successfully. Telescope ID: %d\n",
           telescopeCount);
}

void viewRequests()
{
    int i, position;

    if (requestCount == 0) {
        printf("No observation requests are waiting.\n");
        return;
    }

    position = front;

    for (i = 0; i < requestCount; i++) {
        printf("ID: %d | Organization: %s | Status: %s\n",
               queue[position].id,
               queue[position].organization,
               queue[position].status);

        if (position == MAX - 1)
            position = 0;
        else
            position++;
    }
}

void assignTelescope()
{
    int i;

    if (requestCount == 0) {
        printf("No observation request is waiting.\n");
        return;
    }

    for (i = 0; i < telescopeCount; i++) {

        if (telescope[i].free) {

            telescope[i].free = 0;
            telescope[i].requestID = queue[front].id;

            strcpy(queue[front].status, "Observing");

            printf("Request %d assigned to Telescope ID: %d\n",
                   queue[front].id,
                   i + 1);

            if (front == MAX - 1)
                front = 0;
            else
                front++;

            requestCount--;
            return;
        }
    }

    printf("No telescope is currently available.\n");
}

void releaseTelescope()
{
    char input[20];
    int number, requestID, i;

    printf("Enter Telescope ID: ");
    fgets(input, sizeof(input), stdin);
    number = atoi(input);

    if (number < 1 || number > telescopeCount) {
        printf("Invalid telescope ID.\n");
        return;
    }

    if (telescope[number - 1].free) {
        printf("Telescope is already available.\n");
        return;
    }

    requestID = telescope[number - 1].requestID;

    for (i = 0; i < MAX; i++) {
        if (queue[i].id == requestID) {
            strcpy(queue[i].status, "Observed");
            break;
        }
    }

    telescope[number - 1].free = 1;
    telescope[number - 1].requestID = 0;

    printf("Telescope released successfully.\n");
}

void viewTelescopes()
{
    int i;

    if (telescopeCount == 0) {
        printf("No telescopes have been added.\n");
        return;
    }

    printf("\n--- Telescope List ---\n");

    for (i = 0; i < telescopeCount; i++) {
        printf("Telescope ID: %d | Name: %s | Status: ",
               i + 1, telescope[i].name);

        if (telescope[i].free)
            printf("Available\n");
        else
            printf("Busy (Request ID: %d)\n",
                   telescope[i].requestID);
    }
}

void organizationPanel()
{
    char input[20];
    int choice;

    do {
        printf("\n--- Organization Panel ---\n");
        printf("1. Submit Observation Request\n");
        printf("2. Check Request Status\n");
        printf("3. Back\n");
        printf("Choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            return;

        choice = atoi(input);

        if (choice == 1)
            submitRequest();
        else if (choice == 2)
            checkStatus();

    } while (choice != 3);
}

void adminPanel()
{
    char input[20];
    int choice;

    do {
        printf("\n--- Observation Station Admin ---\n");
        printf("1. Add Telescope\n");
        printf("2. View Observation Requests\n");
        printf("3. Assign Telescope\n");
        printf("4. Release Telescope\n");
        printf("5. View Telescopes\n");
        printf("6. Back\n");
        printf("Choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            return;

        choice = atoi(input);

        if (choice == 1)
            addTelescope();
        else if (choice == 2)
            viewRequests();
        else if (choice == 3)
            assignTelescope();
        else if (choice == 4)
            releaseTelescope();
        else if (choice == 5)
            viewTelescopes();

    } while (choice != 6);
}

int main()
{
    char input[20];
    int choice;

    do {
        printf("\n=== ASTEROID OBSERVATION STATION ===\n");
        printf("1. Organization Panel\n");
        printf("2. Observation Station Admin\n");
        printf("3. Exit\n");
        printf("Choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        choice = atoi(input);

        if (choice == 1)
            organizationPanel();
        else if (choice == 2)
            adminPanel();

    } while (choice != 3);

    return 0;
}

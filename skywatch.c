#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50
#define TEL 5

struct Request {
    int id, telescopeID;
    char organization[30];
    char status[15];
};

struct Telescope {
    int id, free;
    char name[30];
};

struct Request queue[MAX];
struct Telescope telescope[TEL];

int front = 0, rear = -1;
int nextID = 1, requestCount = 0, telescopeCount = 0;

int inputNumber()
{
    char input[20];
    fgets(input, sizeof(input), stdin);
    return atoi(input);
}

void submitRequest()
{
    if (requestCount == MAX) {
        printf("Request queue is full.\n");
        return;
    }

    rear = (rear + 1) % MAX;
    queue[rear].id = nextID++;
    queue[rear].telescopeID = 0;

    printf("Organization Name: ");
    fgets(queue[rear].organization, 30, stdin);
    queue[rear].organization[strcspn(queue[rear].organization, "\n")] = 0;

    strcpy(queue[rear].status, "Pending");
    requestCount++;

    printf("Request submitted successfully. Request ID: %d\n",
           queue[rear].id);
}

void checkStatus()
{
    int id, i;

    printf("Enter Request ID: ");
    id = inputNumber();

    for (i = 0; i < MAX; i++)
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

    telescope[telescopeCount].id = telescopeCount + 1;

    printf("Telescope Name: ");
    fgets(telescope[telescopeCount].name, 30, stdin);
    telescope[telescopeCount].name[
        strcspn(telescope[telescopeCount].name, "\n")] = 0;

    telescope[telescopeCount].free = 1;

    printf("Telescope added. Telescope ID: %d\n",
           telescope[telescopeCount].id);
    telescopeCount++;
}

void viewRequests()
{
    int i, position = front;

    if (requestCount == 0) {
        printf("No observation requests are waiting.\n");
        return;
    }

    for (i = 0; i < requestCount; i++) {
        printf("ID: %d | Organization: %s | Status: %s\n",
               queue[position].id, queue[position].organization,
               queue[position].status);
        position = (position + 1) % MAX;
    }
}

void assignTelescope()
{
    int i;

    if (requestCount == 0) {
        printf("No observation request is waiting.\n");
        return;
    }

    for (i = 0; i < telescopeCount; i++)
        if (telescope[i].free) {
            telescope[i].free = 0;
            queue[front].telescopeID = telescope[i].id;
            strcpy(queue[front].status, "Observing");

            printf("Request %d assigned to Telescope ID: %d\n",
                   queue[front].id, telescope[i].id);

            front = (front + 1) % MAX;
            requestCount--;
            return;
        }

    printf("No telescope is currently available.\n");
}

void releaseTelescope()
{
    int id, i;

    printf("Enter Telescope ID: ");
    id = inputNumber();

    if (id < 1 || id > telescopeCount) {
        printf("Invalid telescope ID.\n");
        return;
    }

    telescope[id - 1].free = 1;

    for (i = 0; i < MAX; i++)
        if (queue[i].telescopeID == id &&
            strcmp(queue[i].status, "Observing") == 0) {
            strcpy(queue[i].status, "Observed");
            break;
        }

    printf("Telescope released successfully.\n");
}

void organizationPanel()
{
    int choice;

    do {
        printf("\n--- Organization Panel ---\n");
        printf("1. Submit Observation Request\n");
        printf("2. Check Request Status\n");
        printf("3. Back\nChoice: ");
        choice = inputNumber();

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
        choice = inputNumber();

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
        choice = inputNumber();

        if (choice == 1) organizationPanel();
        else if (choice == 2) adminPanel();

    } while (choice != 3);

    return 0;
}

#include <stdio.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[20];
};

void saveContacts(struct Contact contacts[], int count) {
    FILE *file = fopen("contacts.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s\n", contacts[i].name);
            fprintf(file, "%s\n", contacts[i].phone);
        }
        fclose(file);
    }
}

int main() {
    
    int choice = 0;
    struct Contact contacts[100];
    int count = 0;

    // Load contacts from file
    FILE *file = fopen("contacts.txt", "r");
    if (file != NULL) {
        while (fgets(contacts[count].name, sizeof(contacts[count].name), file) &&
                fgets(contacts[count].phone, sizeof(contacts[count].phone), file)) {
            contacts[count].name[strlen(contacts[count].name) - 1] = '\0';
            contacts[count].phone[strlen(contacts[count].phone) - 1] = '\0';
            count++;
        }
        fclose(file);
        printf("Contacts loaded!\n");
    }

    while (choice != 5) {
        printf("\n1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display All Contacts\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        while(getchar() != '\n');

        switch (choice) {
            case 1: {
                if (count >= 100) {
                    printf("Contact list is full!\n");
                    break;
                }
                printf("Enter name: ");
                fgets(contacts[count].name, sizeof(contacts[count].name), stdin);
                contacts[count].name[strlen(contacts[count].name) - 1] = '\0';

                printf("Enter phone: ");
                fgets(contacts[count].phone, sizeof(contacts[count].phone), stdin);
                contacts[count].phone[strlen(contacts[count].phone) - 1] = '\0';

                count++;
                printf("Contact added!\n");
                saveContacts(contacts, count);
                break;
            }
            case 2: {
                char search[50];
                printf("Enter name to search: ");
                fgets(search, sizeof(search), stdin);
                search[strlen(search) - 1] = '\0';

                int found = 0;
                for (int i = 0; i < count; i++) {
                    if (strcasecmp(contacts[i].name, search) == 0) {
                        printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No contact found!\n");
                }
                break;
            }
            case 3: {
                if (count == 0) {
                    printf("No contacts to display!\n");
                    break;
                }
                for (int i = 0; i < count; i++) {
                    printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
                }
                break;
            }
            case 4: {
                if (count == 0) {
                    printf("No contacts to delete!\n");
                    break;
                }
                for (int i = 0; i < count; i++) {
                    printf("%d. %s - %s\n", i + 1, contacts[i].name, contacts[i].phone);
                }
                int del;
                printf("Enter the number of the contact to delete: ");
                scanf("%d", &del);
                while(getchar() != '\n');

                del--;

                if (del < 0 || del >= count) {
                    printf("Invalid contact number!\n");
                    break;
                }
                for (int i = del; i < count - 1; i++) {
                    contacts[i] = contacts[i + 1];
                }
                count--;
                printf("Contact deleted!\n");
                saveContacts(contacts, count);
                break;
            }
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option!\n");
                break;
        }
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ROOMS 30

// Structure to represent a Room
typedef struct {
    int roomNumber;
    int isBooked;
    char guestName[50];
    int rent;
    int paid;
} Room;

// Structure to represent the Hotel
typedef struct {
    Room rooms[MAX_ROOMS];
    int totalRooms;
} Hotel;

// Initialize all rooms to default values
void initializeRooms(Hotel *hotel) {
    for (int i = 0; i < hotel->totalRooms; i++) {
        hotel->rooms[i].roomNumber = i + 1;
        hotel->rooms[i].isBooked = 0;
        strcpy(hotel->rooms[i].guestName, "Not Booked");
        hotel->rooms[i].rent = 3000;
        hotel->rooms[i].paid = 0;
    }
}

// Display the status of all rooms
void displayRooms(Hotel *hotel) {
    printf("Room Number | Status     | Guest Name\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < hotel->totalRooms; i++) {
        printf("%-12d| %-11s| %s\n", hotel->rooms[i].roomNumber,
               hotel->rooms[i].isBooked ? "Booked" : "Available",
               hotel->rooms[i].isBooked ? hotel->rooms[i].guestName : "Not Booked");
    }
}

// Function to book a room
void bookRoom(Hotel *hotel) {
    int roomNumber;
    char guestName[50];

    printf("Enter room number to book (1 to %d): ", hotel->totalRooms);
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > hotel->totalRooms) {
        printf("Invalid room number!\n");
        return;
    }

    Room *room = &hotel->rooms[roomNumber - 1];
    
    if (room->isBooked) {
        printf("Room %d is already booked.\n", roomNumber);
    } else {
        char mp;
        printf("Minimum payment of Rs.500 required. Proceed (Y/N): ");
        scanf(" %c", &mp);
        if (mp == 'N' || mp == 'n') {
            return;
        }

        printf("Enter guest name: ");
        getchar();  // To consume newline from previous input
        fgets(guestName, sizeof(guestName), stdin);
        guestName[strcspn(guestName, "\n")] = 0; // Remove newline character

        room->isBooked = 1;
        strcpy(room->guestName, guestName);

        // Process payment
        int payment;
        do {
            printf("Enter payment amount: ");
            scanf("%d", &payment);
            if (payment < 500) {
                printf("Minimum payment of Rs.500 is required. Try again.\n");
            }
        } while (payment < 500);

        room->paid = payment;
        room->rent -= room->paid;
        printf("Room %d booked successfully for %s.\n", roomNumber, guestName);
    }
}

// Function to check out of a room
void checkOut(Hotel *hotel) {
    int roomNumber;

    printf("Enter room number to check out (1 to %d): ", hotel->totalRooms);
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > hotel->totalRooms) {
        printf("Invalid room number!\n");
        return;
    }

    Room *room = &hotel->rooms[roomNumber - 1];

    if (!room->isBooked) {
        printf("Room %d is not booked.\n", roomNumber);
    } else {
        room->isBooked = 0;

        // Process remaining payment
        int remainingAmount = room->rent;
        int payment;
        do {
            if (remainingAmount > 0) {
                printf("Remaining payment: %d\n", remainingAmount);
                printf("Enter payment: ");
                scanf("%d", &payment);
                remainingAmount -= payment;

                if (payment < remainingAmount) {
                    printf("Payment canceled. Remaining rent: %d\n", remainingAmount);
                }
            } else {
                printf("No remaining payment. Thank you for your stay!\n");
                break;
            }
        } while (remainingAmount > 0);

        // Reset guest information
        strcpy(room->guestName, "Not Booked");
        printf("Checked out from room %d successfully.\n", roomNumber);
    }
}

int main() {
    Hotel hotel = { .totalRooms = MAX_ROOMS };
    initializeRooms(&hotel);

    int choice;
    while (1) {
        printf("\n--- Bharath Rooms and Services (Cheap and Best) ---\n");
        printf("1. View all rooms\n");
        printf("2. Book a room (Rs. 3000 per day)\n");
        printf("3. Check out a room\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayRooms(&hotel);
                break;
            case 2:
                bookRoom(&hotel);
                break;
            case 3:
                checkOut(&hotel);
                break;
            case 4:
                printf("Exiting the program. Thank you!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

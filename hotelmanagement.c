#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ROOMS 30  
struct Room {
    int roomNumber;
    int isBooked;
    char guestName[50];
    int Rent;
    int paid;
};
void initializeRooms(struct Room rooms[], int size) {
    for (int i = 0; i < size; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = 0;
        strcpy(rooms[i].guestName, "Not Booked");
        rooms[i].Rent = 3000;
        rooms[i].paid = 0;
    }
}
void displayRooms(struct Room rooms[], int size) {
    printf("Room Number | Status     | Guest Name\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%-12d| %-11s| %s\n", rooms[i].roomNumber,
               rooms[i].isBooked ? "Booked" : "Available",
               rooms[i].isBooked ? rooms[i].guestName : "Not Booked");
    }
}

// Function to book a room
void bookRoom(struct Room rooms[], int size) {
    int roomNumber;
    char guestName[50];
    

    printf("Enter room number to book (1 to %d): ", size);
    scanf("%d", &roomNumber);
    
    if (roomNumber < 1 || roomNumber > size) {
        printf("Invalid room number!\n");
        return;
    }
    
    if (rooms[roomNumber - 1].isBooked) {
        printf("Room %d is already booked.\n", roomNumber);
    } else {
        char mp;
        printf("Minumum payment of Rs.500 {Y/N}:");
        scanf(" %c",&mp);
        if(mp == 'N')
        return;
    
        printf("Enter guest name: ");
        getchar();
        fgets(guestName, 50, stdin);
        guestName[strcspn(guestName, "\n")] = 0; 
        
        rooms[roomNumber - 1].isBooked = 1;
        strcpy(rooms[roomNumber - 1].guestName, guestName);
        a:
        printf("Payment: ");
        scanf("%d",&rooms[roomNumber -1].paid);
        if(rooms[roomNumber -1].paid >= 500){
        rooms[roomNumber - 1].Rent -= rooms[roomNumber -1].paid;
        printf("Room %d booked successfully for %s.\n", roomNumber, guestName);
        }
        else{
        rooms[roomNumber -1].paid =0;
        printf("Payment canceled. Minumum payment of Rs.500 is mandatory!\n");
        goto a;
        }
            
        }
}

void checkOut(struct Room rooms[], int size) {
    int roomNumber;

    printf("Enter room number to check out (1 to %d): ", size);
    scanf("%d", &roomNumber);

    if (roomNumber < 1 || roomNumber > size) {
        printf("Invalid room number!\n");
        return;
    }

    if (!rooms[roomNumber - 1].isBooked) {
        printf("Room %d is not booked.\n", roomNumber);
    } else {
        rooms[roomNumber - 1].isBooked = 0;
        b:
        if(rooms[roomNumber-1].Rent > 0){
        printf("Remaining payment amount: %d\nPayment: ",rooms[roomNumber-1].Rent);
        scanf("%d",&rooms[roomNumber-1].paid);
        if(rooms[roomNumber-1].paid < rooms[roomNumber-1].Rent){
        printf("Payment canceled. Your remaining Rent is %d\n",rooms[roomNumber-1].Rent);
        goto b;
        }
        else if(rooms[roomNumber-1].paid > rooms[roomNumber-1].Rent){
            printf("Thanks for your tip!! Hope you visit us again.\n");
        }
        }
        strcpy(rooms[roomNumber - 1].guestName, "Not Booked");
        printf("Checked out from room %d successfully.\n", roomNumber);
    }
}

int main() {
    struct Room rooms[MAX_ROOMS];
    int choice;
    initializeRooms(rooms, MAX_ROOMS);

    while (1) {
        printf("\n--- Bharath Rooms and Services(Cheap and Best) ---\n");
        printf("1. View all rooms\n");
        printf("2. Book a room (Rs. 3000 per day)\n");
        printf("3. Check out a room\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayRooms(rooms, MAX_ROOMS);
                break;
            case 2:
                bookRoom(rooms, MAX_ROOMS);
                break;
            case 3:
                checkOut(rooms, MAX_ROOMS);
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
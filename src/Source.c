#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_TRAIN_SCHEDULE 100
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_TRAIN_SCHEDULE 100
#define MAX_TIME_LENGTH 10
#define MAX_STATION_LENGTH 50

//TAN QI XUAN
struct User {
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
};

//TAN QI XUAN
struct User users[MAX_USERS];
int userCount = 0;

//TAN QI XUAN
struct TrainSchedule {
	char trainID[10];
	char departureStation[MAX_STATION_LENGTH];
	char arrivalStation[MAX_STATION_LENGTH];
	char departureTime[MAX_TIME_LENGTH];
	char arrivalTime[MAX_TIME_LENGTH];
};

//TAN QI XUAN
struct TrainSchedule trainSchedule[MAX_TRAIN_SCHEDULE];

//TAN QI XUAN
typedef struct {
	struct TrainSchedule trains;
	char name[50];
	char ticketType[40];
	int quantity;
	int totalSale;
	int bookingID;
} Book;

//TAN QI XUAN
int trainCount = 0;


//The Functions
//TAN QI XUAN
void readTrainSchedule();
void writeTrainSchedule();
void login();
void readUserCredentials();
void addTrainSchedule();
void deleteTrainSchedule();
void changeTrainSchedule();
void displayTrainSchedule();
void searchTrainSchedule();
//SAMANTHA LAU ZHEN MIAO
void userBookingMenu();
void userTrainBook();
void userViewRecord();
void staffBookingMenu();
void staffModifyBook();
void staffDisplayBook();
void staffReportSales();
void staffTicketSales();
void userCancelBook();
void staffCancelBook();

//TAN QI XUAN
int main() {
	readTrainSchedule();
	readUserCredentials();
	login();
	writeTrainSchedule();
	return 0;
}

//TAN QI XUAN
void readUserCredentials() {
	FILE* file = fopen("users.txt", "r");
	if (file == NULL) {
		printf("Error opening users.txt file.\n");
		exit(1);
	}

	while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
		userCount++;
	}

	fclose(file);
}

//TAN QI XUAN
void login() {
	char username[MAX_USERNAME_LENGTH];
	char password[MAX_PASSWORD_LENGTH];
	int found = 0;

	printf("Welcome to Train Schedule Management System!\n");
	printf("--------------------------------------------\n");
	printf("Enter as:\n");
	printf("---------\n");
	printf("1. Guest\n");
	printf("2. Admin\n");
	printf("Enter your choice: ");
	int choice;
	scanf("%d", &choice);

	if (choice == 1) {
		printf("You are logged in as a guest.\n");
		//displayTrainSchedule(); removed as it will show in booking menu
		userBookingMenu();
	}
	else if (choice == 2) {
		printf("You choose logged in as a admin.\n");
		printf("Enter username: ");
		scanf("%s", username);
		printf("Enter password: ");
		scanf("%s", password);

		for (int i = 0; i < userCount; i++) {
			if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
				found = 1;
				break;
			}

		}
		if (found)
		{// added do while loop
			int choices;
			do {
				printf("Admin Panel\n");
				printf("1. Train Schedule Management\n");
				printf("2. Train Booking Management\n");
				printf("3. Exit\n");
				rewind(stdin);
				printf("Enter your selection: ");
				scanf("%d", &choices);
				switch (choices) {
				case 1:
					do {
						printf("\nTrain Schedule Management System\n");
						printf("1. Add Train Time\n");
						printf("2. Remove Train Time\n");
						printf("3. Change Train Time\n");
						printf("4. Display all available Train Schedule\n");
						printf("5. Search Train Schedule\n");
						printf("6. Exit\n");
						printf("Enter your choice: ");
						scanf("%d", &choice);

						switch (choice) {
						case 1:
							addTrainSchedule();
							break;
						case 2:
							deleteTrainSchedule();
							break;
						case 3:
							changeTrainSchedule();
							break;
						case 4:
							displayTrainSchedule();
							break;
						case 5:
							searchTrainSchedule();
							break;
						case 6:
							printf("Exiting...\n");
							break;
						default:
							printf("Invalid choice. Please try again.\n");
						}
					} while (choice != 6);
					break;
				case 2: staffBookingMenu(); break;
				case 3: printf("Logging out..\n"); break;
				default: printf("Invalid selection!\n");
				}
			} while (choices != 3);
		}
		else {
			printf("Invalid Password or Username!!Please Try Again!\n");
		}

		return 0;
	}
}

//TAN QI XUAN
void readTrainSchedule() {
	FILE* file = fopen("trainschedule.txt", "r");
	if (file == NULL) {
		printf("Error opening the file.\n");
		exit(1);
	}

	while (fscanf(file, "%s %s %s %s %s", trainSchedule[trainCount].trainID, trainSchedule[trainCount].departureStation, trainSchedule[trainCount].arrivalStation, trainSchedule[trainCount].departureTime, trainSchedule[trainCount].arrivalTime) != EOF) {
		trainCount++;
	}

	fclose(file);
}

//TAN QI XUAN
void writeTrainSchedule() {
	FILE* file = fopen("trainschedule.txt", "w");
	if (file == NULL) {
		printf("Error opening the file for writing.\n");
		exit(1);
	}

	for (int i = 0; i < trainCount; i++) {
		fprintf(file, "%s %s %s %s %s\n", trainSchedule[i].trainID, trainSchedule[i].departureStation,
			trainSchedule[i].arrivalStation, trainSchedule[i].departureTime, trainSchedule[i].arrivalTime);
	}

	fclose(file);
}

//TAN QI XUAN
void addTrainSchedule() {
	if (trainCount >= MAX_TRAIN_SCHEDULE) {
		printf("Train schedule is full. Cannot add more trains.\n");
		return;
	}

	printf("Enter train ID: ");
	scanf("%s", trainSchedule[trainCount].trainID);
	printf("Enter departure station: ");
	scanf("%s", trainSchedule[trainCount].departureStation);
	printf("Enter arrival station: ");
	scanf("%s", trainSchedule[trainCount].arrivalStation);
	printf("Enter departure time (HH:MM): ");
	scanf("%s", trainSchedule[trainCount].departureTime);
	printf("Enter arrival time (HH:MM): ");
	scanf("%s", trainSchedule[trainCount].arrivalTime);

	trainCount++;
	printf("Train time added successfully.\n");
	writeTrainSchedule();
}

//TAN QI XUAN
void deleteTrainSchedule() {
	char trainID[10];
	int i, found = 0;
	char departureTime[MAX_TIME_LENGTH];
	char arrivalTime[MAX_TIME_LENGTH];
	char departureStation[MAX_STATION_LENGTH];
	char arrivalStation[MAX_STATION_LENGTH];

	printf("Enter train ID you want to delete:");
	scanf("%s", trainID);
	printf("Enter the departure station you want to delete:");
	scanf("%s", departureStation);
	printf("Enter the arrival station you want to delete:");
	scanf("%s", arrivalStation);
	printf("Enter the departure time (HH:MM):");
	scanf("%s", departureTime);
	printf("Enter the arrival time (HH:MM):");
	scanf("%s", arrivalTime);
	for (i = 0; i < trainCount; i++) {
		if (strcmp(trainID, trainSchedule[i].trainID) == 0 && strcmp(departureStation, trainSchedule[i].departureStation) == 0 && strcmp(arrivalStation, trainSchedule[i].arrivalStation) == 0 && strcmp(departureTime, trainSchedule[i].departureTime) == 0 && strcmp(arrivalTime, trainSchedule[i].arrivalTime) == 0) {
			found = 1;
			break;
		}
	}

	if (found) {
		for (; i < trainCount - 1; i++) {
			strcpy(trainSchedule[i].trainID, trainSchedule[i + 1].trainID);
			strcpy(trainSchedule[i].departureStation, trainSchedule[i + 1].departureStation);
			strcpy(trainSchedule[i].arrivalStation, trainSchedule[i + 1].arrivalStation);
			strcpy(trainSchedule[i].departureTime, trainSchedule[i + 1].departureTime);
			strcpy(trainSchedule[i].arrivalTime, trainSchedule[i + 1].arrivalTime);
		}
		trainCount--;
		printf("Train time removed successfully.\n");
		writeTrainSchedule();
	}
	else {
		printf("Your searching result are not found in the train schedule!Please Try Again!\n");
	}
}

//TAN QI XUAN
void changeTrainSchedule() {
	char trainID[10];
	int i, found = 0;
	char departureTime[MAX_TIME_LENGTH];
	char arrivalTime[MAX_TIME_LENGTH];
	char departureStation[MAX_STATION_LENGTH];
	char arrivalStation[MAX_STATION_LENGTH];

	printf("Enter the train ID you want to change: ");
	scanf("%s", trainID);
	printf("Enter the departure station you want to change:");
	scanf("%s", departureStation);
	printf("Enter the arrival station you want to change:");
	scanf("%s", arrivalStation);
	printf("Enter the departure time (HH:MM):");
	scanf("%s", departureTime);
	printf("Enter the arrival time (HH:MM):");
	scanf("%s", arrivalTime);

	for (i = 0; i < trainCount; i++) {
		if (strcmp(trainID, trainSchedule[i].trainID) == 0 && strcmp(departureStation, trainSchedule[i].departureStation) == 0 && strcmp(arrivalStation, trainSchedule[i].arrivalStation) == 0 && strcmp(departureTime, trainSchedule[i].departureTime) == 0 && strcmp(arrivalTime, trainSchedule[i].arrivalTime) == 0) {
			found = 1;
			break;
		}
	}

	if (found) {
		printf("----------------------------\n");
		printf("Result Found!");
		printf("----------------------------\n");
		printf("Enter new departure station: ");
		scanf("%s", trainSchedule[i].departureStation);
		printf("Enter new arrival station: ");
		scanf("%s", trainSchedule[i].arrivalStation);
		printf("Enter new departure time (HH:MM): ");
		scanf("%s", trainSchedule[i].departureTime);
		printf("Enter new arrival time (HH:MM): ");
		scanf("%s", trainSchedule[i].arrivalTime);
		printf("Train time changed successfully.\n");
		writeTrainSchedule();
	}
	else {
		printf("Your searching result are not found in the train schedule!Please Try Again!\n");
	}
}

//TAN QI XUAN
void displayTrainSchedule() {
	if (trainCount == 0) {
		printf("Train schedule is empty.\n");
		return;
	}

	printf("Train Schedule\n");
	printf("Train ID\tDeparture Station\tArrival Station\tDeparture Time\tArrival Time\n");
	printf("--------\t-----------------\t--------------\t--------------\t------------\n");
	for (int i = 0; i < trainCount; i++) {
		printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", trainSchedule[i].trainID, trainSchedule[i].departureStation,
			trainSchedule[i].arrivalStation, trainSchedule[i].departureTime, trainSchedule[i].arrivalTime);
	}
}

//TAN QI XUAN
void searchTrainSchedule() {
	char searchID[10];
	int found = 0;

	printf("Enter train ID to search: ");
	scanf("%s", searchID);

	printf("Search Results:\n");
	printf("Train ID\tDeparture Station\tArrival Station\tDeparture Time\tArrival Time\n");
	for (int i = 0; i < trainCount; i++) {
		if (strcmp(searchID, trainSchedule[i].trainID) == 0) {
			found = 1;
			printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\n", trainSchedule[i].trainID, trainSchedule[i].departureStation,
				trainSchedule[i].arrivalStation, trainSchedule[i].departureTime, trainSchedule[i].arrivalTime);
		}
	}

	if (!found) {
		printf("Your searching result are not found in the train schedule!Please Try Again!.\n");
	}
}

//SAMANTHA LAU ZHEN MIAO
void userBookingMenu() {
	int choice;
	do { //validation it only allow number from 1 to 4
		system("cls");
		printf("User booking menu\n");
		printf("1. Book train\n");
		printf("2. View booking records\n");
		printf("3. Cancel booking\n");
		printf("4. Exit\n");
		rewind(stdin);
		printf("Enter your selection: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: userTrainBook(); break;
		case 2: userViewRecord(); system("pause"); break;
		case 3: userCancelBook(); break;
		case 4: printf("Exiting..\n"); break;
		default:
			printf("Invalid choice!\n"); //display error message if input invalid 
			system("pause");
		}
	} while (choice != 4);
}

//SAMANTHA LAU ZHEN MIAO
void userTrainBook() {
	system("cls");
	Book booking, temp;
	FILE* fPtr;
	char con = 'n';
	int count = 0;
	int price[4] = { 90, 40, 20 };
	int tempPrice;
	displayTrainSchedule(); //display available trains
	do {
		rewind(stdin);
		printf("Enter train ID you wish to book: "); //input train to book
		scanf("%[^\n]", &booking.trains.trainID);

		for (int i = 0; i < strlen(booking.trains.trainID); i++) { //make the string to upper case
			booking.trains.trainID[i] = toupper(booking.trains.trainID[i]);
		}

		fPtr = fopen("trainschedule.txt", "r");
		count = 0;
		if (fPtr != NULL) { //check for if the train id is available
			while (fscanf(fPtr, "%s %s %s %s %s\n", &temp.trains.trainID, &temp.trains.departureStation, &temp.trains.arrivalStation,
				&temp.trains.departureTime, &temp.trains.arrivalTime) != EOF) {
				if (strcmp(booking.trains.trainID, temp.trains.trainID) == 0) {
					con = 'y';
					count++;
					strcpy(booking.trains.trainID, temp.trains.trainID);
					strcpy(booking.trains.departureStation, temp.trains.departureStation);
					strcpy(booking.trains.arrivalStation, temp.trains.arrivalStation);
					strcpy(booking.trains.departureTime, temp.trains.departureTime);
					strcpy(booking.trains.arrivalTime, temp.trains.arrivalTime);
				}
			}
			if (count == 0) {
				printf("No such train ID found!\n"); //display error
				con = 'n';
			}
			fclose(fPtr);
		}
		else {
			printf("There is no train available to book!\n"); //display error
		}
	} while (con != 'y');

	do {
		int error = 0;
		rewind(stdin);
		printf("Enter your name: "); //input booking name
		scanf("%[^\n]", &booking.name);

		for (int i = 0; i < strlen(booking.name); i++) { //transform string to upper case
			booking.name[i] = toupper(booking.name[i]);
			if (!isalpha(booking.name[i])) {
				error++;
			}
		}
		if (error == 0) {
			con = 'y';
		}
		else {
			con = 'n'; //display error
			printf("Invalid character used!\n");
		}
	} while (con != 'y');

	do {
		int select;
		rewind(stdin); //select ticket type
		printf("Ticket Type:\n1. First class\n2. Business Class\n3. Economy Class\n");
		printf("Select your ticket type: ");
		scanf("%d", &select);
		switch (select) {
		case 1: strcpy(booking.ticketType, "First_Class"); con = 'y'; tempPrice = price[0];  break;
		case 2: strcpy(booking.ticketType, "Business_Class"); con = 'y'; tempPrice = price[1]; break;
		case 3: strcpy(booking.ticketType, "Economy_Class"); con = 'y'; tempPrice = price[2]; break;
		default:
			printf("Invalid ticket type!\n"); //display error
			con = 'n';
		}
	} while (con != 'y');

	do {
		rewind(stdin); //input booking quantity
		printf("Enter quantity you wish to book: ");
		scanf("%d", &booking.quantity);
		if (booking.quantity < 0) {
			printf("You cannot book negative ticket!\n"); //display error
		}
		else if (booking.quantity > 100) {
			printf("You cannot book more than 100 ticket!\n");  //display error
		}
	} while (booking.quantity < 0 || booking.quantity > 100);

	booking.totalSale = tempPrice * booking.quantity;

	char confirm; //confirmation for users
	printf("Booking Confirmation:\n");
	printf("Train ID: %s\n", booking.trains.trainID);
	printf("Booking Name: %s\n", booking.name);
	printf("Ticket Type: %s\n", booking.ticketType);
	printf("Quantity: %d\n", booking.quantity);
	printf("Total Payment: %d\n", booking.totalSale);
	printf("\nAre you sure you want to confirm booking (Y/N)? ");
	rewind(stdin);
	scanf("%c", &confirm);
	confirm = toupper(confirm);
	if (confirm == 'Y') {
		int payment;
		do { //select payment method
			printf("Payment method:\n1. Bank Transfer\n2. Card\n3. E-Wallet\n");
			printf("\nSelect your payment method:");
			rewind(stdin);
			scanf("%d", &payment);
			if (payment < 1 || payment > 3) {
				printf("Invalid payment type!\n");
			}
		} while (payment < 1 || payment > 3);
		if (payment == 1) {
			char proceed;
			do { //screen that show the bank information for user to transfer
				printf("Please transfer to following bank account:\nName: KTM MALAYSIA\nBank Number: 2342344423423444\n");
				printf("Enter Y to proceed: ");
				rewind(stdin);
				scanf("%c", &proceed);
				proceed = toupper(proceed);
			} while (proceed != 'Y');
		}
		else if (payment == 2) { //no validation
			int cardNum, securityNum;
			char cardName[40], expiryDate[20];
			rewind(stdin);
			printf("Enter your card number: ");
			scanf("%d", &cardNum);
			rewind(stdin);
			printf("Enter your card name: ");
			scanf("%[^\n]", &cardName);
			rewind(stdin);
			printf("Enter expiry date (XX/XX): ");
			scanf("%[^\n]", &expiryDate);
			rewind(stdin);
			printf("Enter your security number: ");
			scanf("%d", &securityNum);
		}
		else {
			char proceed;
			do { //e wallet information for user to transfer
				printf("Please transfer to following ewallet account:\nName: KTM MALAYSIA\nE-Wallet Number: 23434234344\n");
				printf("Enter Y to proceed: ");
				rewind(stdin);
				scanf("%c", &proceed);
				proceed = toupper(proceed);
			} while (proceed != 'Y');
		}
		booking.bookingID = 1000;
		fPtr = fopen("booking.bin", "rb");
		if (fPtr != NULL) {
			while (fread(&temp, sizeof(Book), 1, fPtr)) {
				if (temp.bookingID > booking.bookingID) {
					booking.bookingID = temp.bookingID;
				}
			}
			fclose(fPtr);
		}

		booking.bookingID++;
		fPtr = fopen("booking.bin", "ab");

		fwrite(&booking, sizeof(Book), 1, fPtr);
		fclose(fPtr);
		printf("Booking successful!\n");
		system("pause");
	}
	else {
		printf("Cancelling..\n");
	}
}

//SAMANTHA LAU ZHEN MIAO
void userViewRecord() {
	Book booking;
	FILE* fPtr;
	char inputName[40];
	int count = 0;

	rewind(stdin); //input booking name to check booking records
	printf("Enter your booking name: ");
	scanf("%[^\n]", &inputName);

	for (int i = 0; i < strlen(inputName); i++) {
		inputName[i] = toupper(inputName[i]);
	}
	//display booking records
	printf("%6s | %10s | %13s | %12s | %12s | %8s | %8s | %14s | %10s\n", "BOOKID", "TRAINID", "BOOKING NAME", "DEP STATION", "ARR STATION", "DEP TIME", "ARR TIME", "TICKET TYPE", "QUANTITY");
	fPtr = fopen("booking.bin", "rb");
	if (fPtr != NULL) {
		while (fread(&booking, sizeof(Book), 1, fPtr)) {
			if (strcmp(inputName, booking.name) == 0) {
				printf("%6d | %10s | %13s | %12s | %12s | %8s | %8s | %14s | %d\n", booking.bookingID, booking.trains.trainID, booking.name, booking.trains.departureStation, booking.trains.arrivalStation, booking.trains.departureTime, booking.trains.arrivalTime,
					booking.ticketType, booking.quantity);
				count++;
			}
		}
		
		fclose(fPtr);
		if (count == 0) {
			printf("No booking record found!\n");
		}
	}
	else {
		printf("No record found!\n");
	}
}

//SAMANTHA LAU ZHEN MIAO
void staffBookingMenu() {
	int choice;
	do { //staff booking panel only allow 1 - 6 
		system("cls");
		printf("Staff booking menu\n");
		printf("1. Modify booking record\n");
		printf("2. Display booking record\n");
		printf("3. Report sales\n");
		printf("4. Ticket type sales\n");
		printf("5. Cancel booking\n");
		printf("6. Exit\n");
		rewind(stdin);
		printf("Enter your selection: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1: staffModifyBook(); system("pause");  break;
		case 2: staffDisplayBook(); break;
		case 3: staffReportSales(); break;
		case 4: staffTicketSales(); break;
		case 5: staffCancelBook(); break;
		case 6: printf("Exiting..\n"); break;
		default:
			printf("Invalid choice!\n"); //display error
			system("pause");
		}
	} while (choice != 6);
}

//SAMANTHA LAU ZHEN MIAO
void staffModifyBook() {
	system("cls");
	staffDisplayBook();
	Book booking, temp;
	FILE* fPtr;
	FILE* fPtr2;
	char con = 'n';
	int tempPrice;
	int price[4] = { 90, 40, 20 }; //price list

	do {
		int found = 0; //input booking id 
		printf("Enter Booking ID to modify: ");
		rewind(stdin);
		scanf("%d", &booking.bookingID);
		fPtr = fopen("booking.bin", "rb");
		if (fPtr != NULL) {
			while (fread(&temp, sizeof(Book), 1, fPtr)) {
				if (booking.bookingID == temp.bookingID) {
					found++;
					printf("Default DATA:\n");
					printf("%10s | %15s | %15s | %10s | %10s\n", "BOOK ID", "BOOKING NAME", "TICKET TYPE", "QUANTITY", "TOTAL PAYMENT");
					printf("%10d | %15s | %15s | %10d | %10d\n", temp.bookingID, temp.name, temp.ticketType, temp.quantity, temp.totalSale);
					booking = temp;
				}
			}
			fclose(fPtr);
			if (found == 0) {
				printf("No such booking ID found!\n"); //display error
				con = 'n';
			}
			else {
				con = 'y';
			}
		}
	} while (con != 'y');

	do {
		con = 'n';
		int count = 0;
		rewind(stdin); //input booking name
		printf("Enter new booking name: ");
		scanf("%[^\n]", &booking.name);
		for (int i = 0; i < strlen(booking.name); i++) {  //check if the element is alphabet
			if (!isalpha(booking.name[i])) {
				count++;
			}
		}
		if (count > 0) {
			printf("Please only use alphabet characters!\n"); //display error
		}
		else {
			for (int i = 0; i < strlen(booking.name); i++) { //translate to uppercase
				booking.name[i] = toupper(booking.name[i]);
			}
			con = 'y';
		}
	} while (con != 'y');

	do {
		int select;
		rewind(stdin); //select ticket type
		printf("Ticket Type:\n1. First class\n2. Business Class\n3. Economy Class\n");
		printf("Select your ticket type: ");
		scanf("%d", &select);
		switch (select) {
		case 1: strcpy(booking.ticketType, "First_Class"); con = 'y'; tempPrice = price[0];  break;
		case 2: strcpy(booking.ticketType, "Business_Class"); con = 'y'; tempPrice = price[1]; break;
		case 3: strcpy(booking.ticketType, "Economy_Class"); con = 'y'; tempPrice = price[2]; break;
		default:
			printf("Invalid ticket type!\n"); //display error
			con = 'n';
		}
	} while (con != 'y');

	do {
		rewind(stdin); //input quantity to modify
		printf("Enter quantity you wish to book: ");
		scanf("%d", &booking.quantity);
		if (booking.quantity < 0) {
			printf("You cannot book negative ticket!\n"); //display error
		}
		else if (booking.quantity > 100) {
			printf("You cannot book more than 100 ticket!\n"); //display error
		}
	} while (booking.quantity < 0 || booking.quantity > 100);

	booking.totalSale = tempPrice * booking.quantity;

	char confirm; //modify confirmation
	printf("Booking Confirmation:\n");
	printf("Train ID: %s\n", booking.trains.trainID);
	printf("Booking Name: %s\n", booking.name);
	printf("Ticket Type: %s\n", booking.ticketType);
	printf("Quantity: %d\n", booking.quantity);
	printf("Total Payment: %d\n", booking.totalSale);
	printf("\nAre you sure you want to confirm booking (Y/N)? ");
	rewind(stdin);
	scanf("%c", &confirm);
	confirm = toupper(confirm);
	if (confirm == 'Y') {
		fPtr = fopen("booking.bin", "rb");
		fPtr2 = fopen("tempBooking.bin", "wb");
		if (fPtr == NULL) {
			printf("Something went wrong!\n"); //display error
			exit(-1);
		}
		while (fread(&temp, sizeof(Book), 1, fPtr)) {
			if (booking.bookingID != temp.bookingID) {
				fwrite(&temp, sizeof(Book), 1, fPtr2);
			}
		}
		fclose(fPtr);
		fclose(fPtr2);
		remove("booking.bin");
		rename("tempBooking.bin", "booking.bin");

		fPtr = fopen("booking.bin", "ab");
		fwrite(&booking, sizeof(Book), 1, fPtr);
		fclose(fPtr);
		printf("Successfully modified booking ID %d\n", booking.bookingID);
	}
	else {
		printf("Cancelling...\n");
		system("pause");
	}

}

//SAMANTHA LAU ZHEN MIAO
void staffDisplayBook() {
	Book booking;
	FILE* fPtr; //display all booking records
	printf("Staff Side Display Booking Records:\n");
	printf("%6s | %10s | %13s | %12s | %12s | %8s | %8s | %14s | %10s\n", "BOOKID", "TRAINID", "BOOKING NAME", "DEP STATION", "ARR STATION", "DEP TIME", "ARR TIME", "TICKET TYPE", "QUANTITY");
	fPtr = fopen("booking.bin", "rb");
	if (fPtr != NULL) {
		while (fread(&booking, sizeof(Book), 1, fPtr)) {
			printf("%6d | %10s | %13s | %12s | %12s | %8s | %8s | %14s | %d\n", booking.bookingID, booking.trains.trainID, booking.name, booking.trains.departureStation, booking.trains.arrivalStation, booking.trains.departureTime, booking.trains.arrivalTime,
				booking.ticketType, booking.quantity);
		}
		fclose(fPtr);
	}
	system("pause");
}

//SAMANTHA LAU ZHEN MIAO
void staffReportSales() {
	Book booking;
	struct TrainSchedule trains;
	FILE* fPtr;
	FILE* fPtr2;
	int sales = 0;
	system("cls");
	fPtr = fopen("trainschedule.txt", "r");
	fPtr2 = fopen("booking.bin", "rb");

	if (fPtr == NULL || fPtr2 == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	//display sales for evert train
	printf("Sales for each train:\n");

	while (fscanf(fPtr, "%s %s %s %s %s\n", trains.trainID, trains.departureStation, trains.arrivalStation, trains.departureTime, trains.arrivalTime) != EOF) {
		sales = 0;

		fseek(fPtr2, 0, SEEK_SET);

		while (fread(&booking, sizeof(Book), 1, fPtr2)) {
			if (strcmp(trains.trainID, booking.trains.trainID) == 0) {
				sales += booking.totalSale;
			}
		}
		//train details
		printf("TRAIN ID: %s\nTOTAL SALES: RM %d\n\n", trains.trainID, sales);
	}

	fclose(fPtr);
	fclose(fPtr2);

	fPtr = fopen("booking.bin", "rb");
	if (fPtr == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	sales = 0;
	while (fread(&booking, sizeof(Book), 1, fPtr)) {
		sales += booking.totalSale;
	}
	fclose(fPtr);
	//display total sales of all train
	printf("Total sales of all train:\n");
	printf("SALES: %d\n", sales);
	system("pause");
}

//SAMANTHA LAU ZHEN MIAO
void staffTicketSales() {
	Book booking;
	FILE* fPtr;
	int sales[4] = { 0 };
	system("cls");

	fPtr = fopen("booking.bin", "rb");
	if (fPtr == NULL) {
		printf("Something went wrong!\n");
		exit(-1);
	}
	while (fread(&booking, sizeof(Book), 1, fPtr)) {
		if (strcmp(booking.ticketType, "Business_Class") == 0) {
			sales[1] += booking.totalSale;
		}
		else if (strcmp(booking.ticketType, "First_Class") == 0) {
			sales[0] += booking.totalSale;
		}
		else if (strcmp(booking.ticketType, "Economy_Class") == 0) {
			sales[2] += booking.totalSale;
		}
	}
	//display sales for each ticket type
	printf("Sales for each ticket type:\n");
	printf("First Class: RM %d\n", sales[0]);
	printf("Business Class: RM %d\n", sales[1]);
	printf("Economy Class: RM %d\n", sales[2]);
	system("pause");
}

//SAMANTHA LAU ZHEN MIAO
void userCancelBook() {
	userViewRecord();
	FILE* fPtr;
	FILE* fPtr2;
	Book books;
	int tempBook;
	char con = 'n';
	int found = 0;
	char choice;
	int refundAmount;
	do {
		//input id to cancel
		rewind(stdin);
		printf("Enter book id to cancel: ");
		scanf("%d", &tempBook);
		fPtr = fopen("booking.bin", "rb");
		if (fPtr != NULL) {
			while (fread(&books, sizeof(Book), 1, fPtr)) {
				if (tempBook == books.bookingID) {
					found++;
					refundAmount = books.totalSale;
				}
			}
			fclose(fPtr);
		}
		else {
			printf("No booking records\n"); //display error
			con = 'y';
		}
		if (found > 0) {
			con = 'y';
		}
		else {
			printf("Invalid booking id!\n"); //display error
		}
	} while (con != 'y');

	if (found > 0) {
		//confirmation to cancel booking
		rewind(stdin);
		printf("Booking ID: %d\n", tempBook);
		printf("Are you sure you want to cancel the following booking (Y/N)? ");
		scanf("%c", &choice);
		choice = toupper(choice);
	}

	if (choice == 'Y') {
		fPtr = fopen("booking.bin", "rb");
		fPtr2 = fopen("tempBooking.bin", "ab");

		while (fread(&books, sizeof(Book), 1, fPtr)) {
			if (books.bookingID != tempBook) {
				fwrite(&books, sizeof(Book), 1, fPtr2);
			}
		}
		fclose(fPtr);
		fclose(fPtr2);
		remove("booking.bin");
		rename("tempBooking.bin", "booking.bin");
		//show successfully messages
		printf("Successfully cancel the booking!\n");
		printf("RM %d has refunded to your account!\n", refundAmount);
		system("pause");
	}
}

//SAMANTHA LAU ZHEN MIAO
void staffCancelBook() {
	staffDisplayBook();
	FILE* fPtr;
	FILE* fPtr2;
	Book books;
	int tempBook;
	char con = 'n';
	int found = 0;
	char choice;
	int refundAmount;
	do {
		rewind(stdin);
		printf("Enter book id to cancel: ");
		scanf("%d", &tempBook);
		fPtr = fopen("booking.bin", "rb");
		if (fPtr != NULL) {
			while (fread(&books, sizeof(Book), 1, fPtr)) {
				if (tempBook == books.bookingID) {
					found++;
					refundAmount = books.totalSale;
				}
			}
			fclose(fPtr);
		}
		else {
			printf("No booking records\n");
			con = 'y';
		}
		if (found > 0) {
			con = 'y';
		}
		else {
			printf("Invalid booking id!\n");
		}
	} while (con != 'y');

	if (found > 0) {
		rewind(stdin);
		//cancel booking confirmation
		printf("Booking ID: %d\n", tempBook);
		printf("Are you sure you want to cancel the following booking (Y/N)? ");
		scanf("%c", &choice);
		choice = toupper(choice);
	}

	if (choice == 'Y') {
		fPtr = fopen("booking.bin", "rb");
		fPtr2 = fopen("tempBooking.bin", "ab");

		while (fread(&books, sizeof(Book), 1, fPtr)) {
			if (books.bookingID != tempBook) {
				fwrite(&books, sizeof(Book), 1, fPtr2);
			}
		}
		fclose(fPtr);
		fclose(fPtr2);
		remove("booking.bin");
		rename("tempBooking.bin", "booking.bin");
		//display the successful messages
		printf("Successfully cancel the booking!\n");
		printf("RM %d has refunded to your account!\n", refundAmount);
		system("pause");
	}
}
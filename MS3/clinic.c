/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Ping-Ju, Chen
Student ID#: 151043205
Email      : pchen72@myseneca.ca
Section    : NAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

// System library
#include <stdio.h>

// String library
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"

// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu (hub) for application
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}

// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, invalid = 0;

    // If fmt is table format -> show the header
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            invalid++;
        }
        else
        {
            displayPatientData(&patient[i], fmt);
        }
    }
    if (invalid == i)
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int opt;

    do {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");
        opt = inputIntRange(0, 2);
        putchar('\n');

        if (opt == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (opt == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
    } while (opt);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int index = 0;

    index = findPatientIndexByPatientNum(0, patient, max);

    if (index == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientID, index;

    printf("Enter the patient number: ");
    patientID = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientID, patient, max);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientID, index;
    char option;
    struct Patient empty = { 0 };

    printf("Enter the patient number: ");
    patientID = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientID, patient, max);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n"
               "Are you sure you want to remove this patient record? (y/n): ");
        option = inputCharOption("yn");
        if (option == 'n')
        {
            printf("Operation aborted.\n\n");
        }
        else
        {
            patient[index] = empty;
            printf("Patient record has been removed!\n\n");
        }
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i;
    int emptyCheck = 0, index = 0;

    displayScheduleTableHeader(&data->appointments->date, FMT_ALL_RECS);
    sortAppointsByDateTime(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber == 0)
        {
            emptyCheck++;
        }
        else
        {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, 
                                                 data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], 
                                &data->appointments[i], FMT_DATE_FIELD);
        }
    }
    if (emptyCheck == i)
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i;
    int matchAppoint = 0, matchRecs = 0, index = 0;
    struct Date optDate = { 0 };

    optDate = inputAppointDate();
    putchar('\n');
    displayScheduleTableHeader(&optDate, !FMT_ALL_RECS);
    sortAppointsByDateTime(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)
    {
        matchAppoint = searchSameDateAppoint(&data->appointments[i], 
                                             &optDate, data->maxAppointments);
        if (matchAppoint)
        {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, 
                                                 data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], 
                                &data->appointments[i], !FMT_DATE_FIELD);
            matchRecs++;
        }
    }
    if (!matchRecs)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment appoints[], int maxAppoints, 
                    struct Patient patients[], int maxPatients)
{
    int i, freeIndex = 0, matchPatient = 0, matchAppoint = 0;
    int timeClash = 0;
    struct Appointment optAppoint = { 0 };

    freeIndex = findAvailableAppointment(appoints, maxAppoints);
    if (freeIndex == -1)
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
    }
    else
    {
        matchPatient = inputPatientValidation(&optAppoint, patients, maxPatients);
        if (matchPatient == -1)
        {
            printf("ERROR: Patient record not found!\n\n");
        }
        else
        {
            do {
                timeClash = 0;
                optAppoint.date = inputAppointDate();
                optAppoint.time = inputAppointTime();

                for (i = 0; !timeClash && i < maxAppoints; i++)
                {
                    matchAppoint = searchSameDateAppoint(&appoints[i],
                                                         &optAppoint.date, 
                                                         maxAppoints);
                    if (matchAppoint &&
                        optAppoint.time.hour == appoints[i].time.hour &&
                        optAppoint.time.min == appoints[i].time.min)
                    {
                        putchar('\n');
                        printf("ERROR: Appointment timeslot is not available!\n\n");
                        timeClash = 1;
                    }
                }
            } while (timeClash);

            appoints[freeIndex] = optAppoint;
            putchar('\n');
            printf("*** Appointment scheduled! ***\n\n");
        }
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appoints[], int maxAppoints, 
                       struct Patient patients[], int maxPatients)
{
    int i, rmOpt;
    int patientIndex = 0, matchAppoint = 0, exitFlag = 0;
    struct Appointment rmAppoint = { 0 };
    struct Appointment empty = { 0 };

    patientIndex = inputPatientValidation(&rmAppoint, patients, maxPatients);
    if (patientIndex == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        rmAppoint.date = inputAppointDate();
        putchar('\n');
        displayPatientData(&patients[patientIndex], FMT_FORM);

        printf("Are you sure you want to remove this appointment (y,n): ");
        rmOpt = inputCharOption("yn");
        if (rmOpt == 'y')
        {
            for (i = 0; !exitFlag && i < maxAppoints; i++)
            {
                matchAppoint = searchSameDateAppoint(&appoints[i], 
                                                     &rmAppoint.date, 
                                                     maxAppoints);
                if (matchAppoint && 
                    rmAppoint.patientNumber == appoints[i].patientNumber)
                {
                    appoints[i] = empty;
                    putchar('\n');
                    printf("Appointment record has been removed!\n\n");
                    exitFlag = 1;
                }
            }
            if (!exitFlag)
            {
                printf("ERROR: Appointment record not found!\n\n");
            }
        }
        else
        {
            putchar('\n');
            printf("Operation aborted.\n\n");
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientID, index;

    printf("Search by patient number: ");
    patientID = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patientID, patient, max);
    if (index == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    putchar('\n');
    suspend();
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, valid = 0;
    char phone[PHONE_LEN + 1] = { '\0' };

    printf("Search by phone number: ");
    inputCString(phone, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (!strcmp(phone, patient[i].phone.number))
        {
            displayPatientData(&patient[i], FMT_TABLE);
            valid++;
        }
    }
    if (!valid)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int nextPatientNum = patient[0].patientNumber;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > nextPatientNum)
        {
            nextPatientNum = patient[i].patientNumber;
        }
    }
    nextPatientNum += 1;

    return nextPatientNum;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i, index = 0, valid = 0;

    //exit the loop once valid
    for (i = 0; i < max && !valid; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            index = i;
            valid = 1;
        }
    }
    if (valid == 0)
    {
        index = -1;
    }

    return index;
}

// Using bubble sort, sort the appointment Date and Time. (ascending order)
void sortAppointsByDateTime(struct Appointment appoints[], int itemCount)
{
    int i, j;
    struct Appointment tempAppoint;

    for (i = itemCount - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if ((appoints[j].date.year > appoints[j + 1].date.year) ||

                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month > appoints[j + 1].date.month) ||

                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month == appoints[j + 1].date.month &&
                    appoints[j].date.day > appoints[j + 1].date.day) ||

                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month == appoints[j + 1].date.month &&
                    appoints[j].date.day == appoints[j + 1].date.day &&
                    appoints[j].time.hour > appoints[j + 1].time.hour) ||

                (appoints[j].date.year == appoints[j + 1].date.year &&
                    appoints[j].date.month == appoints[j + 1].date.month &&
                    appoints[j].date.day == appoints[j + 1].date.day &&
                    appoints[j].time.hour == appoints[j + 1].time.hour &&
                    appoints[j].time.min > appoints[j + 1].time.min))
            {
                tempAppoint = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = tempAppoint;
            }
        }
    }
}

// Search for the appointment that match the DATE (return 0 if not found)
int searchSameDateAppoint(struct Appointment* appoints,
                          struct Date* optDate, int maxAppoints)
{
    int match = 0;

    if (optDate->year == appoints->date.year &&
        optDate->month == appoints->date.month &&
        optDate->day == appoints->date.day)
    {
        match = 1;
    }

    return match;
}

// Find an available appointment index (return -1 if not found)
int findAvailableAppointment(struct Appointment appoints[], int max)
{
    int i, index = 0, valid = 0;
    
    for (i = 0; !valid && i < max; i++)
    {
        if (appoints[i].patientNumber < 1)
        {
            index = i;
            valid = 1;
        }
    }
    if (!valid)
    {
        index = -1;
    }

    return index;
}
 

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
           "------------------\n"
           "Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int option = 0;
    char newLine = '\0';
    char fmt[50 + 1] = { '\0' };

    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    option = inputIntRange(1, 4);
    putchar('\n');

    switch (option)
    {
    case 1:
        strcpy(phone->description, "CELL");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        break;
    }

    if (option != 4)
    {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");

        do {
            sprintf(fmt, "%%%d[^\n]%%c", PHONE_LEN);
            scanf(fmt, &phone->number, &newLine);

            if (strlen(phone->number) != 10)
            {
                printf("Invalid %d-digit number! Number: ", PHONE_LEN);
            }
            else if (newLine != '\n')
            {
                clearInputBuffer();
                printf("Invalid %d-digit number! Number: ", PHONE_LEN);
            }
        } while (strlen(phone->number) != 10 || newLine != '\n');

        putchar('\n');
    }
}

// Get user input for appointment date, calculate for leap year and number of days in a month
struct Date inputAppointDate(void)
{
    int numOfDay;
    struct Date optDate = { 0 };

    printf("Year        : ");
    optDate.year = inputIntPositive();

    printf("Month (%d-%d): ", FIRST_MONTH, LAST_MONTH);
    optDate.month = inputIntRange(1, 12);
    numOfDay = checkDayInMonth(optDate.year, optDate.month);

    printf("Day (%d-%d)  : ", FIRST_DAY, numOfDay);
    optDate.day = inputIntRange(1, numOfDay);

    return optDate;
}

// Get user input for appointment time and validate if the time is during the operation hour
struct Time inputAppointTime(void)
{
    int invalid;
    struct Time optTime = { 0 };

    do {
        invalid = 0;

        printf("Hour (%d-%d)  : ", FIRST_HOUR, LAST_HOUR);
        optTime.hour = inputIntRange(0, 23);
        printf("Minute (%d-%d): ", FIRST_MIN, LAST_MIN);
        optTime.min = inputIntRange(0, 59);

        if ((optTime.hour < START_HOURS || optTime.hour > END_HOURS) ||
            (optTime.min % APPOINT_INTERVAL != 0) ||
            (optTime.hour == END_HOURS && optTime.min != 0))
        {
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n",
                   START_HOURS, END_HOURS, APPOINT_INTERVAL);
            invalid = 1;
        }
    } while (invalid);

    return optTime;
}

// Get user input a patient number and get the patient index (return -1 if patient not found)
int inputPatientValidation(struct Appointment* optAppoint,
                           struct Patient patients[], int maxPatient)
{
    int index = 0;

    printf("Patient Number: ");
    optAppoint->patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(optAppoint->patientNumber, patients, maxPatient);

    return index;
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;

    FILE* fp = fopen(datafile, "r");
    if (fp != NULL)
    { 
        while (i < max && fscanf(fp, "%d|%15[^|]|%4[^|]|", 
               &patients[i].patientNumber, patients[i].name, 
               patients[i].phone.description) == 3)
        {
            if (strcmp(patients[i].phone.description, "TBD"))
            { 
                fscanf(fp, "%10s\n", patients[i].phone.number);
            }
            else
            {
                strcpy(patients[i].phone.number, "\0");
            }
            i++;
        }
        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("Error!! Unable to open %s file!", datafile);
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;

    FILE* fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d\n", 
               &appoints[i].patientNumber, &appoints[i].date.year, 
               &appoints[i].date.month, &appoints[i].date.day, 
               &appoints[i].time.hour, &appoints[i].time.min) == 6)
        {
            i++;
        }
        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("Error!! Unable to open %s file!", datafile);
    }

    return i;
}
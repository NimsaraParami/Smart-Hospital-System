#include <stdio.h>

#define WARDS 4
#define BEDS 20

/* Doctor Specialty Lookup Data */

const char specialtyName[4][30] = {
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

const double baseFee[4] = {
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

const int consultationTime[4] = {
    15,
    20,
    30,
    30
};

const int dailyPatientCap[4] = {
    30,
    20,
    12,
    10
};


/* Hospital Ward Lookup Data */

const char wardName[4][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU (Intensive Care Unit)"
};

const double dailyBedRate[4] = {
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

const int bedCapacity[4] = {
    20,
    10,
    10,
    5
};



int bedOccupancy[4][20] = {0};


/* Display Doctor Specialties */

void displaySpecialties()
{
    int i;

    printf("\n=============================================\n");
    printf("           DOCTOR SPECIALTIES\n");
    printf("=============================================\n");

    printf("%-5s %-30s %-15s %-15s %-10s\n",
           "ID", "Specialty", "Fee", "Time", "Daily Cap");

    printf("--------------------------------------------------------------------------\n");

    for(i = 0; i < 4; i++)
    {
        printf("%-5d %-30s %-15.2f %-15d %-10d\n",
               i + 1,
               specialtyName[i],
               baseFee[i],
               consultationTime[i],
               dailyPatientCap[i]);
    }
}


/* Display Hospital Wards */

void displayWards()
{
    int i;

    printf("\n=============================================\n");
    printf("             HOSPITAL WARDS\n");
    printf("=============================================\n");

    printf("%-5s %-35s %-18s %-10s\n",
           "ID", "Ward Name", "Daily Rate", "Capacity");

    printf("--------------------------------------------------------------------------\n");

    for(i = 0; i < 4; i++)
    {
        printf("%-5d %-35s %-18.2f %-10d\n",
               i + 1,
               wardName[i],
               dailyBedRate[i],
               bedCapacity[i]);
    }
}


/* Display Bed Occupancy */

void displayBeds()
{
    int i, j;

    printf("\n=============================================\n");
    printf("              BED OCCUPANCY\n");
    printf("=============================================\n");

    for(i = 0; i < WARDS; i++)
    {
        printf("\nWard %d - %s\n", i + 1, wardName[i]);
        printf("---------------------------------------------\n");

        for(j = 0; j < bedCapacity[i]; j++)
        {
            printf("Bed %d : ", j + 1);

            if(bedOccupancy[i][j] == 0)
            {
                printf("Available\n");
            }
            else
            {
                printf("Occupied\n");
            }
        }
    }
}


/* Main Function */

int main()
{
    displaySpecialties();

    displayWards();

    displayBeds();

    return 0;
}

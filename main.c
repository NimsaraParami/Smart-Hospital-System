#include<stdio.h>
#define MAXPATIENTS 100
#define WARDS 4
#define BEDS 20
#define SPECIALTIES 4


char specialtyName[4][30]={"General Practice(OPD)","Paediatrics","Cardiology","Neurology"};
double baseFee[4]={1500.00,2500.00,4500.00,5000.00};
int consultationTime[4]={15,20,30,30};
int dailyPatientCap[4]={30,20,12,10};
char wardName[4][40]={"General Ward","Paediatric Ward","Surgical Ward","ICU(Inensive Care Unit)"};
double dailyBedRate[4]={3000.00,6000.00,12000.00,25000.00};
int bedCapacity[4]={20,10,10,5};
int bedOccupancy[4][20]={0};


void displaySpecialties(){
  int i;
  printf("\n---------------------------------------------------------------------------------------------------\n");
  printf("                                      Doctor Specialties Data                                          ");
  printf("\n---------------------------------------------------------------------------------------------------\n");
  printf("%5s %30s %15s %15s %10s\n","ID","Specialty","Fee","Time","Daily Cap");
  printf("\n---------------------------------------------------------------------------------------------------\n");

  for(i=0;i<4;i++){
    printf("%5d %30s %15.2f %15d %10d\n",i+1,specialtyName[i],baseFee[i],consultationTime[i],dailyPatientCap[i]);
  }
}

void displayWards(){
     int i;
     printf("\n=================================================================================================\n");
     printf("                                   Hospital Wards Data                                             \n");
     printf("===================================================================================================\n");
     printf("%5s %35s %18s %10s\n","ID","ward Name","Daily Rate","Capacity");
     printf("----------------------------------------------------------------------------------------------------\n");
     for(i=0;i<4;i++){
        printf("%5d %35s %18.2f %10d\n",i+1,wardName[i],dailyBedRate[i],bedCapacity[i]);
     }
}

void displayBeds(){
     int i,j;
     printf("\n==================================================================================================\n");
     printf("                                    Bed Occupancy                                                   \n");
     printf("====================================================================================================\n");
     for(i=0;i< WARDS;i++){
        printf("\nWard %d %s\n",i+1,wardName[i]);
        printf("------------------------------------------------------------------------------------------------\n");
        for(j=0;j<bedCapacity[i];j++){
            printf("Bed %d : ",j+1);
            if (bedOccupancy[i][j]== 0)
                printf("Available\n");
            else
                printf("Occupied\n");

        }
     }
}
int main()
{
    displaySpecialties();
    displayWards();
    displayBeds();

    return 0;
}


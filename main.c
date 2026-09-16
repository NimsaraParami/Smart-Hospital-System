#include<stdio.h>
#define MAXPATIENTS 100
#define WARDS 4
#define BEDS 20
#define SPECIALTIES 4

void displaySpecialties();
void displayWards();
void displayBeds();
void displayMenu();
void registerPatient();
void allocateBed(int patientIndex);
void calculateBilling(int patientIndex);
void displayHospitalStatus();

char specialtyName[SPECIALTIES][30]={"General Practice(OPD)","Paediatrics","Cardiology","Neurology"};
double baseFee[SPECIALTIES]={1500.00,2500.00,4500.00,5000.00};
int consultationTime[SPECIALTIES]={15,20,30,30};
int dailyPatientCap[SPECIALTIES]={30,20,12,10};
char wardName[WARDS][40]={"General Ward","Paediatric Ward","Surgical Ward","ICU(Inensive Care Unit)"};
double dailyBedRate[WARDS]={3000.00,6000.00,12000.00,25000.00};
int bedCapacity[WARDS]={20,10,10,5};
int bedOccupancy[WARDS][BEDS]={0};

char patientName[MAXPATIENTS][50];
int patientAge[MAXPATIENTS];
int urgencyLevel[MAXPATIENTS];
int selectedSpecialty[MAXPATIENTS];
int isAdmittedWard[MAXPATIENTS];
int selectedWard[MAXPATIENTS];
int assignedBed[MAXPATIENTS];
int daysAdmitted[MAXPATIENTS];
int specialtyWaitingCount[SPECIALTIES]={0};
double waitingTime[MAXPATIENTS];
double emergencySurcharge[MAXPATIENTS];
double wardStayCost[MAXPATIENTS];
double grossTotal[MAXPATIENTS];
double ageDiscount[MAXPATIENTS];
double finalAmount[MAXPATIENTS];
int patientCount=0;


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
void displayMenu(){
     printf("\n=================================================================================================\n");
     printf("                            SMART HOSPITAL PATIENT ALLOCATION                                      \n");
     printf("===================================================================================================\n");
     printf("1.Register New Patient Intake\n");
     printf("2.Allocate Ward Bed To Patient\n");
     printf("3.Calculate & Display Patient Bill\n");
     printf("4.Display Hospital Occupancy & System Status\n");
     printf("5.Exit System\n");
     printf("Enter Your Choice (1-5):");
}
int main(){
    int choice=0;
    while (choice!=5){
        displayMenu();
        if(scanf("%d",&choice)!=1){
            printf("Invalid input! Please enter a number\n");
            while (getchar()!='\n');
            continue;
        }
    switch (choice){
     case 1:
        printf("\n[Patient Intake Selected]\n");
        break;
     case 2:
        printf("\n[Bed Allocation Selected]\n");
        break;
     case 3:
        printf("\n[Billing Calculation Selected]\n");
        break;
     case 4:
        printf("\n[Hospital Status Selected]\n");
        displaySpecialties();
        displayWards();
        displayBeds();
        break;
     case 5:
        printf("\nExiting System.GOOD BYE!\n");
        break;
     default:
         printf("\n INVALID CHOICE!Please selected between 1 and 5\n");
    }
  }
  return 0;
}

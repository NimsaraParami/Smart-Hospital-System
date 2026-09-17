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
void allocateBed();
void calculateBilling();
void displayHospitalStatus();
void dusplayPatientsByPriority();
void searchPatient();

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
int emergencyLevel[MAXPATIENTS];
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
void registerPatient(){
     if(patientCount>=MAXPATIENTS){
        printf("\nHospital capacity is full!\n");
        return;
     }
     printf("\n---------------------------------NEW PATIENT REGISTRATION----------------------------------------\n");
     printf("Enter Patient Name:");
     scanf("%s",patientName[patientCount]);
     printf("Enter Patient Age:");
     scanf("%d",&patientAge[patientCount]);
     displaySpecialties();
     printf("\nSelect Doctor Specialty (1-4):");
     scanf("%d",&selectedSpecialty[patientCount]);
     selectedSpecialty[patientCount]--;

     int spec=selectedSpecialty[patientCount];
     if (specialtyWaitingCount[spec]>= dailyPatientCap[spec]){
        printf("\nDaily limit reached for this specialty!\n");
        return;
     }
     printf("Enter Emergency Level (1:Normal 2: Urgent 3:Critical):");
     scanf("%d",&urgencyLevel[patientCount]);
     waitingTime[patientCount]=specialtyWaitingCount[spec]* consultationTime[spec];
     specialtyWaitingCount[spec]++;

     isAdmittedWard[patientCount]=0;
     selectedWard[patientCount]= -1;
     assignedBed[patientCount]= -1;
     daysAdmitted[patientCount]= 0;
     printf("\nPatient Registered Successfully!\n");
     printf("Patient ID: %d | Estimated Wait Time:%.0f mins\n", patientCount+1,waitingTime[patientCount]);

     patientCount++;
}
void allocateBed(){
     int patientID,wardChoice,j;
     if(patientCount == 0){
        printf("\n No Patients Registered Yet!\n");
        return;
     }
     printf("\n------------------------------------WARD BED ALLOCATION------------------------------------------\n");
     printf("Enter Patient ID(1 to %d):",patientCount);
     scanf("%d",&patientID);
     patientID--;

     if(patientID<0 || patientID >= patientCount){
        printf("INVALID PATIENT ID!\n");
        return;
     }
     if(isAdmittedWard[patientID]==1){
        printf("Patient is already admitted to a ward!\n");
        return;
     }
     displayWards();
     printf("\nSelect Ward For Admission(1-4):");
     scanf("%d",&wardChoice);
     wardChoice--;
     if(wardChoice<0 || wardChoice>=WARDS){
            printf("Invalid Ward Selection!\n");
            return;
     }
     int bedFound = -1;
     for(j=0;j<bedCapacity[wardChoice];j++){
        if(bedOccupancy[wardChoice][j]==0){
            bedFound = j;
            break;
        }
     }
     if(bedFound == -1){
        printf("\nSelected Ward Is currently full!\n");
        return;
     }
     printf("Enter number of estimated stay days:");
     scanf("%d",&daysAdmitted[patientID]);

     bedOccupancy[wardChoice][bedFound]=1;
     isAdmittedWard[patientID]=1;
     selectedWard[patientID]= wardChoice;
     assignedBed[patientID] = bedFound;

     printf("\nBed Allocated Successfully!\n");
     printf("Patient: %s | Ward:%s | Bed No:%d | Days: %d\n",patientName[patientID],wardName[wardChoice],bedFound+1,daysAdmitted[patientID]);
}

void displayPatientsByPriority(){
int i,j;
if(patientCount == 0){
    printf("\nNo patients registered yet!\n");
    return;
}
int indexList[MAXPATIENTS];
for(i=0;i<patientCount;i++){
    indexList[i]=i;
}
for(i=0;i<patientCount-1;i++){
    for(j=0;i<patientCount-i-1;j++){
        if(emergencyLevel[indexList[j]]<emergencyLevel[indexList[j+1]]){
            int temp= indexList[j];
            indexList[j]=indexList[j+1];
            indexList[j+1]=temp;
        }
    }
}
printf("\n==================================================================================================================================\n");
printf("                                          PATIENT PRIORITY LIST (BY URGENCY)                                                        \n");
printf("\n==================================================================================================================================\n");
printf("%10s %20s %10s %24s %18s\n","Patient ID" , "Patient Name" , "Age" , "Specialty" , "Emergency Status");
printf("----------------------------------------------------------------------------------------------------------------------------------\n");
for(i=0;i<patientCount;i++){
    int idx=indexList[i];
    printf("%10d %20s %10d %25s",idx+1,patientName[idx],patientAge[idx],specialtyName[selectedSpecialty[idx]]);

    if(emergencyLevel[idx] == 3){
        printf("%15s\n","3-Critical");
    }else if (emergencyLevel[idx] == 2){
        printf("%15s\n","2-Urgent");
    }else{
        printf("%15s\n","1-Normal");
    }
  }
  printf("===================================================================================================================================\n");
}

void searchPatient(){
     if(patientCount == 0){
        printf("\nNo patient registered in the system yet!\n");
        return;
     }
     int searchId=0;
     printf("\nEnter Patient ID to search(1 to %d ):",patientCount);
     scanf("%d",&searchId);
     if(searchId<1 || searchId>patientCount){
        printf("Invalid Patient ID! Out of Bound\n");
        return;
     }
     int index= searchId-1;
     printf("\n----------PATIENT DETAILS-------\n");
     printf("Patient ID      :%d\n",searchId);
     printf("Name            :%s\n",patientName[index]);
     printf("Age             :%d\n",patientAge[index]);
     printf("Specialty Code  :%d\n",selectedSpecialty[index]);
     printf("Emergency Level :%d\n",emergencyLevel[index]);
}
void calculateBilling(){
     if(patientCount == 0){
        printf("\nNo patients registered in the system yet!\n");
        return;
     }
     int patientId = 0;
     printf("\nEnter Patient ID to calculate bill(1 to %d):",patientCount);
     scanf("%d",&patientId);

     if (patientId < 1 || patientId > patientCount){
        printf("Invalid Patient ID!Out of bounds.\n");
        return;
     }
     int days=0;
     do{
        printf("Enter number of days admitted(1-365):");
        scanf("%d",&days);
        if(days<1 || days > 365){
            printf("Invalid duration!Please enter days between 1 and 365\n");
        }
     }while(days<1 || days>365);
     float dailyRate = 2500.00;
     float totalBill = days * dailyRate;

     int discountRate = 10;
     if(discountRate!=0){
        float discount = (totalBill * discountRate)/100;
        totalBill -= discount;
     }
     printf("\n=========================================================================================================\n");
     printf("\n                                           PATIENT BILL DETAILS                                            ");
     printf("\n=========================================================================================================\n");
     printf("\nPatient ID                      : %d",patientId);
     printf("\nDays Admitted                   : %d",days);
     printf("\nTotal Amount                    : Rs.%.2f",totalBill);
     printf("\n=========================================================================================================\n");
}


void displayMenu(){
     printf("\n==================================================================================================\n");
     printf("                            SMART HOSPITAL PATIENT ALLOCATION                                      \n");
     printf("==================================================================================================\n");
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
        registerPatient();
        break;
     case 2:
        allocateBed();
        break;
     case 3:
        printf("\n[Billing Calculation Selected]\n");
        calculateBilling();
        break;
     case 4:
        printf("\n[Hospital Status Selected]\n");
        displaySpecialties();
        displayWards();
        displayBeds();
        displayPatientsByPriority();
        searchPatient();
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


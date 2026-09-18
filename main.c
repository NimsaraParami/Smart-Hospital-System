#include<stdio.h>
#include<string.h>

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
void cleanExit();
void generateAnalyticsReport();

char specialtyName[SPECIALTIES][30]={"General Practice(OPD)","Paediatrics","Cardiology","Neurology"};
double baseFee[SPECIALTIES]={1500.00,2500.00,4500.00,5000.00};
int consultationTime[SPECIALTIES]={15,20,30,30};
int dailyPatientCap[SPECIALTIES]={30,20,12,10};
char wardName[WARDS][40]={"General Ward","Paediatric Ward","Surgical Ward","ICU"};
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
    char firstName[30],lastName[30];
     if(patientCount>=MAXPATIENTS){
        printf("\nHospital capacity is full!\n");
        return;
     }
     printf("\n---------------------------------NEW PATIENT REGISTRATION----------------------------------------\n");
     printf("\nEnter Patient First Name:");
     scanf("%s",firstName);
     printf("Enter Patient Second Name:");
     scanf("%s",lastName);
     strcpy(patientName[patientCount],firstName);
     strcat(patientName[patientCount]," ");
     strcat(patientName[patientCount],lastName);
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
     if(wardChoice<1 || wardChoice>=WARDS){
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
     printf("\nEnter Patient ID for billing(1 to %d):",patientCount);
     scanf("%d",&patientId);

     if (patientId < 1 || patientId > patientCount){
        printf("Invalid Patient ID!Out of bounds.\n");
        return;
     }
     int index = patientId-1;
     int days = 0;
     if(isAdmittedWard[index]==1){
        printf("Enter number of days admitted (1-365):");
        scanf("%d",&days);
     }

     double consultationFee= baseFee[selectedSpecialty[index]];
     double surcharge =0.0;

     if(urgencyLevel[index] == 2){
        surcharge = consultationFee* 0.20;
     }else if (urgencyLevel[index] == 3){
         surcharge = consultationFee * 0.50;
     }

     double wardDailyRate = (isAdmittedWard[index]==1)? dailyBedRate[selectedWard[index]] : 0.0;
     double wardCost = days * wardDailyRate;
     double grossTotal = consultationFee + surcharge + wardCost;

     double discount = 0.0;
     if(patientAge[index]<5 || patientAge[index]>65){
        discount = grossTotal * 0.15;
     }
     double finalAmount = grossTotal - discount;

     printf("\n=========================================================================================================\n");
     printf("\n                                  SMART  HOSPITAL ADMISSION & BILL                                         ");
     printf("\n---------------------------------------------------------------------------------------------------------\n");
     printf("\nPatient ID                         : PAT %d", 1000+patientId);
     printf("\nPatient Name                       : %s",patientName[index]);
     printf("\nAge                                : %d Years %s",patientAge[index],(patientAge[index]<5 || patientAge[index]>65)?"(15% Subsidy Eligible)" : "");
     printf("\nSpecialty                          : %s",specialtyName[selectedSpecialty[index]]);
     if(isAdmittedWard[index]==1){
        if(selectedWard[index]==3){
            printf("\nAssigned Ward                      : ICU(Bed #%02d)",index+1);
        }else{
            printf("\nAssigned Ward                      : %s",wardName[selectedWard[index]]);
        }
     }else{
            printf("\nAssigned Ward                      : Outpatient(OPD)");
      }
     printf("\nUrgency Level                      : Level %d",urgencyLevel[index]);
     printf("\n---------------------------------------------------------------------------------------------------------\n");
     printf("\nBase Consultation Fee              : LKR %.2f",consultationFee);
     printf("\nEmergency Surcharge                : LKR %.2f %s",surcharge,(urgencyLevel[index] == 3)? "(50%)": (urgencyLevel[index] == 2) ? "(20%)" : "");
     printf("\nWard Stay Cost(%d days)             : LKR %.2f",days,wardCost);
     printf("\n---------------------------------------------------------------------------------------------------------\n");
     printf("\nGross Total Bill                   : LKR %.2f",grossTotal);
     printf("\nAge Subsidy Discount               : LKR -%.2f %s",discount,(patientAge[index]< 5 || patientAge[index] > 65) ? "(15%)" : "");
     printf("\n---------------------------------------------------------------------------------------------------------\n");
     printf("\nFinal Payable Amount               : LKR %.2f",finalAmount);
     printf("\nEstimated Waiting Time             : %.2f mins %s",waitingTime[index],(waitingTime[index]==0) ? "(Immediate Attention)" : "");
     printf("\n=========================================================================================================\n");
}

void generateAnalyticsReport(){
     if (patientCount == 0){
        printf("\nNo data available for analytics report!\n");
        return;
     }
     int level1 = 0, level2 = 0, level3 = 0;
     double totalRevenue = 0.0, totalDiscount = 0.0;
     int highestIndex = 0;
     double maxBill = 0.0;

     for(int i = 0; i < patientCount; i++){
        if(urgencyLevel[i] == 1) level1++;
        else if (urgencyLevel[i] == 2) level2++;
        else if (urgencyLevel[i] == 3) level3++;

        int spec = selectedSpecialty[i];
        double currentBaseFee = baseFee[spec];
        double surCharge = (urgencyLevel[i] == 2) ? currentBaseFee * 0.20 : (urgencyLevel[i] == 3) ? currentBaseFee * 0.50 : 0.0;
        double gross = currentBaseFee + surCharge;

        if(isAdmittedWard[i] == 1 && selectedWard[i] >= 0 && selectedWard[i] < WARDS){
            gross += daysAdmitted[i] * dailyBedRate[selectedWard[i]];
        }

        double discount = (patientAge[i] < 5 || patientAge[i] > 65) ? gross * 0.15 : 0.0;
        double finalBill = gross - discount;

        totalRevenue += finalBill;
        totalDiscount += discount;
        if(finalBill > maxBill){
            maxBill = finalBill
            highestIndex = i;
        }
     }

     printf("\n============================================================================================================\n");
     printf("                                     PERFORMANCE REPORT & ANALYTICS                                           \n");
     printf("==============================================================================================================\n");
     printf("\n1. Patients by Urgency Level:");
     printf("\n  - Normal   (Level 1)                : %d", level1);
     printf("\n  - Urgent   (Level 2)                : %d", level2);
     printf("\n  - Critical (Level 3)                : %d", level3);
     printf("\n\n2. Financial Summary:");
     printf("\n  - Total Revenue Earned              : LKR %.2f", totalRevenue);
     printf("\n  - Total Discount Given              : LKR %.2f", totalDiscount);


     printf("\n\n3. Bed Occupancy per Ward:");
     for (int w = 0; w < WARDS; w++) {
         int occupiedCount = 0;
         for (int b = 0; b < bedCapacity[w]; b++) {
             if (bedOccupancy[w][b] == 1) {
                 occupiedCount++;
             }
         }
         double percentage = 0.0;
         if (bedCapacity[w] > 0) {
             percentage = ((double)occupiedCount / (double)bedCapacity[w]) * 100.0;
         }
         printf("\n  - %-20s              : %d/%d occupied (%.1f%%)", wardName[w], occupiedCount, bedCapacity[w], percentage);
     }

     printf("\n\n4. Highest Paying Patient             :");
     printf("\n   - Name: %s | Total Bill: LKR %.2f", patientName[highestIndex], maxBill);
     printf("\n=========================================================================================================\n");
}

void cleanExit(){
     printf("\n=========================================================================================================\n");
     printf("\n                                    Exiting Smart Hospital System                                          ");
     printf("\n                                   Thank you for using our system!                                        \n");
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
     printf("5.Performance Report & Analytics\n");
     printf("6.Exit System\n");
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
        printf("\n[Performance Report & Analytics Selected]\n");
        generateAnalyticsReport();
        break;
     case 6:
        printf("\nExiting System.GOOD BYE!\n");
        cleanExit();
        break;
     default:
         printf("\n INVALID CHOICE!Please selected between 1 and 5\n");
    }
  }
  return 0;
}


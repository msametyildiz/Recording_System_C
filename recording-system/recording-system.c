#include <stdio.h>
struct patientData{
    int patientNo;
	int age;
    char name[20];
    char disease[20];
	
};
typedef struct patientData Patient;
void createfile(FILE *cfPtr){
    Patient p={0,0,"",""};
    for (int i=0;i<100;i++){
        fwrite(&p,sizeof(Patient),1,cfPtr);
    }
    printf("File succesfully created!!\n\n");
}

void addnewpatient(FILE *cfPtr){
    rewind(cfPtr);
    Patient p={0,0,"",""};
    printf("Enter patient no between [1-100] : \n");
    scanf("%d", &p.patientNo);
    while (p.patientNo != 0){
        if (p.patientNo<0 || p.patientNo>101){
            printf("Please enter patient no between [1-100]\n");
            scanf("%d", &p.patientNo);
        }
        else{
            printf("Enter name-disase-age\n");
            fscanf(stdin,"%s %s %d",p.name,p.disease,&p.age);
            fseek(cfPtr,(p.patientNo-1)*sizeof(Patient),SEEK_SET);
            if (fwrite(&p,sizeof(Patient),1,cfPtr)==1){
                printf("\n\nPatient Succesfully Added\n\n");
            }
        }
        printf("Please enter patient no between [1-100]\n");
        printf("Enter 0 to Quit\n");
        scanf("%d",&p.patientNo);
    }
}

void listpatients(FILE *cfPtr){
    rewind(cfPtr);
    printf("________________________________________________________________________\n");
    printf("Patient No | \tName\t\t |  Disease \t\t  |       Age\n");
    printf("________________________________________________________________________");
    while (!feof(cfPtr)){
        Patient p={0,0,"",""};
        int result=fread(&p,sizeof(Patient),1,cfPtr);

        if (result != 0 && p.patientNo != 0){
            printf("\n     %-2d\t   | %-18s  | %-20s   | %-3d", p.patientNo, p.name, p.disease, p.age);
        }
    }
    printf("\n________________________________________________________________________\n");
}
void editpatient(FILE *cfPtr){
    rewind(cfPtr);
    printf("Please enter patient number to update between [1-100]\n");
    int id;
    scanf("%d",&id);
    fseek(cfPtr,(id-1)*sizeof(Patient),SEEK_SET);
    Patient p={0,0,"",""};
    fread(&p,sizeof(Patient),1,cfPtr);
    if (p.patientNo==0){
    	printf("Patient with %d. number does not exist\n", id);
	}
    else{
        printf("Retrieved Acoount\n");
        printf("%-6d||%-19s||%-19s||%-6d\n",p.patientNo,p.name,p.disease,p.age);
        fscanf(stdin,"%s%s%d",p.name,p.disease,&p.age);
        printf("This is new record ; \n");
        printf("%-6d||%-19s||%-19s||%-6d\n", p.patientNo, p.name, p.disease, p.age);
        fseek(cfPtr, (id - 1) * sizeof(Patient), SEEK_SET);
        fwrite(&p, sizeof(Patient), 1, cfPtr) == 1
            ? printf("\n\nPatient updated succesfully\n\n")
            : printf("\n\nUpdate went wrong\n\n");
    }
}

void deletepatient(FILE *cfPtr){
    printf("Please enter patient number to delete between [1-100]\n");
    int id;
    scanf("%d",&id);
    fseek(cfPtr,(id-1)*sizeof(Patient),SEEK_SET);
    Patient p={0,0,"",""};
    fread(&p,sizeof(Patient),1,cfPtr);
    if (p.patientNo==0){
    	printf("Patient with %d. number does not exist\n", id);
	}
    else{
        Patient blankP={0,0,"",""};
        fseek(cfPtr,(id-1)*sizeof(Patient),SEEK_SET);
        fwrite(&blankP, sizeof(Patient), 1, cfPtr) == 1
            ? printf("\n\nPatient deleted succesfully\n\n")
            : printf("\n\nDelete went wrong\n\n");
    }
}
void printmenu(){
    printf("Please select operation:\n1 - Create empty file with 100 potential patient\n2 - Add new patient information\n3 - Edit patient information\n4 - Delete patient information\n5 - List all patients information\n0 - Exit\n");
}

int main(){
    FILE *ptr;
    if ((ptr = fopen("infopatients.dat","wb+")) == NULL){
    	printf("Somethings went wrong!\n");
	}
    else{
        printmenu();
        int input;
        printf("Please Select Operation\n");
        scanf("%d", &input);
        while (input != 0){
            switch (input){
            case 1:createfile(ptr); break;
            case 2:addnewpatient(ptr);break;
            case 3:editpatient(ptr);break;
            case 4:deletepatient(ptr); break;
            case 5:listpatients(ptr);break;
            default:printf("Wrong Choice !\n");
            }
            printmenu();
            printf("Please select new operation\n");
            scanf("%d", &input);
        }
    }
    fclose(ptr);
}

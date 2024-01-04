#define _GNU_SOURCE		//strcasestr is a nonstandard GNU extension, 
//we need this line while serching for matching last name
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"



void create_record (char* ID, char* first_n, char* last_n, char* email, double sal, struct date h_date, struct DataBase *db )// specify parameters. clues are in the initalize function.
{
 /*  struct Employee new;
  strcpy(new.ID, ID); 
  strcpy(new.first_name, first_n);
  strcpy(new.last_name, last_n);
  strcpy(new.email, email);
  new.hire_date->month=h_date.month;
  new.hire_date->day = h_date.day;
  new.hire_date->year= h_date.year;
  db->emp[db->total]=new;
  db->total++;
  */
  
  int tot = db->total;
  strcpy(db->emp[tot].ID, ID); 
  strcpy(db->emp[tot].first_name, first_n);  
  strcpy(db->emp[tot].last_name, last_n);  
  strcpy(db->emp[tot].email, email);
  db->emp[tot].salary= sal;  
  db->emp[tot].hire_date.month= h_date.month;
  db->emp[tot].hire_date.year= h_date.year;
  db->emp[tot].hire_date.day=h_date.day;

  db->total++;
  //define function. Clues are in the initalize function
  //do not forget to increase total number of employees in the database
}


void print_title ()// you can keep this fuction or remove if needed
{
  printf ("No. ID    Name          Email        Salary     Hire Date\n");
  printf ("--- ----- ------------- ------------ ---------- --/--/----\n");

}


//fix save function. Save array into file: database_updated in the same format with the 
//database file.
void save (dataBase_ptr db)// this function is for saving the database into a text file
{
  FILE *dbfu;
  dbfu = fopen ("database_updated", "w");//open an Std IO file to write into
  if (dbfu == NULL)
  {
    printf ("File cannot be created");
    return;
  }
  for (int i = 0; i < db->total; i++)
  {
      fprintf (dbfu,"%-5s %s %s %s %.2lf %d/%d/%d\n", db->emp[i].ID, db->emp[i].first_name, db->emp[i].last_name,db->emp[i].email, db->emp[i].salary, db->emp[i].hire_date.month,
		    db->emp[i].hire_date.day, db->emp[i].hire_date.year);  
	      //add other members);

  }
  fclose (dbfu);//close file after writing
  return;

}

int comp_ID(const void *a, const void *b){
  struct Employee *emA = (struct Employee*) a;
  struct Employee *emB = (struct Employee*) b;
  return strcmp(emA->ID, emB->ID);
}



int comp_date(const void *a, const void *b){
  struct Employee *emA = (struct Employee*) a;
  struct Employee *emB = (struct Employee*) b;
  if(emA->hire_date.year!=emB->hire_date.year){
    return emA->hire_date.year-emB->hire_date.year;
  }
  else if(emA->hire_date.month!=emB->hire_date.month){ 
    return emA->hire_date.month - emB->hire_date.month;
  }
  else{ 
    return emA->hire_date.day - emB->hire_date.day;
  }
}


void sort_ID(dataBase_ptr db){
  qsort(&(db->emp[0]), db->total, sizeof(struct Employee), comp_ID);  
}

void sort_date(dataBase_ptr db){
  qsort(&(db->emp[0]), db->total, sizeof(struct Employee), comp_date);
}


void display_em(dataBase_ptr db){
 print_title();
  for (int i=0; i<db->total; i++){
   // char* name = malloc(strlen(db->emp[i].first_name)+strlen(db->emp[i].last_name)+sizeof(char));
    char name[1084];
    sprintf(name, "%s %s",db->emp[i].first_name, db->emp[i].last_name); 
   /* strcpy(name, db->emp[i].first_name);
    strcat(name, " ");
    strcat(name, db->emp[i].last_name);*/

    printf("%-3d %-5s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",i, db->emp[i].ID, name, db->emp[i].email, db->emp[i].salary,
		    db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);
  }
}


void search_ID(dataBase_ptr db){
  char input[6];
  char tempid[6];
  printf("Enter ID you are searching for: \n");
  scanf("%s", input);
  
  int length = strlen(input);
  if (length<5){
    int lead_z= 5-length;
    for(int i=0; i<lead_z; i++){
      tempid[i]= '0';
    }
  	tempid[lead_z]='\0';
    strcat(tempid, input);
  }
  else{
    strcpy(tempid, input);
  }

  int f=0;
  for(int i=0; i<db->total; i++){
    if (strcmp(db->emp[i].ID, tempid)==0){
    	f=1;
	print_title();
	char name[1084];
	sprintf(name, "%s %s",db->emp[i].first_name, db->emp[i].last_name); 
//    	char* name = malloc(strlen(db->emp[i].first_name)+strlen(db->emp[i].last_name)+sizeof(char));
//    	strcpy(name, db->emp[i].first_name);
//	strcat(name, " ");
//	strcat(name, db->emp[i].last_name);
   	 printf("%-3d %-5s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",i, db->emp[i].ID, name, db->emp[i].email, db->emp[i].salary,
		    db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);
    }

  }
  if(f!=1){
    printf("No employee with ID %s found.\n", tempid);
  }
}

void search_Lname(dataBase_ptr db){
	
	//make temp database for employee's whose last name match
	struct DataBase* t_db;
	t_db= malloc(sizeof(struct DataBase));
  	t_db->emp = malloc (sizeof (struct Employee) * (db->total));
  	t_db->total = 0;
	
	//array to keep track of placement in original array
	int place[db->total];
	char input[10];
	printf("Enter last name of employee you're searching for: \n");
	scanf("%s", input);
	
	int len = strlen(input);
	char temp_name[10]="";
  		
	for(int i=0; i<db->total; i++){
		
		if(len==strlen(db->emp[i].last_name)){
			strcpy(temp_name, db->emp[i].last_name);
		}
		else{
			strncpy(temp_name, db->emp[i].last_name, len);
		}
		
		if(strcasecmp(input, temp_name)==0){
			t_db->emp[t_db->total]=db->emp[i];
			place[t_db->total]=i;
			t_db->total++;
		}
	
	}

	if(t_db->total==0){
		printf("No employee with last name %s found.\n", input);
	}
	else{
		
 		print_title();
 		 for (int i=0; i<t_db->total; i++){
   			// char* name = malloc(strlen(t_db->emp[i].first_name)+strlen(t_db->emp[i].last_name)+sizeof(char));
   			 char name[1084];
    			 sprintf(name, "%s %s",t_db->emp[i].first_name, t_db->emp[i].last_name); 
			// strcpy(name,t_db->emp[i].first_name);
		   	// strcat(name, " ");
		   	// strcat(name, t_db->emp[i].last_name);

		   	 printf("%-3d %-5s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",place[i], t_db->emp[i].ID, name, t_db->emp[i].email, t_db->emp[i].salary,
			    t_db->emp[i].hire_date.month, t_db->emp[i].hire_date.day, t_db->emp[i].hire_date.year);
  		}
	}
	free(t_db->emp);
	free(t_db);

}


void del_Employee(dataBase_ptr db){
	
 	 char input[6];
 	 char tempid[6]="";
	 printf("Enter ID you are searching for: \n");
 	 scanf("%s", input);
  
	 int length = strlen(input);
	 if (length<5){
   		 int lead_z= 5-length;
		 for(int i=0; i<lead_z; i++){
     			 strcat(tempid, "0");
    	 	 }
	 }	
 	 strcat(tempid, input);


	 int f=0;
	 for(int i=0; i<db->total; i++){
		 if (strcmp(db->emp[i].ID, tempid)==0){
    			f=1;
			printf("The following employee is deleted: \n");
			print_title();
				
   			char name[1084];
    			sprintf(name, "%s %s",db->emp[i].first_name, db->emp[i].last_name); 
    		/*	char* name = malloc(strlen(db->emp[i].first_name)+strlen(db->emp[i].last_name)+sizeof(char));
  		  	strcpy(name, db->emp[i].first_name);
			strcat(name, " ");
			strcat(name, db->emp[i].last_name);*/
		   	 printf("%-3d %-5s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",i, db->emp[i].ID, name, db->emp[i].email, db->emp[i].salary,
				    db->emp[i].hire_date.month, db->emp[i].hire_date.day, db->emp[i].hire_date.year);

			 for(int n=i; n<db->total-1; n++){
			 	db->emp[n]=db->emp[n+1];
			 }
			 db->total--;

    		}


  	}
 	 if(f!=1){
   		 printf("No employee with ID %s found.\n", tempid);
 	 }

}


void quit(dataBase_ptr db){
	free(db->emp);
	free(db);
	return;
}

void display_menu (struct DataBase *db)
{
  int input = 0;
  while (input != 8)
  {
    puts
      ("\n**************************************************************");
    printf
      (  "********** Employee Database - Total Employees: %03d **********\n",db->total );//you need to fix this line so that total employees in the database is printed
    puts
      ("**************************************************************\n");
    puts ("Choose one of the menu options below:");
    puts ("1. Sort by ID");
    puts ("2. Sort by Hire Date");
    puts ("3. Display all employees");
    puts ("4. Search employees by ID");
    puts ("5. Search employees by Last Name");
    puts ("6. Delete employee by ID");
    puts ("7. Save");
    puts ("8. Exit");

    scanf ("%d", &input);

    switch (input)
    {
      case 1:
        //call the function you defined for sorting by ID
	sort_ID(db);
        break;
      case 2:
        //call the function you defined for sorting by Hire Date
	sort_date(db);
        break;
      case 3:
        //call the function you defined for displaying employees
	display_em(db);
        break;
      case 4:
        //call the function you defined for searching employees by ID
	search_ID(db);
        break;
      case 5:
        //call the function you defined for searching employees by Last Name
	search_Lname(db);
        break;
      case 6:
        //call the function you defined for deleting employee by ID
	del_Employee(db);	
        break;
      case 7:
        save (db);
        break;
      case 8:
        //free all allocated memory
        printf("Bye!\n");
	quit(db);
        break;

    }
  }

}

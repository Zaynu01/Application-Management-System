#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int N = 0; // Global Var

typedef struct
{ // applicant info

    char name[20];
    char id[20];
    int expected_sal;

} a_info;

typedef struct tag
{ // waiting list

    a_info applicant;
    struct tag *next;

} w_info;

void menu(void)
{
    printf("\n\t\t-------------------- Menu To Use--------------------\n");
    printf("\n\t\t1. Start calling for Applications\n");
    printf("\n\t\t2. Apply to SSE\n");
    printf("\n\t\t3. Drop my Application!\n");
    printf("\n\t\t4. View list of Applicants \n");
    printf("\n\t\t5. Calling for Applications is OVER\n");
    printf("\n\t\tYour Choice:");
}

w_info *create_fill_node(FILE *infp)
{

    char line[50], temp[20];

    w_info *newnode = (w_info *)malloc(sizeof(w_info));

    fgets(newnode->applicant.name, 20, infp);
    newnode->applicant.name[strlen(newnode->applicant.name)-1] = '\0';
    fscanf(infp, "%d", &newnode->applicant.expected_sal);
    sprintf(temp,"%d_%s", ++N, newnode->applicant.name);
    strcpy(newnode->applicant.id,temp);
    fgetc(infp);
    fgets(line, 50, infp);

    newnode->next = NULL;

    return newnode;
}

void enqueue_wlist(w_info **pfront, w_info **prear, w_info *newnode)
{

    if (*pfront == NULL)
    {
        *pfront = newnode;
        *prear = newnode;
    }
    else
    {
        (*prear)->next = newnode;
        *prear = newnode;
    }

}

void traverse_waitlist(w_info* front){ // for testing

    if(front == NULL)
        printf("\n\t\tThe waitlist is empty!\n");

    while(front != NULL){
        printf("\n\t\tName:%s \tID:%s \tSalary:%d\n", front->applicant.name, front->applicant.id, front->applicant.expected_sal);
        front = front->next;
    }

}

void traverse_official(a_info* o_queue, int rear){

    for(int i = 0; i <= rear; i++)
        printf("\n\t\tName:%s\tID:%s\tSalary:%d\n", o_queue[i].name, o_queue[i].id, o_queue[i].expected_sal);

    if(rear == -1)
        printf("\n\t\tThe official queue is empty!\n");
}

int enqueue_official(FILE *infp, a_info *o_queue, int *rear, int size)
{

    char line[50];
    while (!feof(infp))
    {

        if (*rear == size - 1)
        {
            return 0;
        } // Add the function to add to the waiting list
        else
        {
        
            (*rear)++;
            fgets(o_queue[*rear].name, 20, infp);
            o_queue[*rear].name[strlen(o_queue[*rear].name)-1] = '\0';
            // printf("%s\n",o_queue[*rear].name);
            fscanf(infp, "%d", &o_queue[*rear].expected_sal); // dont forget the id
            fgetc(infp);
            fgets(line, 50, infp);
            char temp[20];
            sprintf(temp,"%d_%s",++N,o_queue[*rear].name);
            strcpy(o_queue[*rear].id,temp);    

        }
    }

    // return 1; this return is never reached
}

a_info get_applicant_info(){

    a_info data;

    printf("\n\t\tEnter the name of the applicant: ");
    gets(data.name);
    printf("\n\t\tEnter the expected salary: ");
    scanf("%d", &data.expected_sal);
    getchar();

    return data;
}

enqueue_official_new_applicant(a_info data, a_info* o_queue, int* rear, int size){

    if (*rear == size - 1)
    {
        return 0;
    } // Add the function to add to the waiting list
    else
    {
        
        (*rear)++;
        strcpy(o_queue[*rear].name, data.name);
        // printf("%s\n",o_queue[*rear].name);
        o_queue[*rear].expected_sal = data.expected_sal; // dont forget the id
        char temp[20];
        sprintf(temp,"%d_%s",++N,o_queue[*rear].name);
        strcpy(o_queue[*rear].id,temp);    

            /*c = '0' + ((*rear)+1); //To make the int appear as a char for the id
            strcpy(o_queue[*rear].id, c);
            strcat(o_queue[*rear].id, "_");
            strcat(o_queue[*rear].id, o_queue[*rear].name);*/
    }

    return 1; 

}

w_info* create_fill_node_new_applicant(a_info data){

    char temp[20];

    w_info *newnode = (w_info *)malloc(sizeof(w_info));

    strcpy(newnode->applicant.name, data.name);
    newnode->applicant.expected_sal = data.expected_sal;
    sprintf(temp,"%d_%s", ++N, newnode->applicant.name);
    strcpy(newnode->applicant.id,temp);

    newnode->next = NULL;

    return newnode;
}

int drop_official(a_info* o_queue, int* rear, char* dropped_applicant){// do i need to return the info abt the served applicant

    if(*rear == -1)
        return -11;
    else{

        //*applicant = o_queue[0]; // for testing, it skips the last name in the official queue
        //printf("%s", (*applicant).name);

        for(int i = 1; i <= *rear; i++){

            if(strcmp(dropped_applicant, o_queue[i-1].name) == 0)
                o_queue[i-1] = o_queue[i];
            
        }
    
            (*rear)--;

    }

    return 1;
}

int dequeue_waitList(w_info** front, w_info** rear, char* dropped_applicant){// do we need to compare also the salary to aviod duplicates

    w_info* walker, *temp;

    if(*front == NULL)
        return 0;
    else{

        if(strcmp(dropped_applicant, (*front)->applicant.name) == 0){

            temp = *front;
            *front = (*front)->next;
            free(temp);

        }
        else if(*front != NULL && strcmp(dropped_applicant, (*rear)->applicant.name) != 0){
            
            walker = *front;

            while(walker->next != NULL){

                if(strcmp(dropped_applicant, walker->next->applicant.name) == 0){
                    temp = walker->next;
                    walker->next = temp->next;
                    free(temp);
                }

                walker = walker->next;
            }

        }
        else if(strcmp(dropped_applicant, (*rear)->applicant.name) == 0){
            
            // walker = *front;

            // while(walker->next != NULL){
                
            //     if(walker->next == *rear){
            //         printf("The rear is %s \n",(*rear)->applicant.name);
            //         temp = *rear;
            //         **rear = walker;
            //         free(temp);
            //         break;
            //     }

            //     walker = walker->next;
            // }
            walker = *front;
 
            while(walker->next != *rear){
                walker = walker->next;
            }
 
            temp = *rear;
            *rear = walker;
            (*rear)->next = temp->next;
            free(temp);
 
        }
            
            return 1;
            
    }

        return 1;

}

a_info dequeue_waitList_auto(w_info** front){

    a_info data;

    if(*front == NULL)
        return;
    else{ 

        w_info* temp = *front;
        data = temp->applicant;
        *front = (*front)->next;
        free(temp);

        return data;
    }

}

int search_applicant_official(a_info* o_queue, int o_rear, char* dropped_applicant){

    for(int i = 0; i <= o_rear; i++){

        if(strcmp(dropped_applicant, o_queue[i].name) == 0)
            return 1;

    }

    return 0;
}

int search_applicant_waitlist(w_info* front, char* dropped_applicant){

    while(front != NULL){

        if(strcmp(dropped_applicant, front->applicant.name) == 0)
            return 1;
        
        front = front->next;
    }

    return 0;
}

a_info dequeue_official(a_info* o_queue, int* rear){

    a_info applicant;

    applicant = o_queue[0]; 

     for(int i = 1; i <= *rear; i++)
        o_queue[i-1] = o_queue[i];

    (*rear)--;

    return applicant;
}

void process_application(int* acceptance_count, int max_salary, FILE* outpf, a_info applicant){
    
    char status[30];
    time_t t;
    time(&t);
    char *currentTime = ctime(&t);

    if(applicant.expected_sal > max_salary){

        sprintf(status,"Rejection_%s.txt",applicant.name);
        outpf = fopen(status, "w");// 
        fprintf(outpf, "Dear %s, we regret to infrom you that you were rejected since you did not match the profil we are looking for.\n", applicant.name);
        fprintf(outpf, "%s", currentTime);
        
    }
    else{

        sprintf(status,"Acceptance_%s.txt",applicant.name);
        outpf = fopen(status, "w");
        fprintf(outpf, "Dear %s, Congrats! You have been chosen to be part of SSE faculty. Welcome to the team!!\n", applicant.name);
        fprintf(outpf, "%s", currentTime);
        (*acceptance_count)++;

    }

    fclose(outpf);

}
int main()
{

    FILE *infp;
    int choice, size = 3, status, queue_choice, queue_loaded = 0;
    a_info o_queue[size];
    a_info data, applicant;// to get info for case 2
    int o_front = 0, o_rear = -1;
    w_info *front = NULL, *rear = NULL, *newnode;

    do
    {

        menu();
        scanf("%d", &choice);
        getchar();

        if((choice > 1 && choice < 6) && (queue_loaded == 0))
                printf("\n\t\tYou need to load applicants to the queue!\n");
        else{

            switch (choice)
            {

            case 1:

                infp = fopen("Applicants.txt", "r");

                if (infp == NULL)
                    printf("\n\t\tThe file does not exist!\n");
                else
                {
                    if(queue_loaded == 0){
                
                        status = enqueue_official(infp, o_queue, &o_rear, size); // status is always 0

                        for (int i = 0; i <= o_rear; i++)
                        {
                            //printf("%s\n",o_queue[i].id);
                            printf("\n\t\tDear %s, your file was received. You are#%d in the official queue. Thanks for applying!\n", o_queue[i].name, i+1);
                            /*puts(o_queue[i].name);
                            printf("\tExpected Salary: %d\n", o_queue[i].expected_sal);*/
                        }
                        if (status == 0)
                        {
                            // Enque the linked list waiting
                            while(!feof(infp)){

                                newnode = create_fill_node(infp);
                                enqueue_wlist(&front, &rear, newnode);
                                printf("\n\t\tDear %s, your file was received. You are#%d in the waiting queue. Thanks for applying!\n", newnode->applicant.name, N);
                                //do we need to print the position in the official or waiting queue

                            }
                            
                        }
                        
                        queue_loaded = 1;
                    }
                    else
                        printf("\n\t\tQueue already loaded!");
                        
                }

                fclose(infp);

                break;

            case 2:

                data = get_applicant_info();
                status = enqueue_official_new_applicant(data, o_queue, &o_rear, size); // status is always 0

                if(status == 1)//But if we chose case 2 after case 1 the applicant is always added the the waiting list
                    printf("\n\t\tDear %s, your file was received. You are#%d in the official queue. Thanks for applying!\n", data.name, N);
                else{

                    newnode = create_fill_node_new_applicant(data);
                    enqueue_wlist(&front, &rear, newnode);
                    printf("\n\t\tDear %s, your file was received. You are#%d in the waiting queue. Thanks for applying!\n", newnode->applicant.name, N);

                }
                        
                break;

            case 3:

                char dropped_applicant[30];
                int flag;

                printf("\n\t\tEnter the name of the applicant to drop: ");
                gets(dropped_applicant);

                status = search_applicant_official(o_queue, o_rear, dropped_applicant);

                //status = dequeue_official(o_queue, &o_rear, &applicant);// what abt the last applicant 

                if(status == 1){
                    
                    flag = drop_official(o_queue, &o_rear, dropped_applicant);

                    if(flag == -11){//if queue empty at the firt place
                        printf("\n\t\tThe Official Queue is empty!\n");
                        break;
                    }

                    //dequeue successfully
                    printf("\n\t\tThe applicant: %s had dropped his/her application to SSE!\n", dropped_applicant);
                    //Add from waitlist then dequeue from waitlist to avoid duplicate
                    if(front != NULL){// to handle when the waiting list is empty
                        o_queue[o_rear+1] = dequeue_waitList_auto(&front); // bring the old fct 
                        o_rear++;
                    }
                    
                    //o_queue[o_rear] = front->applicant;
                    //front = front->next;
                    
                }
                else{
                    
                    flag = search_applicant_waitlist(front, dropped_applicant);

                    if(flag == 1){

                        dequeue_waitList(&front, &rear, dropped_applicant);
                        printf("\n\t\tThe applicant: %s had dropped his/her application to SSE!\n", dropped_applicant);

                    }
                    else
                        printf("\n\t\tThere is no applicant with the name of %s nor in Official Queue nor in Waitlist.\n", dropped_applicant);

                }

                break;

            case 4:

                printf("\n\t\tSelect a queue to print:\n");
                printf("\n\t\t-------------------------------------\n");
                printf("\n\t\t1.Official Queue\n");
                printf("\n\t\t-------------------------------------\n");
                printf("\n\t\t2.Waitlist Queue\n");
                printf("\n\t\t-------------------------------------\n");
                printf("\n\t\tQueue Choice: ");
                scanf("%d", &queue_choice);

                if(queue_choice == 1)
                    traverse_official(o_queue, o_rear); //Traverse for official queue
                else if(queue_choice == 2)// what if the waitlist is empty
                    traverse_waitlist(front); //Traverse for waitlist queue
                else
                    printf("\n\t\t Invalid Choice!\n");

                break;

            case 5:

                int max_salary; 
                int acceptance_count = 0;
                FILE* outpf;

                printf("\n\t\tWhat is the maximum salary: ");
                scanf("%d", &max_salary);

                while(acceptance_count < 3){

                    if(o_rear != -1){

                        applicant = dequeue_official(o_queue, &o_rear);
                        process_application(&acceptance_count, max_salary, outpf, applicant);

                    }
                    else if(front != NULL){
                        applicant = dequeue_waitList_auto(&front);
                        process_application(&acceptance_count, max_salary, outpf, applicant);
                    }

                    else
                        break;
                       
                }

                break;

            default:
                printf("\n\t\tThat was a wrong choice!\n");
            }

        }

    } while (choice != 5);

    return 0;
}
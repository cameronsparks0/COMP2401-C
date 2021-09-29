#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRANSACTION_INCREMENT 2 //Defining different pointer increments and string lengths.
#define TRANSACTION_LENGTH 9
#define CUSTOMER_INCREMENT 11
#define CUSTOMER_LENGTH 7
#define AMOUNT_INCREMENT 8
#define AMOUNT_LENGTH 10

typedef struct Transaction{ // A structure containing the variables needed to store the message details.
    unsigned int transactionId; //Ints used due to a char array taking up more memory.
    unsigned int customerId;
    float amount;
} transaction;

typedef struct NodeType{ // A linked list data structure that contains all the entered transactions.
    transaction *data;
    struct NodeType *next;
} node;

void createTransaction(unsigned int transactionId, unsigned int customerId, float amount, transaction **curTransaction);
void createNode(node **newNode, transaction *data);
void parseMessage(node **transactions, char *message);
void printMessageSingle(node *transaction);
void printMessageAll(node *transaction);
void freeData(node *transaction, char *message);

int main(int argc, char **argv){
    
    char *initMessage = NULL; //Temporary char pointer that will store the user input.
    node *transactions = NULL; // Node pointer that will store all the transaction information in a linked list.

    printf("Welcome to the Message Consumer Program!\n");
    printf("Please enter the message payload: ");
    scanf("%ms",&initMessage); //Dynamically allocating memory based on the size of user input.

    parseMessage(&transactions,initMessage);
    printMessageAll(transactions);
    freeData(transactions,initMessage);

    return(EXIT_SUCCESS);
}

void createTransaction(unsigned int transactionId, unsigned int customerId, float amount, transaction **curTransaction){ //Allocates memory and sets variables for a new transaction.
    *curTransaction = (transaction *) malloc(sizeof(transaction)); //Allocating memory for the new transaction.
    if (curTransaction == NULL) {
        printf("Memory allocation error\n");
        exit(0);
    }
    (*curTransaction)->transactionId = transactionId; //Setting all the new transaction variables to the parsed variables
    (*curTransaction)->customerId = customerId;
    (*curTransaction)->amount = amount;
}

void createNode(node **newNode, transaction *data){ //Allocates memory for a new linked list node and stores a new transaction.
    *newNode = (node *) malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(0);
    }
    (*newNode)->data = data; // Storing the memory location of the new transaction.
}

void parseMessage(node **transactions, char *message){ //Parses the user input and stores it in a linked list data structure.
    // Variables to temporarily store parsed input.
    unsigned int tempTransactionId=0;
    unsigned int tempCustomerId=0;
    float tempAmount=0;
    char curString[15]="";

    //Variables to temporarily store a new node and transaction.
    node *currNode=NULL;
    transaction *currTransaction;

    while(1 == 1){
        if(*message == '|'){ //Verify that a new transaction is being entered

            //Transaction Id Parse
            message = message + TRANSACTION_INCREMENT; //Incrementing the message pointer by 2 to access Transaction Id number.
            strncat(curString,message,TRANSACTION_LENGTH); //Grabbing the transaction Id number as a string.
            tempTransactionId = atoi(curString); // Converting the transaction id string to an int.
            curString[0] = '\0'; //Reseting the temp string variable.

            //Customer Id Parse 
            message = message + CUSTOMER_INCREMENT; //Similar parse method as above.
            strncat(curString,message,CUSTOMER_LENGTH);
            tempCustomerId = atoi(curString);
            curString[0] = '\0';

            //Amount Parse
            message = message + AMOUNT_INCREMENT; //Similar parse method as above.
            strncat(curString,message,AMOUNT_LENGTH);
            tempAmount = atof(curString);
            curString[0]='\0';

            //Next Entry
            message = message + 10; // Move to possible start of new transaction.

            createTransaction(tempTransactionId,tempCustomerId,tempAmount,&currTransaction);
            createNode(&currNode,currTransaction);
            currNode->next = *transactions; //Setting the next node pointer to the memory location of the previously created node. Or to NULL if it's the first node.
            *transactions = currNode; 

        }
        else{
            return;
        }
    }

}

void printMessageSingle(node *transaction){ // Takes in a transaction node and prints it's stored transaction.
    char sizeOfNumber[10];
    int curLength=0;

        //Transaction Id
        curLength = sprintf(sizeOfNumber,"%d",transaction->data->transactionId); // Grabbing the length of the transaction ID.
        printf("%s","Transaction ID: T");
        for(int x=0; x<(TRANSACTION_LENGTH-curLength); x++){ // Padding the transaction ID with 0's based on length of ID.
            printf("%d",0);
        }
        printf("%d\n",transaction->data->transactionId);
        sizeOfNumber[0] = '\0';

        //Customer Id
        curLength = sprintf(sizeOfNumber,"%d",transaction->data->customerId); // Uses same print method as transaction ID.
        printf("%s","Customer ID: C");
        for(int x=0; x<(CUSTOMER_LENGTH-curLength); x++){
            printf("%d",0);
        }
        printf("%d\n",transaction->data->customerId);
        sizeOfNumber[0] = '\0';

        //Amount
        printf("%s%.2f\n","Amount: $ ",transaction->data->amount);
}

void printMessageAll(node *transaction){ // Takes in the head node and prints the contents of every node. Also prints total amount of transactions and average amount.
    int transactionNumb=1; 
    float totalTransactionAmount=0;
    if(transaction==NULL){
        return;
    }
    while(transaction->next != NULL){ //Print until there are no more filled nodes.
        printf("%s: %d\n","Transaction #",transactionNumb);
        printMessageSingle(transaction);
        printf("--------------------\n");
        transactionNumb++;
        totalTransactionAmount = totalTransactionAmount + transaction->data->amount;
        printf("%f\n",transaction->data->amount);
        transaction = transaction->next;
    }
    totalTransactionAmount = totalTransactionAmount + transaction->data->amount;
    printf("%s: %d\n","Transaction #",transactionNumb);
    printMessageSingle(transaction);
    printf("--------------------\n");
    printf("TOTAL TRANSACTIONS IN PAYLOAD = %d\n",transactionNumb);
    printf("AVERAGE TRANSACTION AMOUNT = %f\n",totalTransactionAmount/transactionNumb);
}

void freeData(node *transaction, char *message){ //Free's the linked list and message pointer of all the allocated memory.
    node *tempTransaction = transaction;

    while(transaction!=NULL){ // Free until there are no more filled nodes.
        tempTransaction = transaction->next;
        free(transaction->data); // Free data first so you the memory location is not lost.
        free(transaction);
        transaction = tempTransaction;
    }
    free(message);
}
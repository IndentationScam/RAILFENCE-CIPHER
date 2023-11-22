#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;  //easch node of the adjacency list

Node* addNode(Node* head, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        return head;
    }
}

char* encrypt_rail_fence(char* plaintext, int rails) {
    int len = strlen(plaintext);
    Node** fence = (Node**)malloc(rails * sizeof(Node*));  // fence here is the pointer poinitng to the adjacency list,we alocate memory for that dynamically

    // Initialize the adjacency list
    for (int i = 0; i < rails; i++) {    //all elements are set to NULL initlaly as and when new nodes are generated,it will be linked and the first node's adddress will be stored here
        fence[i] = NULL;
    }

    // Populate the adjacency list with the plaintext characters

//MAIN ENCRYPTION PART

    int rail = 0;
    int direction = 1; // 1 for down, -1 for up to move between the rails 

    for (int i = 0; i < len; i++) {
        fence[rail] = addNode(fence[rail], plaintext[i]);  //we start with rail=0 and add a node there

        rail += direction;   //for the next rail to be taken in the upcoming iteration,we update the rail value by adding 1 while going down to it using direction variable

        if (rail == rails - 1 || rail == 0) {
            direction = -direction; // Change direction at the top or bottom rail
        }
    }

    // Concatenate the characters from the adjacency list
    char* ciphertext = (char*)malloc(len + 1);  //+1 for the nul char at the end of a string
    int index = 0;

    for (int i = 0; i < rails; i++) {
        Node* temp = fence[i];
        while (temp != NULL) {
            ciphertext[index++] = temp->data;
            Node* current = temp;    //this is to clean up the allocate memory,as and when the elements from the adjacency list are being read,
                                            //current is pointer pointing to the current node whoose data is being read and after that the node is freeed 
            temp = temp->next;
            free(current);
        }
    }

    free(fence); // Free the array of pointers  

    ciphertext[index] = '\0';
    return ciphertext;
}



char* decrypt_rail_fence(char* ciphertext, int rails) {
    int len = strlen(ciphertext);
    Node** fence = (Node**)malloc(rails * sizeof(Node*));  // fence here is a pointer pointing to the adjacency list,and adjacency list holds the pointer to the
                                                            //       first element of the list,hence we use double pointers while declaration

    // Allocate memory for each element in the array
    for (int i = 0; i < rails; i++) {
        fence[i] = (Node*)malloc(sizeof(Node));
        fence[i] = NULL; // Initialize each element to NULL
    }

    int *railCounts=(int*)malloc(sizeof(int)*rails);

    for (int i = 0; i < rails; i++) {
        railCounts[i] = 0; // Initialize each element to 0
    }

    int rail = 0;
    int direction = 1;  //inorder to decide the direction in which we have to move direction variable is set,
                              // if direction =1 then we have to move down ,if its -1 then we move up in the fence

    for (int i = 0; i < len; i++) {
        railCounts[rail]++;
        rail += direction;

        if (rail == rails - 1 || rail == 0) {
            direction = -direction;
        }
    }

    int index = 0;
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < railCounts[i]; j++) {
            fence[i] = addNode(fence[i], ciphertext[index++]);
        }
    }

    char* plaintext = (char*)malloc(len + 1);  //+1 inorder to accomodate null char at the end of a string
    index = 0;
    rail = 0;
    direction = 1;

    for (int i = 0; i < len; i++) {
        plaintext[index++] = fence[rail]->data;
        fence[rail] = fence[rail]->next;
        rail += direction;

        if (rail == rails - 1 || rail == 0) {
            direction = -direction;
        }
    }

    plaintext[index] = '\0';

    // Free memory
    for (int i = 0; i < rails; i++) {
        free(fence[i]);
    }
    free(fence);

    return plaintext;
}


int main() {
    // int rails = 3;
    // char ciphertext[] = "HOLELWRDLO";

    // char* decryptedText = decrypt_rail_fence(ciphertext, rails);
    // printf("Decrypted: %s\n", decryptedText);

    // free(decryptedText);
    printf("\nWELCOME TO CIPHERNAUTS!!!\n");
    int choice;
    while(1){
        printf("\nIF U WISH TO ENCRYPT A PLAINTEXT TEXT INPUT THEN ENTER 1,IF U WISH TO DECRYPT A PLAINTEXT TEXT INPUT THEN ENTER 2 :\n");
        // scanf()
      
        // printf("\nIF U WISH TO DECRYPT A PLAINTEXT TEXT INPUT THEN ENTER 2 :\n");
        scanf("%d",&choice);


        if(choice ==1){
            char plaintext[50];
            printf("\nEnter the plain text to be encrypted:\n");
            fflush(stdin);
            gets(plaintext);
            int rails;
            printf("\nenter the number of rails\n");
            scanf("%d",&rails);
            char* encryptedtext= encrypt_rail_fence(plaintext,rails);
            printf("ENCYPTED TEXT IS: %s",encryptedtext);
        }


        if(choice==2){
                        char ciphertext[50];
            printf("\nEnter the plain text to be decrypted:\n");
            fflush(stdin);
            gets(ciphertext);
            int rails;
            printf("\nenter the number of rails\n");

            scanf("%d",&rails);
            char* decryptedtext= decrypt_rail_fence(ciphertext,rails);
            printf("DECYPTED TEXT IS: %s",decryptedtext);

        }
        break;

        // if(choice==2)

        
    }
    // int rails;
    

    return 0;
}
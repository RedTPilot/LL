#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void clear() {
#if defined(_WIN32) || defined(_WIN64)
system("cls");
#else
system("clear");
#endif
}

typedef struct Frequence {
    char c;
    int nb_occurence;
} Frequence;

typedef struct node {
    Frequence value;
    struct node* next;
} List;

List* transform(char* str) {
    List* head = NULL;
    List* current = NULL;
    int bb[256] = { 0 };

for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

    if (!bb[(unsigned char)c]) {
            bb[(unsigned char)c] = 1;
            List* newNode = (List*)malloc(sizeof(List));
            newNode->value.c = c;
            newNode->value.nb_occurence = 1;
            newNode->next = NULL;

        if (head == NULL) {
                head = newNode;
                current = head;
        } else {
                current->next = newNode;
                current = current->next;
        }} else {List* temp = head;
            while (temp != NULL) {
                if (temp->value.c == c) {
                    temp->value.nb_occurence++;
                    break;
                }
        temp = temp->next;
    }}}
    return head;
}

void display_list(List* head) {
    List* current = head;
    char listString[100] = "";
    while (current != NULL) {
        char currentChar[2] = { current->value.c, '\0' };
        strcat(listString, currentChar);
        current = current->next;
    }
    printf("List's string: %s\n", listString);
    current = head;
    while (current != NULL) {
        printf("%c  %d\n", current->value.c, current->value.nb_occurence);
        current = current->next;
    }
}

char most_frequent(List* head) {
    List* current = head;
    char mf = '\0';
    int mo = 0;
    while (current != NULL) {
        if (current->value.nb_occurence > mo) {
            mf = current->value.c;
            mo = current->value.nb_occurence;
        }
        current = current->next;
    }
    return mf;
}

void delete_element(List** head, char del) {
    List* current = *head;
    List* prev = NULL;
while (current != NULL) {if (current->value.c == del) {
            if (prev == NULL) {
                *head = current->next;
            } else {prev->next = current->next;}
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

void replace_char(List** head, char oldc, char newc) {
    List* current = *head;
    while (current != NULL) {
        if (current->value.c == oldc) {current->value.c = newc;}
        current = current->next;
    }
}

List* merge_lists(List* head1, List* head2) {
    List* merged = NULL;
    List* tail = NULL;

    while (head1 != NULL) {
        List* temp = merged;
        while(temp != NULL){
            if (temp->value.c == head1->value.c) {temp->value.nb_occurence += head1->value.nb_occurence;
                break;}
            temp = temp->next;
        }
        if(temp == NULL){
        List* newNode = (List*)malloc(sizeof(List));
        if (newNode == NULL) {exit(1);}
        newNode->value = head1->value;
        newNode->next = NULL;
            if(merged == NULL) {merged = newNode;
                tail = newNode;
            }else{tail->next = newNode;
                  tail = newNode;}
        }
        head1 = head1->next;
    }
    while(head2 != NULL) {
        List* temp = merged;
        while (temp != NULL) {
            if (temp->value.c == head2->value.c) {temp->value.nb_occurence += head2->value.nb_occurence;
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL){List* newNode = (List*)malloc(sizeof(List));
            if (newNode == NULL){exit(1);}
            newNode->value = head2->value;
            newNode->next = NULL;
            if(merged == NULL){merged = newNode;
                tail = newNode;
            }else{tail->next = newNode;
                tail = newNode;}
        }
        head2 = head2->next;
    }
    int swapped;
    List *ptr1;
    List *lptr = NULL;
    if (merged == NULL) return NULL;
    do {
        swapped = 0;
        ptr1 = merged;
        while (ptr1->next != lptr) {
            if (ptr1->value.c > ptr1->next->value.c) {swap(ptr1, ptr1->next);
            swapped = 1;}
            ptr1 = ptr1->next;}
            lptr = ptr1;
    }while(swapped);
    return merged;
}

void swap(List* a, List* b) {
    Frequence temp = a->value;
    a->value = b->value;
    b->value = temp;
}

int main() {
    int choice, choice1, cc = 0, cc1 = 0, cc2 = 0;

    char* string = (char*)malloc(100 * sizeof(char));
    if(string == NULL){return 1;}

    char* string2 = (char*)malloc(100 * sizeof(char));
    if(string2 == NULL){return 1;}

    printf("Input a string: ");
    scanf("%100s", string);
    List* head = NULL;
location1:
    choice = 0;
    choice1 = 0;
    clear();
    if(cc1 != 0){printf("You added the string: %s\n", string2);}
    if(cc == 0){printf("Your string: %s\n\nActions:\n1)Transform into a Linked List.\n2)Display the Linked List.\n3)Display the most frequent character.\n4)Delete a character.\n5)Replace character.\n6)Read another string.\n7)Merge the Linked Lists.\n8)Display the merged List.\n0)Exit.\n\nYour choice [1-8]: ", string);
    }else{printf("Your original string: %s\n\nActions:\n1)Transform into a Linked List[DONE].\n2)Display the Linked List.\n3)Display the most frequent character.\n4)Delete a character.\n5)Replace character.\n6)Read another string.\n7)Merge the Linked Lists.\n8)Display the merged List.\n0)Exit.\n\nYour choice [2-8]: ", string);}
    scanf("%d", &choice);

    switch (choice) {
    case 0:
        exit(0);
        break;

    case 1:
        if (cc > 0) {
            printf("\nAlready Done.\nReturning...");
            sleep(1);
            goto location1;
        }
        cc++;
        head = transform(string);
        clear();
        printf("Done.\n");
        sleep(1);
        goto location1;
        break;

    case 2:
        clear();
        if(cc == 0){
            cc++;
            head = transform(string);
        }
        display_list(head);
        printf("Input 1 to go back: ");
        while(choice1 != 1){scanf("%d", &choice1);}
        if(choice1 == 1) {goto location1;}
        break;

    case 3:
        clear();
        if(cc == 0){
            cc++;
            head = transform(string);
        }
        display_list(head);
        char mf = most_frequent(head);
        printf("\nMost frequent character: %c\n", mf);
        printf("Input 1 to go back: ");
        while(choice1 != 1){scanf("%d", &choice1);}
        if(choice1 == 1) {goto location1;}
        break;

    case 4:
        clear();
        if(cc == 0){
            cc++;
            head = transform(string);
        }
        display_list(head);
        char delete_char;
        printf("\nEnter the character to delete: ");
        scanf(" %c", &delete_char);
        delete_element(&head, delete_char);
        clear();
        printf("Character %c deleted.\n", delete_char);
        display_list(head);
        printf("Input 1 to go back: ");
        while(choice1 != 1){scanf("%d", &choice1);}
        if(choice1 == 1) {goto location1;}
        break;

    case 5: {
        clear();
        if(cc == 0){
            cc++;
            head = transform(string);
        }
        display_list(head);
        char oldc, newc;
        printf("Enter the character to replace: ");
        scanf(" %c", &oldc);
        printf("Enter the new character: ");
        scanf(" %c", &newc);
        replace_char(&head, oldc, newc);
        printf("Character %c replaced with %c:\n", oldc, newc);
        display_list(head);
        printf("Input 1 to go back: ");
        while(choice1 != 1){scanf("%d", &choice1);}
        if(choice1 == 1) {goto location1;}
        break;
    }

    case 6:
        clear();
        cc1++;
        printf("Input another string: ");
        scanf("%s", string2);
        goto location1;
        break;

    case 7:
        clear();
        if(cc1 == 0){
            printf("Input another string first(6).\nReturning...");
            sleep(2);
            goto location1;
        }
        cc2++;
        List* head1 = transform(string);
        List* head2 = transform(string2);
        head = merge_lists(head1, head2);
        printf("Lists merged.\n");
        sleep(1);
        goto location1;
        break;

    case 8:
        clear();
        if(cc1 == 0){
            printf("Input another string first(6).\nReturning...");
            sleep(2);
            goto location1;
        }
        display_list(head);
        printf("Input 1 to go back: ");
        while(choice1 != 1){scanf("%d", &choice1);}
        if(choice1 == 1) {goto location1;}
        break;
    }

    free(string);
    string = NULL;
    free(string2);
    string2 = NULL;
    List* temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

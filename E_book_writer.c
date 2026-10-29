#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    char topic_name[50];
    char stroy[40000];
    struct node *nextpage;
    struct node *prepage;
};

struct linkedlist {
    struct node *head;
    struct node *tail;
};

struct node* createpage(char topic_name[], char stroy[]) {
    struct node *temp = malloc(sizeof(struct node));

    if(temp == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strcpy(temp->topic_name, topic_name);
    strcpy(temp->stroy, stroy);

    temp->nextpage = NULL;
    temp->prepage = NULL;

    return temp;
}

void readbook(struct linkedlist *list) {
    struct node *temp = list->head;
    int page_number = 1;

    if(temp == NULL) {
        printf("Book is empty\n");
        return;
    }

    while(temp != NULL) {
        printf("\nPage %d\n", page_number);
        printf("%s\n", temp->topic_name);
        printf("%s\n", temp->stroy);

        page_number++;
        temp = temp->nextpage;
    }
}

void addtolast(struct linkedlist *list, char topic_name[], char stroy[]) {

    struct node *newpage = createpage(topic_name, stroy);

    if(newpage == NULL) return;

    if(list->head == NULL) {
        list->head = newpage;
        list->tail = newpage;
    } else {
        newpage->prepage = list->tail;
        list->tail->nextpage = newpage;
        list->tail = newpage;
    }

    readbook(list);
}

void addpage_into_front(struct linkedlist *list, char topic_name[], char stroy[]) {

    struct node *newpage = createpage(topic_name, stroy);

    if(newpage == NULL) return;

    if(list->head == NULL) {
        list->head = newpage;
        list->tail = newpage;
    } else {
        newpage->nextpage = list->head;
        list->head->prepage = newpage;
        list->head = newpage;
    }

    readbook(list);
}

void addpage_in_middle(struct linkedlist *list, char topic_name[], char stroy[],int pageno) {

    int count = 0;
    struct node *temp = list->head;

    while(temp != NULL) {
        count++;
        temp = temp->nextpage;
    }

    if(pageno < 1 || pageno > count + 1) {
        printf("Invalid position\n");
        return;
    }

    if(pageno == 1) {
        addpage_into_front(list, topic_name, stroy);
        return;
    }

    if(pageno == count + 1) {
        addtolast(list, topic_name, stroy);
        return;
    }

    temp = list->head;

    for(int i = 1; i < pageno - 1; i++) {
        temp = temp->nextpage;
    }

    struct node *newpage = createpage(topic_name, stroy);

    if(newpage == NULL) return;

    newpage->nextpage = temp->nextpage;
    newpage->prepage = temp;

    temp->nextpage->prepage = newpage;
    temp->nextpage = newpage;

    readbook(list);
}

void deletepage(struct linkedlist *list, int position) {

    struct node *temp = list->head;
    int count = 0;

    while(temp != NULL) {
        count++;
        temp = temp->nextpage;
    }

    if(position < 1 || position > count) {
        printf("Invalid page number\n");
        return;
    }

    temp = list->head;

    for(int i = 1; i < position; i++) {
        temp = temp->nextpage;
    }

    if(temp->prepage != NULL) {
        temp->prepage->nextpage = temp->nextpage;
    } else {
        list->head = temp->nextpage;
    }

    if(temp->nextpage != NULL) {
        temp->nextpage->prepage = temp->prepage;
    } else {
        list->tail = temp->prepage;
    }

    free(temp);

    readbook(list);
}

int main() {

    struct linkedlist book;
    book.head = NULL;
    book.tail = NULL;

    struct linkedlist *list = &book;

    int deletepagenumber, choice, addpagenumber;
    char topic_name[50], stroy[40000];

    do {
        printf("\nWelcome to book writing app\n\n");

        printf("Create new page: 1\n");
        printf("Add new page in last: 2\n");
        printf("Add page into front: 3\n");
        printf("Add page in your preferred position: 4\n");
        printf("Delete page: 5\n");
        printf("Read book: 6\n");
        printf("Exit: 7\n\n");

        printf("Enter number for your task: ");

        if(scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            printf("Invalid input\n");
            continue;
        }

        getchar();

        switch(choice) {

            case 1:
                printf("Enter topic name: ");
                fgets(topic_name, sizeof(topic_name), stdin);
                topic_name[strcspn(topic_name, "\n")] = '\0';

                printf("Enter story: ");
                fgets(stroy, sizeof(stroy), stdin);
                stroy[strcspn(stroy, "\n")] = '\0';

                if(list->head == NULL) {
                    addtolast(list, topic_name, stroy);
                } else {
                    printf("Book already has pages. Use another option.\n");
                }
                break;

            case 2:
                printf("Enter topic name: ");
                fgets(topic_name, sizeof(topic_name), stdin);
                topic_name[strcspn(topic_name, "\n")] = '\0';

                printf("Enter story: ");
                fgets(stroy, sizeof(stroy), stdin);
                stroy[strcspn(stroy, "\n")] = '\0';

                addtolast(list, topic_name, stroy);
                break;

            case 3:
                printf("Enter topic name: ");
                fgets(topic_name, sizeof(topic_name), stdin);
                topic_name[strcspn(topic_name, "\n")] = '\0';

                printf("Enter story: ");
                fgets(stroy, sizeof(stroy), stdin);
                stroy[strcspn(stroy, "\n")] = '\0';

                addpage_into_front(list, topic_name, stroy);
                break;

            case 4:
                printf("Enter topic name: ");
                fgets(topic_name, sizeof(topic_name), stdin);
                topic_name[strcspn(topic_name, "\n")] = '\0';

                printf("Enter story: ");
                fgets(stroy, sizeof(stroy), stdin);
                stroy[strcspn(stroy, "\n")] = '\0';

                printf("Enter position to insert: ");
                if(scanf("%d", &addpagenumber) != 1) {
                    while(getchar() != '\n');
                    printf("Invalid input\n");
                    break;
                }
                getchar();

                addpage_in_middle(list, topic_name,stroy, addpagenumber);
                break;

            case 5:
                printf("Enter page number to delete: ");

                if(scanf("%d", &deletepagenumber) != 1) {
                    while(getchar() != '\n');
                    printf("Invalid input\n");
                    break;
                }
                getchar();

                deletepage(list, deletepagenumber);
                break;

            case 6:
                readbook(list);
                break;

            case 7:
                printf("Closing book writing app\n");
                break;

            default:
                printf("You chose the wrong number\n");
        }

    } while(choice != 7);

    struct node *temp = list->head;

    while(temp != NULL) {
        struct node *next = temp->nextpage;
        free(temp);
        temp = next;
    }

    return 0;
}

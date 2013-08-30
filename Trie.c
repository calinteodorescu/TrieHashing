/*
 * Marcelo Pereira Novaes
 * 2011.2
 * MATA 40 - Estrutura de dados e algoritmos.
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXNAME 30

//trie

typedef struct Btrie{
    char letter;
    struct Btrie* parent;
    struct Btrie* right;
    struct Btrie* left;
}ABB;

//stack

typedef struct stack{
    char word;
    struct stack* next;
    struct stack* prev;    
}stack,*top;

//global var to last element of stack

typedef stack *ult;
ult last;

//----------------------------------STACK FUNTIONS----------------------

void new_stack(top *l){
    *l = NULL;
    last = NULL;
}

void push(top *l,char letter){
    stack* p=(stack*)malloc(sizeof(stack));
    if(*l){
    p->word = letter;
    p->next = (*l);
    (*l)->prev = p;
    *l = p;
    }
    else {
        p->word = letter;
        p->next = NULL;
        p->prev = NULL;
        *l=p;
    }
}

void pop(top *l){
    stack* p;
    if(*l){
        p=(*l);
        (*l)=(*l)->next;    
        if((*l))
            (*l)->prev=NULL;
        free(p);
    }
    else
        *l = NULL;
}

void printStack(top* t){
    stack *p,*q;
    for(p=*t;(p);p=p->next){
        if(!p->next)
            last = p;
    }
    for(q=last;(q);q=q->prev)
        printf("%c",q->word);
    printf("\n");
}

//----------------------------------------------------------------------

int main();
ABB* create(char c);
void InsertL(ABB** root);
void InOrder(ABB* root);
void WordPreOrder(ABB* root,top *t);

//TODO Debugar
void add_right_node(ABB** z,ABB** node){
    (*node)->right = NULL;
    (*node)->parent = *z;
    (*z)->right = *node;                                        
}

ABB* create(char c){
    ABB* node;
    node=(ABB*)malloc(sizeof(ABB));
    node->right = NULL;
    node->left = NULL;
    node->parent = NULL;
    node->letter = c;
    return node;
}

void ListWord(ABB* root){
    top t;
    new_stack(&t);
    if(root)
        WordPreOrder(root,&t);
    }
    
void WordPreOrder(ABB* root,top *t){
    if(root){
        if (root->letter=='*'){
            printf("palavra: ");
            printStack(t);//imprime pilha
                ABB* opt = root->left;
                switch (opt->letter) {
                case 's':
                    printf("substantivo\n");
                    opt = opt->left;
                    if (opt->letter == 'f')
                        printf("feminino, ");
                    else if(opt->letter == 'm')
                        printf("masculino, ");

                    opt = opt->left;
                    if (opt->letter == 's')
                        printf("singular\n");
                    else if(opt->letter == 'p')
                        printf("plural\n");
                    break;
                case 'a':
                    printf("adjetivo\n");
                    opt = opt->left;
                    if (opt->letter == 'f')
                        printf("feminino\n");
                    else if(opt->letter == 'm')
                        printf("masculino\n");
                    else if(opt->letter == 'n')
                        printf("neutro\n");
                    break;
                case 'p':
                    printf("preposicao\n");
                    break;
                case 'v':
                    printf("verbo\n");

                    opt = opt->left;
                    if (opt->letter == '1')
                        printf("primeira pessoa, ");
                    else if(opt->letter == '2')
                        printf("segunda pessoa, ");
                    else if(opt->letter == '3')
                        printf("terceira pessoa, ");

                    opt = opt->left;
                    if (opt->letter == 's')
                        printf("singular, ");
                    else if(opt->letter == 'p')
                        printf("plural, ");

                    opt = opt->left;
                    if (opt->letter == '1')
                        printf("primeira conjugacao\n");
                    else if(opt->letter == '2')
                        printf("segunda conjugacao\n");
                    else if(opt->letter == '3')
                        printf("terceira conjugacao\n");
                    break;
                }
        }else{
            push(t,root->letter); //empilho
            WordPreOrder(root->left,t);
            pop(t);//desempilha
            WordPreOrder(root->right,t);
        }
    }
}

ABB* InsertOtherInf(char c, ABB* z) {
    ABB* leftson = create(c);
    z->left = leftson;
    leftson->parent = z;
    return leftson;
}

void InsertL(ABB** root) {
    ABB *x, *par, *z, *node, *leftson;
    int i = 0;
    char name[MAXNAME];
    char c[4] = {'-','-','-','-'};

    scanf("%s %c%*c", name, c);
    //TODO Debugar
    switch (c[0]) {
    case 's':
        scanf("%c %c%*c", c+1, c+2);
        break;
    case 'a':
        scanf("%c%*c", c+3);
        break;
    case 'p':
        break;
    case 'v':
        scanf("%c %c %c%*c", c+1, c+2, c+3);
        break;
    }

    strcat(name, "*");
    par = NULL;
    if ((*root) == NULL ) { // trie empty
        x = create(name[i]);
        *root = x;
    } else {
        x = *root;
        while ((name[i] != '*') && ((!((x == NULL )|| ((x->letter == '*') ))) && (x->letter <= name[i]) )) {
            par=x;
            if( x->letter == name[i] ) {
                x=x->left;
                i++;
            }
            else
            x=x->right;
        }
        if (x == NULL ) {
            node = create(name[i]);
            node->right = NULL;
            node->parent = par;
            par->right = node;
        } else {
            if (!(x->letter == '*' && name[i] == '*') /* new */
                    && (!(x->letter != '*' && name[i] == '*'))) /*  */{ // Doesn't exist this letter
                node = create(name[i]);
                node->right = x;
                node->parent = par;

                if (x == *root)
                    (*root) = node;        //Must be root
                else if ((par != NULL )&& (x == par->right) )par->right = node;
                else
                if(par != NULL)
                par->left = node;

                if (x != NULL )
                    x->parent = node;
            } else {
                if ((x->letter != '*') && (name[i] == '*')) {
                    for (z = x; (z) && (z->letter != '*'); z = z->right)
                        ;        //test for if already exist
                    if (!z) {
                        node = create(name[i]);
                        node->right = NULL;        //CHANGE ( I HAVE PARENT)
                        for (z = x->parent; (x); z = x, x = x->right)
                            ;        //z just for aux , doesn't change z in under
                        node->parent = z;
                        z->right = node;
                        //----------------------------

                        z = node;

                        node = create(c[0]);
                        add_right_node(&node, &z);

                        ABB* node1;
                        ABB* node2;
                        z = node;
                        if (c[0] != '-') {
                            if (c[1] != '-') {
                                node = create(c[0]);
                                add_right_node(&node, &z);
                                node1 = create(c[1]);
                                add_right_node(&node, &node1);
                                if (c[2] != '-') {
                                    node2 = create(c[2]);
                                    add_right_node(&node2, &node);
                                }
                            } else {
                                node2 = create(c[0]);
                                add_right_node(&z, &node);
                            }
                        } else {
                            node = create('p');
                            add_right_node(&z, &node);
                        }

                        node = create(name[i]);
                        node->right = NULL;        //CHANGE ( I HAVE PARENT)
                        for (z = x->parent; (x); z = x, x = x->right)
                            ;        //z just for aux , doesn't change z in under
                        node->parent = z;
                        z->right = node;

                        //----------------------------

                        node = create(name[i]);
                        node->right = NULL;        //CHANGE (I HAVE PARENT)
                        for (z = x->parent; (x); z = x, x = x->right)
                            ;        //z just for aux , doesn't change z in under
                        node->parent = z;
                        z->right = node;
                    } else
                        printf("palavra jah existente\n");

                } else
                    printf("palavra jah existente\n");
            }
        }
    }

    if (*root == x) {
        z = x;
    } else // x isn't root
    {
        z = node;
    }

    for (++i; i < strlen(name); i++) { //node remeber name is [word + *]
        leftson = create(name[i]);
        z->left = leftson;
        leftson->parent = z;
        z = leftson;
    }
    if(leftson->letter == '*'){
        int i;
        for(i=0;i<3 && c[i] != '-';i++)
            z = InsertOtherInf(c[i], z);
    }
}

void PrintLine(ABB* root,int i,int* flag){ 
    i--;
    if(root){
        if(i==0){
            if (*flag == 0)
            {
                printf("%c",root->letter);
                (*flag)++;
            }
            else
            {
                printf(", %c",root->letter);
            }            
    }
        else{
            PrintLine(root->left,i,flag);
            PrintLine(root->right,i,flag);
        }
    }
}
    
void PrintLevel(ABB* root){ //realloc on end string, incress positions .
    int i,flag=0;
    scanf("%d",&i);
    if ( i == 1 )
        printf("%c",root->letter);
    else
        PrintLine(root,i,&flag);
    printf("\n");
}

void InOrder(ABB* trie){
    if(trie){
        InOrder(trie->left);
            if(trie->left == NULL){
                if(trie->right == NULL)
                    printf("chave: %c filho esquerdo: nil filho direito: nil\n",trie->letter);
                else
                    printf("chave: %c filho esquerdo: nil filho direito: %c\n",trie->letter,trie->right->letter);
            }
            else{
                if((trie->right == NULL))
                    printf("chave: %c filho esquerdo: %c filho direito: nil\n",trie->letter,trie->left->letter);                    
                else
                    printf("chave: %c filho esquerdo: %c filho direito: %c\n",trie->letter,trie->left->letter,trie->right->letter);
            }
        InOrder(trie->right);
    }
}

//NEW PART--------------------------------------------------------------

void printChangeStack(top* t,char* name){
    int i; int flag=0;
    stack *p,*q;
    for(p=*t;(p);p=p->next){
        if((!p->next))
            last = p;
    }//has to get last =P
    i=0;q=last;
    while((q) && i<strlen(name)){
        if(name[i] == q->word){
            q=q->prev;i++;                
        }
        else{
            flag++;
            i++;
            if(q){
                q=q->prev;} 
        }    
    }
    if(flag==1 && !q && name[i] == '\0'){
        for(p=last;(p);p=p->prev)
            printf("%c",p->word);
        printf("\n");
    }
}

void ChangeWordPreOrder(ABB* root,top *t,char* name){
    if(root){
        if (root->letter=='*'){
            printChangeStack(t,name);//imprime pilha 
        }
        else{ 
            push(t,root->letter); //empilho
            ChangeWordPreOrder(root->left,t,name);
            pop(t);//desempilha
            ChangeWordPreOrder(root->right,t,name);
        }
    }
}

void ChangeWord(ABB* root){
    top t; char name[MAXNAME];
    scanf("%s",name);
    new_stack(&t);
    if(root)
        ChangeWordPreOrder(root,&t,name);
}

//----------------------------------------------------------------------

//ADD 

void printAddStack(top* t,char* name){
    int i; int flag=0;
    stack *p,*q;
    for(p=*t;(p);p=p->next){
        if((!p->next))
            last = p;
    }//has to get last =P
    i=0;q=last;
    while((q) && i<strlen(name)){
        if(name[i] == q->word){
            q=q->prev;i++;                
        }
        else{
            flag++;
            if(q)
                q=q->prev;
        }    
    }
    if(flag==1 && !q && name[i] == '\0' ){
        for(p=last;(p);p=p->prev)
            printf("%c",p->word);
        printf("\n");
    }
    if(flag==0 && q)
        if(q->prev == NULL){
            for(p=last;(p);p=p->prev)
                printf("%c",p->word);
            printf("\n");
        }
}


void addWordPreOrder(ABB* root,top *t,char* name){
    if(root){
        if (root->letter=='*'){;
            printAddStack(t,name);//imprime pilha 
        }
        else{ 
            push(t,root->letter); //PUSH stack
            addWordPreOrder(root->left,t,name);
            pop(t);//POP stack
            addWordPreOrder(root->right,t,name);
        }
    }
}

void addWord(ABB* root){
    top t; char name[MAXNAME];
    scanf("%s",name);
    new_stack(&t);
    if(root)
        addWordPreOrder(root,&t,name);
}

//----------------------------------------------------------------------

//Remove

void printRmStack(top* t,char* name){
    int i; int flag=0;
    stack *p,*q;
    for(p=*t;(p);p=p->next){
        if((!p->next))
            last = p;
    }//has to get last =P
    i=0;q=last;
    while((q) && i<strlen(name)){
        if(name[i] == q->word){
            q=q->prev;i++;                
        }
        else{
            flag++;
            i++;
        }    
    }
    if(flag==1 && !q && name[i] == '\0'){
        for(p=last;(p);p=p->prev)
            printf("%c",p->word);
        printf("\n");
    }
    if(flag==0 && (q == NULL) && (i<strlen(name))){
        for(p=last;(p);p=p->prev)
            printf("%c",p->word);
        printf("\n");
    }
}

void rmWordPreOrder(ABB* root,top *t,char* name){
    if(root){
        if (root->letter=='*'){;
            printRmStack(t,name);//imprime pilha 
        }
        else{ 
            push(t,root->letter);//PUSH stack
            rmWordPreOrder(root->left,t,name);
            pop(t);//POP stack
            rmWordPreOrder(root->right,t,name);
        }
    }
}

void rmWord(ABB* root){
    top t; char name[MAXNAME];
    scanf("%s",name);//WITH OUT *
    new_stack(&t);
    if(root)
        rmWordPreOrder(root,&t,name);
}

//------------------------------------REMOVE----------------------------

void Stack(top* t,char* name,int* flag){
    stack *p,*q;
    int i=0; 
    for(p=*t;(p);p=p->next){
        if(!p->next)
            last = p;
    }//has to get last =P
    q=last;
    while((q) && name[i] != '\0'){
        if(name[i] == q->word){
            //~ printf("%c",q->word); //  TEST
            //~ printf("%c",name[i]);  // TEST
            q=q->prev;i++;        
         }
         else{
            *flag=0;
            i++;
        }    
    }
    if(!q && name[i] == '\0' ){
        *flag=2;
    }
    //~ printf("\n\n %d \n\n",*flag); //TEST
}

void RemoveWordPreOrder(ABB** node,top *t,char* name,int*flag){//How to change root to apoint NULL, in a recursive function
    if(*node){
        if ( (*node)->letter == '*' ){
            Stack(t,name,flag);//verify if they're equals
        }
        else{ 
            push(t,(*node)->letter); //PUSH
            RemoveWordPreOrder(&((*node)->left),t,name,flag);
            pop(t);//POP
            if(*flag!=2 && *flag!=3)
                RemoveWordPreOrder(&((*node)->right),t,name,flag);
        }
        if( *flag == 2 && *flag!=3){
            if((*node)->parent){
                if ((*node)->parent->right){
                    if((*node)->parent->right == (*node) ){(*node)->parent->right = (*node)->right;}        
                    else{
                        if((*node)->parent->parent){
                            if((*node)->parent->parent->right!=(*node)->parent){
                                (*node)->parent->parent->left = (*node)->parent->right;// CASA CARRO CARONA
                                (*node)->parent->right->parent = (*node)->parent->parent;
                                //free  (*node) and (*node)->parent
                                }
                            else{
                                (*node)->parent->parent->right = (*node)->parent->right;                            
                            }
                    
                        }    
                        else{//root ex. CEIL, DURTY , remove CEIL
                            node=&((*node)->parent->right);//0
                            
                        }        
                    }
                    *flag=3;
                }
                else{    
                    (*node)->parent->left = NULL;
                }    
            }    
            else{
                *node = NULL;
            }        
        }                                                                    
    }
}    

void RemoveWord(ABB** root){
    top t; char name[MAXNAME];int flag=1;
    scanf("%s",name);
    new_stack(&t);
    if(*root)
        RemoveWordPreOrder(root,&t,name,&flag);
    if(flag !=2 && flag!=3)
        printf("palavra inexistente\n");
    
}
//----------------------------------------------------------------------

void saveTrie(ABB* trie){
    int i=0;
    ABB ** array = (ABB **)malloc(sizeof(ABB));
    array[0] = trie;
    int n = 1;
    while(i<n){
        if(array[i]->left != NULL){
            n++;
            array = (ABB **)realloc(array, n*sizeof(ABB));
            array[n-1] = array[i]->left;
        }
        if(array[i]->right != NULL){
            n++;
            array = (ABB **)realloc(array, n*sizeof(ABB));
            array[n-1] = array[i]->right;
        }
        i++;
    }
    int j;
    FILE * file;
    file = fopen("trie","wb");
    if(!file){
        printf("Erro ao criar o arquivo\n");
        exit(1);
    }
    for(j=0;j<n;j++){
        //~ if(fwrite(&array[j]->letter,sizeof(char),1,f)!=1){
            //~ printf("Erro ao escrever %c no arquivo\n",array[j]->letter);
            //~ exit(1);
        //~ }
        printf("%c\n",array[j]->letter);
    }
    fclose(file);
}

int main(){
    ABB* trie = NULL;
    char choice;
    do{
        scanf("%c",&choice);
        switch(choice){
            case 'p':
                InsertL(&trie);
                break;
            case 'a':
                InOrder(trie);
                break;
            case 'n':
                PrintLevel(trie);
                break;
            case 'o':
                ListWord(trie);
                break;
            case 't':
                ChangeWord(trie);
                break;
            case 'i':
                addWord(trie);
                break;
            case 'r':
                rmWord(trie);
                break;
            case 'd':
                RemoveWord(&trie);
                break;
            case 'w'://no texto �� o "p"
            
            break;
            case 's':
                saveTrie(trie);
                break;
            case 'e':
                break;
        }
    }while(choice!='e');    
    return 0;
}

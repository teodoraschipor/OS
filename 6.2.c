//Write a program that will calculate the multiplication of two given matrices (compatible dimensions); where each element of the result matrix is calculated by a distinct thread.

#include <math.h>
#include <stdio.h>
#include <pthread.h>


struct myStruct
{
 int** c;
 int** m1;
 int** m2;
 int m,n,p;//dimensions of the matrices
 int i;//the line where I am
 int j;//the column where I am
};

void ourMatrix(void* s)
{
 struct myStruct* t = (struct myStruct*)s;
 t->c[t->i][t->j] = 0;
 for(int k = 0; k < t->p; k++)
  {
  t->c[t->i][t->j] += (t->m1[t->i][k] * t->m2[k][t->j] );
  }
}
int main()
{
 struct myStruct* str;
 str = (struct myStruct*)malloc(sizeof(struct myStruct));
 printf("m,n,p = ");
 scanf("%d %d %d",&str->m,&str->n,&str->p);//introduce the dimensions of the matrices

 //ALLOCATE MEMORY FOR THE FIRST MATRIX
 str->m1 = (int**)malloc(str->m * sizeof(int*));
  for(int i = 0 ; i < str->m ; i++)
   str->m1[i] = (int*)malloc(str->p * sizeof(int));

  //ALLOCATE MEMORY FOR THE SECOND MATRIX
 str->m2 = (int**)malloc(str->p * sizeof(int*));
   for(int i = 0 ; i < str->p; i++)
     str->m2[i] = (int*)malloc(str->n * sizeof(int));

   //INTRODUCE ELEMENTS FOR THE FIRST MATRIX
 for(int i = 0 ; i < str->m ; i++)
  for(int j = 0; j < str->p; j++)
   {
   int nr;
   printf("m1[%d][%d] = ",i,j);
   scanf("%d",&nr);
   str->m1[i][j] = nr;
   }
  //INTRODUCE ELEMENTS FOR THE SECOND MATRIX
 for(int i = 0 ; i < str->p; i++)
   for(int j = 0; j < str->n; j++)
   {
  int nr;
   printf("m2[%d][%d] = ",i,j);
   scanf("%d",&nr);
   str->m2[i][j] = nr;
   }

 //ALLOCATE MEMORY FOR THE RESULT MATRIX
   str->c = (int**)malloc(str->m * sizeof(int*));
   for(int i = 0 ; i < str->m ; i++)
    str->c[i] = (int*)malloc(str->n * sizeof(int));

   //MATRIX OF THREADS
 pthread_t** thr = (pthread_t**)malloc(str->m * sizeof(pthread_t*));
   for(int i = 0 ; i < str->m; i++)
     thr[i] = (pthread_t*)malloc(str->n * sizeof(pthread_t)); 


 for(int i = 0 ; i < str->m ; i++)
  for(int j = 0 ; j < str->n ; j++)
    {
    str->i = i;
    str->j = j;
    
    if(pthread_create(&thr[i][j],NULL,ourMatrix,str))
    {
    return -1;
    }
    int* res;
    if(pthread_join(thr[i][j],&res))
    {
     return -1;
    }
}
  
  printf("\n");
  for(int i = 0 ; i < str->m; i++)
  {
   for(int j = 0; j < str->n; j++)
   {
   int nr = str->c[i][j];
   printf("%d ",nr);
   }
  printf("\n");
  }
 return 0;
}

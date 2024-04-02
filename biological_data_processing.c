#include<stdio.h>
#include<string.h>
void Transcription();
void Translation();
void percentage_atgc();
void reverse_transcription();
int codon_table(int,int,int,char*,char*);
void main()
{
    long int selection=0;
    while(selection!=5)
    {
        printf("----------------------------------------------------\n");
        printf("Choose the operation that you want to perform:\n");
        printf("1.Calculate the percentage of ATGC\n");
        printf("2.Transcription\n");
        printf("3.Translation\n");
        printf("4.Reverse transcription\n");
        printf("5.EXIT\n->");
        scanf("%ld",&selection);
        switch(selection)
        {
            case 1:
                printf("---------------Percentage of:-A,T,G,C---------------\n");
                percentage_atgc();
                break;
            case 2:
                printf("------------------Transcription---------------------\n");
                Transcription();
                break;
            case 3:
                printf("--------------------Translation---------------------\n");
                Translation();
                break;
            case 4:
                printf("---------------Reverse Transcription----------------\n");
                reverse_transcription();
                break;
            case 5:
                break;                                                               //it exits because the value of selection is 5
            default:
            printf("Please select a proper response\n     exiting--->\n");           //it exits because the value of selection becomes 5 in the next iteration
            selection=5;
            break;
        }
    }
}

void percentage_atgc()                                                        //calculates percentage of bases A,T,G,C in nucleotide sequence
{
    char DNA[1000][1000],m_RNA[1000][1000],name[1000];
    int i,n,j=0,g=0,k=0;
    float percentA,percentT,percentG,percentC,percentAT,percentGC;
    printf("Enter the file location:");
    scanf("%s",name);
    FILE *DNAf=fopen(name,"r");
    if(DNAf==NULL)
         printf("Error opening file\n");


    else
    {
    while(!(feof(DNAf)))
       {
           fgets(DNA[j],1000,DNAf);
           j++;
       }
    int countA=0,countT=0,countC=0,countG=0;
    for(i=0;i<j;i++)
           {
              for(k=0;k<=n;k++)
                 {
                    switch (DNA[i][k])
                      {
                          case 'A':
                                   countA+=1;
                                   g++;
                                   break;
                          case 'T':
                                   countT+=1;
                                   g++;
                                   break;
                          case 'G':
                                   countG+=1;
                                   g++;
                                   break;
                          case 'C':
                                   countC+=1;
                                   g++;
                                   break;

                          default :
                                   break;
                      }
                 }
            }


   percentA=countA/(float)(g)*100;
   percentT=countT/(float)(g)*100;
   percentG=countG/(float)(g)*100;
   percentC=countC/(float)(g)*100;
   percentAT=percentA+percentT;
   percentGC=percentG+percentC;


   printf("The percentage of base A is %f%%\n",percentA);
   printf("The percentage of base T is %f%%\n",percentT);
   printf("The percentage of base G is %f%%\n",percentG);
   printf("The percentage of base C is %f%%\n",percentC);
   printf("The percentage of bases AT is %f%%\n",percentAT);
   printf("The percentage of bases GC is %f%%\n",percentGC);
   fclose(DNAf);
   }
}

void Transcription()                                                     //Converts the nucleotide sequence to mRNA sequence
{
    char DNA[1000][1000],m_RNA[1000][1000],name[1000000];
    int i,n,m=0,j=0;
    printf("Enter the file location:");
    scanf("%s",name);
    FILE *DNAf=fopen(name,"r");
    if(DNAf==NULL)
         printf("Error opening file\n");


    else
    {
    while(!(feof(DNAf)))
       {
           fgets(DNA[j],1000,DNAf);
           j++;

       }
    n=strlen(DNA[0]);
    int k=0;
    for(i=0;i<j;i++)
       {
          for(k=0,m=0;k<=1000;k++)
             {
                 if((DNA[i][k]=='A')||(DNA[i][k]=='G')||(DNA[i][k]=='C'))
                    {
                       m_RNA[i][m]=DNA[i][k];
                       m++;
                    }
                 else if(DNA[i][k]=='T')
                    {
                       m_RNA[i][m]='U';
                       m++;
                    }
                 else if(DNA[i][k]=='*')
                    {
                      m_RNA[i][m]=DNA[i][k];
                      m++;
                      break;
                    }
                 else
                    {
                       continue;
                    }
             }
       }
    fclose(DNAf);


    printf("Enter the name or location of the file in which the result is to be updated\n");
    scanf("%s",name);
    FILE *m_RNAf=fopen(name,"w");
    for(i=0;i<j;i++)
        {
            fputs(m_RNA[i],m_RNAf);
        }
    fclose(m_RNAf);
    }
}


void Translation()                                                           //converts mRNA sequence to protein sequence
{
    int rows=0,i=0,j=0;
    char mrna[1000][1000],protein[1000][1000],name[1000],*mrna_ptr,*protein_ptr;
    mrna_ptr=&mrna[0][0];
    protein_ptr=&protein[0][0];
    printf("Enter the file location:");
    scanf("%s",name);
    FILE *MRNA=fopen(name,"r");
    if(MRNA==NULL)
         printf("Error opening file\n");


    else
    {
    while(!feof(MRNA))
    {
        fgets(mrna[rows],1000,MRNA);
        rows++;
    }
    for(i;i<1000*rows;i++)
    {
     if(*(mrna_ptr+i)=='A'&&*(mrna_ptr+i+1)=='U'&&*(mrna_ptr+i+2)=='G')
     break;
    }
    j=codon_table(i,j,rows,mrna_ptr,protein_ptr);
    fclose(MRNA);


    printf("Enter the file name or location where you want to update the result:\n");
    scanf("%s",name);
    FILE * ProteinFile=fopen(name,"w");
    for(i=0;i<=j/1000;i++)
       {
           fputs(protein[i],ProteinFile);
       }
    fclose(ProteinFile);
    }
}

int codon_table(int i,int j,int rows,char *m_rna,char *protein)
{
    do
    {

        if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='G')||(*(m_rna+i+2)=='A')))
            break;
        else if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='G')&&(*(m_rna+i+2)=='A'))
            break;
        else
        {
        if((*(m_rna+i)=='A')&&(*(m_rna+i+1)=='U')&&(*(m_rna+i+2)=='G'))
            *(protein+j)='M';
        else if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='G')&&(*(m_rna+i+2)=='G'))
            *(protein+j)='W';
        else if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='U')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')))
            *(protein+j)='F';
        else if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='U')&&((*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='L';
        else if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='G')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')))
            *(protein+j)='C';
        else if((*(m_rna+i)=='A')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')))
            *(protein+j)='N';
        else if((*(m_rna+i)=='A')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='K';
        else if((*(m_rna+i)=='G')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')))
            *(protein+j)='D';
        else if((*(m_rna+i)=='G')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='E';
        else if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')))
            *(protein+j)='Y';
        else if((*(m_rna+i)=='C')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')))
            *(protein+j)='H';
        else if((*(m_rna+i)=='C')&&(*(m_rna+i+1)=='A')&&((*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='Q';
        else if((*(m_rna+i)=='A')&&(*(m_rna+i+1)=='G')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')))
            *(protein+j)='S';
        else if((*(m_rna+i)=='A')&&(*(m_rna+i+1)=='G')&&((*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='R';
        else if((*(m_rna+i)=='A')&&(*(m_rna+i+1)=='U')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')))
            *(protein+j)='I';
        else if((*(m_rna+i)=='C')&&(*(m_rna+i+1)=='U')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='L';
        else if((*(m_rna+i)=='G')&&(*(m_rna+i+1)=='U')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='V';
        else if((*(m_rna+i)=='U')&&(*(m_rna+i+1)=='C')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='S';
        else if((*(m_rna+i)=='C')&&(*(m_rna+i+1)=='C')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='P';
        else if((*(m_rna+i)=='A')&&(*(m_rna+i+1)=='C')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='T';
        else if((*(m_rna+i)=='G')&&(*(m_rna+i+1)=='C')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='A';
        else if((*(m_rna+i)=='C')&&(*(m_rna+i+1)=='G')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='R';
        else if((*(m_rna+i)=='G')&&(*(m_rna+i+1)=='G')&&((*(m_rna+i+2)=='U')||(*(m_rna+i+2)=='C')||(*(m_rna+i+2)=='A')||(*(m_rna+i+2)=='G')))
            *(protein+j)='G';
    }
    i=i+3;
    j++;
    }
    while(i<rows*1000);
    return j;
}

void reverse_transcription()                                   //converts mRNA sequence to get the original DNA sequence
{
    char name[100],m_RNA[1000][1000],DNA[1000][1000];
    int j=0,k,m,n,i;
    printf("Enter the m_RNA file name or location:\n");
    scanf("%s",name);
    FILE * m_RNAf = fopen(name,"r");
    if(m_RNAf==NULL)
          printf("Error opening file\n");
    else
    {
    while(!(feof(m_RNAf)))
       {
           fgets(m_RNA[j],1000,m_RNAf);
           j++;
       }
    fclose(m_RNAf);


    n=strlen(m_RNA[0]);
    for (i=0;i<j;i++)
       {
           for (k=0,m=0;k<=n;k++)
               {
                   if((m_RNA[i][k]=='A')||(m_RNA[i][k]=='G')||(m_RNA[i][k]=='C'))
                        {
                            DNA[i][m]=m_RNA[i][k];
                            m++;
                        }
                    else if(m_RNA[i][k]=='U')
                        {
                            DNA[i][m]='T';
                            m++;
                        }
                    else if (m_RNA[i][k]=='*')
                        {
                            DNA[i][m]=m_RNA[i][k];
                            m++;
                            break;
                        }
                    else
                            continue;
               }
       }


    printf("Enter the file name or location where you want to update the result:\n");
    scanf("%s",name);
    FILE * DNAfrt=fopen(name,"w");
    for(i=0;i<j;i++)
       {
           fputs(DNA[i],DNAfrt);
       }
    fclose(DNAfrt);
    }
}

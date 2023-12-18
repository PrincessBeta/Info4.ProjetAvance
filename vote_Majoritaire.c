#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#define MENTIONS 6


int* getVoteCandidat(int **table, int numCand, int nbElector){
    int* listCand = malloc(sizeof(int)*nbElector);

    for (int i=0; i<nbElector; i++){
        listCand[i]= table[i][numCand];
    }
    return listCand;
}

//0-> tres bien; 5-> a rejeter
float* statCandidatJugMaj(int* listCand, int nbElector){
    float* stat = malloc(sizeof(float)*MENTIONS);
    for (int i=0; i<MENTIONS; i++){
        stat[i] = 0;
    }
    
    for (int i=0; i<nbElector; i++){
        switch(listCand[i]){
            case -1: 
                stat[5] +=1;
                break;
            case 6: 
                stat[5] +=1;
                break;
            case 5: 
                stat[4] +=1;
                break;
            case 4: 
                stat[3] +=1;
                break;
            case 3: 
                stat[2] +=1;
                break;
            case 2:    
                stat[1] +=1;
                break;
            case 1: 
                stat[0] +=1;
                break;
        }
    }

    for (int i=0; i<MENTIONS; i++){
        stat[i]= stat[i]/nbElector;
    }

    return stat;
}

int medStatMaj(float* stat){
    float seen=0;

    for (int i=0; i<6; i++){
        seen+=stat[i];
        if (seen>0.5)
            return i;
    }
    return -1;
}

float* calculInsatisfait(float* statCand, int medianInf, int medianSup){
    float* rslt = malloc(sizeof(float)*2);
    rslt[0]=0;
    rslt[1]=0;

    for (int i=0; i<6; i++){
        if (i<medianInf)
            rslt[0] += statCand[i];
        else if (i>medianSup)
            rslt[1] += statCand[i];
    }
    return rslt;
}

int egaliteInsatisfait(int nbCand, int med, int* lstCand, float** listStatCand){
    int nbWin = nbCand;
    int medInf = med;
    int medSup = med;
    int fstCand = 0;
    int lstWin[nbCand];
    float statWin;
    while(nbWin>1){
        nbWin =0;
        statWin = 0;
        for(int i=0; i<nbCand; i++){
            float* cand = calculInsatisfait(listStatCand[lstCand[i]], medInf, medSup);
            if(statWin>=0){
                if (cand[0]>statWin){
                    nbWin=0;
                    statWin = cand[0];
                    fstCand = i;
                }
                if (cand[1]>statWin){
                    nbWin=0;
                    statWin= -1*cand[1];
                    fstCand = i;
                }
            }else{
                if ((-1*cand[0])<=statWin){
                    nbWin=0;
                    statWin = cand[0];
                    fstCand = i;
                }
                if ((-1*cand[1])<statWin){
                    nbWin=0;
                    statWin= -1*cand[1];
                    fstCand = i;
                }
            }

            if (cand[0]==statWin||(-1*cand[1])==statWin){
                lstWin[nbWin] = lstCand[i];                 
                nbWin +=1;
            }
        }

        if (nbWin>1 && statWin<0){
            medSup+=1;
        }else if(nbWin>1){
            medInf-=1;
        }

        if (nbWin ==1 && statWin<0){
            lstCand[fstCand] = lstCand[nbCand-1];
            nbCand-=1;
            nbWin = nbCand;
        }
    }
    return lstWin[0];
}

int mtdGrpInsatisfait(float** listStatCand, int* listMedCand, int nbCand){
    int nbWin = 0;
    int winner= 0;
    int medWin = listMedCand[0];
    int* lstIndWin = malloc(sizeof(int)*nbCand);
    
    for (int i=0; i<nbCand; i++){
        if (listMedCand[i] < medWin){
            winner =i;
            nbWin=0;
        }
        if (listMedCand[i] ==medWin){
            lstIndWin[nbWin] = i;
            nbWin +=1;
        }
    }

    if (nbWin>1){
        winner = egaliteInsatisfait(nbWin, medWin, lstIndWin, listStatCand);
    }
    return winner;
}

int jugementMaj(int **table, int nbCol, int nbRow, char ** candidats){
    float **listStatCand = (float**)malloc(sizeof(float)*nbRow);
    int *listMedCand = malloc(sizeof(int*)*nbRow);

    for (int i =0; i<nbCol; i++){
        listStatCand[i] = statCandidatJugMaj(getVoteCandidat(table,i,nbRow), nbRow);
        listMedCand[i] = medStatMaj(listStatCand[i]);
    }
    return candidats[mtdGrpInsatisfait(listStatCand, listMedCand, nbCol)];
}
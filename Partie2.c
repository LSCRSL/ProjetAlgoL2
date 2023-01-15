#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/**** Compteur malloc de Liste ****/
int cptmallocL = 0;

/**** Compteur malloc de Liste De Liste ****/
int cptmallocLDL = 0;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

/*************************************************/
/*                                               */
/*       definition type liste de liste          */
/*                                               */
/*************************************************/

typedef struct BlocDeBloc{
    Liste list;
    struct BlocDeBloc *suiv;
} BlocDeBLoc;

typedef BlocDeBLoc *ListeDeListe;

/*************************************************/
/*                                               */
/*         definition type liste bis             */
/*                                               */
/*************************************************/

typedef struct BlocBis{
    int nb;
    struct BlocBis *suivt;
    struct BlocBis **pred;
} BlocBis;

typedef BlocBis *ListeBis ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);

/* Verfie s'il a des 0 à la position 1, 2 ou 3 de la liste */
bool ZeroEnPositionUnouDeuxOuTrois (Liste l);

/* Verfie si l1 est plus court que l2 */
bool Pluscourte (Liste l1, Liste l2);

/* Compte le nombre de 0 dans une liste jusqu'à la position K */
/* Bis_rec est la sous-fonction utilitaire de la version recursive */
/* Bis_proc est la sous-procedure utilitaire de la version recursive */
int Bis_rec(Liste l, int K, int cpt);
int NombreDe0AvantPositionK_sfrec(Liste l, int K);
void Bis_proc(Liste l, int K, int *cpt);
int NombreDe0AvantPositionK_sfproc(Liste l, int K);
int NombreDe0AvantPositionK(Liste l, int K);
int NombreDe0AvantPositionK_rec(Liste l, int K);

/* Compte le nombre de 0 après la position K en partant de la fin */
void NombreDe0ApresRetroPositionK_sf(Liste L, int K, int* retropos, int* r);
int NombreDe0ApresRetroPositionK(Liste L, int K);

/* Renvoie une liste contenant les nombres positifs de la liste en doublon */
Liste FctBegaye(Liste l);
Liste FctBegayeRec(Liste l);
Liste FctBegayeIT2(Liste l);
Liste fctBegayeAcc(Liste l, Liste acc, Liste* accE);

/* Modifie la liste en entrée en dédoublant les nombres positifs et en supprimant les nombres négatifs*/
void ProcBegaye(Liste *L);

/* initialise une Liste � de liste vide */
void initVideDeVide(ListeDeListe *L);

/* renvoie 1 si la Liste de liste en parametre est vide, 0 sinon */
bool estVideDeVide(ListeDeListe l);

/* renvoie le premier element de la Liste de liste en parametre */
Liste premierDeListe(ListeDeListe l);

/* renvoie une nouvelle Liste de liste correspondant a celle en parametre, avec la liste l ajoute en haut de la pile */
ListeDeListe ajouteDeListe(Liste x, ListeDeListe l);

/* modifie la Liste en parametre: l est ajoutee comme premier element */
void empileDeListe(Liste l, ListeDeListe* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
ListeDeListe suiteDeListe(ListeDeListe l);

/* modifie la Liste en parametre: le premier element est retire */
void depileDeListe(ListeDeListe* l);

/* affichage simple en recursif d'une liste de liste */
void affiche_iterDeListe(ListeDeListe l);

/*Fonctions nécessaires pour déterminer toutes les permutations */
ListeDeListe Concat(ListeDeListe L1, ListeDeListe L2);
ListeDeListe AETTL( int x, ListeDeListe L);
ListeDeListe ATP(int x, Liste L);
ListeDeListe ATLTP(int x, ListeDeListe L);
ListeDeListe Permutations(int n);

/* initialise une ListeBis � de liste vide */
void initVideBis(ListeBis *L);

/* renvoie 1 si la Liste bis en parametre est vide, 0 sinon */
bool estVideBis(ListeBis l);

/* renvoie le premier element de la Liste bis en parametre */
int premierBis(ListeBis l);

/* renvoie une nouvelle Liste de liste correspondant a celle en parametre, avec l element x ajoute en haut de la pile */
ListeBis ajouteBis(int x, ListeBis l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empileBis(int x, ListeBis* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
ListeBis suiteBis(ListeBis l);

/* modifie la Liste en parametre: le premier element est retire */
void depileBis(ListeBis* l);

/* affichage simple en recursif d'une liste de liste */
void affiche_recBis(ListeBis l);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void initVide( Liste *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
}

/*************************************************/
/*                                               */
/*          briques de base de liste             */
/*                de liste                       */
/*                                               */
/*************************************************/

void initVideDeVide( ListeDeListe *L)
{
    *L = NULL ;
}

bool estVideDeVide(ListeDeListe l)
{
    return l == NULL ;
}

Liste premierDeListe(ListeDeListe l)
{
    return l->list ; 
}

ListeDeListe ajouteDeListe(Liste x, ListeDeListe l)
{
    ListeDeListe tmp = (ListeDeListe) malloc(sizeof(BlocDeBLoc)) ;
    cptmallocLDL++;
    tmp->list = x ;
    tmp->suiv = l ;
    return tmp ;
}

void empileDeListe(Liste l, ListeDeListe *L)
{
      *L = ajouteDeListe(l,*L) ; 
}

ListeDeListe suiteDeListe(ListeDeListe l)
{
    return l->suiv ;
}

void depileDeListe(ListeDeListe *L)
{
    ListeDeListe tmp = *L ;
    *L = suiteDeListe(*L) ;
    free(tmp) ;
}

void affiche_recDeListe(ListeDeListe l)
{
    if(estVideDeVide(l))
        printf("\n");
    else
    {
        affiche_rec(premierDeListe(l));
        affiche_recDeListe(suiteDeListe(l));
    }
}

/*************************************************/
/*                                               */
/*         briques de base de liste bis          */
/*                                               */
/*************************************************/

void initVideBis( ListeBis *L)
{
    *L = NULL ;
}

bool estVideBis(ListeBis l)
{
    return l == NULL ;
}

int premierBis(ListeBis l)
{
    return l->nb ; 
}

ListeBis ajouteBis(int x, ListeBis l){
    ListeBis tmp = (ListeBis) malloc(sizeof(BlocBis)) ;
    tmp->nb = x ;
    tmp->suivt = l;
    tmp->pred = &(tmp);
    return tmp ;
}

void empileBis(int x, ListeBis *L)
{
      *L = ajouteBis(x,*L) ; 
}

ListeBis suiteBis(ListeBis l)
{
    return l->suivt ;
}
ListeBis pred(ListeBis l){
    return *l->pred;
}
void depileBis(ListeBis *L)
{
    ListeBis tmp = *L ;
    *L = suiteBis(*L) ;
    free(tmp) ;
}

void affiche_recBis(ListeBis l){
    if(estVideBis(l))
        printf("\n");
    else{
        printf("%d ", premierBis(l));
        affiche_recBis(suiteBis(l));
    }
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

int longueur_iterBis(ListeBis l){
    ListeBis P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivt ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}

/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
      
}

/*************************************************/
/*                                               */
/*       Fonctions partie 2                      */
/*                                               */
/*************************************************/

/* Question 1 */
bool ZeroEnPositionUnouDeuxOuTrois (Liste l)
{
    Liste p = l;
    for (int i = 0; i < 3; i++){
        if (estVide(p)) {
            return FALSE;
        }
        if (premier(p) == 0){
            return TRUE;
        }
        p = suite(p);  
    }
    return FALSE;
}

/* Question 2 */
bool Pluscourte(Liste l1, Liste l2){
    if (estVide(l2)){
        return FALSE;
    } else {
        if (estVide(l1)){
            return TRUE;
        } else {
            return Pluscourte(suite(l1), suite(l2));
        }
    }
    
}

/* Question 3 */
int NombreDe0AvantPositionK(Liste l, int K){ //fonction itérative
    
    Liste p = l;
    int nbre = 0;
    while (K > 0){
        if (estVide(l)) {
        return nbre;
        }
        if (premier(p) == 0){
            nbre ++;
        }
        p = suite(p);
        K--;
    }
    return nbre;

}

int NombreDe0AvantPositionK_rec(Liste l, int K){ //fonction recursive non terminale
    if (estVide(l) || K == 0){
        return 0;
    }
    if (premier(l) == 0){
        return 1 + NombreDe0AvantPositionK_rec(suite(l), K-1);
    } else {
        return NombreDe0AvantPositionK_rec(suite(l), K-1);
    }
}

int Bis_rec(Liste l, int K, int cpt){ //sous-fonction recursive terminale
    if (estVide(l) || K == 0){
        return cpt;
    }
    if (premier(l) == 0){
        return Bis_rec(suite(l), K-1, cpt+1);
    } else{
        return Bis_rec(suite(l), K-1, cpt);
    }
}

int NombreDe0AvantPositionK_sfrec(Liste l, int K){ //fonction utilisant la sous-fonction
    return Bis_rec(l, K, 0);
}

void Bis_proc(Liste l, int K, int *cpt){ //sous-procedure recursive terminale
    if (!(estVide(l)) && K != 0 ){
        if (premier(l) == 0){
            *cpt = *cpt + 1;
            Bis_proc(suite(l),K-1, cpt);
        } else {
            Bis_proc(suite(l), K-1, cpt);
        }
    }

}

int NombreDe0AvantPositionK_sfproc(Liste l, int K){ //fonction utilisant la sous-procedure
    int c = 0;
    Bis_proc(l, K, &c);
    return c;
}

/* Question 4 */
void NombreDe0ApresRetroPositionK_sf(Liste L, int K, int* retropos, int* r){ //sous-fonction avec deux arguments en "out"
    if (L==NULL){
        *retropos=0;
        *r=0;
    }else{
        NombreDe0ApresRetroPositionK_sf(suite(L), K, retropos, r);
        if (*retropos<K && premier(L)==0){
            *r=*r+1 ;
        }
        *retropos=*retropos+1;
    }

}

int NombreDe0ApresRetroPositionK(Liste L, int K){ //surfonction
    int retropos;
    int r;
    NombreDe0ApresRetroPositionK_sf(L, K, &retropos, &r);
    return r;
}

/* Question 5 */
Liste FctBegaye(Liste l){ //fonction recursive non terminale
    if (estVide(l)){
        Liste vide;
        initVide(&vide); 
        return vide; //j'ai essayé de renvoyer "[]" mais ça ne compilait pas
    } else{
        int p = premier(l);
        Liste l1 = FctBegaye(suite(l));
        if (p > 0){
                empile(p, &l1);
                empile(p,&l1);
        }
        return l1;

        }
}

Liste fctBegayeAcc(Liste l, Liste acc, Liste* accE) //sous fonction recursive terminale
{
    if (estVide(l))
    {
        return acc;
    }
    else
    {
        if (premier(l) > 0)
        {
            if (estVide(acc))
            {
                initVide(&acc);
                empile(premier(l), &acc);
                empile(premier(l), &acc);
                accE = &(acc->suivant->suivant);
            }
            else
            {
                empile(premier(l), accE);
                empile(premier(l), accE);
                accE = &((*accE)->suivant->suivant);
            }
        }
        return fctBegayeAcc(suite(l), acc, accE);
    }
}

Liste FctBegayeRec(Liste l)
{
    return fctBegayeAcc(l, NULL, NULL);
}

Liste FctBegayeIT2(Liste l){ //fonction iterative 
    Liste vide;
    initVide(&vide);
    if (estVide(l)){
        return vide;  //idem que pour la fonction recursive
    }
    Liste acc = vide;
    Liste *accE = &acc;
    while (!(estVide(l))){
        if (premier(l) > 0){
            empile(premier(l), accE);
            empile(premier(l), accE);
            accE = &((*accE)->suivant->suivant);

        }
        l = suite(l);
    }
    return acc;
}

/* Question 6 */
void ProcBegaye(Liste *L){ 
    if (estVide(*L)){}
    else{
        int p=premier(*L);
        if (p<=0){
            depile(&(*L));
            ProcBegaye(&(*L));
        }else{ //if premier(L)>0
            empile(p,&(*L));
            ProcBegaye(&(((**L).suivant)->suivant));
        }
    }
}

/*Question 7 */
ListeDeListe Concat(ListeDeListe L1, ListeDeListe L2){
    if (estVideDeVide(L1)){
        return L2;
    }else {
        return ajouteDeListe(premierDeListe(L1), Concat( suiteDeListe(L1), L2));
    }
}

ListeDeListe AETTL( int x, ListeDeListe L){
    if (estVideDeVide(L)){
        return NULL;
    }else {
        cptmallocL++;
        return ajouteDeListe( ajoute(x,premierDeListe(L)), AETTL(x, suiteDeListe(L)));
    }
}

ListeDeListe ATP(int x, Liste L){
    if (estVide(L)){
        ListeDeListe vide;
        initVideDeVide(&vide);
        Liste v;
        initVide(&v);
        cptmallocL++;
        return ajouteDeListe(ajoute(x,v), vide);
    } else {
        cptmallocL++;
        return ajouteDeListe( ajoute(x,L), AETTL(premier(L), ATP(x, suite(L))));
    }
}

ListeDeListe ATLTP(int x, ListeDeListe L){
    if (estVideDeVide(L)){ 
        return NULL;
    } else {
        return Concat (ATP(x,premierDeListe(L)), ATLTP(x, suiteDeListe(L)));
    }
}

ListeDeListe Permutations(int n){
    if (n == 0){
        ListeDeListe vide;
        initVideDeVide(&vide);
        Liste v;
        initVide(&v);
        return ajouteDeListe(v,vide);
    } else {
        return ATLTP(n , Permutations (n-1));
    }
}

/*Question 8 */
//Nous avons essayé de résoudre cette question en implémentant 2 procédures:
//-retire1 prend en argument la liste à modifier et le pointeur vers le champs pred du bloc à retirer
//-retire prend en argument le pointeur uniquement
//aucune de ces 2 procédures ne fonctionne

void retire1(ListeBis *l, ListeBis ***P){ //on arrive à executer le code jusqu'au bout mais ce n'est pas pertinent puisque la liste n'est pas modifiée
    ListeBis suitel=(**l).suivt;
    if (l==NULL){ //on ne fait rien
    }else if (suitel==***P){ //n'est jamais égal, ce qui explique pourquoi la liste n'est jamais modifiée
        ListeBis tmp = ***P;
        suitel = tmp->suivt;
        *(suitel->pred) = (suitel);//ligne où ça plante
        P=NULL;
        free(tmp);
    }else{
        return retire1(&suitel,P);
    }
}

void retire(ListeBis ***P){
    ListeBis tmp = (ListeBis)malloc(sizeof(BlocBis));
    tmp =  ***P;
    **P = &(tmp->suivt);
    (tmp->suivt)->pred = &(tmp->suivt); // produit un seg fault
    free(tmp);
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}

int main(int argc, char** argv)
{
    Liste l ;
    Liste L; 
    Liste l3 ;

        initVide (&l) ;
        initVide (&L);
        initVide (&l3) ;

        //Quelques tests sur liste vide
        /*printf("QUESTION 1\n");
        printf("\nTest 1 : %d \n\n", ZeroEnPositionUnouDeuxOuTrois (l));
        printf("QUESTION 2\n");
        printf("Test court1 : %d \n\n", Pluscourte(l,l3));
        printf("QUESTION 3\n");
        printf("Nbre 0 avant K1 : %d \n\n", NombreDe0AvantPositionK(l, 2));
        printf("Nbre 0 avant K1_rec : %d \n\n", NombreDe0AvantPositionK_rec(l, 2));
        printf("Nbre 0 avant K1_sfrec : %d \n\n", NombreDe0AvantPositionK_sfrec(l, 2));
        printf("Nbre 0 avant K1_sfproc : %d \n\n", NombreDe0AvantPositionK_sfproc(l, 2));
        printf("QUESTION 4\n");
        printf("Nbre 0 apres K=6 : %d \n\n", NombreDe0ApresRetroPositionK(L,6));*/

             empile(4, &l) ;
             empile(0, &l) ;
             empile(-1, &l);
             empile(7, &l);
             empile(-2, &l);
             empile(3, &l);
             printf("\nLa liste l : ");
             affiche_rec(l);
             empile(2, &L);
             empile(0, &L);
             empile(5, &L);
             empile(6, &L);
             empile(9, &L);
             empile(0, &L);
             empile(0, &L);
             empile(0, &L);
             empile(1, &L);
             empile(0, &L);
             printf("\nLa liste L : ");
             affiche_rec(L) ;
             printf("\nQUESTION 1 : ZeroEnPositionUnDeuxOuTrois\n"); //Affichage Question 1
             printf("Test avec l : %d \n", ZeroEnPositionUnouDeuxOuTrois (l));
             printf("Test avec L : %d \n", ZeroEnPositionUnouDeuxOuTrois (L));

             printf("\nQUESTION 2 : PlusCourte\n"); //Affichage Question 2
             printf("Longueur l : %d\n", longueur_rec(l));
             printf("Longueur L : %d\n", longueur_iter(L));
             printf("Teste si l est plus courte que L : %d \n", Pluscourte(l,L));
             printf("Teste si L est plus courte que l : %d \n", Pluscourte(L,l));

             printf("\nQUESTION 3 : NombreDe0AvantpositionK\n"); //Affichage Question 3
             printf("Nbre 0 avant K=2 dans l (iteratif) : %d \n", NombreDe0AvantPositionK(l, 2));
             printf("Nbre 0 avant K=9 dans l (recursive): %d \n", NombreDe0AvantPositionK_rec(l, 9));
             printf("Nbre 0 avant K=6 dans l (sous-fonction recursive): %d \n", NombreDe0AvantPositionK_sfrec(l, 6));
             printf("Nbre 0 avant K=6 dans L (sous-procedure): %d \n", NombreDe0AvantPositionK_sfproc(L, 6));
             
             Liste T;
             initVide(&T);
             empile(3, &T);
             empile(0, &T);
             empile(0, &T);
             empile(5, &T);
             printf("\nQUESTION 4 : NombreDe0apresRetroPositionK\n"); //Affichage Question 4
             printf("Nbre 0 apres K=6 dans L: %d \n", NombreDe0ApresRetroPositionK(L,6));
             printf("Liste T: ");
             affiche_rec(T);
             printf("Nbre 0 apres K=6 dans T: %d \n", NombreDe0ApresRetroPositionK(T,6));
             
             printf("\nQUESTION 5 : Fonctions \"Begaye\"\n"); //Affichage Question 5
             printf("La liste l : ");
             affiche_rec(l);
             printf("Nouvelle liste l creee de maniere recursive non terminale : ");
             affiche_rec(FctBegaye(l));
             printf("Nouvelle liste l creee de maniere iterative : ");
             affiche_rec(FctBegayeIT2(l));
             printf("Nouvelle liste l creee de maniere recursive terminale : ");
             affiche_rec(FctBegayeRec(l));

             printf("\nQUESTION 6\n"); //Affichage Question 6
             printf("La liste l modifiee par la procedure \"ProcBegaye\" : ");
             ProcBegaye(&l);
             affiche_rec(l);

             printf("\nQUESTION 7 : Permutations\nEnsemble des permutations pour n=4\n"); //Affichage Question 7
             affiche_recDeListe(Permutations(4)); //A partir de n=9 la fuite de mémoire devient trop importante pour que le code s'execute jusqu'au bout
             printf("Le compteur de malloc de Liste : %d \n", cptmallocL ); //On a essayé de la limiter en rendant de l'espace mémoire mais on n'a pas réussi à obtenir un meilleur résultat
             printf("Le compteur de malloc de Liste De Liste : %d \n", cptmallocLDL );

             printf("\nQUESTION 8 : Procedure sur ListesBis\n"); //Affichage Question 8 -> ne fonctionne pas
             ListeBis l8; //Création de la listeBis sur laquelle on veut appeler notre procédure
             initVideBis(&l8);
             for (int i=4;i>0;i--){
                empileBis(i,&l8);
             }
             printf("Liste avant d'appeler la procedure:  ");
             affiche_recBis(l8);
             printf("Liste apres l'appel de la procedure sur le pointeur vers '3':  ");
             ListeBis ***P = (ListeBis***) malloc(sizeof(BlocBis));
             *P=&(l8->suivt->suivt->pred); //le pointeur ainsi declaré devrait pointer vers le bloc de valeur 3, on soupçonne une mauvaise implémentation/utilisation du champs 'pred'
             retire(P); //ligne à partir de laquelle le code plante
             affiche_recBis(l8);

            //Tests supplémentaires effectués:
             /*empile(5, &l) ;
             empile(6, &l) ;
             //QUESTION 1
             printf("Test 3 : %d \n\n", ZeroEnPositionUnouDeuxOuTrois (l));
             empile(0, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(0, &l) ;
             empile(9, &l) ;
             printf("Test 4 : %d \n\n", ZeroEnPositionUnouDeuxOuTrois (l));
             empile(0, &l);
             poup(l);
             //QUESTION 3
             printf("Nbre 0 avant K=9 (itérative): %d \n\n", NombreDe0AvantPositionK(l, 9));
             printf("Nbre 0 avant K=9 (récursive): %d \n\n", NombreDe0AvantPositionK_rec(l, 9));
             printf("Nbre 0 avant K=9 (avec sous-fonction récursive): %d \n\n", NombreDe0AvantPositionK_sfrec(l, 9));
             printf("Nbre 0 avant K=9 (avec sous-procédure): %d \n\n", NombreDe0AvantPositionK_sfproc(l, 9));
             //QUESTION 4 (test avec une liste remplie de zéros)
             Liste t;
             initVide (&t);
             empile(0, &t);
             empile(0, &t);
             empile(0, &t);
             empile(0, &t);
             empile(0, &t);
             poup(t);
             printf("Nbre 0 apres K=1 : %d \n\n", NombreDe0ApresRetroPositionK(t,1));
             printf("Nbre 0 apres K=2 : %d \n\n", NombreDe0ApresRetroPositionK(t,2));
             printf("Nbre 0 apres K=3 : %d \n\n", NombreDe0ApresRetroPositionK(t,3));
             printf("Nbre 0 apres K=4 : %d \n\n", NombreDe0ApresRetroPositionK(t,4));*/
        /*VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

    VideListe(&l);*/
    return 0;
}






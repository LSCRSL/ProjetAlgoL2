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

/*Définition du type image*/
typedef struct bloc_image
    { bool toutnoir ;
    struct bloc_image * fils[4] ;
    } bloc_image ;
typedef bloc_image *image ;

/*Definition du type img pour la question 12*/
typedef struct bloc_img{ 
    bool toutnoir ;
    bool toutblanc ;
    int n ; //nombre d'images noires contenues dans l'image
    struct bloc_img * fils[4] ;
    } 
    bloc_img ;
typedef bloc_img *img ;

/*************************************************/
/*                                               */
/*   Déclarations des fonctions & procédures     */
/*                                               */
/*************************************************/

/*Question 1*/
/*Qui rend une image blanche a partir de rien*/
image Construit_Blanc();
/*Qui rend une image noire a partir de rien*/
image Construit_Noir();
/*Qui construit une image composee des sous-images i0,...,i3*/
image Construit_Composee(image i0,image i1,image i2,image i3);

/*Question 2*/
/*sous-procédure pour l'affichage normale*/
void BisAN(image i);
/*procédure pour l'affichage normal*/
void Affichage_normal(image i);
/*sous-procédure pour l'affichage mode profondeur*/
void BisAP(image i, int d);
/*procédure pour l'affichage normal*/
void Affichage_profondeur(image i);

/*Question 3*/
/*sous-fonction permettant de construire l'image
 à partir des caractères lus dans le terminal*/
image Lbis(char string[], int *i);
/*lit l'arbre qui est donné dans le terminal*/
image Lecture();

/*Question 4*/
/*rend vrai si l'image est blanche*/
bool EstBlanche(image i);
/*rend vrai si l'image est noire*/
bool EstNoire(image i);

/*Question 5*/
image Diagonale(int p);

/*Question 6*/
image QuartDeTour(image i);

/*Question 7*/
void Negatif(image *i);

/*Question 8*/
void SimplifieProfP(image *i, int p);

/*Question 9*/
bool Incluse(image i, image img);

/*Question 10*/
/*renvoie le maximum entre 2 valeurs*/
int max(int a, int b); 
/*Sous-fonction avec le résultat h en 'out'*/
void hauteur(image si, int *h);
/*Sur-fonction*/
int HautMaxblanc(image i);

/*Question 11*/ 
/*calcule 2^n, r est le résultat*/
int pow2(int n, int r);
/*sous-procédure*/
void pixel(image *i, int P, int x, int y);
/*procédure*/
void BlanchitProfP(image *i, int P, int x, int y);

/*Question 12*/
/*Fonstions et procédures pour le type img:*/
/*Qui rend une image blanche a partir de rien*/
img Construit_Blanc2();
/*Qui rend une image noire a partir de rien*/
img Construit_Noir2();
/*Qui construit une image composee des sous-images i0,...,i3*/
img Construit_Composee2(img i0,img i1,img i2,img i3);
/*sous-procédure pour l'affichage normale*/
void BisAN2(img i);
/*procédure pour l'affichage normal*/
void Affichage_normal2(img i);
/*rend vrai si l'image est blanche*/
bool EstBlanche2(img i);
/*rend vrai si l'image est noire*/
bool EstNoire2(img i);
/*Simplifie pour le type img*/
void SimplifieProfP2(img *i, int p);
/*objectif: faire agir la gravité entre 2 images: */
/*echange les cases en bas du carré supérieur avec les cases en haut du carré inférieur
 s'il y a plus de cases noires au-dessus*/
void echange(img *f0, img *f1, img *f2, img *f3);
/*idem mais implémentation différente:
 echange et echange 2 ne donnent pas les mêmes résultats*/
void echange2(img *f0, img *f1, img *f2, img *f3);
/*fait agir la gravité au sein d'une image*/
void tombe(img *i, int nb);
/*sur-fonction*/
img Chute(img i); //ne fonctionne pas bien sur l'exemple de l'énoncé


/*************************************************/
/*                                               */
/*            fonctions & procédures             */
/*                                               */
/*************************************************/

/*Question 1*/
image Construit_Blanc(){
    return NULL;
}

image Construit_Noir(){
    image n = (image)malloc(sizeof(bloc_image));
    n->toutnoir = TRUE;
    n->fils[0] = NULL;
    n->fils[1] = NULL;
    n->fils[2] = NULL;
    n->fils[3] = NULL;
    return n;
}

image Construit_Composee(image i0, image i1, image i2, image i3){
    image c = (image)malloc(sizeof(bloc_image));
    c->toutnoir = FALSE;
    c->fils[0] = i0;
    c->fils[1] = i1;
    c->fils[2] = i2;
    c->fils[3] = i3;
    return c;

}

/*Question 2*/
/*Affichage mode normal*/
void BisAN(image i){ 
    if (i == NULL){
        printf("B");
    } else {
        if (i->toutnoir){
            printf("N");
        } else {
            printf("(");
            for (int k = 0; k<4; k++){
                BisAN(i->fils[k]);
            }
            printf(")");
        }
    }
}

void Affichage_normal(image i){
    BisAN(i);
    printf("\n");
}

/*Affichage mode profondeur*/
void BisAP(image i, int d){
      if (i == NULL){
        printf("B%d ",d);
    } else {
        if (i->toutnoir){
            printf("N%d ",d);
        } else {
            printf("(");
            d++;
            for (int k = 0; k<4; k++){
                BisAP(i->fils[k], d);
            }
            printf(")");
        }
    }
}

void Affichage_profondeur(image i){
    int d = 0;
    BisAP(i, d);
    printf("\n");
}


/*Question 3*/ 
/*sous-procédure permettant de déterminer les sous-arbres*/
image Lbis(char string[], int *i){ 
    char car=string[*i];
    if (car=='N'){
        (*i)++;
        return Construit_Noir();
    }else if (car=='B'){
        (*i)++;
        return Construit_Blanc();
    }else if (car=='('){
        (*i)++;
        image f0= Lbis(string, i);
        image f1= Lbis(string, i);
        image f2= Lbis(string, i);
        image f3= Lbis(string, i);
        car=string[*i];
        if (car!=')'){
            printf("Erreur: veuillez entrer 4 sous images par image.\n");
            return Lecture();
        }else{
            (*i)++;
            return Construit_Composee(f0,f1,f2,f3);
        }
    }if (car==')'){
            printf("Erreur: veuillez entrer 4 sous images par image.\n");
            return Lecture();
    }else{
        printf("Erreur: veuillez entrer des caracteres parmi \"(\", \")\",\"N\" et \"B\".\n"); 
             //Si un autre caratère est entré, on suppose que l'arbre donné est faux
        return Lecture();
    }
}

image Lecture(){ 
    printf("Ecrire l'arbre desire :");
    char arbre[51]; //On suppose que l'arbre entré n'est pas plus grand que 50 caractères
    scanf("%s",arbre);
    if (arbre[0]==')'){
        printf("Erreur: l'arbre doit necessairement commencer par \"(\",\"N\" ou \"B\".\n");
        return Lecture();
    }else{
        int i=0;
        return Lbis(arbre, &i);
    }
}



/*Question 4*/
bool EstBlanche(image i){
    if (i == NULL){
        return TRUE;
    } else {
        if (i->toutnoir){
            return FALSE;
        } else {
            return (EstBlanche(i->fils[0]) && EstBlanche(i->fils[1])
            && EstBlanche(i->fils[2]) && EstBlanche(i->fils[3]));
        }
    }
}

bool EstNoire(image i){
    if (i == NULL){
        return FALSE;
    } else {
        if (i->toutnoir){
            return TRUE;
        } else {
            return (EstNoire(i->fils[0]) && EstNoire(i->fils[1]) 
            && EstNoire(i->fils[2]) && EstNoire(i->fils[3]));
        }
    }
}

/*Question 5*/
image Diagonale(int p){
    if (p == 0){
        return Construit_Noir();
    } else {
        return Construit_Composee(Diagonale(p-1), Construit_Blanc(),
         Construit_Blanc(), Diagonale(p-1));
    }
}

/*Question 6*/
image QuartDeTour(image i){
    if (i == NULL){
        return i;
    }else { 
        if (i->toutnoir){
        return Construit_Noir();
        } else {
            return Construit_Composee(QuartDeTour(i->fils[2]), QuartDeTour(i->fils[0]),
            QuartDeTour(i->fils[3]), QuartDeTour(i->fils[1]));
        }
    }

}

/*Question 7*/
void Negatif(image *i){
    if ((*i) == NULL){
        *i = Construit_Noir();
    } else if ((**i).toutnoir){
            *i = Construit_Blanc(); 
    } else {
            Negatif(&((**i).fils[0]));
            Negatif(&((**i).fils[1]));
            Negatif(&((**i).fils[2]));
            Negatif(&((**i).fils[3]));
    }
}

/*Question 8*/
void SimplifieProfP(image *i, int p){
    if ((*i) != NULL && !(*i)->toutnoir){
        if (p == 0){
            if (EstNoire(*i)){
                *i = Construit_Noir();
            }
            if (EstBlanche(*i)){
                *i = Construit_Blanc();
            }  
        } else {
            SimplifieProfP(&(**i).fils[0], p-1);
            SimplifieProfP(&(**i).fils[1], p-1);
            SimplifieProfP(&(**i).fils[2], p-1);
            SimplifieProfP(&(**i).fils[3], p-1);
        }
    } 
}

/*Question 9*/
bool Incluse(image i, image img){
    if (EstBlanche(i)|| EstNoire(img)){
        return TRUE;
    }if (i->toutnoir){
        return FALSE;
    }else {
        if (EstBlanche(img)){
            return Incluse(i->fils[0], img) && Incluse(i->fils[1], img) &&
             Incluse(i->fils[2], img) && Incluse(i->fils[3], img);
        } else {
            return Incluse(i->fils[0], img->fils[0]) &&
             Incluse(i->fils[1], img->fils[1]) && Incluse(i->fils[2], img->fils[2]) &&
              Incluse(i->fils[3], img->fils[3]);
        }
    }
}

/*Question 10*/
int max(int a, int b){ //Fonction qui renvoie la plus grande valeur
    if (a>=b){
        return a;
    }else{
        return b;
    }
}

void hauteur(image si, int *h){ //Sous-fonction avec le résultat h en 'out'
    if (si==NULL){ //Cas de base: si l'image est une feuille blanche ou noire
        (*h)=0;
    }else if (si->toutnoir){ 
        (*h)=-1;
    }else{ 
        int h0, h1, h2, h3;
        hauteur(si->fils[0], &h0);
        hauteur(si->fils[1], &h1);
        hauteur(si->fils[2], &h2);
        hauteur(si->fils[3], &h3);
        (*h)=max(max(h0,h1), max(h2, h3));
        if (EstBlanche(si)){
            (*h)++;
        }
    }
}

int HautMaxblanc(image i){ //Sur-fonction
    int h;
    hauteur(i, &h);
    return h;
}

/*Question 11*/
int pow2(int n, int r){ //calcule 2^n, r est le résultat
    if (n<=0){
        return r;
    }else{
        return pow2(n-1, r*2);
    }
}

void pixel(image *i, int P, int x, int y){ //sous-procédure
    if (P==1){
        if (x==0){
            if (y==0){
                (**i).fils[2]=Construit_Blanc();
            }else{
                (**i).fils[0]=Construit_Blanc();
            }
        }else{
            if (y==0){
                (**i).fils[3]=Construit_Blanc();
            }else{
                (**i).fils[1]=Construit_Blanc();
            }
        }
    }else{
        image n=Construit_Noir();
        image n4=Construit_Composee(n,n,n,n);
        if (y>P){
            if (x<=P){
                if ( EstBlanche((**i).fils[0]) ){ //Ne rien faire
                }else if (EstNoire((**i).fils[0])){
                    (**i).fils[0]=n4;
                }
                pixel(&(**i).fils[0],P-1,x,y-P);
            }else{
                if ( EstBlanche((**i).fils[1])){ //Ne rien faire
                }else if (EstNoire((**i).fils[1])){
                    (**i).fils[1]=n4;
                }
                pixel(&(**i).fils[1],P-1,x-P,y-P);
                }
        }else{
            if (x<=P){
                if ( EstBlanche((**i).fils[2]) ){ //Ne rien faire
                }else if (EstNoire((**i).fils[2])){
                    (**i).fils[2]=n4;
                }
                pixel(&(**i).fils[2],P-1,x,y);
            }else{
                if ( EstBlanche((**i).fils[3]) ){ //Ne rien faire
                }else if (EstNoire((**i).fils[3])){
                    (**i).fils[3]=n4;
                }
                pixel(&(**i).fils[3],P-1,x-P,y);
            }
        }
    }
}

void BlanchitProfP(image *i, int P, int x, int y){
    int xmax=pow2(P,1)-1;
    int ymax=pow2(P,1)-1;
    if (x<0 || x>xmax || y<0 || y>ymax){
        printf("Coordonnee invalide.\n");
    }else{
        pixel(i,P,x,y);
    }
}

/*Question 12*/
//Briques de bases pour le type img
img Construit_Blanc2(){
    img n = (img)malloc(sizeof(bloc_img));
    n->toutblanc = TRUE;
    n->toutnoir = FALSE;
    n->fils[0] = NULL;
    n->fils[1] = NULL;
    n->fils[2] = NULL;
    n->fils[3] = NULL;
    n->n = 0;
    return n;
}

img Construit_Noir2(){
    img n = (img)malloc(sizeof(bloc_img));
    n->toutnoir = TRUE;
    n->toutblanc = FALSE;
    n->fils[0] = NULL;
    n->fils[1] = NULL;
    n->fils[2] = NULL;
    n->fils[3] = NULL;
    n->n = 1;
    return n;
}

img Construit_Composee2(img i0, img i1, img i2, img i3){
    img c = (img)malloc(sizeof(bloc_img));
    c->toutnoir = FALSE;
    c->toutblanc = FALSE;
    c->fils[0] = i0;
    c->fils[1] = i1;
    c->fils[2] = i2;
    c->fils[3] = i3;
    int n0 = i0->n;
    int n1 = i1->n;
    int n2 = i2->n;
    int n3 = i3->n;
    int nt = n0+n1+n2+n3;
    c->n = nt;
    return c;
}

/*Affichage mode normal pour type img*/
void BisAN2(img i){ 
    if (i->toutblanc){
        printf("B");
    } else {
        if (i->toutnoir){
            printf("N");
        } else {
            printf("(");
            for (int k = 0; k<4; k++){
                BisAN2(i->fils[k]);
            }
            printf(")");
        }
    }
}

void Affichage_normal2(img i){
    BisAN2(i);
    printf("\n");
}

bool EstBlanche2(img i){
    if (i->toutblanc){
        return TRUE;
    } else if (i->toutnoir){
        return FALSE;
    } else {
        return (EstBlanche2(i->fils[0]) && EstBlanche2(i->fils[1]) &&
    EstBlanche2(i->fils[2]) && EstBlanche2(i->fils[3]));
    }
}

bool EstNoire2(img i){
    if (i->toutblanc){
        return FALSE;
    } else if (i->toutnoir){
            return TRUE;
    } else {
        return (EstNoire2(i->fils[0]) && EstNoire2(i->fils[1]) &&
    EstNoire2(i->fils[2]) && EstNoire2(i->fils[3]));
    }
}

void SimplifieProfP2(img *i, int p){
    if (!(**i).toutblanc && !(**i).toutnoir){
        if (p == 0){
            if (EstNoire2(*i)){
                *i = Construit_Noir2();
            }
            if (EstBlanche2(*i)){
                *i = Construit_Blanc2();
            }  
        } else {
            SimplifieProfP2(&(**i).fils[0], p-1);
            SimplifieProfP2(&(**i).fils[1], p-1);
            SimplifieProfP2(&(**i).fils[2], p-1);
            SimplifieProfP2(&(**i).fils[3], p-1);
        }
    }   
}
// Fin des briques de base

void echange(img *f0, img *f1, img *f2, img *f3){
    img N=Construit_Noir2();
    img B=Construit_Blanc2();
    img NNNN=Construit_Composee2(N,N,N,N);
    img BBBB=Construit_Composee2(B,B,B,B);
    if ((*f0)->toutnoir){
        *f0=NNNN;
    }else if((*f0)->toutblanc){
        *f0=BBBB;
    }
    if ((*f1)->toutnoir){
        *f1=NNNN;
    }else if((*f1)->toutblanc){
        *f1=BBBB;
    }
    if ((*f2)->toutnoir){
        *f2=NNNN;
    }else if((*f2)->toutblanc){
        *f2=BBBB;
    }
    if ((*f3)->toutnoir){
        *f3=NNNN;
    }else if((*f3)->toutblanc){
        *f3=BBBB;
    }
    if ((*f0)->fils[2]->n > (*f2)->fils[0]->n){
        img tmp=(*f0)->fils[2];
        *f0=Construit_Composee2((**f0).fils[0],(**f0).fils[1],(*f2)->fils[0], (*f0)->fils[3]);
        *f2=Construit_Composee2(tmp,(*f2)->fils[1],(**f2).fils[2],(**f2).fils[3]);
    }
    if ((*f1)->fils[2]->n > (*f3)->fils[0]->n){
        img tmp=(*f1)->fils[2];
        *f1=Construit_Composee2((**f1).fils[0],(**f1).fils[1], (*f3)->fils[0],(*f1)->fils[3]);
        *f3=Construit_Composee2(tmp,(*f3)->fils[1],(**f3).fils[2],
        (**f3).fils[3]);
    }
    if ( (*f0)->fils[3]->n > (*f2)->fils[1]->n){
        img tmp=(*f0)->fils[3];
        *f0=Construit_Composee2((**f0).fils[0],(**f0).fils[1],(*f0)->fils[2],(*f2)->fils[1]);
        *f2=Construit_Composee2((*f2)->fils[0],tmp,(**f2).fils[2],(**f2).fils[3]);
    }
    if ((*f1)->fils[3]->n > (*f3)->fils[1]->n){
        img tmp=(*f1)->fils[3];
        *f1=Construit_Composee2((**f1).fils[0],(**f1).fils[1],(*f1)->fils[2],(*f3)->fils[1]);
        *f3=Construit_Composee2((*f3)->fils[0],tmp,(**f3).fils[2],(**f3).fils[3]);
    }
    SimplifieProfP2(f0,0);
    SimplifieProfP2(f1,0);
    SimplifieProfP2(f2,0);
    SimplifieProfP2(f3,0);
}
/*2ème implémentation, donne des résultats différents*/
void echange2(img *f0, img *f1, img *f2, img *f3){ 
    img N=Construit_Noir2();
    img B=Construit_Blanc2();
    img NNNN=Construit_Composee2(N,N,N,N);
    img BBBB=Construit_Composee2(B,B,B,B);
    bool bf1=(*f1)->toutblanc || (*f1)->toutnoir;
    bool bf0=(*f0)->toutblanc || (*f0)->toutnoir;
    bool bf2=(*f2)->toutblanc || (*f2)->toutnoir;
    bool bf3=(*f3)->toutblanc || (*f3)->toutnoir;
    if (!(bf0) && !(bf2) && (*f0)->fils[2]->n > (*f2)->fils[0]->n){
        img tmp=(*f0)->fils[2];
        *f0=Construit_Composee2((**f0).fils[0],(**f0).fils[1],(*f2)->fils[0], (*f0)->fils[3]);
        *f2=Construit_Composee2(tmp,(*f2)->fils[1],(**f2).fils[2],(**f2).fils[3]);
    }
    if (!bf1 && !bf3 && (*f1)->fils[2]->n > (*f3)->fils[0]->n){
        img tmp=(*f1)->fils[2];
        *f1=Construit_Composee2((**f1).fils[0],(**f1).fils[1],(*f3)->fils[0],(*f1)->fils[3]);
        *f3=Construit_Composee2(tmp,(*f3)->fils[1],(**f3).fils[2],(**f3).fils[3]);
    }
    if ( !bf0 && !bf2 && (*f0)->fils[3]->n > (*f2)->fils[1]->n){
        img tmp=(*f0)->fils[3];
        *f0=Construit_Composee2((**f0).fils[0],(**f0).fils[1],(*f0)->fils[2],(*f2)->fils[1]);
        *f2=Construit_Composee2((*f2)->fils[0],tmp,(**f2).fils[2],(**f2).fils[3]);
    }
    if (!bf1 && !bf3 && (*f1)->fils[3]->n > (*f3)->fils[1]->n){
        img tmp=(*f1)->fils[3];
        *f1=Construit_Composee2((**f1).fils[0],(**f1).fils[1],(*f1)->fils[2],(*f3)->fils[1]);
        *f3=Construit_Composee2((*f3)->fils[0],tmp,(**f3).fils[2],(**f3).fils[3]);
    }
    SimplifieProfP2(f0,0);
    SimplifieProfP2(f1,0);
    SimplifieProfP2(f2,0);
    SimplifieProfP2(f3,0);
}

void tombe(img *i, int nb){
    if ((*i)->toutblanc){ //si l'image est B
        nb=0;
    }else if ((*i)->toutnoir){ //si l'image est N
        nb=1;
    }else{
        img hg=(**i).fils[0];
        img hd=(**i).fils[1];
        img bg=(**i).fils[2];
        img bd=(**i).fils[3];
        int nbhd, nbhg, nbbd, nbbg;
        tombe(&hg,nbhg); 
        tombe(&hd,nbhd);
        tombe(&bg,nbbg);
        tombe(&bd,nbbd);
        if (nbhg>nbbg){
            img tmp=bg;
            bg=hg;
            hg=tmp;
        }
        if (nbhd>nbbd){
            img tmp=bd;
            bd=hd;
            hd=tmp;
        }
        echange(&hg,&hd,&bg,&bd);
        echange(&hg,&hd,&bg,&bd);
        nb=nbhd+nbhg+nbbd+nbbg;
        *i=Construit_Composee2(hg,hd,bg,bd);
    }
}

img Chute(img i){
    img ir=i;
    int nb;
    tombe(&ir, nb);
    return ir;
}

/*************************************************/
/*                                               */
/*                  TESTS                        */
/*                                               */
/*************************************************/

int main(){
    //Question 1
    image b = Construit_Blanc();
    image n = Construit_Noir();
    image cb = Construit_Composee(b,b,b,b);
    image cn = Construit_Composee(n,n,n,n);
    image cc = Construit_Composee(b,n,b,n);
    //creation de l'image dans le sujet partie affichage
    image c1 = Construit_Composee(n,b,n,n);
    image c2 = Construit_Composee(n,n,b,c1);
    image c3 = Construit_Composee(n,c2,b,n);
    image c4 = Construit_Composee(b,b,n,b);
    image c5 = Construit_Composee(n,c4,b,c3); //image finale
    image tn = Construit_Composee(cn,cn,cn,cn);
    image tb = Construit_Composee(cb,b,cb,cb);
    //image cc = Construit_Composee(b,c,n,c1);
    /*Affichage_normal(b);
    Affichage_normal(n);
    Affichage_normal(c);
    Affichage_normal(c1);*/

    printf("\nQUESTION 2 :\n");
    printf("Affichage classique : \n");
    Affichage_normal(c5);
    printf("\nAffichage en profondeur : \n");
    Affichage_profondeur(c5);

    printf("\nQUESTION 3 :\n");
    image l=Lecture();
    printf("Verification que l'arbre construit correspond a l'arbre entre dans le terminal: ");
    Affichage_normal(l);

    printf("\nQUESTION 4 :\n");
    printf("Test de la fonction EstNoire\nVerifie que l'image suivante est noire (1): ");
    Affichage_normal(tn);
    printf("%d\n", EstNoire(tn));
    printf("Verifie que l'image suivante n'est pas noire (0): ");
    Affichage_normal(c1);
    printf("%d\n", EstNoire(c1));
    printf("Test de la fonction EstBlanche\nVerifie que l'image suivante est blanche (1): ");
    Affichage_normal(tb);
    printf("%d\n", EstBlanche(tb));
    printf("Verifie que l'image suivante n'est pas blanche (0): ");
    Affichage_normal(c5);
    printf("%d\n", EstBlanche(c5));

    printf("\nQUESTION 5 :\nConstruit une image de profondeur 3 avec une diagonale noire: ");
    image d = Diagonale(3);
    Affichage_normal(d);

    printf("\nQUESTION 6 : \nL'image: ");
    image z = Construit_Composee(b,n,n,n);
    image y = Construit_Composee(n,n,b,b);
    image a = Construit_Composee(z,b,y,n);
    Affichage_normal(a);
    printf("devient apres le quart de tour : \n");
    Affichage_normal(QuartDeTour(a));

    printf("\nQUESTION7 : \n");
    printf("L'image : \n");
    Affichage_normal(a);
    Negatif(&a);
    printf("apres avoir ete transformee en son negatif devient: ");
    Affichage_normal(a);

    printf("\nQUESTION8 : \nL'image: ");
    image a1 = Construit_Composee(b,b,cb,b);
    image a2 = Construit_Composee(n,b,n, cb);
    image a3 = Construit_Composee(n,b,n,a2);
    image a4 = Construit_Composee(n,n,cn,n);
    image a5 = Construit_Composee(n,b,a4,b);
    image finale = Construit_Composee(n,a5,a3,a1);
    Affichage_normal(finale);
    printf("devient apres simplification a la profondeur 2: ");
    SimplifieProfP(&finale, 2);
    Affichage_normal(finale);

    printf("\nQUESTION9 : \n");
    image b1 = Construit_Composee(cb,n,b,n);
    image b2 = Construit_Composee(b,b,n,n);
    image b3 = Construit_Composee(n,b,b,n);
    image b4 = Construit_Composee(b2, b,b ,b3);
    image b5  = Construit_Composee(b1, b, n ,b4);
    image d1 = Construit_Composee(b,n,n,n);
    image d2 = Construit_Composee(b,b,n,b);
    image d4 = Construit_Composee(n,n,n,b);
    image d5 = Construit_Composee(n,b,b,d4);
    image d6 = Construit_Composee(d1, d2, cn, d5);
    //permet de verifier que ca renvoit true si le dernier pixel est un N
    image d7 = Construit_Composee(n, b,b,cn);
    image d8 = Construit_Composee(d1,d2,cn,d7);
    printf("Verifie que l'image: ");
    Affichage_normal(d8);
    printf("est incluse dans: ");
    Affichage_normal(b5);
    bool p0 = Incluse(b5, d8);
    printf("La fonction Incluse renvoie %d.\n\n", p0);
    printf("Verifie que l'image: ");
    Affichage_normal(d6);
    printf("n'est pas incluse dans: ");
    Affichage_normal(b5);
    bool p = Incluse(b5, d6);
    printf("La fonction Incluse renvoie %d.\n\n", p);

    printf("\nQUESTION 10:\nArbre 1:");
    image q10=Construit_Composee(cb,n,cc,
    Construit_Composee(n,b,n, Construit_Composee(n,b,
    Construit_Composee(b,b,cb,Construit_Composee(b,b,b,cb)),n)));
    Affichage_normal(q10);
    printf("Hauteur Max Blanc de l'arbre 1: %d (doit renvoyer 3)\nArbre 2:", HautMaxblanc(q10));
    Affichage_normal(n);
    printf("Hauteur Max Blanc de l'arbre 2: %d (doit renvoyer -1)\nArbre 3:", HautMaxblanc(n));
    Affichage_normal(b);
    printf("Hauteur Max Blanc de l'arbre 3: %d (doit renvoyer 0)\nArbre 4:", HautMaxblanc(b));
    image t101=Construit_Composee(Construit_Composee(cb,b,b,b),b,b,b);
    Affichage_normal(t101);
    printf("Hauteur Max Blanc de l'arbre 4: %d (doit renvoyer 3)\nArbre 5:", HautMaxblanc(t101));
    image t102=Construit_Composee(d4,n,n,Construit_Composee(Construit_Composee(cb,n,n,n),n,n,n));
    Affichage_normal(t102);
    printf("Hauteur Max Blanc de l'arbre 5: %d (doit renvoyer 1)\n", HautMaxblanc(t102));

    printf("\nQUESTION 11:\n");
    image nbnb= Construit_Composee(n,b,n,b);
    printf("La procedure transforme (NBNB) en: ");
    BlanchitProfP(&nbnb,2,1,3);
    Affichage_normal(nbnb);
    image q11=Construit_Composee(Construit_Composee(n,Construit_Composee(n,b,n,n),n,n),b,n,b);
    printf("La procedure transforme ((N(NBNN)NN)BNB) en: ");
    BlanchitProfP(&q11,2,1,3);
    Affichage_normal(q11);

    printf("\nQUESTION 12:\n");
    img N=Construit_Noir2();
    img B=Construit_Blanc2();
    img NBNN=Construit_Composee2(N,B,N,N);
    img BNBN=Construit_Composee2(B,N,B,N);
    img NBBN=Construit_Composee2(N,B,B,N);
    img BNNN=Construit_Composee2(B,N,N,N);
    img NBNB=Construit_Composee2(N,B,N,B);
    img NBBB=Construit_Composee2(N,B,B,B);
    img NNBB=Construit_Composee2(N,N,B,B);
    img t12=Construit_Composee2(NNBB,NNBB,NNBB,NNBB);
    img q12=Construit_Composee2(N,Construit_Composee2(NBNN,N,B,BNBN),
    Construit_Composee2(N,NBBN,BNNN,NBNB), Construit_Composee2(N,N,NBBB,BNBN));
    printf("Suite a la chute, l'image: ");
    Affichage_normal2(t12);
    printf("devient: ");
    img res=Chute(t12);
    Affichage_normal2(res); //C'est le résultat attendu
    printf("Suite a la chute, l'image: ");
    Affichage_normal2(q12);
    printf("devient: ");
    img res2=Chute(q12);
    Affichage_normal2(res2); //Ce n'est pas résultat attendu
}
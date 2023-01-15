#include <stdio.h>
#include <stdlib.h>

/* Sucre syntaxique */
#define ISNOT != 
#define NOT ! 
#define AND && 
#define OR || 
#define then 
typedef enum { false, true } bool;

/*Question 1*/

double somme_e(){ //calcule e, soit la somme de 1/n! pour n allant de 0 à 9
    double s=1.0; //valeur de 1/0!
    double r=1.0;
    for (int i=1;i<10;i++){ //on calcule la somme pour n allant de 1 à 9 car au-delà la valeur affichée reste la même
        r=r*(1.0/i);
        s=s+r;
    }
    return s;
}

/*Question 2*/

void Affiche_premiers_termes(){
    double en=somme_e()-1.0;  //Quand la valeur de départ est un double, la suite décroit moins vite
    printf("e_0=%f\n",en);
    for (int i=1;i<50;i++){
        en=i*en-1.0;
        printf("e_%d=%f\n",i,en);
    }
    printf("\n");
}

/*Question 3*/
//CODE 1 -> rame et s'arrête au 4eme terme
float power1(float x, int n){
    if (n==0){
        return 1;
    } else if (n>0){
        return power1(x, n-1) * x;
    }else{
        return power1(x,n+1)/x;
    }
}
//CODE 2 -> rame beaucoup au debut, puis affiche les termes
float power2(float x, int n){
    float r=1;
    if (n >=0){
        for(int i=1;i<=n;i++){
        r=r*x;
        }
    }else{
        for(int i=n;i<0;i++){
            r=r/x;
        }
    }
    return r;
}
//CODE 3 -> affiche les 4 premiers termes, puis s'arrête
void pow3(float x, int n, float* r){
    if (n==0){} else {
        *r=*r*x;
        pow3(x,n-1,r);
    }
}

float power3(float x, int n){
    float r=1;
    pow3(x,n,&r);
    return r;
}

//CODE 4 -> affiche les 4 premiers termes, puis s'arrête
float pow4(float x, int n, float r){
    if (n==0){
        return r;
    }else{
        return pow4( x, n-1, r*x);
    }
}

float power4(float x, int n){
    return pow4(x,n,1);
}

//CODE 5 -> rame beaucoup, puis donne des résultats légèrment plus grand que le CODE 2 puis rame
float power5(float x, int n){
    if (n==0){
        return 1;
    }else{
        if (n%2==0){
            return power5(x,n/2)*power5(x,n/2);
        }else{
            return power5(x,n/2)*power5(x,n/2)*x;
        }
    }
}
//CODE 6 -> très rapide, donne le même résultat que le CODE 5
float power6(float x, int n){
    if (n==0){
        return 1;
    }else{
        float y=power6(x, n/2);
        if (n%2==0){
            return y*y;
        }else{
            return y*y*x;
        }
    }
}
//CODE 7 -> idem CODE 6
float power7(float x, int n){
    if (n==0){
        return 1;
    } else {
        if (n%2==0){
            return power7(x*x,n/2);
        } else {
            return power7(x*x,n/2)*x;
        }
    }
}
//CODE 8  ->idem CODE 6
float pow8(float x, int n, float r){
    if (n==0){
        return r;
    }else{
        if (n%2==0){
            return pow8(x*x,n/2,r);
        }else{
            return pow8(x*x,n/2,r*x);
        }
    }
}

float power8(float x, int n){
    return pow8(x,n,1);
}

//CODE 9 ->idem CODE 6
void pow9(float x, int n, float* r){
    if (n==0) {} else {
        if (n%2==1){
            *r=(*r)*x;
        }
        pow9(x*x,n/2,r);
    }
}

float power9(float x, int n){
    float r=1;
    pow9(x,n,&r);
    return r;
}

//CODE 10 -> IDEM CODE 6
float power10(float x, int n){
    float r=1;
    while (n!=0){
        if (n%2==1){
            r=r*x;
        }
        n=n/2;
        x=x*x;
    }
    return r;
}

//code pour afficher les termes de la suite (1+1/N)^N pour N des puissances de 10 croissantes
void affiche_suite(){
    double i=10;
    while (i<=1000000000000){
        printf("s_%f=%f  \n",i,power10(1+(1/i),i));
        i=i*10.0;
    }
    printf("\n");
}

/* Question 4 */

int Ackermann1(int m, int n){ //récurso-itératif sur n
    if (m==0){
        return n+1;
    }else{
        int r=1;
        for (int i=1;i<=n+1;i++){
            r=Ackermann1(m-1,r);
        }
        return r;
    }
} //pour A(6,0), tourne sans donner de résultat sans s'arrêter

int Ackermann2(int m, int n){ //récursif pur
    if (m==0){
        return n+1;
    }else{
        if (n==0){
            return Ackermann2(m-1,1);
        }else{
            return Ackermann2(m-1,Ackermann2(m,n-1));
        }
    }
} //pour A(6,0) et A(5,0), tourne sans donner de résultat et s'arrête

void affiche_Ackermann(){ //Affichage des premiers termes avec le premier code
    printf("Premieres valeurs de A(m,0):\n");
    for (int i=0;i<=5;i++){
        printf("A(%d,0)=%d  ", i, Ackermann1(i,0));
    }
    printf("\n\n");
}

/* Question 5 */

// Méthode 1: Version itérative
float suite_xn1(int n){
    float x=1;               //x0=1
    for (int i=1;i<=n;i++){  // itération de x1 à xn
        x=x+2/x;
    }
    return x;
}

// Méthode 2: Verion récursive simple
float suite_xn2(int n){
    if (n==0){
        return 1;
    }else{
        float x=suite_xn2(n-1);
        return x+2/x;
    }
}

// Méthode 3: Récursive terminale avec sous-fonction
float sfonction3(int n, float r){
    if (n==0){
        return r;
    }else{
        return sfonction3(n-1, r+2/r);
    }
}

float suite_xn3(int n){
    return sfonction3(n,1);
}

// Méthode 4: Récursive terminale avec sous-procédure
void sprocedure4(int n, float* r){
    if (n==0) {} else {
        *r=*r+2/(*r);
        sprocedure4(n-1,r);
    }
}

float suite_xn4(int n){
    float r=1;
    sprocedure4(n, &r);
    return r;
}

void affichage_x100(){
    printf("Methode 1: x(100)=%f \n", suite_xn1(100));
    printf("Methode 2: x(100)=%f \n", suite_xn2(100)); //le résultat est très légèrement différente
    printf("Methode 3: x(100)=%f \n", suite_xn3(100));
    printf("Methode 4: x(100)=%f \n\n", suite_xn4(100));
}

int main(){
    /* Question 1 */
    printf("QUESTION 1 \ne = %f\n\n", somme_e());

    /* Question 2 */
    printf("QUESTION 2\nAffichage des 50 premiers termes:\n");
    Affiche_premiers_termes(); //On observe qu'à partir d'un certain nombres de chiffres, les chiffres sont à 0
    printf("\n");

    /* Question 3 */
    printf("QUESTION 3\nPremiers termes avec le CODE 10:\n");
    affiche_suite();     
    //-> La suite semble croitre bien qu'à partir d'un certain terme le résultat affiché soit 1.
    
    /* Question 4 */
    printf("QUESTION 4\n");
    affiche_Ackermann(); 
    //printf("A(6,0) = %d\n\n", Ackermann2(6,0)); //affichage du terme A(6,0)

    /* Question 5 */
    printf("QUESTION 5\nAffichage de X_100:\n");
    affichage_x100();
    
    return 0;
}
/* Montecarlo for card probabilities
Pablo Cruzat
*/

#include<stdio.h>
#include<stdlib.h>

typedef enum suit{ club, diamond, heart, spade} suit;
typedef struct card{suit s; int p;} card;


void fill_deck(void* emptyDeckPtr){
    card* deckPtr = emptyDeckPtr;
    int i, j;
    for(i = club; i <= spade; i++){
        for(j = 0; j < 13; j++, deckPtr++){
            deckPtr -> s  = i;
            deckPtr -> p = j;
        }
    }
}

void swap_card();

void shuffle(card deck[], int n){
    int i;
    for(i = 0; i < n - 1; i++){
        int chosen = i + (rand() % (n - i));
        swap_card(&deck[i], &deck[chosen]);
    }
}
void swap_card(card *a, card *b)
{
    card temp = *a;
    *a = *b;
    *b = temp;
}

void get_hand(card hand[], card deck[], int n){
    int i;
    for (i = 0; i < n; i++){
        hand[i] = deck[51 - i];
    }
}

void swap();
int partition();
void quick_sort();



void get_pips(void* pips, void *pickedHandPtr, int n){
    int* pipsPtr = pips;
    card* handPtr = pickedHandPtr;
    int i;
    
    for (i = 0; i < n; i ++, handPtr++, pipsPtr++){
        *pipsPtr = handPtr ->  p;
    }
}

void quick_sort(int arr[], int low, int high){
    if (low < high){
        int pivotIndex = partition(arr, low, high);
        quick_sort(arr, low, pivotIndex - 1);
        quick_sort(arr, pivotIndex + 1, high);
    }
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1, j;

    for(j = low; j < high; j++){
        if (arr[j] < pivot){
            i++;
            swap( &arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


int n_pairs(int pips[], int n){
    int i;
    int pairs = 0;
    if ( 
    pips[0] == pips[1] &&
    pips[1] != pips[2]
    ){
        pairs++;
    }
    for(i = 1; i < n - 2 ; i++){
        if ( 
        pips[i - 1] != pips[i] &&
        pips[i] == pips[i + 1] &&
        pips[i + 1] != pips[i + 2]){
            pairs++;
        }
    }

    if (
    pips[n - 3] != pips[n - 2] &&
    pips[n - 2] == pips[n - 1]){
        pairs++;
    }
    return pairs;
}
int n_trios(int pips[], int n){
    int i;
    int trios = 0;
    if ( 
    pips[0] == pips[2] &&
    pips[2] != pips[3]
    ){
        trios++;
    }
    for(i = 1; i < n - 3 ; i++){
        if ( 
        pips[i - 1] != pips[i] &&
        pips[i] == pips[i + 2] &&
        pips[i + 2] != pips[i + 3]){
            trios++;
        }
    }

    if (
    pips[n - 4] != pips[n - 3] &&
    pips[n - 3] == pips[n - 1]){
        trios++;
    }
    return trios;
}
int n_quartets(int pips[], int n){
    int i;
    int quartets = 0;

    for(i = 0; i < n - 3 ; i++){
        if (pips[i] == pips[i + 3]){
            quartets++;
        }  
    }
    
    return quartets;
}


int partition();
void swap();


void print_probs(noPair, onePair, twoPair, oneTrio, fullHouse, oneQuartet, times){
    printf("prob of no pairs: %lf\n", (double)  noPair / times);
    printf("prob of one pairs: %lf\n", (double)  onePair / times);
    printf("prob of two pairs: %lf\n", (double)  twoPair / times);
    printf("prob of 3 of a kind: %lf\n", (double) oneTrio / times);
    printf("prob of a full house: %lf\n", (double) fullHouse / times);
    printf("prob of 4 of a kind: %lf\n", (double)  oneQuartet / times);
}


int main(void)
{   

    int i, n = 7, times = 1000000, j;
    
    int pair, trio, quartet;

    int noPair = 0, onePair = 0,
    twoPair = 0, oneTrio = 0,
    fullHouse = 0, oneQuartet = 0;

    card deck[52];
    fill_deck(&deck);
    for ( i = 0; i < times; i++)
    {
        srand(i+1);
        shuffle(deck, 52);
        card hand[n];
        int pips[n];

        get_hand(hand, deck, n);
        get_pips(&pips, &hand, n);
        quick_sort(pips, 0, n - 1);
        
        pair = n_pairs(pips, n);
        trio = n_trios(pips, n);
        quartet = n_quartets(pips, n);

    if (quartet == 1)
    {
        oneQuartet++;
    }
    else if (pair == 1 && trio == 1)
    {
        fullHouse++;
    }

    else if (pair != 1 && trio == 1)
    {
        oneTrio++;
    }
    else if (pair >= 2 && trio == 0)
    {
        twoPair++;
    }
    else if (pair == 1 && trio == 0)
    {
        onePair++;
    }

    else if (pair == 0 && trio == 0)
    {
        noPair++;
    }

    }

    printf("number of nothing: %d\n number of pairs: %d\n number of two pairs: %d\n number of trios: %d\n number of full house: %d\n number of quartets: %d\n", 
    noPair, onePair, twoPair, oneTrio, fullHouse, oneQuartet);

    printf("\n\n");

    print_probs(noPair, onePair, twoPair, oneTrio, fullHouse, oneQuartet, times);

    return 0;
}


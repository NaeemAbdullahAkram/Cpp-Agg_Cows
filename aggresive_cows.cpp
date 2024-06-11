#include <iostream>
#include <cmath>

using namespace std;

struct Stall{
  int x; //position of stall
  bool c; //is cow or not
};

void q_sort( Stall tab[], int left, int right ) //for struct
{
    int i = left;
    int j = right;
    int y = tab[( left + right ) / 2 ].x;
    do{
        while( tab[i].x < y ) i++;
        while( tab[j].x > y ) j--;
        if( i <= j )  {
            swap( tab[i], tab[j] );
            i++;
            j--;
        }
    } while( i <= j );
    if( left < j ) q_sort( tab, left, j );
    if( right > i ) q_sort( tab, i, right );
}

int cow_m_dist(Stall tab[], int left, int right){
        int min = right-left;
        int pos=-1;
            for(int a=left; a<right; a++){
                if( (tab[a].c==true) && (pos==-1) ){
                    pos=tab[a].x;
                    continue;
                }
                if(tab[a].c==true){
                    if(min>tab[a].x-pos) min=tab[a].x-pos;
                    pos=tab[a].x;
                }
            }
        return min;
}

void cow_search(Stall tab[], int cows, int left, int right){
    int piv = round((float)(right+left)/2);
    if(cows>0){
        tab[piv].c=true;
        cows--;
    }
    if( (cows>0) && (cow_m_dist(tab, left, piv)>cow_m_dist(tab,piv,right)) ){
        cow_search(tab, cows, left, piv);
        cows--;
    }
    if(cows>0){
        cow_search(tab, cows, piv, right);
        cows--;
    }
}

int main(){
    int nam;
    int n; //number of stalls
    int c; //number of cows
    cin >> nam;
    for(int i=0; i<nam; i++){
          cin >> n >> c;
          Stall s[n];
          for(int i=0; i<n; i++){
              int pos; //position of stall
              cin >> pos;
              s[i] ={pos, false};
          }
          q_sort(s, 0, n-1);
          s[0].c=true;
          s[n-1].c=true;
          cow_search(s, c-2 ,0 ,n-1);
          cout << cow_m_dist(s, 0, n);

          cin.clear();
          cin.ignore();
    }
    return 0;
}
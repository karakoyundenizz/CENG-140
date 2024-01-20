

#include <stdio.h>
 
int main() {
    int parti_sayisi, vekil_sayisi, i, j;
    int oy[26], koltuk[26];
    char party[26];
    scanf("%d %d",&parti_sayisi,&vekil_sayisi);
    
    for(i = 0 ; i < parti_sayisi; i++){
        scanf("%d",&oy[i]);
    }
    
    for(i = 0 ; i < parti_sayisi; i++){
        koltuk[i] = 0;
    }
    
    for(i = 1 ; i <= vekil_sayisi; i++){
        int j, max_oy = 0, kazanan= -1;
        double max_kalan = 0;
        
        for(j = 0 ; j < parti_sayisi ; j++){
            double kalan = (double) oy[j] / (koltuk[j] + 1);
            if (kalan > max_kalan || (kalan == max_kalan && oy[j] > max_oy)) {
                max_kalan = kalan;
                max_oy = oy[j];
                kazanan = j;
            }
        }
        
        if(kazanan != -1){
            koltuk[kazanan]++;
        }
    }
    for(i = 0; i < parti_sayisi; i++){
        party[i] = 'A' + i;
    }
    for(i = 0 ; i < parti_sayisi; i++){
        for(j = 0; j < parti_sayisi - 1; j++){
            if(koltuk[j] < koltuk[j+1] || (koltuk[j] == koltuk[j+1] && party[j] > party[j+1]) ){
                int chn;
                char harf;
                harf = party[j];
                party[j] = party[j+1];
                party[j+1] = harf;
                chn = koltuk[j];
                koltuk[j] = koltuk[j+1];
                koltuk[j+1] = chn;
            }
        }
    }
    
    for(i = 0; i < parti_sayisi; i++){
        if(koltuk[i] > 0){
            printf("%c: %d\n", party[i], koltuk[i]);
        }
    }
                                      
    return 0;
}



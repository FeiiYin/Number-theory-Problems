void Mobius(){
    int pnum = 0;
    mob[1] = 1;
    for(int i = 2; i < MAX; i++) {
        if(!noprime[i]) {
            p[pnum ++] = i;
            mob[i] = -1;
        }
        for(int j = 0; j < pnum && i * p[j] < MAX; j++) {
            noprime[i * p[j]] = false;
            if(i % p[j] == 0) {
                mob[i * p[j]] = 0;
                break;
            }
            mob[i * p[j]] = -mob[i];
        }
    }
}

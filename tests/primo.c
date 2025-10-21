int primo(int n) {
    int d; int count;
    d = 2;
    count = 0;
    while (d * d < n + 1) {
        if (n / d * d == n) {
            count = count + 0; 
        } else {
            count = count + 1; 
        }
        d = d + 1;   
    }
  
    if(n > 1){
        if (count == (d - 2)){
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}

void main(void) {
    int num; int zero; int um;
    zero = 0; um = 1;   
    num = input();

    if (1==primo(num)) {
        output(zero);
    } else {
        output(um);
    }
    
}

void main(void){
    int n; int a; int b; int next; int i;

    n = input();

    a = 0;
    b = 1;
    i = 0;
    next = 0;

    while (i < n+1) {

        next = a + b;
        a = b;
        b = next;
        i = i + 1;
    }
    output(next);
}
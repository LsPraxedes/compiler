int fat( int n )
{
    int vfat;
    vfat = n;
    
    while ( n != 1 ) {
        vfat = vfat * (  n - 1 );
        n = n - 1;
    }
        return vfat;

}
void main ( void )
{
    int x;
    x = input();

    output ( fat(x) );

}
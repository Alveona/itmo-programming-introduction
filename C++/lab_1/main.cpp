#include <iostream>
#include "LN.h"

int main() {

    /*LN ln1("232335637289086537");
    LN ln2("23123123123123");
    LN ln3("101010");
    LN ln4("1111");*/
    LN ln1("25"); //60
    LN ln2("5");

    LN ln3(0);
    //ln3 = ln1 * ln2;
    //ln3.print();

    //ln3 = ln1.division(ln2);
    ln3 = ln1 / ln2;
    ln3.print();
    //LN ln4(98);
    //ln4.print();
    //LN ln5(63);
    //LN ln6(0);
    //ln6 = ln4 - ln5;
    //ln6.print();
    //ln5.print();
    //printf("%s", ln4 > ln5? "true":"false");
    //printf("ln3:");
    //ln3.print();
    /*LN ln1(22);
    LN ln2(4);
    LN ln3(0);
    ln3 = ln1.division(ln2);
    ln3.print();*/
    /*LN ln1(-10);
    LN ln2(7);
    LN ln3(0);
    ln1 *= ln2;
    ln1.print();*/
    return 0;
}
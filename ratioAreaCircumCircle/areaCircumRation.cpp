#include<iostream>

using namespace std;

int main(){
    int radius;
    double area, circum;
    cout<<"Enter radius of circle : ";
    cin>>radius;
    area = (22/7)*radius*radius;
    circum = 2*(22/7)*radius;
    cout<<"Radius of area and circumference of the circle is : "<< area/circum;
    return 0;
}
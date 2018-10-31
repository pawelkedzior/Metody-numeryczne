#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>

using namespace std;

int main (void)
{
    int i=0;
    int j=0;
    complex<float> x;
    complex<float> x1;
    float y;
    float y1;
    float aa[8][3];
    float ab[8][3];
    float ba[11][3];
    float bb[11][3];
    complex<float> ca[5][3];
    complex<float> cb[5][3];
    int n;
    aa[0][0]=60;//16;
    aa[1][0]=146;//-72;
    aa[2][0]=134;//-28;
    aa[3][0]=58;//558;
    aa[4][0]=12;//-990;
    aa[5][0]=1;//783;
    aa[6][0]=0;//-486;
    aa[7][0]=0;//243;
    for (i=1;i<3;i++)
    for (j=1;j<8;j++)
        aa[j-1][i]=static_cast<float>(j)*aa[j][i-1];
    aa[7][1]=0;/*
    for (i=0;i<2;i++)
    {
    for (j=0;j<8;j++)
    cout<<aa[j][i]<<endl;
    cout<<endl;
    }*/
    n=7;
    y=-3;   
    float z; 
    float zprim;
    float zbis;
    for (j=0;j<50000040;j++){
    for (i=0;i<8;i++)
        {
                 z=z+pow(y,i)*aa[i][0];
        }
    for (i=0;i<7;i++)
        {
                 zprim=zprim+pow(y,i)*aa[i][1];
        }
    for (i=0;i<6;i++)
        {
                 zbis=zbis+pow(y,i)*aa[i][2];
        }    
    if (zprim>=0)
       y1=y-static_cast<float>(n)*z/(zprim+sqrt(static_cast<float>(n-1)*(static_cast<float>(n-1)*zprim*zprim-static_cast<float>(n)*z*zbis)));
    else
        y1=y-(static_cast<float>(n)*z/(zprim-sqrt(static_cast<float>(n-1)*(static_cast<float>(n-1)*zprim*zprim-static_cast<float>(n)*z*zbis))));
    y=y1;
    }
    cout<<y1<<endl;
   // 
    cout<<y1<<endl;
    float wynik;
    for (i=0;i<8;i++)
        wynik=wynik+pow(y,i)*aa[i][0];
    cout<<wynik<<endl;
        
    
    
    system("pause");
    fstream plik;
    plik.open("Zad4.txt",ios::out);
    /*
    for (i=0;i<63;i++) //tworzenie macierzy A
        {
           for (j=0;j<63;j++)
               {
                if (j==i)
                   macierz[i][j]=4;
                else
                    if (i==j-1||i==j+1)
                       macierz[i][j]=1;
                    else
                        macierz[i][j]=0;
               }
        }*/
    plik.close();
    return 0;
}
